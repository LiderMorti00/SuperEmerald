#!/usr/bin/env python3
"""Super Emerald: Veilstone City Gym (Maylene) - a dojo with two sliding panels.

Run from the repo root: python3 tools/sfr/gyms/veilstone.py
Panels are metatiles moved by scripts (scripts.inc): panel A stands in front of the gap in
the first partition and slides one tile east (pushed from the west); panel B stands in front
of the last corridor and only slides east (pushed from the west side). Their positions
live in VAR_TEMP_1 / VAR_TEMP_2, so they reset whenever the player leaves the gym.
"""
import json, os, sys
sys.path.insert(0, os.path.dirname(__file__))
from gymkit import Canvas, Tileset, build_map, write_metatile_defs

TS = 'data/tilesets/secondary/dewford_gym_sinnoh'
MAP = 'data/maps/VeilstoneCity_Gym_sinnoh/map.json'
LAYOUT = 'LAYOUT_VEILSTONE_CITY_GYM_SINNOH'

DOJO = [(0, 0, 0), (28, 22, 18), (84, 52, 30), (128, 84, 48), (172, 122, 72), (208, 166, 104),
        (198, 196, 132), (222, 220, 160), (156, 160, 96), (236, 232, 216), (176, 40, 40), (224, 88, 72),
        (56, 72, 136), (96, 120, 188), (40, 40, 48), (120, 118, 110)]
P = 10
K, WD, W, WL, WH, TM, TL, TD, PAPER, RED, REDL, BLU, BLUL, IRON, GREY = range(1, 16)


def wood_floor():
    c = Canvas(WL)
    for y in range(0, 16, 4):
        c.hline(0, 15, y, W)
    for y, x in ((1, 5), (5, 11), (9, 3), (13, 9)):
        c.vline(x, y, y + 2, W)
    c.px(2, 2, WH); c.px(12, 10, WH)
    return c


def tatami(edge=False):
    c = Canvas(TM)
    for y in range(1, 16, 2):
        c.hline(0, 15, y, TL)
    c.vline(0, 0, 15, TD); c.vline(15, 0, 15, TD)
    if edge:
        c.hline(0, 15, 0, K); c.hline(0, 15, 1, RED)
    return c


def mat(edges=''):
    """Training tatami: straw weave with a dark cloth border on its outer sides."""
    c = Canvas(TM)
    for y in range(0, 16, 2):
        c.hline(0, 15, y, TL)
    for e in edges:
        for i in range(16):
            for k in range(2):
                p = {'n': (i, k), 's': (i, 15 - k), 'w': (k, i), 'e': (15 - k, i)}[e]
                c.px(*p, K if k == 0 else BLU)
    return c


def wall_top():
    c = Canvas(WD)
    c.hline(0, 15, 14, W); c.hline(0, 15, 15, K)
    return c


def wall_face(kind=None):
    c = Canvas(PAPER)
    for x in (0, 8):
        c.vline(x, 0, 15, W); c.vline(x + 1, 0, 15, WD)
    c.hline(0, 15, 7, W)
    c.hline(0, 15, 14, WD); c.hline(0, 15, 15, K)
    if kind == 'scroll':
        c.rect(4, 1, 11, 13, PAPER); c.rect(4, 1, 11, 1, WD); c.rect(4, 13, 11, 13, WD)
        c.vline(4, 2, 12, GREY); c.vline(11, 2, 12, GREY)
        for y in (3, 5, 6, 8, 10):
            c.hline(6, 9, y, K)
        c.rect(7, 11, 8, 12, RED)
    if kind == 'banner':
        c.rect(3, 0, 12, 12, RED); c.rect(4, 1, 11, 11, REDL); c.rect(6, 3, 9, 8, PAPER)
        c.vline(7, 4, 7, K); c.hline(6, 9, 5, K)
    return c


