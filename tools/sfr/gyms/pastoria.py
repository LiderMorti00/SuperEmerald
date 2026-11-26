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
    for e in edges:
        f = SIDES[e]
        if e == 'n':          # the concrete wall or deck above shows its face down to the water
            h = 4 if level == 0 else 10
            for i in range(16):
                for k in range(h):
                    v = CM if k < h - 2 else CD
                    if i % 8 == 7 and k < h - 2: v = CD                       # formwork joints
                    if level == 1 and k == 4 and i % 4 < 2: v = YE           # level marks
                    if level == 1 and 5 <= k < h - 2: v = CD if (i + k) % 5 == 0 else SD  # wet, stained
                    c.px(i, k, v)
                c.px(i, h - 1, K); c.px(i, h, WH if i % 3 else WL)
        else:                 # rim of the tank seen from above
            band = 2 if level == 0 else 4
            for i in range(16):
                for k in range(band):
                    c.px(*f(i, k), CH if k == 0 else CL if k < band - 1 else CD)
                if level == 1:
                    c.px(*f(i, band), SD)
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
    """Floating walkway section. HIGH: a plank deck on two orange floats, its shadow on the water.
    LOW: grounded on the tank floor, deep under the drained water, out of reach."""
    c = water(level)
    if level == 0:
        for y in range(16):
            for x in range(16):
                if x <= 3 or x >= 12:                       # float tubes
                    c.px(x, y, ORD if x in (0, 15) else OR if x in (1, 2, 13, 14) else YE)
                    if y % 8 in (3, 4) and x in (1, 2, 13, 14): c.px(x, y, K)   # straps
        for y in range(16):                                  # deck planks between the floats
            for x in range(4, 12):
                c.px(x, y, CL if y % 4 else CD)
            c.px(4, y, CD); c.px(11, y, CM)
        c.hline(0, 15, 15, WD)                               # shadow on the water
    else:
        c.rect(2, 2, 13, 13, WD)
        c.rect(3, 3, 5, 12, ORD); c.rect(10, 3, 12, 12, ORD)
        for y in range(3, 13, 3):
            c.hline(6, 9, y, WM)
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
    c.hline(0, 15, 15, CM); c.vline(15, 0, 15, CM); c.hline(0, 14, 0, CH); c.vline(0, 0, 14, CH)
    for x, y in ((3, 3), (11, 4), (5, 11), (12, 12), (8, 7), (2, 9)):
        c.px(x, y, CM)
    for x, y in ((4, 3), (6, 12), (13, 6)):
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


def plant_wall(cx, cy):
    """Top wall of the hydraulic plant, 17x3 tiles: concrete cap, a big pipe with flanges and
    a valve wheel, and grated outlets at the water line."""
    c = Canvas(0)
    for y in range(16):
        for x in range(16):
            X, Y = cx * 16 + x, cy * 16 + y
            if Y < 8:
                v = SD if Y in (0, 7) else SM if Y < 3 else CD
            else:
                v = CM if (X % 32) else CD
                if Y == 8: v = CH
                if Y % 16 == 0 and Y > 8: v = CD
            if 14 <= Y <= 24:                                   # main pipe
                v = SM if Y in (14, 24) else SD if Y > 21 else (CH if Y == 16 else SM)
                if X % 48 in (0, 1, 2) and cx not in (0, 16): v = SD if Y in (14, 24) else CL   # flanges
            if cy == 2:
                if Y >= 44: v = K if Y == 47 else CD
                if X % 64 in range(24, 40) and 34 <= Y <= 43:   # grated outlets above the water
                    v = K if (X % 2 == 0 or Y in (34, 43)) else SD
            c.px(x, y, v)
    if cy == 1 and cx == 8:                                     # valve wheel in the middle
        for y in range(16):
            for x in range(16):
                r = ((x - 7.5) ** 2 + (y - 3.5) ** 2) ** 0.5
                if 5.0 <= r <= 6.5 or (r < 5 and (abs(x - 7.5) < 1 or abs(y - 3.5) < 1)):
                    c.px(x, y, OR if r > 1.5 else K)
    return c


def side_wall(east):
    """Retaining wall down the sides: concrete top with its inner face lit."""
    c = Canvas(CM)
    for y in range(16):
        c.px(15 if east else 0, y, K)
        c.px(0 if east else 15, y, CH)
        c.px(1 if east else 14, y, CL)
    for x in range(16):
        c.px(x, 7, CD); c.px(x, 15, CD)
    for y in (3, 11):
        c.px(7, y, SM); c.px(8, y, SM)
    return c


