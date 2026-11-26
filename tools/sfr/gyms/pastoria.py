#!/usr/bin/env python3
"""Super Emerald: Pastoria City Gym (Crasher Wake) - a hydraulic plant with two water levels.

Run from the repo root: python3 tools/sfr/gyms/pastoria.py
Adapted from Diamond/Platinum (pret/pokeplatinum src/overlay008/gym_features.c, PastoriaGym_*):
coloured floor buttons raise or lower the water, and each level opens different ground.
On GBA there are two levels:
  HIGH (start): the orange pontoons float up to deck height and can be walked on; the low
                concrete paths are under water.
  LOW:          the water drains, the pontoons sink out of reach and the low paths dry out.
A yellow button (arrow down) drains the tanks, a blue button (arrow up) fills them. Level
gauges on the side walls and the drain outlets show the level. Every level-dependent tile has a
HIGH and a LOW metatile; the scripts swap them all with special SE_SwapMapMetatiles
(src/sinnoh_scene.c), graphics and collision together (water_levels.inc is generated).
The level lives in VAR_TEMP_1 (0 HIGH, 1 LOW) and resets to HIGH when the player leaves.
check() walks every reachable (position, level) pair: the door and WAKE must stay reachable.
"""
import json, os, struct, sys
from collections import deque
sys.path.insert(0, os.path.dirname(__file__))
from gymkit import Canvas, Tileset, build_map, write_metatile_defs

TS = 'data/tilesets/secondary/pastoria_city_gym_sinnoh'
MAP = 'data/maps/PastoriaCity_Gym_sinnoh/map.json'
LAYOUT = 'LAYOUT_PASTORIA_CITY_GYM_SINNOH'
GEN_INC = 'data/maps/PastoriaCity_Gym_sinnoh/water_levels.inc'

P = 11
TANK = [(0, 0, 0), (16, 30, 36), (30, 74, 80), (48, 112, 116), (92, 160, 160), (170, 214, 206),
        (84, 84, 80), (128, 126, 118), (170, 168, 158), (212, 210, 200), (52, 60, 72), (100, 110, 126),
        (232, 196, 64), (224, 110, 40), (150, 64, 24), (240, 240, 236)]
K, WD, WM, WL, WH, CD, CM, CL, CH, SD, SM, YE, OR, ORD, WT = range(1, 16)
DECK = 0x205

# '|' side wall, 'D' deck, '~' water, 'd' water with a drain outlet in the wall, 'F' pontoon
# (HIGH), 'L' low path (LOW), 'g' level gauge in a side wall, Z/Y/z statues, m exit mat.
# Buttons (BUTTONS) sit on deck tiles.
PLAN = [
    None, None, None,
    "|~~~~DDDDDDD~~~~|",  # 3   WAKE (8,3) on his deck
    "g~~~~DDDDDDD~~~~g",  # 4
    "|~~~~~~~~~~L~~~~|",  # 5   low path up to WAKE's deck (x11)
    "|d~~~~~~~~~L~~~~|",  # 6
    "|~~~~~~~~~~L~~~~|",  # 7
    "|DDDD~~~~DDDDDDD|",  # 8   island 4 x1-4 (side), island 3 x9-15
    "|DDDDLLLLDDDDDDD|",  # 9   low path between islands 4 and 3
    "|DDDD~~~~DDDDDDD|",  # 10
    "|~~~~~~~~~~~F~~d|",  # 11  pontoons up to island 3 (x12)
    "g~~~~~~~~~~~F~~~g",  # 12
    "|~~~~~~~~~~~F~~~|",  # 13
    "|~DDDDD~~~DDDDDD|",  # 14  island 1 x2-6, island 2 x10-15
    "|~DDDDDLLLDDDDDD|",  # 15  low path between islands 1 and 2
    "|~DDDDD~~~DDDDDD|",  # 16
    "|~~~F~~~~~~~L~~~|",  # 17  pontoons to island 1 (x4), low path to island 2 (x12)
    "g~~~F~~~~~~~L~~~g",  # 18
    "|d~~F~~~~~~~L~~~|",  # 19
    "|DDDDDDDDDDDDDDD|",  # 20  entrance hall
    "|DDDDDZDDDYDDDDD|",  # 21  statues (6,21), (10,21)
    "|DDDDDzDDDzDDDDD|",  # 22
    "|DDDDDDmmmDDDDDD|",  # 23  exit mat
    None,                 # 24  bottom wall with the exit
]
BUTTONS = {(2, 15): 'y', (15, 14): 'y', (15, 16): 'u', (15, 8): 'y', (15, 10): 'u', (11, 3): 'y'}
W_ = 17