def partition(face):
    """Fixed shoji partition, a solid wall object. face=True (floor to the south): dark wooden
    cap on top, paper panes in a lattice frame, dark sill. face=False: only the thick cap
    (another partition stands in front of it)."""
    c = Canvas(0)
    c.rect(0, 0, 15, 4, WD); c.hline(0, 15, 0, K); c.hline(0, 15, 1, W); c.hline(0, 15, 4, K)
    if not face:
        c.rect(0, 0, 15, 15, WD); c.hline(0, 15, 0, K)
        for y in range(2, 16, 4):
            c.hline(0, 15, y, W)
        c.vline(0, 0, 15, K); c.vline(15, 0, 15, K)
        return c
    c.rect(0, 5, 15, 13, PAPER)
    for x in (0, 5, 10, 15):
        c.vline(x, 5, 13, WD)
    c.hline(0, 15, 9, W)
    c.rect(0, 14, 15, 15, K); c.hline(0, 15, 14, WD)
    return c


def panel(cap):
    """Movable panel: red lacquered frame, paper face with a black handle bar, sitting on two
    small wheels in its rail (blocks). Reads as an object: taller than the floor, own shadow."""
    c = Canvas(0)
    c.rect(1, 0, 14, 3, RED); c.hline(1, 14, 0, K); c.hline(2, 13, 1, REDL)
    c.rect(1, 4, 14, 12, RED); c.rect(3, 5, 12, 11, PAPER); c.vline(7, 5, 11, REDL); c.vline(8, 5, 11, RED)
    c.rect(4, 8, 11, 8, K)                                   # push bar
    c.vline(1, 0, 12, K); c.vline(14, 0, 12, K)
    c.rect(2, 13, 4, 14, IRON); c.rect(11, 13, 13, 14, IRON)  # wheels
    c.hline(1, 14, 15, K)
    return c


def sandbag():
    """Hanging sandbag (the top half is drawn over the player)."""
    c = Canvas(0)
    c.vline(7, 0, 2, IRON); c.vline(8, 0, 2, GREY)
    c.rect(4, 3, 11, 14, TD); c.rect(5, 3, 10, 13, TM); c.rect(6, 4, 7, 12, TL)
    c.hline(4, 6, 6, WD); c.hline(4, 6, 10, WD); c.hline(9, 11, 6, WD); c.hline(9, 11, 10, WD)
    c.hline(5, 10, 15, K)
    return c


def rail(end, base=None):
    """Steel floor rail for a panel: a dark groove with a brass stop at the end it can't pass
    and arrows showing the way it runs (east)."""
    c = (base or wood_floor()).copy() if base else wood_floor()
    c.rect(0, 11, 15, 13, IRON); c.hline(0, 15, 11, GREY); c.hline(0, 15, 13, K)
    for x in range(2, 16, 5):
        c.px(x, 7, RED); c.px(x + 1, 8, RED); c.px(x, 9, RED)
    x0 = 0 if end == 'l' else 13
    c.rect(x0, 9, x0 + 2, 14, TD); c.rect(x0, 9, x0 + 2, 9, WH); c.vline(x0 + (2 if end == 'l' else 0), 9, 14, K)
    return c


def shade(c, rows=2):
    for y in range(rows):
        for x in range(16):
            c.px(x, y, K if y == 0 else WD)
    return c


def bottom():
    c = Canvas(K)
    c.hline(0, 15, 0, WD)
    return c


