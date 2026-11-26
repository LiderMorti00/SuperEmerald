#!/usr/bin/env python3
"""Super Emerald: Canalave City Gym (Byron) - a two-level steel workshop with freight lifts.

Run from the repo root: python3 tools/sfr/gyms/canalave.py
Floor level (entrance): LIFT 1 rides to a small test platform with a trainer and back;
LIFT 2 rides up to the main catwalk. LIFT 3, at the far end of the catwalk, rides to
BYRON's floor. Every pad is numbered and the arrival pad has the same number, so stepping
on it again rides back. The rides are coord events in scripts.inc (YES/NO + warpsilent).
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
}


def plate():
    c = Canvas(SM)
    for y in range(0, 16, 4):
        for x in range((y // 4) % 2 * 2, 16, 4):
            c.px(x, y + 1, SL); c.px(x + 1, y + 2, SL); c.px(x + 1, y + 1, S)
    c.hline(0, 15, 0, SL); c.hline(0, 15, 15, SD)
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
    c = Canvas(K)
    for i in range(16):
        for j in range(16):
            if i in (0, 1, 14, 15) or j in (0, 1, 14, 15):
                c.px(i, j, Y if ((i + j) // 2) % 2 == 0 else K)
    c.rect(2, 2, 13, 13, S); c.rect(3, 3, 12, 12, SL)
    for y, row in enumerate(DIGITS[n]):
        for x, ch in enumerate(row):
            if ch == '#':
                c.px(6 + x, 4 + y, K)
    # small up/down arrows under the number
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
    ts.add('rail', [floor, p(rail_top()), None])
    ts.add('rail_l', [p(rail_side(True)), None, None])
    ts.add('rail_r', [p(rail_side(False)), None, None])
    ts.add('face', [p(face()), None, None])
    ts.add('face_low', [p(face(False)), None, None])
    for k in ('gauge', 'pipe', 'vent'):
        ts.add('machine_' + k, [p(machine(k)), None, None])
    for n in (1, 2, 3):
        ts.add(f'pad{n}', [p(pad(n)), None, None])
        ts.add(f'panel{n}', [floor, p(panel(n)), None])
        ts.add(f'panel{n}_plate', [p(plate()), p(panel(n)), None])
    ts.save({P: STEEL})
    return ts.names


# . floor  P plate  R rail  l/r side rails  F face  g/p/v machines
# 1/2/3 lift pads (A,B,C on the arrival side use the same art)  a/b/c panels on floor,
# A/B/C panels on plate.  rows 0-1 and 22-23 come from the original map.
PLAN = [
    None, None,
    "c...................",   # 2  panel 3' (0,2); BYRON (9,2)
    "3...................",   # 3  LIFT 3 arrival (0,3)
    "....................",   # 4
    "RRRRRRRRRRRRRRRRRRRR",   # 5  catwalk rail
    "CPPPPPPPPPPPPPPPPBPP",   # 6  panels: LIFT 3 (0,6), LIFT 2 (17,6)
    "3PPPPPPPPPPPPPPPP2PP",   # 7  LIFT 3 (0,7), LIFT 2 arrival (17,7)
    "PPPPPPPPPPPPPPPPPPPP",   # 8
    "FFFFFFFFFFFFFFFFFFFF",   # 9  catwalk face
    "b...................",   # 10 panel 2 (0,10)
    "2...................",   # 11 LIFT 2 (0,11)
    "....................",   # 12
    "gpvpgpvpgpvpgp.vpgpv",   # 13 machine row, one gap at (14,13)
    "....................",   # 14
    "a.......RARRR.......",   # 15 panel 1 (0,15); panel 1' (9,15)
    "1.......l1PPr.......",   # 16 LIFT 1 (0,16); arrival (9,16)
    "........lPPPr.......",   # 17
    "........FFFFF.......",   # 18
    "...............s...s",   # 19 statues (15,19) and (19,19)
    "...............z...z",   # 20
    "....................",   # 21
    None, None,
]


def main():
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
    rows['1'] = [0x613] * 20                                   # plain wall: the old window is gone
    rows['22'] = [r if 0x222 <= (r & 0x3FF) <= 0x224 else 0x3202 for r in rows['22']]   # floor + exit mat
    legend = {
        '.': (FLOOR, 0, 3), 'P': (n('plate'), 0, 3), 'R': (n('rail'), 1, 3), 'l': (n('rail_l'), 1, 3),
        'r': (n('rail_r'), 1, 3), 'F': (n('face'), 1, 3), 'g': (n('machine_gauge'), 1, 3),
        'p': (n('machine_pipe'), 1, 3), 'v': (n('machine_vent'), 1, 3),
        '1': (n('pad1'), 0, 3), '2': (n('pad2'), 0, 3), '3': (n('pad3'), 0, 3),
        'a': (n('panel1'), 1, 3), 'b': (n('panel2'), 1, 3), 'c': (n('panel3'), 1, 3),
        'A': (n('panel1'), 1, 3), 's': (0x21a, 0, 3), 'z': (0x221, 1, 3), 'B': (n('panel2_plate'), 1, 3), 'C': (n('panel3_plate'), 1, 3),
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
            out.append(r)
    build_map(LAYOUT, out, legend)

    d = json.load(open(MAP))
    pos = {
        'CanalaveCity_Gym_EventScript_Jackson': (14, 10, 'MOVEMENT_TYPE_FACE_DOWN', '2'),   # watches the gap
        'CanalaveCity_Gym_EventScript_Gary': (4, 10, 'MOVEMENT_TYPE_FACE_DOWN', '1'),
        'CanalaveCity_Gym_EventScript_Gerardo': (5, 19, 'MOVEMENT_TYPE_FACE_LEFT', '3'),
        'CanalaveCity_Gym_EventScript_Cesar': (11, 16, 'MOVEMENT_TYPE_FACE_LEFT', '1'),     # LIFT 1 platform
        'CanalaveCity_Gym_EventScript_Breanna': (10, 6, 'MOVEMENT_TYPE_FACE_DOWN', '2'),    # catwalk, forced
        'CanalaveCity_Gym_EventScript_David': (4, 8, 'MOVEMENT_TYPE_FACE_UP', '2'),         # catwalk, forced
        'CanalaveCity_Gym_EventScript_Ricky': (14, 6, 'MOVEMENT_TYPE_FACE_DOWN', '1'),      # catwalk, optional
        'SE_EventScript_SinnohLeader_Byron': (9, 2, 'MOVEMENT_TYPE_FACE_DOWN', '0'),
        'CanalaveCity_Gym_EventScript_PtGymGuide': (16, 20, 'MOVEMENT_TYPE_FACE_DOWN', '0'),
    }
    for o in d['object_events']:
        x, y, mv, s = pos[o['script']]
        o['x'], o['y'], o['movement_type'], o['elevation'] = x, y, mv, 3
        if o['trainer_type'] != 'TRAINER_TYPE_NONE':
            o['trainer_sight_or_berry_tree_id'] = s
    any_ = 'BG_EVENT_PLAYER_FACING_ANY'
    sign = lambda x, y, s: {'type': 'sign', 'x': x, 'y': y, 'elevation': 0, 'player_facing_dir': any_,
                            'script': 'CanalaveCity_Gym_EventScript_' + s}
    d['bg_events'] = [sign(15, 20, 'PtGymStatue'), sign(19, 20, 'PtGymStatue'),
                      sign(0, 15, 'Panel1'), sign(9, 15, 'Panel1'), sign(0, 10, 'Panel2'),
                      sign(17, 6, 'Panel2'), sign(0, 6, 'Panel3'), sign(0, 2, 'Panel3')]
    trig = lambda x, y, s: {'type': 'trigger', 'x': x, 'y': y, 'elevation': 3, 'var': 'VAR_TEMP_0',
                            'var_value': '0', 'script': 'CanalaveCity_Gym_EventScript_' + s}
    d['coord_events'] = [trig(0, 16, 'Lift1Up'), trig(9, 16, 'Lift1Down'), trig(0, 11, 'Lift2Up'),
                         trig(17, 7, 'Lift2Down'), trig(0, 7, 'Lift3Up'), trig(0, 3, 'Lift3Down')]
    open(MAP, 'w').write(json.dumps(d, indent=2, ensure_ascii=False) + '\n')


if __name__ == '__main__':
    main()
