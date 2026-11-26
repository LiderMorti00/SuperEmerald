#!/usr/bin/env python3
"""Super Emerald: Canalave City Gym (Byron) - a steel workshop on three levels joined by lifts.

Run from the repo root: python3 tools/sfr/gyms/canalave.py
After Platinum's moving platforms (pokeplatinum CanalaveGym_*): numbered lifts join the
sheet-metal workshop floor, two grating catwalks and BYRON's beam floor. Each lift has the
same number at both ends; stepping on a pad asks YES/NO and rides to the other end
(lifts.inc is generated). The player has to pick: LIFT 1 -> west catwalk -> LIFT 5 (a
sideways platform over the drop) -> east catwalk -> LIFT 4 -> BYRON. LIFT 2 only reaches a
lower part of the east catwalk and LIFT 3 a balcony above, each with a trainer.
check() verifies BYRON is reachable and every pad leads back to the door.
"""
import json, os, struct, sys
sys.path.insert(0, os.path.dirname(__file__))
from gymkit import Canvas, Tileset, build_map, write_metatile_defs

TS = 'data/tilesets/secondary/canalave_city_gym_sinnoh'
MAP = 'data/maps/CanalaveCity_Gym_sinnoh/map.json'
LAYOUT = 'LAYOUT_CANALAVE_CITY_GYM_SINNOH'

STEEL = [(0, 0, 0), (16, 16, 24), (56, 60, 72), (104, 110, 124), (152, 160, 176), (208, 214, 224),
         (248, 248, 248), (232, 192, 40), (168, 128, 24), (200, 56, 48), (64, 184, 96), (64, 120, 200),
         (152, 88, 56), (120, 200, 248), (80, 84, 96), (184, 190, 204)]
P = 11
K, SD, S, SL, SH, WH, Y, YD, RED, GRN, BLU, RUST, CYAN, SM, SLL = range(1, 16)
FLOOR = 0x202

DIGITS = {
    1: ["..#..", ".##..", "..#..", "..#..", "..#..", "..#..", ".###."],
    2: [".###.", "#...#", "....#", "...#.", "..#..", ".#...", "#####"],
    3: [".###.", "#...#", "....#", "..##.", "....#", "#...#", ".###."],
    4: ["...#.", "..##.", ".#.#.", "#..#.", "#####", "...#.", "...#."],
    5: ["#####", "#....", "####.", "....#", "....#", "#...#", ".###."],
}