def build_tileset():
    ts = Tileset(TS)
    p = lambda c: (c, P)
    wood = p(wood_floor())
    ts.add('wood', [wood, None, None])
    ts.add('tatami', [p(tatami()), None, None])
    ts.add('tatami_edge', [p(tatami(True)), None, None])
    ts.add('mat', [p(mat()), None, None])
    ts.add('wall_top', [p(wall_top()), None, None])
    ts.add('wall_face', [p(wall_face()), None, None])
    ts.add('wall_scroll', [p(wall_face('scroll')), None, None])
    ts.add('wall_banner', [p(wall_face('banner')), None, None])
    ts.add('partition', [wood, p(partition(True)), None])
    ts.add('partition_top', [wood, p(partition(False)), None])
    ts.add('rail_l', [p(rail('l')), None, None])
    ts.add('rail_r', [p(rail('r')), None, None])
    ts.add('panel_l', [p(rail('l')), p(panel(True)), None])
    ts.add('panel_r', [p(rail('r')), p(panel(True)), None])
    ts.add('wood_sh', [p(shade(wood_floor())), None, None])
    for e in ('', 'n', 's', 'w', 'e', 'nw', 'ne', 'sw', 'se', 'ns', 'we', 'nsw', 'nse', 'nwe', 'swe', 'nswe'):
        ts.add('mat_' + (e or '0'), [p(mat(e)), None, None])
        ts.add('matsh_' + (e or '0'), [p(shade(mat(e))), None, None])
    ts.add('sandbag', [wood, p(sandbag()), None])
    ts.add('bottom', [p(bottom()), None, None])
    ts.save({P: DOJO})
    return ts.names


# x 0..16, y 0..15. P partition, A panel A (12,9), B panel B (8,5), s sandbag, m mat,
# t tatami, e tatami edge, . wood, Z statue top, z statue base, 1-2 exit mat.
PLAN = [
    "TTTTTTTTTTTTTTTTT",  # 0
    "|ffbffSffbffSffb|",  # 1   wall face, banners and scrolls
    "|s,...ttttt...,s|",  # 2   MAYLENE at (8,2) on the tatami dais
    "|..s...eeeee.s..|",  # 3
    "|PPPPPPP.PPPPPPP|",  # 4   the last corridor (8,4)
    "|PPPPP..B..PPPPP|",  # 5   panel B only slides east, to (9,5)
    "|PPPPP.PPP.PPPPP|",  # 6   accesses to row 5 at (6,6) and (10,6)
    "|..mmm......mmm.|",  # 7   zone 2
    "|s.mmm......mmm.|",  # 8
    "|PPPPPPPPPPP.PPP|",  # 9   gap (12,9)
    "|.s.........A...|",  # 10  zone 1; panel A (12,10) in front of the gap, slides east to (13,10)
    "|..mmm....mmm...|",  # 11
    "|..mmm....mmm..s|",  # 12
    "|.Z.s.......s.Z.|",  # 13
    "|.z...........z.|",  # 14
    "________12_______",  # 15
]