def grid():
    g = [list(r) if r else None for r in PLAN]
    for (x, y), k in BUTTONS.items():
        assert g[y][x] == 'D', (x, y)
        g[y][x] = k
    return g


def walk(ch, level):
    if ch in 'DyuZYm':
        return True
    if ch == 'F':
        return level == 0
    if ch == 'L':
        return level == 1
    return False


def check():
    g = grid()
    H = len(g)
    start = ((8, 23), 0)

    def nxt(node):
        (x, y), lv = node
        for dx, dy in ((0, 1), (0, -1), (1, 0), (-1, 0)):
            nx, ny = x + dx, y + dy
            if not (0 <= ny < H and g[ny] and 0 <= nx < W_) or not walk(g[ny][nx], lv):
                continue
            l2 = lv
            if (nx, ny) in BUTTONS:
                l2 = 1 if BUTTONS[(nx, ny)] == 'y' else 0
            yield ((nx, ny), l2)
    seen = {start}; q = deque([start])
    while q:
        n = q.popleft()
        for m in nxt(n):
            if m not in seen:
                seen.add(m); q.append(m)
    assert any(p == (8, 4) for p, _ in seen), 'WAKE unreachable'
    for n in seen:
        s2 = {n}; q2 = deque([n]); ok = False
        while q2 and not ok:
            for m in nxt(q2.popleft()):
                if m[0] == (8, 23):
                    ok = True; break
                if m not in s2:
                    s2.add(m); q2.append(m)
        assert ok, f'trapped at {n}'
    return len(seen)


# ---------------------------------------------------------------- art
SIDES = {'n': lambda i, k: (i, k), 's': lambda i, k: (i, 15 - k), 'w': lambda i, k: (k, i), 'e': lambda i, k: (15 - k, i)}


def water(level, edges='', drain=''):
    """Tank water. HIGH: light, rippled, up to the rim. LOW: darker, with the wet concrete wall
    exposed along the rims, level marks on it and the outlets pouring."""
    c = Canvas(WM if level == 0 else WD)
    for x, y in ((2, 3), (3, 3), (10, 6), (11, 6), (12, 6), (5, 11), (6, 11), (13, 13)):
        c.px(x, y, WL if level == 0 else WM)
    if level == 0:
        c.px(11, 5, WH); c.px(5, 10, WH)
    band = 3 if level == 0 else 7
    for e in edges:
        f = SIDES[e]
        for i in range(16):
            for k in range(band):
                c.px(*f(i, k), CH if k == 0 else CL if k < 3 else CM if k < band - 1 else K)
            if level == 1 and i % 4 == 1:
                c.px(*f(i, 4), YE)                               # level marks on the tank wall
    if drain:
        f = SIDES[drain]
        for i in range(5, 11):
            for k in range(4):
                c.px(*f(i, k), K if 6 <= i <= 9 else SD)
        if level == 1:                                           # it pours when the tank drains
            for k in range(4, 16):
                for i in (7, 8):
                    c.px(*f(i, k), WT if (k + i) % 3 else WH)
    return c