def base_wall():
    c = Canvas(CD)
    c.hline(0, 15, 0, CL); c.hline(0, 15, 1, CM); c.hline(0, 15, 15, K)
    for x in range(0, 16, 8):
        c.vline(x, 2, 14, SD)
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
    for cy in range(3):
        for cx in range(17):
            ts.add('top_%d_%d' % (cx, cy), [(plant_wall(cx, cy), P), None, None])
    ts.add('side_w', [(side_wall(False), P), None, None]); ts.add('side_e', [(side_wall(True), P), None, None])
    ts.add('base', [(base_wall(), P), None, None])
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
            if y < 3:
                out.append(''.join(raw((n('top_%d_%d' % (x, y)) & 0x3FF) | (1 << 10)) for x in range(W_)))
            else:
                out.append(''.join(raw((n('base') & 0x3FF) | (1 << 10)) for x in range(W_)))
            continue
        line = ''
        for x, ch in enumerate(r):
            if ch == 'm':
                line += raw(rows['mat'][x])
            elif ch == '|':
                line += raw((n('side_e' if x == 16 else 'side_w') & 0x3FF) | (1 << 10))
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


# ------------------------------------------------------------------ FRLG dressing (Cerulean Gym)
# Base: FRLG's Cerulean Gym (Misty). Its pool (water with rim, corners and the shadow a
# walkway casts), its raised cream walkways with posts, the tiled floor around the pool and
# the windowed north wall become the tanks and decks. LOW water reuses the very same pool
# pieces re-toned as a drained tank floor (drained() below), so every edge keeps its shape and
# the tank's rim still reads as a front face above the lower water line. Pontoons, submerged
# walkways, buttons and gauges are new pixels laid over those pieces.
CER = 'CeruleanCity_Gym_Frlg'
CER_WATER = {m for m in range(0x288, 0x294)} | {0x2A8, 0x2B0, 0x2B7, 0x2BB, 0x2BC, 0x2BD, 0x2BE, 0x2BF,
                                              0x2C3, 0x2C6, 0x2C7, 0x2D3, 0x298, 0x299, 0x29A, 0x29B}
CER_DECK = {0x2A1, 0x2A2, 0x2A9, 0x2AA, 0x2B1, 0x2B2, 0x29C, 0x2C4, 0x2C5}