def main():
    names = build_tileset()
    n = lambda k: names[k]
    write_metatile_defs('data/maps/VeilstoneCity_Gym_sinnoh', 'VeilstoneGym', names)
    legend = {
        'T': (n('wall_top'), 1, 0), 'f': (n('wall_face'), 1, 0), 'b': (n('wall_banner'), 1, 0),
        'S': (n('wall_scroll'), 1, 0), '|': (n('wall_top'), 1, 0), '_': (n('bottom'), 1, 0),
        '.': (n('wood'), 0, 3), ',': (n('wood'), 0, 3), 't': (n('tatami'), 0, 3), 'e': (n('tatami_edge'), 0, 3),
        'm': (n('mat'), 0, 3), 'P': (n('partition'), 1, 3), 'A': (n('panel_l'), 1, 3), 'B': (n('panel_l'), 1, 3), 'r': (n('rail_r'), 0, 3),
        's': (n('sandbag'), 1, 3), 'Z': (0x21f, 0, 3), 'z': (0x227, 1, 3), '1': (0x006, 0, 3), '2': (0x007, 0, 3),
    }
    plan = [list(r) for r in PLAN]
    plan[10][13] = 'r'; plan[5][9] = 'r'           # the rail's far end for panels A and B
    H, Wd = len(plan), len(plan[0])
    rows = []
    for y in range(H):
        row = []
        for x in range(Wd):
            ch = plan[y][x]
            north = plan[y - 1][x] if y else 'T'
            sh = north in 'PTfbS|AB'
            if ch == 'P':
                face = y + 1 < H and plan[y + 1][x] not in 'P'
                row.append((n('partition' if face else 'partition_top'), 1, 3))
            elif ch == 'm':
                e = ''.join(k for k, dx, dy in (('n', 0, -1), ('s', 0, 1), ('w', -1, 0), ('e', 1, 0))
                            if plan[y + dy][x + dx] != 'm')
                row.append((n(('matsh_' if sh else 'mat_') + (e or '0')), 0, 3))
            elif ch in '.,' and sh:
                row.append((n('wood_sh'), 0, 3))
            else:
                row.append(legend[ch])
        rows.append(row)
    from gymkit import build_cells
    build_cells(LAYOUT, rows, border=n('wall_top'))
    d = json.load(open(MAP))
    d['warp_events'] = [{'x': x, 'y': 15, 'elevation': 0, 'dest_map': 'MAP_VEILSTONE_CITY_SINNOH', 'dest_warp_id': '11'}
                        for x in (8, 9)]
    pos = {
        'VeilstoneCity_Gym_EventScript_Colby': (11, 12, 'MOVEMENT_TYPE_FACE_UP', '2'),      # guards the push spot (11,10)
        'VeilstoneCity_Gym_EventScript_Jeffery': (14, 11, 'MOVEMENT_TYPE_FACE_LEFT', '2'),
        'VeilstoneCity_Gym_EventScript_Darren': (2, 7, 'MOVEMENT_TYPE_FACE_RIGHT', '2'),
        'VeilstoneCity_Gym_EventScript_Rafael': (15, 8, 'MOVEMENT_TYPE_FACE_LEFT', '2'),
        'SE_EventScript_SinnohLeader_Maylene': (8, 2, 'MOVEMENT_TYPE_FACE_DOWN', '0'),
        'VeilstoneCity_Gym_EventScript_PtGymGuide': (11, 14, 'MOVEMENT_TYPE_FACE_DOWN', '0'),
    }
    for o in d['object_events']:
        x, y, mv, s = pos[o['script']]
        o['x'], o['y'], o['movement_type'], o['elevation'] = x, y, mv, 3
        if o['trainer_type'] != 'TRAINER_TYPE_NONE':
            o['trainer_sight_or_berry_tree_id'] = s
    any_ = 'BG_EVENT_PLAYER_FACING_ANY'
    d['bg_events'] = [
        {'type': 'sign', 'x': 2, 'y': 14, 'elevation': 0, 'player_facing_dir': any_, 'script': 'VeilstoneCity_Gym_EventScript_PtGymStatue'},
        {'type': 'sign', 'x': 14, 'y': 14, 'elevation': 0, 'player_facing_dir': any_, 'script': 'VeilstoneCity_Gym_EventScript_PtGymStatue'},
        {'type': 'sign', 'x': 12, 'y': 10, 'elevation': 0, 'player_facing_dir': any_, 'script': 'VeilstoneCity_Gym_EventScript_PanelA'},
        {'type': 'sign', 'x': 13, 'y': 10, 'elevation': 0, 'player_facing_dir': any_, 'script': 'VeilstoneCity_Gym_EventScript_PanelA'},
        {'type': 'sign', 'x': 8, 'y': 5, 'elevation': 0, 'player_facing_dir': any_, 'script': 'VeilstoneCity_Gym_EventScript_PanelB'},
        {'type': 'sign', 'x': 9, 'y': 5, 'elevation': 0, 'player_facing_dir': any_, 'script': 'VeilstoneCity_Gym_EventScript_PanelB'},
    ]
    d['coord_events'] = []
    open(MAP, 'w').write(json.dumps(d, indent=2, ensure_ascii=False) + '\n')


if __name__ == '__main__':
    main()