def pontoon(level):
    c = water(level)
    if level == 0:     # floating at deck height: planks on orange floats
        c.rect(1, 1, 14, 14, OR); c.rect(2, 2, 13, 13, CM)
        for y in range(2, 14, 3):
            c.hline(2, 13, y, CL)
        c.hline(1, 14, 1, YE); c.hline(1, 14, 14, ORD)
        for x, y in ((2, 2), (13, 2), (2, 13), (13, 13)):
            c.px(x, y, K)
    else:              # sunk to the bottom: a dim shape under dark water
        c.rect(3, 3, 12, 12, ORD); c.rect(4, 4, 11, 11, WM)
        for y in range(5, 11, 3):
            c.hline(4, 11, y, WD)
    return c


def low_path(level):
    if level == 1:     # dry concrete ridge with wet edges and a drain grid
        c = Canvas(CL)
        c.hline(0, 15, 0, CH); c.hline(0, 15, 15, CD)
        for x in (0, 15):
            c.vline(x, 0, 15, WL)
        for x, y in ((3, 3), (11, 10), (4, 12)):
            c.px(x, y, CM); c.px(x + 1, y, WL)
        c.rect(6, 6, 9, 9, CD)
        for i in (6, 8):
            c.vline(i, 6, 9, K)
    else:              # under water: the ridge shows through, blurred
        c = water(0)
        c.rect(1, 0, 14, 15, WL)
        for y in range(0, 16, 2):
            c.hline(2, 13, y, WM)
        c.rect(6, 6, 9, 9, WM)
    return c


def concrete(edges=''):
    """Deck slab: poured concrete with joints; a yellow safety line along any edge over water."""
    c = Canvas(CL)
    c.hline(0, 15, 7, CM); c.hline(0, 15, 15, CM); c.vline(7, 0, 6, CM); c.vline(15, 8, 14, CM)
    for x, y in ((3, 3), (11, 4), (5, 11), (12, 12)):
        c.px(x, y, CH)
    for e in edges:
        f = SIDES[e]
        for i in range(16):
            c.px(*f(i, 0), CD); c.px(*f(i, 1), YE); c.px(*f(i, 2), YE if i % 4 < 2 else K)
    return c


def button(kind):
    """Floor button on the deck: yellow drains (arrow down), blue fills (arrow up)."""
    c = concrete()
    col, dk = (YE, ORD) if kind == 'y' else (WL, WD)
    c.rect(2, 2, 13, 13, K); c.rect(3, 3, 12, 12, dk); c.rect(4, 3, 11, 11, col)
    arrow = [(7, 4), (8, 4), (7, 5), (8, 5), (7, 6), (8, 6), (5, 7), (6, 7), (7, 7), (8, 7), (9, 7), (10, 7),
             (6, 8), (7, 8), (8, 8), (9, 8), (7, 9), (8, 9)]
    for x, y in arrow:
        c.px(x, y + 1 if kind == 'y' else 14 - y, K)
    return c


def gauge(level):
    """Water level gauge set into the side wall."""
    c = Canvas(CM)
    c.vline(0, 0, 15, CH); c.vline(15, 0, 15, CD)
    c.rect(4, 0, 11, 15, K); c.rect(5, 1, 10, 14, CH)
    for y in range(2, 15, 3):
        c.hline(5, 7, y, K)
    top = 2 if level == 0 else 10
    c.rect(8, top, 10, 14, WL if level == 0 else WM)
    c.hline(5, 10, top, OR)
    return c