def drained(c):
    r, g, b = c
    if b > r + 24:          # water blues -> wet, mossy tank floor
        L = 0.3 * r + 0.5 * g + 0.2 * b
        q = lambda v: max(0, min(248, int(v) // 8 * 8))
        return (q(L * 0.55 + 18), q(L * 0.62 + 20), q(L * 0.58 + 14))
    return c


def pontoon_ov(level):
    c = Canvas(0)
    if level == 0:
        c.rect(0, 1, 15, 13, ORD); c.rect(1, 1, 14, 12, OR)
        for y in range(2, 12, 3):
            c.hline(1, 14, y, YE)
        c.rect(5, 1, 10, 12, CL); c.vline(5, 1, 12, CD); c.vline(10, 1, 12, CM)
        c.hline(0, 15, 13, K); c.hline(1, 14, 14, WD); c.hline(2, 13, 15, WD)
    else:
        c.rect(2, 4, 13, 14, K); c.rect(3, 4, 12, 13, ORD)
        c.rect(6, 4, 9, 13, CD)
    return c


def lowpath_ov(level, ns):
    """ns: the strip runs north-south (else east-west)."""
    c = Canvas(0)
    if level == 0:                  # under water: only its outline shows through
        for i in range(0, 16, 2):
            if ns:
                c.px(2, i, WL); c.px(13, i, WL)
            else:
                c.px(i, 2, WL); c.px(i, 13, WL)
        c.rect(6, 6, 9, 9, WL)
    else:                           # dry concrete ridge
        if ns:
            c.rect(2, 0, 13, 15, CL); c.vline(2, 0, 15, CH); c.vline(13, 0, 15, CD); c.vline(14, 0, 15, K)
        else:
            c.rect(0, 2, 15, 13, CL); c.hline(0, 15, 2, CH); c.hline(0, 15, 13, CD); c.hline(0, 15, 14, K)
        c.rect(6, 6, 9, 9, CD); c.vline(7, 6, 9, K)
    return c


def button_ov(kind):
    c = Canvas(0)
    col, dk = (YE, ORD) if kind == 'y' else (WL, WD)
    c.rect(2, 3, 13, 14, K); c.rect(3, 3, 12, 13, dk); c.rect(3, 2, 12, 11, col); c.hline(3, 12, 2, WT)
    arrow = [(7, 4), (8, 4), (7, 5), (8, 5), (5, 6), (6, 6), (7, 6), (8, 6), (9, 6), (10, 6),
             (6, 7), (7, 7), (8, 7), (9, 7), (7, 8), (8, 8)]
    for x, y in arrow:
        c.px(x, y if kind == 'y' else 12 - y, K)
    return c


def gauge_ov(level):
    c = Canvas(0)
    c.rect(4, 1, 11, 14, K); c.rect(5, 2, 10, 13, CH)
    for y in range(3, 13, 3):
        c.hline(5, 6, y, K)
    top = 3 if level == 0 else 10
    c.rect(7, top, 10, 13, WL if level == 0 else WM); c.hline(5, 10, top, OR)
    return c


def main_frlg():
    import gbaref as G
    print('reachable states checked:', check())
    g = grid()
    H = len(g)
    ts = Tileset(TS)
    ts.free_unused(set())
    src = G.source_for(CER)
    imp = G.Importer(ts, G.free_slots({P}))

    def cl(m, c, b):
        if m in CER_WATER: return 'S'
        if m in CER_DECK: return 'K'
        if 0x2A3 <= m <= 0x2B5 or m in (0x2B9, 0x2BA, 0x2C1, 0x2C8, 0x2C9, 0x2CA, 0x2D0, 0x2D1, 0x2D2): return 'X'
        return 'W' if c else 'F'
    table = G.learn(src, [CER], cl, edge='F')
    # classes: walls count as the pool rim (floor) for the water/deck pieces around them
    cls = []
    for y in range(H):
        row = []
        for x in range(W_):
            ch = g[y][x] if g[y] else '#'
            if y >= 20 and ch in 'DZYzm':
                row.append('F')
            elif ch in 'DyuZYz':
                row.append('F')          # platforms: Cerulean's tiled floor; the pool rim is on the water pieces
            elif ch in '~dFL':
                row.append('S')
            else:
                row.append('F')
        cls.append(row)
    picks = {}
    for y in range(H):
        for x in range(W_):
            c = cls[y][x]
            key = G.neigh(cls, x, y)
            if c == 'S':
                mid, d = G.pick(table, c, key)
                if c == 'S' and d > 2: mid = 0x291
                if mid == 0x2C6: mid = 0x299            # pool ladder rails: plain rim (the landings stay open)
                if c == 'K' and d > 2: mid = 0x2B2
                picks[(x, y)] = mid
    floor_l = G.base(imp.layers(src, 0x281))
    rows = [[None] * W_ for _ in range(H)]
    pairs = []

    def pair(name, mid, ov_hi, ov_lo, c_hi, c_lo):
        """hi/lo metatiles of a level-dependent cell; returns the HIGH one."""
        hn, ln = name + '_hi', name + '_lo'
        if hn not in ts.names:
            hb = imp.flat(src, mid)
            imp.tint = drained
            lb = imp.flat(src, mid)
            imp.tint = None
            ts.add(hn, [hb, (ov_hi, P) if ov_hi else None, None], 0)
            ts.add(ln, [lb, (ov_lo, P) if ov_lo else None, None], 0)
            pairs.append((hn, ln, c_hi, c_lo))
        return ts.names[hn]
    for y in range(H):
        for x in range(W_):
            ch = g[y][x] if g[y] else None
            if y in (0, 1, 2):          # Cerulean's north wall: rim, window band, base
                k = 0 if x == 0 else 2 if x == W_ - 1 else 1
                mid = [[0x2A6, 0x286, 0x2A7], [0x2AE, 0x28E, 0x2AF], [0x2AE, 0x296, 0x2AF]][y][k]
                if y == 0 and x == 1: mid = 0x285
                if y == 0 and x == W_ - 2: mid = 0x287
                if y == 0 and x == W_ // 2: mid = 0x294
                if y == 1 and x in (5, 7, 9, 11): mid = 0x2CB
                if y == 1 and x == 1: mid = 0x28D
                if y == 1 and x == W_ - 2: mid = 0x28F
                if y == 2 and x == 1: mid = 0x295
                if y == 2 and x == W_ - 2: mid = 0x297
                rows[y][x] = (imp.add('top_%x' % mid, src, mid, 0), 1, 0)
            elif ch is None:            # bottom: black, FRLG mat in the middle
                if x in (7, 8, 9):
                    rows[y][x] = (imp.add('mat%d' % (x - 7), src, 0x174 + x - 7, 0x65), 0, 3)
                else:
                    rows[y][x] = (0x000, 1, 0)
            elif ch == '|':
                rows[y][x] = (imp.add('side_%d' % (x > 8), src, 0x2AF if x > 8 else 0x2AE, 0), 1, 0)
            elif ch == 'g':
                side = imp.layers(src, 0x2AF if x > 8 else 0x2AE)
                ts.names.setdefault('dummy', 0)
                nm = 'gauge%d' % (x > 8)
                if nm + '_hi' not in ts.names:
                    ts.add(nm + '_hi', [G.base(side), (gauge_ov(0), P), None], 0)
                    ts.add(nm + '_lo', [G.base(side), (gauge_ov(1), P), None], 0)
                    pairs.append((nm + '_hi', nm + '_lo', 1, 1))
                rows[y][x] = (ts.names[nm + '_hi'], 1, 0)
            elif ch in '~d':
                mid = picks[(x, y)]
                rows[y][x] = (pair('water_%x' % mid, mid, None, None, 1, 1), 1, 3)
            elif ch == 'F':
                mid = picks[(x, y)]
                rows[y][x] = (pair('pontoon_%x' % mid, mid, pontoon_ov(0), pontoon_ov(1), 0, 1), 0, 3)
            elif ch == 'L':
                mid = picks[(x, y)]
                ns = g[y - 1][x] in 'L' or g[y + 1][x] in 'L' if g[y + 1] else False
                rows[y][x] = (pair('lowpath%d_%x' % (ns, mid), mid, lowpath_ov(0, ns), lowpath_ov(1, ns), 1, 0), 1, 3)
            elif ch in 'yu':
                mid = 0x281
                nm = 'button_%s_%x' % (ch, mid)
                if nm not in ts.names:
                    ts.add(nm, [imp.flat(src, mid), (button_ov(ch), P), None], 0)
                rows[y][x] = (ts.names[nm], 0, 3)
            elif ch == 'Z' or ch == 'Y':
                ts.add('statue_top', [floor_l, None, ('raw', [0x0001, 0x0002, 0x0011, 0x0012])], 0) if 'statue_top' not in ts.names else None
                rows[y][x] = (ts.names['statue_top'], 0, 3)
            elif ch == 'z':
                ts.add('statue_base', [floor_l, ('raw', [0x0021, 0x0022, 0x0031, 0x0032]), None], 0) if 'statue_base' not in ts.names else None
                rows[y][x] = (ts.names['statue_base'], 1, 3)
            elif cls[y][x] == 'F':
                mid = 0x281 if y < H - 2 or True else 0x281
                rows[y][x] = (imp.add('floor', src, 0x281, 0), 0, 3)
            else:                      # platform
                rows[y][x] = (imp.add('floor', src, 0x281, 0), 0, 3)
    ts.names.pop('dummy', None)
    print('palette slots:', sorted(imp.colors), '+', P, '| level pairs:', len(pairs))
    pals = imp.palettes(); pals[P] = TANK
    ts.save(pals)
    write_metatile_defs('data/maps/PastoriaCity_Gym_sinnoh', 'PastoriaGym', ts.names)
    lines = ['@ Generated by tools/sfr/gyms/pastoria.py; do not edit.']
    for lv, label in ((1, 'Low'), (0, 'High')):
        lines.append(f'PastoriaCity_Gym_EventScript_SetWater{label}::')
        for hi, lo, c_hi, c_lo in pairs:
            a, b, col = (hi, lo, c_lo) if lv == 1 else (lo, hi, c_hi)
            lines += [f'\tsetvar VAR_0x8004, METATILE_PastoriaGym_{a}', f'\tsetvar VAR_0x8005, METATILE_PastoriaGym_{b}',
                      f'\tsetvar VAR_0x8006, {col}', '\tspecial SE_SwapMapMetatiles']
        lines.append('\treturn\n')
    open(GEN_INC, 'w').write('\n'.join(lines) + '\n')
    from gymkit import build_cells
    build_cells(LAYOUT, rows, border=0x000)
    d = json.load(open(MAP))
    d['warp_events'] = [{'x': x, 'y': H - 1, 'elevation': 0, 'dest_map': 'MAP_PASTORIA_CITY_SINNOH', 'dest_warp_id': '1'}
                        for x in (7, 8, 9)]
    open(MAP, 'w').write(json.dumps(d, indent=2, ensure_ascii=False) + '\n')


if __name__ == '__main__':
    main_frlg()