def plate():
    c = Canvas(SM)
    for y in range(0, 16, 4):
        for x in range((y // 4) % 2 * 2, 16, 4):
            c.px(x, y + 1, SL); c.px(x + 1, y + 2, SL); c.px(x + 1, y + 1, S)
    c.hline(0, 15, 0, SL); c.hline(0, 15, 15, SD)
    return c


def sheet():
    """Workshop floor: riveted steel sheets (ground level)."""
    c = Canvas(S)
    c.hline(0, 15, 0, SL); c.vline(0, 0, 15, SL); c.hline(0, 15, 15, SD); c.vline(15, 0, 15, SD)
    for x, y in ((2, 2), (13, 2), (2, 13), (13, 13)):
        c.px(x, y, SH); c.px(x + 1, y + 1, SD)
    c.px(7, 6, SL); c.px(8, 9, SD)
    return c


def grate():
    """Catwalk grating (middle level): open mesh with light trim."""
    c = Canvas(SD)
    for y in range(16):
        for x in range(16):
            if x % 3 == 0 or y % 3 == 0:
                c.px(x, y, SL if (x + y) % 2 else S)
    return c


def beams():
    """BYRON's floor (top): heavy plates over I-beams, bolted."""
    c = Canvas(SM)
    c.rect(0, 6, 15, 9, SD); c.hline(0, 15, 6, SL); c.hline(0, 15, 9, K)
    for x in (3, 8, 13):
        c.px(x, 7, SH); c.px(x, 8, K)
    c.hline(0, 15, 0, SLL); c.hline(0, 15, 15, SD)
    return c


def pillar():
    c = beams()
    c.rect(4, 0, 11, 15, SD); c.rect(5, 0, 10, 15, S); c.vline(5, 0, 15, SL); c.vline(10, 0, 15, K)
    for y in (2, 13):
        c.hline(4, 11, y, YD)
    return c


def drop():
    """The drop between catwalks: the workshop floor far below, in shadow (blocks)."""
    c = Canvas(K)
    for y in range(2, 16, 5):
        c.hline(0, 15, y, SD)
    for x in range(0, 16, 6):
        c.vline(x, 0, 15, SD)
    for x, y in ((3, 8), (11, 4)):
        c.px(x, y, SM)
    return c


def rail_top():
    """Top edge of a raised level: plate with a hand rail across the bottom, seen from above."""
    c = Canvas(0)
    c.rect(0, 9, 15, 15, SM)
    c.hline(0, 15, 9, SH); c.hline(0, 15, 10, SL); c.hline(0, 15, 11, SD)
    for x in (2, 13):
        c.rect(x, 6, x + 1, 11, S); c.px(x, 6, SH)
    c.hline(0, 15, 6, SL); c.hline(0, 15, 7, S)
    return c


def rail_side(left):
    c = plate()
    x0 = 0 if left else 12
    c.rect(x0, 0, x0 + 3, 15, SD)
    c.vline(x0 + 1, 0, 15, SL); c.vline(x0 + 2, 0, 15, S)
    for y in (3, 11):
        c.rect(x0, y, x0 + 3, y + 1, SH)
    return c


def face(lip=True):
    """Front face of a raised level, with a hazard stripe along the top edge."""
    c = Canvas(SD)
    if lip:
        for x in range(16):
            c.vline(x, 0, 2, Y if (x // 2) % 2 == 0 else K)
        c.hline(0, 15, 3, K)
    for y in (6, 12):
        c.hline(0, 15, y, S)
    for x, y in ((2, 9), (13, 9)):
        c.px(x, y, SL); c.px(x + 1, y + 1, K)
    c.hline(0, 15, 15, K)
    return c


def machine(kind):
    c = Canvas(S)
    c.rect(0, 0, 15, 1, SL); c.hline(0, 15, 15, K); c.rect(0, 12, 15, 14, SD)
    if kind == 'gauge':
        c.rect(3, 3, 12, 10, K); c.rect(4, 4, 11, 9, WH)
        c.px(7, 6, RED); c.px(8, 5, RED); c.px(9, 4, RED); c.px(7, 7, K)
    elif kind == 'pipe':
        c.rect(0, 4, 15, 8, RUST); c.hline(0, 15, 4, SH); c.hline(0, 15, 8, SD)
        c.rect(6, 3, 9, 9, SD); c.vline(7, 3, 9, SL)
    else:
        c.rect(2, 3, 13, 10, SD)
        for x in range(3, 13, 3):
            c.rect(x, 4, x + 1, 9, K)
        c.px(12, 4, GRN)
    return c


def pad(n):
    """Lift platform: a steel deck sunk into its shaft (black gap all round), hazard-striped
    rim, big number on top, and the deck's front face with its shadow below."""
    c = Canvas(K)
    for i in range(1, 15):
        for j in range(1, 12):
            c.px(i, j, Y if ((i + j) // 2) % 2 == 0 and (i in (1, 14) or j in (1, 11)) else
                 K if (i in (1, 14) or j in (1, 11)) else SL)
    c.rect(3, 3, 12, 10, SH); c.hline(3, 12, 3, WH)
    for y, row in enumerate(DIGITS[n]):
        for x, ch in enumerate(row):
            if ch == '#':
                c.px(5 + x, 3 + y, K); c.px(6 + x, 3 + y, K)
                c.px(5 + x, 3 + y, SD)
    for y, row in enumerate(DIGITS[n]):
        for x, ch in enumerate(row):
            if ch == '#':
                c.px(6 + x, 3 + y, K)
    c.rect(1, 12, 14, 14, SD); c.hline(1, 14, 12, S)                 # front face
    for x in (3, 7, 11):
        c.px(x, 13, SL)
    c.hline(0, 15, 15, K)
    return c


def mast(n, bg):
    """Lift tower beside each pad: two guide rails with bracing and a big yellow number plate,
    so the same number shows at both ends of the trip (blocks)."""
    c = {'sheet': sheet, 'grate': grate, 'beams': beams, 'drop': drop}[bg]()
    for x0 in (2, 12):
        c.rect(x0, 0, x0 + 1, 15, SD); c.vline(x0, 0, 15, SL); c.vline(x0 + 2, 0, 15, K)
    for y in (1, 14):
        c.hline(2, 13, y, SD)
    c.rect(3, 3, 12, 12, K); c.rect(4, 4, 11, 11, Y)
    for y, row in enumerate(DIGITS[n]):
        for x, ch in enumerate(row):
            if ch == '#':
                c.px(5 + x, 4 + y, K); c.px(6 + x, 4 + y, K)
    c.hline(2, 13, 15, K)
    return c


def wall_top(cx, cy):
    """Back wall of the workshop, 2 rows: girder on top, a riveted steel wall below with a
    pipe and the shield of the steel gym in the middle."""
    c = Canvas(SD)
    for y in range(16):
        for x in range(16):
            X, Y_ = cx * 16 + x, cy * 16 + y
            if cy == 0:
                v = SM if 3 <= Y_ <= 12 else SD
                if Y_ in (0, 15): v = K
                if (X - Y_) % 16 in (0, 1) and 3 <= Y_ <= 12: v = SD                # girder lattice
                if (X + Y_) % 16 in (0, 1) and 3 <= Y_ <= 12: v = SD
                if Y_ == 3: v = SL
            else:
                v = S if (X % 32) else SD
                if Y_ == 16: v = SL
                if X % 32 in (3, 28) and Y_ in (19, 27): v = SH                        # rivets
                if 22 <= Y_ <= 25: v = RUST if Y_ in (23, 24) else SD                  # pipe
                if Y_ == 31: v = K
            c.px(x, y, v)
    if cy == 1 and cx in (9, 10):                                                 # shield
        for y in range(2, 14):
            for x in range(16):
                X = cx * 16 + x - 160
                if abs(X) <= 7 - max(0, y - 8):
                    c.px(x, y, SH if X < 0 else SL)
                    if abs(X) == 7 - max(0, y - 8) or y == 2: c.px(x, y, K)
    return c


def panel(n):
    c = Canvas(0)
    c.rect(3, 4, 12, 15, SD); c.rect(4, 5, 11, 11, K)
    c.rect(5, 6, 10, 10, BLU)
    for y, row in enumerate(DIGITS[n][::2]):          # tiny digit, every other row
        for x, ch in enumerate(row):
            if ch == '#':
                c.px(5 + x, 6 + y, CYAN)
    c.rect(5, 12, 6, 13, Y); c.rect(9, 12, 10, 13, GRN)
    c.hline(3, 12, 4, SL)
    return c


def build_tileset():
    ts = Tileset(TS)
    p = lambda c: (c, P)
    floor = ('mt', FLOOR, 1)
    ts.add('plate', [p(plate()), None, None])
    ts.add('sheet', [p(sheet()), None, None])
    ts.add('grate', [p(grate()), None, None])
    ts.add('beams', [p(beams()), None, None])
    ts.add('pillar', [p(pillar()), None, None])
    ts.add('drop', [p(drop()), None, None])
    ts.replace(0x21a, [p(sheet()), None, ('mt', 0x21a, 2)])       # statues and exit mat on sheet metal
    ts.replace(0x221, [p(sheet()), ('mt', 0x221, 1), None])
    for m in (0x222, 0x223, 0x224):
        ts.replace(m, [p(sheet()), ('mt', m, 1), None])
    ts.add('rail', [p(beams()), p(rail_top()), None])
    ts.add('rail_l', [p(rail_side(True)), None, None])
    ts.add('rail_r', [p(rail_side(False)), None, None])
    ts.add('face', [p(face()), None, None])
    ts.add('face_low', [p(face(False)), None, None])
    for k in ('gauge', 'pipe', 'vent'):
        ts.add('machine_' + k, [p(machine(k)), None, None])
    for n in (1, 2, 3, 4, 5):
        ts.add(f'pad{n}', [p(pad(n)), None, None])
    for n_, bg in MASTS.values():
        ts.add('mast%d_%s' % (n_, bg), [p(mast(n_, bg)), None, None])
    for cy in range(2):
        for cx in range(20):
            ts.add('top_%d_%d' % (cx, cy), [p(wall_top(cx, cy)), None, None])
    bw = Canvas(SD); bw.hline(0, 15, 0, SL); bw.hline(0, 15, 1, S); bw.hline(0, 15, 15, K)
    for x in range(0, 16, 4): bw.px(x, 8, SH)
    ts.add('bottom', [p(bw), None, None])
    ts.save({P: STEEL})
    return ts.names


# . workshop sheet (ground)  P catwalk grating (middle)  T beam floor (top)  x pillar
# R rail along the top edge of a level  F front face of a raised level  v drop  digits: lift pads
# s/z statue top/base. Rows 0-1 and 22-23 come from the original map.
PLAN = [
    None, None,
    "TTTTTTxTTTTTTTTTTTTT",   # 2  balcony x0-5 | BYRON's floor x7-19, BYRON (13,2)
    "T3TTTTxTTTTTTTTTTT4T",   # 3  LIFT 3 top (1,3), LIFT 4 top (18,3)
    "TTTTTTxTTTTTTTTTTTTT",   # 4
    "RRRRRRRRRRRRRRRRRRRR",   # 5  top edge
    "P3PPPPPPvvvvPPPPPP4P",   # 6  west catwalk x0-7 rows 6-10: LIFT 3 (1,6); east catwalk north: LIFT 4 (18,6)
    "PPPPPPPPvvvv5PPPPPPP",   # 7  LIFT 5 east end (12,7)
    "PPPPPPP5vvvvFFFFFFFF",   # 8  LIFT 5 west end (7,8); front of the east catwalk north
    "PPPPPPPPvvvvPPPPPPPP",   # 9  east catwalk south x12-19 rows 9-10
    "P1PPPPPPvvvvPPPPPP2P",   # 10 LIFT 1 top (1,10), LIFT 2 top (18,10)
    "FFFFFFFFvvvvFFFFFFFF",   # 11 front of the catwalks
    "........vvvv........",   # 12
    ".1................2.",   # 13 LIFT 1 (1,13), LIFT 2 (18,13)
    "....................",   # 14
    "....................",   # 15
    "....................",   # 16
    "....................",   # 17
    "....................",   # 18
    "...............s...s",   # 19 statues (15,19) and (19,19)
    "...............z...z",   # 20
    "....................",   # 21
    None, None,
]
MASTS = {(0, 13): (1, 'sheet'), (0, 10): (1, 'grate'), (19, 13): (2, 'sheet'), (19, 10): (2, 'grate'),
         (0, 6): (3, 'grate'), (0, 3): (3, 'beams'), (19, 6): (4, 'grate'), (19, 3): (4, 'beams'),
         (8, 8): (5, 'drop'), (11, 7): (5, 'drop')}
for (mx, my), _ in MASTS.items():
    PLAN[my] = PLAN[my][:mx] + 'M' + PLAN[my][mx + 1:]
LIFTS = {   # number: (end A, end B, label A->B, label B->A)
    1: ((1, 13), (1, 10), 'WEST CATWALK', 'WORKSHOP FLOOR'),
    2: ((18, 13), (18, 10), 'EAST CATWALK', 'WORKSHOP FLOOR'),
    3: ((1, 6), (1, 3), 'BALCONY', 'WEST CATWALK'),
    4: ((18, 6), (18, 3), "BYRON'S FLOOR", 'EAST CATWALK'),
    5: ((7, 8), (12, 7), 'EAST CATWALK', 'WEST CATWALK'),
}


def check():
    from collections import deque
    walk = lambda ch: ch in '.PT12345'
    rows = {y: r for y, r in enumerate(PLAN) if r}
    def ok(x, y): return y in rows and 0 <= x < 20 and walk(rows[y][x])
    ends = {}
    for n, (a, b, _, _) in LIFTS.items():
        ends[a] = b; ends[b] = a
    start = (16, 21)
    seen = {start}; q = deque([start])
    while q:
        x, y = q.popleft()
        nb = [(x + dx, y + dy) for dx, dy in ((1, 0), (-1, 0), (0, 1), (0, -1))]
        if (x, y) in ends:
            nb.append(ends[(x, y)])
        for m in nb:
            if m not in seen and ok(*m):
                seen.add(m); q.append(m)
    assert (13, 3) in seen, 'BYRON unreachable'
    assert all(e in seen for e in ends), [e for e in ends if e not in seen]
    return len(seen)


def main():
    print('reachable tiles:', check())
    names = build_tileset()
    n = lambda k: names[k]
    write_metatile_defs('data/maps/CanalaveCity_Gym_sinnoh', 'CanalaveGym', names)
    L = json.load(open('data/layouts/layouts.json'))
    lay = [l for l in L['layouts'] if l.get('id') == LAYOUT][0]
    state = json.load(open(TS + '/se_gymkit.json'))
    if 'orig_rows' not in state:
        old = open(lay['blockdata_filepath'], 'rb').read()
        ow = lay['width']
        row = lambda y: [struct.unpack_from('<H', old, (y * ow + x) * 2)[0] for x in range(ow)]
        state['orig_rows'] = {str(y): row(y) for y in (0, 1, 22, 23)}
        json.dump(state, open(TS + '/se_gymkit.json', 'w'), indent=1)
    rows = dict(state['orig_rows'])
    rows['0'] = [n('top_%d_0' % x) | 0x400 for x in range(20)]
    rows['1'] = [n('top_%d_1' % x) | 0x400 for x in range(20)]
    rows['22'] = [r if 0x222 <= (r & 0x3FF) <= 0x224 else (n('sheet') | 0x3000) for r in rows['22']]   # floor + exit mat
    rows['23'] = [n('bottom') | 0x400 for x in range(20)]
    legend = {
        '.': (n('sheet'), 0, 3), 'P': (n('grate'), 0, 3), 'T': (n('beams'), 0, 3), 'x': (n('pillar'), 1, 3),
        'R': (n('rail'), 1, 3), 'F': (n('face'), 1, 3), 'v': (n('drop'), 1, 3),
        '1': (n('pad1'), 0, 3), '2': (n('pad2'), 0, 3), '3': (n('pad3'), 0, 3), '4': (n('pad4'), 0, 3),
        '5': (n('pad5'), 0, 3), 's': (0x21a, 0, 3), 'z': (0x221, 1, 3),
    }
    keymap = {}

    def raw(vals):
        line = ''
        for v in vals:
            if v not in keymap:
                keymap[v] = chr(0x100 + len(keymap))
                legend[keymap[v]] = (v & 0x3FF, (v >> 10) & 3, v >> 12)
            line += keymap[v]
        return line
    out = []
    for y, r in enumerate(PLAN):
        if r is None:
            out.append(raw(rows[str(y)]))
        else:
            assert len(r) == 20, (y, len(r))
            line = ''
            for x, ch in enumerate(r):
                if ch == 'M':
                    line += raw([n('mast%d_%s' % MASTS[(x, y)]) | 0x3400])
                else:
                    line += ch
            out.append(line)
    build_map(LAYOUT, out, legend)

    d = json.load(open(MAP))
    pos = {
        'CanalaveCity_Gym_EventScript_Jackson': (3, 13, 'MOVEMENT_TYPE_FACE_LEFT', '1'),     # guards LIFT 1
        'CanalaveCity_Gym_EventScript_Gary': (19, 14, 'MOVEMENT_TYPE_FACE_LEFT', '2'),       # guards LIFT 2
        'CanalaveCity_Gym_EventScript_David': (4, 8, 'MOVEMENT_TYPE_FACE_RIGHT', '3'),       # west catwalk, before LIFT 5
        'CanalaveCity_Gym_EventScript_Breanna': (3, 6, 'MOVEMENT_TYPE_FACE_LEFT', '1'),      # west catwalk, by LIFT 3
        'CanalaveCity_Gym_EventScript_Cesar': (15, 10, 'MOVEMENT_TYPE_FACE_RIGHT', '2'),     # east catwalk south (detour)
        'CanalaveCity_Gym_EventScript_Gerardo': (4, 3, 'MOVEMENT_TYPE_FACE_LEFT', '2'),      # balcony (detour)
        'CanalaveCity_Gym_EventScript_Ricky': (16, 7, 'MOVEMENT_TYPE_FACE_RIGHT', '1'),      # east catwalk north, by LIFT 4
        'SE_EventScript_SinnohLeader_Byron': (13, 2, 'MOVEMENT_TYPE_FACE_DOWN', '0'),
        'CanalaveCity_Gym_EventScript_PtGymGuide': (14, 21, 'MOVEMENT_TYPE_FACE_RIGHT', '0'),
    }
    for o in d['object_events']:
        x, y, mv, s_ = pos[o['script']]
        o['x'], o['y'], o['movement_type'], o['elevation'] = x, y, mv, 3
        if o['trainer_type'] != 'TRAINER_TYPE_NONE':
            o['trainer_sight_or_berry_tree_id'] = s_
    any_ = 'BG_EVENT_PLAYER_FACING_ANY'
    sign = lambda x, y, s_: {'type': 'sign', 'x': x, 'y': y, 'elevation': 0, 'player_facing_dir': any_,
                             'script': 'CanalaveCity_Gym_EventScript_' + s_}
    d['bg_events'] = [sign(15, 20, 'PtGymStatue'), sign(19, 20, 'PtGymStatue')]
    trig = lambda x, y, s_: {'type': 'trigger', 'x': x, 'y': y, 'elevation': 3, 'var': 'VAR_TEMP_0',
                             'var_value': '0', 'script': 'CanalaveCity_Gym_EventScript_' + s_}
    d['coord_events'] = []
    lines = ['@ Generated by tools/sfr/gyms/canalave.py; do not edit.']
    for num, (a_, b_, to_b, to_a) in LIFTS.items():
        for tag, here, there, label in (('A', a_, b_, to_b), ('B', b_, a_, to_a)):
            name = f'Lift{num}{tag}'
            d['coord_events'].append(trig(here[0], here[1], name))
            lines += [f'CanalaveCity_Gym_EventScript_{name}::', '\tlockall',
                      f'\tmsgbox CanalaveCity_Gym_Text_{name}, MSGBOX_YESNO',
                      '\tgoto_if_eq VAR_RESULT, NO, CanalaveCity_Gym_EventScript_LiftStay',
                      '\tcall CanalaveCity_Gym_EventScript_LiftRide',
                      f'\twarpsilent MAP_CANALAVE_CITY_GYM_SINNOH, {there[0]}, {there[1]}', '\twaitstate', '\tend', '',
                      f'CanalaveCity_Gym_Text_{name}::', f'\t.string "LIFT {num}: to the {label}.\\n"',
                      '\t.string "Ride it?$"', '']
    open('data/maps/CanalaveCity_Gym_sinnoh/lifts.inc', 'w').write('\n'.join(lines) + '\n')
    open(MAP, 'w').write(json.dumps(d, indent=2, ensure_ascii=False) + '\n')


# ------------------------------------------------------------------ FRLG dressing (Power Plant)
# Base: FRLG's Power Plant. Workshop floor = its beige floor plates (with the shade its walls
# cast, learned from the map); catwalks and BYRON's floor = its steel grating; their front
# faces = the plate base of its machine walls; the rail between levels = its girder band; the
# pillar = its wall divider; the back wall = cap + girder. Lift decks are its yellow mesh with
# a new frame and number; the lift towers keep their drawn guide rails and number plate, now
# standing on the FRLG floor of each level.
PPM = 'PowerPlant_Frlg'


def pad_ov(n):
    """Lift deck seen from above and in front: a raised plate with a hazard rim, the number on a
    steel boss, the deck's front face (riveted) and its shadow on the gap below."""
    c = Canvas(0)
    c.rect(0, 0, 15, 11, 0)
    for i in range(16):                                    # hazard rim around the deck top
        for j in (0, 11):
            c.px(i, j, Y if (i // 2) % 2 else K)
    for j in range(12):
        c.px(0, j, Y if (j // 2) % 2 else K); c.px(15, j, Y if (j // 2) % 2 else K)
    c.rect(4, 2, 11, 9, SH); c.hline(4, 11, 2, WH); c.hline(4, 11, 9, SD); c.vline(11, 2, 9, SD)
    for y, row in enumerate(DIGITS[n]):
        for x, ch in enumerate(row):
            if ch == '#':
                c.px(5 + x, 2 + y, K); c.px(6 + x, 2 + y, K)
    c.rect(0, 12, 15, 14, SD); c.hline(0, 15, 12, S)       # front face
    for x in (2, 7, 13):
        c.px(x, 13, SL)
    c.hline(0, 15, 15, K)                                  # shadow on the floor/gap
    return c


def mast_ov(n):
    c = Canvas(0)
    for x0 in (2, 12):
        c.rect(x0, 0, x0 + 1, 15, SD); c.vline(x0, 0, 15, SL); c.vline(x0 + 2, 0, 15, K)
    for y in (1, 14):
        c.hline(2, 13, y, SD)
    c.rect(3, 3, 12, 12, K); c.rect(4, 4, 11, 11, Y)
    for y, row in enumerate(DIGITS[n]):
        for x, ch in enumerate(row):
            if ch == '#':
                c.px(5 + x, 4 + y, K); c.px(6 + x, 4 + y, K)
    c.hline(2, 13, 15, K)
    return c


def main_frlg():
    import gbaref as G
    print('reachable tiles:', check())
    ts = Tileset(TS)
    ts.free_unused(set())
    src = G.source_for(PPM)
    imp = G.Importer(ts, G.free_slots({P}))
    A = lambda nm, mid, col, el=3, mb=0: (imp.add(nm, src, mid, mb), col, el)
    table = G.learn(src, [PPM], lambda m, c, b: 'W' if c else 'F', edge='W')
    plan = [r if r else None for r in PLAN]
    H, Wd = len(plan), 20
    cls = []
    for y in range(H):
        r = plan[y]
        cls.append(['F' if r and ch in '.12s' else 'W' for ch in (r or '#' * Wd)])
    rows = []
    for y in range(H):
        r = plan[y]
        row = []
        for x in range(Wd):
            ch = r[x] if r else None
            if y == 0:
                mid = 0x284 if x == 0 else 0x286 if x == Wd - 1 else 0x285
                row.append(A('w_%x' % mid, mid, 1, 0))
            elif y == 1:
                mid = 0x28C if x == 0 else 0x28E if x == Wd - 1 else (0x2E6 if x % 10 == 3 else 0x2E7 if x % 10 == 7 else 0x28D)
                row.append(A('w_%x' % mid, mid, 1, 0))
            elif y == H - 1:
                if x in (16, 17, 18):
                    row.append(A('mat%d' % (x - 16), 0x174 + x - 16, 0, 3, 0x65))
                else:
                    row.append((0x000, 1, 0))
            elif ch is None or ch in '.s' and y == H - 2 or ch in '.':
                key = ''.join(k for k in G.neigh(cls, x, y))
                mid, d = G.pick(table, 'F', key)
                if d > 2 or mid not in (0x29F, 0x29B, 0x29C, 0x29D, 0x29E): mid = 0x29F
                row.append(A('f_%x' % mid, mid, 0))
            elif ch in 'PT':
                row.append(A('grate', 0x2C4, 0))
            elif ch == 'x':
                mid = 0x2A0 if plan[y - 1] and plan[y - 1][x] == 'x' else 0x2BC
                row.append(A('w_%x' % mid, mid, 1))
            elif ch == 'R':
                mid = 0x2D4 if x == 0 else 0x2D3 if x == Wd - 1 else 0x28D
                row.append(A('w_%x' % mid, mid, 1))
            elif ch == 'F':
                row.append(A('w_295', 0x295, 1))
            elif ch == 'v':
                row.append((0x000, 1, 3))
            elif ch in '12345':
                nm = 'pad' + ch
                if nm not in ts.names:
                    ts.add(nm, [imp.flat(src, 0x2CC), (pad_ov(int(ch)), P), None], 0)
                row.append((ts.names[nm], 0, 3))
            elif ch == 'M':
                n_, bg = MASTS[(x, y)]
                nm = 'mast%d_%s' % (n_, bg)
                if nm not in ts.names:
                    base = {'sheet': 0x29F, 'grate': 0x2C4, 'beams': 0x2C4, 'drop': None}[bg]
                    ts.add(nm, [imp.flat(src, base) if base else None, (mast_ov(n_), P), None], 0)
                row.append((ts.names[nm], 1, 3))
            elif ch == 's':
                fl = imp.flat(src, 0x29F)
                if 'statue_top' not in ts.names:
                    ts.add('statue_top', [fl, None, ('raw', [0x0001, 0x0002, 0x0011, 0x0012])], 0)
                row.append((ts.names['statue_top'], 0, 3))
            elif ch == 'z':
                fl = imp.flat(src, 0x29F)
                if 'statue_base' not in ts.names:
                    ts.add('statue_base', [fl, ('raw', [0x0021, 0x0022, 0x0031, 0x0032]), None], 0)
                row.append((ts.names['statue_base'], 1, 3))
            else:
                raise SystemExit((x, y, ch))
        rows.append(row)
    print('palette slots:', sorted(imp.colors), '+', P)
    pals = imp.palettes(); pals[P] = STEEL
    ts.save(pals)
    write_metatile_defs('data/maps/CanalaveCity_Gym_sinnoh', 'CanalaveGym', ts.names)
    from gymkit import build_cells
    build_cells(LAYOUT, rows, border=0x000)
    d = json.load(open(MAP))
    d['warp_events'] = [{'x': x, 'y': H - 1, 'elevation': 3, 'dest_map': 'MAP_CANALAVE_CITY_SINNOH', 'dest_warp_id': '1'}
                        for x in (16, 17, 18)]
    open(MAP, 'w').write(json.dumps(d, indent=2, ensure_ascii=False) + '\n')


if __name__ == '__main__':
    main()            # objects, lift scripts
    main_frlg()