# ---------------------------------------------------------------- build
def main():
    print('reachable states checked:', check())
    g = grid()
    H = len(g)
    ts = Tileset(TS)
    print('free tile slots:', ts.free_unused({DECK, 0x22e, 0x22f, 0x24a, 0x24b, 0x24c, 0x201, 0x202, 0x203,
                                               0x204, 0x245, 0x246, 0x247, 0x214, 0x215, 0x216, 0x217,
                                               0x226, 0x227, 0x248, 0x23f, 0x20d} | set(range(0x206, 0x210))))

    def solid(x, y):
        if not (0 <= y < H) or g[y] is None or not (0 <= x < W_):
            return True
        return g[y][x] in '|gDyuZYzm'
    pairs = []                      # (name_hi, name_lo, collision_hi, collision_lo)
    cell_kind, variants = {}, set()
    for y in range(H):
        if not g[y]:
            continue
        for x in range(W_):
            if g[y][x] in '~d':
                edges = ''.join(e for e, (dx, dy) in (('n', (0, -1)), ('s', (0, 1)), ('w', (-1, 0)), ('e', (1, 0)))
                                if solid(x + dx, y + dy))
                drain = ('w' if x == 1 else 'e') if g[y][x] == 'd' else ''
                k = (edges, drain)
                variants.add(k); cell_kind[(x, y)] = k
    wname = lambda k: 'water_%s%s' % (k[0] or '0', '_d' + k[1] if k[1] else '')
    for k in sorted(variants):
        ts.add(wname(k) + '_hi', [(water(0, *k), P), None, None])
        ts.add(wname(k) + '_lo', [(water(1, *k), P), None, None])
        pairs.append((wname(k) + '_hi', wname(k) + '_lo', 1, 1))
    for nm, fn, c_hi, c_lo in (('pontoon', pontoon, 0, 1), ('lowpath', low_path, 1, 0), ('gauge', gauge, 1, 1)):
        ts.add(nm + '_hi', [(fn(0), P), None, None]); ts.add(nm + '_lo', [(fn(1), P), None, None])
        pairs.append((nm + '_hi', nm + '_lo', c_hi, c_lo))
    ts.add('button_y', [(button('y'), P), None, None])
    ts.add('button_u', [(button('u'), P), None, None])
    deck_kinds = {}
    for y in range(H):
        if not g[y]:
            continue
        for x in range(W_):
            if g[y][x] in 'DZY':
                e = ''.join(k for k, (dx, dy) in (('n', (0, -1)), ('s', (0, 1)), ('w', (-1, 0)), ('e', (1, 0)))
                            if 0 <= y + dy < H and g[y + dy] and 0 <= x + dx < W_ and g[y + dy][x + dx] in '~dFL')
                deck_kinds[(x, y)] = e
    for e in sorted(set(deck_kinds.values())):
        ts.add('deck_' + (e or '0'), [(concrete(e), P), None, None])
    ts.replace(0x24a, [(concrete(), P), None, ('mt', 0x24a, 2)])       # statues on concrete
    ts.replace(0x24b, [(concrete(), P), None, ('mt', 0x24b, 2)])
    ts.replace(0x24c, [(concrete(), P), ('mt', 0x24c, 1), None])
    ts.save({P: TANK})
    names = ts.names
    n = lambda k: names[k]
    write_metatile_defs('data/maps/PastoriaCity_Gym_sinnoh', 'PastoriaGym', names)

    lines = ['@ Generated by tools/sfr/gyms/pastoria.py; do not edit.']
    for lv, label in ((1, 'Low'), (0, 'High')):
        lines.append(f'PastoriaCity_Gym_EventScript_SetWater{label}::')
        for hi, lo, c_hi, c_lo in pairs:
            src, dst, col = (hi, lo, c_lo) if lv == 1 else (lo, hi, c_hi)
            lines += [f'\tsetvar VAR_0x8004, METATILE_PastoriaGym_{src}', f'\tsetvar VAR_0x8005, METATILE_PastoriaGym_{dst}',
                      f'\tsetvar VAR_0x8006, {col}', '\tspecial SE_SwapMapMetatiles']
        lines.append('\treturn\n')
    open(GEN_INC, 'w').write('\n'.join(lines) + '\n')

    state = json.load(open(TS + '/se_gymkit.json'))
    rows = state['orig_rows']
    legend = {'|': (0x22e, 1, 0), 'D': (DECK, 0, 3), 'Z': (0x24a, 0, 3), 'Y': (0x24b, 0, 3), 'z': (0x24c, 1, 3),
              'F': (n('pontoon_hi'), 0, 3), 'L': (n('lowpath_hi'), 1, 3), 'g': (n('gauge_hi'), 1, 0),
              'y': (n('button_y'), 0, 3), 'u': (n('button_u'), 0, 3)}
    keymap = {}

    def raw(v):
        if v not in keymap:
            keymap[v] = chr(0x100 + len(keymap))
            legend[keymap[v]] = (v & 0x3FF, (v >> 10) & 3, v >> 12)
        return keymap[v]
    out = []
    for y, r in enumerate(g):
        if r is None:
            src = rows[str(y)] if y < 3 else rows['bottom']
            out.append(''.join(raw(v) for v in src))
            continue
        line = ''
        for x, ch in enumerate(r):
            if ch == 'm':
                line += raw(rows['mat'][x])
            elif ch == '|' and x == 16:
                line += raw(0x062f)
            elif ch in '~d':
                line += raw((n(wname(cell_kind[(x, y)]) + '_hi') & 0x3FF) | (1 << 10) | (3 << 12))
            elif ch == 'D':
                line += raw((n('deck_' + (deck_kinds[(x, y)] or '0')) & 0x3FF) | (3 << 12))
            else:
                line += ch
        out.append(line)
    build_map(LAYOUT, out, legend, border=0x201)

    d = json.load(open(MAP))
    d['warp_events'] = [{'x': x, 'y': 23, 'elevation': 0, 'dest_map': 'MAP_PASTORIA_CITY_SINNOH', 'dest_warp_id': '1'}
                        for x in (7, 8, 9)]
    pos = {
        'PastoriaCity_Gym_EventScript_Jacky': (6, 16, 'MOVEMENT_TYPE_FACE_LEFT', '2'),      # island 1: sees the pontoon landing
        'PastoriaCity_Gym_EventScript_Caitlyn': (13, 14, 'MOVEMENT_TYPE_FACE_DOWN', '2'),   # island 2: guards the buttons
        'PastoriaCity_Gym_EventScript_Samson': (10, 9, 'MOVEMENT_TYPE_FACE_RIGHT', '5'),    # island 3: guards the buttons
        'PastoriaCity_Gym_EventScript_Damian': (2, 9, 'MOVEMENT_TYPE_FACE_RIGHT', '2'),     # island 4 (side)
        'PastoriaCity_Gym_EventScript_Erick': (6, 4, 'MOVEMENT_TYPE_FACE_RIGHT', '2'),      # WAKE's deck
        'PastoriaCity_Gym_EventScript_Walter': (10, 3, 'MOVEMENT_TYPE_FACE_DOWN', '1'),
        'SE_EventScript_SinnohLeader_Wake': (8, 3, 'MOVEMENT_TYPE_FACE_DOWN', '0'),
        'PastoriaCity_Gym_EventScript_PtGymGuide': (11, 22, 'MOVEMENT_TYPE_FACE_LEFT', '0'),
    }
    for o in d['object_events']:
        x, y, mv, s = pos[o['script']]
        o['x'], o['y'], o['movement_type'], o['elevation'] = x, y, mv, 3
        if o['trainer_type'] != 'TRAINER_TYPE_NONE':
            o['trainer_sight_or_berry_tree_id'] = s
    any_ = 'BG_EVENT_PLAYER_FACING_ANY'
    d['bg_events'] = [
        {'type': 'sign', 'x': 6, 'y': 22, 'elevation': 0, 'player_facing_dir': any_, 'script': 'PastoriaCity_Gym_EventScript_PtGymStatue'},
        {'type': 'sign', 'x': 10, 'y': 22, 'elevation': 0, 'player_facing_dir': any_, 'script': 'PastoriaCity_Gym_EventScript_PtGymStatue'},
    ]
    d['coord_events'] = [
        {'type': 'trigger', 'x': x, 'y': y, 'elevation': 3, 'var': 'VAR_TEMP_0', 'var_value': '0',
         'script': 'PastoriaCity_Gym_EventScript_' + ('Drain' if k == 'y' else 'Fill')}
        for (x, y), k in sorted(BUTTONS.items())]
    open(MAP, 'w').write(json.dumps(d, indent=2, ensure_ascii=False) + '\n')


if __name__ == '__main__':
    main()
