#!/usr/bin/env python3
"""Super Emerald: Eterna City Gym (Gardenia) - a greenhouse with three flower clearings.

Run from the repo root: python3 tools/sfr/gyms/eterna.py
A gardener waits in each side clearing (red, yellow and blue beds). The gate in the hedge
north of the central clearing opens once all three are beaten (their trainer flags):
on load and right after each of those battles (scripts.inc).
"""
import json, os, sys
sys.path.insert(0, os.path.dirname(__file__))
from gymkit import Canvas, Tileset, build_map, write_metatile_defs

TS = 'data/tilesets/secondary/eterna_gym_sinnoh'
MAP = 'data/maps/EternaCity_Gym_sinnoh/map.json'
LAYOUT = 'LAYOUT_ETERNA_CITY_GYM_SINNOH'

GARDEN = [(0, 0, 0), (34, 30, 26), (92, 58, 30), (140, 92, 48), (186, 134, 78), (226, 182, 120),
          (200, 40, 52), (248, 110, 110), (232, 184, 32), (252, 236, 120), (48, 96, 208), (132, 176, 252),
          (248, 248, 248), (36, 104, 52), (72, 160, 72), (96, 64, 40)]
P = 11
K, WD, W, WL, WH, RED, REDL, YEL, YELL, BLU, BLUL, WHT, GD, G, SOIL = range(1, 16)
FLOWER = {'r': (RED, REDL), 'y': (YEL, YELL), 'b': (BLU, BLUL)}


def flowers(col, seed=0):
    """Loose flowers on grass (middle layer, passable)."""
    c = Canvas(0)
    a, b = FLOWER[col]
    pts = [(2, 2), (9, 1), (13, 6), (5, 8), (11, 12), (2, 12), (7, 4)]
    for i, (x, y) in enumerate(pts):
        x, y = (x + seed * 3) % 14, (y + seed * 5) % 14
        c.px(x + 1, y, a); c.px(x, y + 1, a); c.px(x + 2, y + 1, a); c.px(x + 1, y + 2, a)
        c.px(x + 1, y + 1, b if i % 2 else YELL)
        c.px(x + 1, y + 3, GD)
    return c


def planter(col):
    """Wooden planter full of flowers (blocks)."""
    c = Canvas(0)
    c.rect(1, 6, 14, 14, W); c.hline(1, 14, 6, WH); c.hline(1, 14, 14, WD); c.vline(1, 6, 14, WL)
    c.vline(14, 6, 14, WD)
    for x in (5, 10):
        c.vline(x, 7, 13, WD)
    c.rect(2, 4, 13, 6, SOIL)
    a, b = FLOWER[col]
    for i, x in enumerate(range(2, 14, 3)):
        c.rect(x, 1, x + 2, 3, a); c.px(x + 1, 2, b); c.px(x + 1, 0, a)
        c.px(x + 1, 4, G); c.px(x, 5, GD); c.px(x + 2, 5, G)
    return c


def gate(open_):
    c = Canvas(0)
    if not open_:
        c.rect(0, 2, 1, 15, WD); c.rect(14, 2, 15, 15, WD)
        c.vline(0, 2, 15, K); c.vline(15, 2, 15, K)
        for x in range(2, 14, 3):
            c.rect(x, 3, x + 1, 14, W); c.px(x, 3, WH); c.vline(x + 1, 4, 14, WD)
        c.rect(2, 5, 13, 6, WL); c.rect(2, 11, 13, 12, WL); c.hline(2, 13, 6, WD); c.hline(2, 13, 12, WD)
        c.rect(6, 7, 9, 10, YEL); c.rect(7, 8, 8, 9, WD)        # latch
    else:
        c.rect(0, 2, 1, 15, WD); c.rect(14, 2, 15, 15, WD)
        c.vline(0, 2, 15, K); c.vline(15, 2, 15, K)
        c.rect(2, 3, 3, 14, W); c.vline(3, 4, 14, WD); c.rect(12, 3, 13, 14, W); c.vline(12, 4, 14, WD)
    # arch of leaves
    c.rect(0, 0, 15, 1, GD); c.hline(1, 14, 0, G)
    for x in (0, 3, 7, 11, 15):
        c.px(x, 2, G)
    return c


def glass_wall(right):
    """Greenhouse side wall: tall glass panes in white frames with leaves pressed behind."""
    c = Canvas(BLUL)
    for y in range(16):
        for x in range(16):
            if (x + y * 2) % 9 == 0:
                c.px(x, y, WHT)
    for x in (0, 7, 15):
        c.vline(x, 0, 15, WHT)
    c.hline(0, 15, 0, WHT); c.hline(0, 15, 8, WHT)
    for x, y in ((3, 3), (4, 4), (10, 11), (11, 12), (3, 12), (12, 4)):
        c.px(x, y, G); c.px(x + 1, y, GD)
    edge = 15 if right else 0
    c.vline(edge, 0, 15, WD)
    return c


def soil(seed=0):
    """Tilled bed with seedlings (walkable): cultivation rows."""
    c = Canvas(SOIL)
    for y in (2, 6, 10, 14):
        c.hline(0, 15, y, WD); c.hline(0, 15, y + 1, W)
    for i, x in enumerate(range(1 + seed, 16, 4)):
        for y in (1, 5, 9, 13):
            c.px(x, y, G); c.px(x + 1, y - 1, GD if i % 2 else G)
    return c


def signpost():
    c = Canvas(0)
    c.rect(1, 2, 14, 9, W); c.hline(1, 14, 2, WH); c.hline(1, 14, 9, WD); c.vline(1, 2, 9, WL); c.vline(14, 2, 9, WD)
    c.hline(3, 12, 4, WD); c.hline(3, 10, 6, WD)
    c.rect(7, 10, 8, 15, WD); c.px(7, 10, W)
    return c


def build_tileset():
    ts = Tileset(TS)
    grass = ('mt', 0x204, 1)
    grass2 = ('mt', 0x205, 1)
    sand = ('mt', 0x226, 1)
    for col in 'ryb':
        ts.add('flowers_' + col, [grass, (flowers(col), P), None])
        ts.add('flowers2_' + col, [grass2, (flowers(col, 1), P), None])
        ts.add('planter_' + col, [grass, (planter(col), P), None])
    ts.add('gate_closed', [grass, (gate(False), P), None])
    ts.add('gate_open', [sand, (gate(True), P), None])
    ts.add('sign', [grass, (signpost(), P), None])
    ts.add('glass_l', [(glass_wall(False), P), None, None])
    ts.add('glass_r', [(glass_wall(True), P), None, None])
    ts.add('soil', [(soil(), P), None, None])
    ts.add('soil2', [(soil(2), P), None, None])
    ts.add('sign_sand', [sand, (signpost(), P), None])
    ts.save({P: GARDEN})
    return ts.names


# ------------------------------------------------------------------ plan
# x 0..20, y 0..26. ',' ';' grass, 'h' 'H' hedges (two bush tiles, block), '.' sand,
# r/y/b flowers, R/Y/B planters, G gate (closed), s sign on grass, S sign on sand,
# Z statue top, z statue base, 1-3 exit mat, | side wall, _ bottom wall.
PLAN = [
    "#####################",  # 0  (top wall, filled below)
    "#####################",  # 1
    "|rR,;hHhH,;,,HhHh,Yy|",  # 2   NW red clearing | Gardenia's garden | NE yellow clearing
    "|,;r,hb,,;,,;,rh,;,y|",  # 3
    "|;,,;h,;,,,,,,;H;,,;|",  # 4   Gardenia at (10,4); Angela (3,4); Jenna (17,4)
    "|R;,,H;y,;,;,y,h,;,Y|",  # 5
    "|,r;,h,,;,,;,;,H;,y,|",  # 6
    "|HH;HhHhHhGhHhHhH,hH|",  # 7   gate at (10,7)
    "|hH,hHh,......,hH,hH|",  # 8
    "|Hh;HhH,.S....,Hh;Hh|",  # 9   central clearing; garden notice (9,9)
    "|hH,hH,.......;hH,hH|",  # 10
    "|,;,,,,.......,,;,,;|",  # 11  west & east paths
    "|HhHhH;.......,hHhHh|",  # 12
    "|hHhHhH;,....;HhHhHh|",  # 13
    "|HhHhHhHh,..HhHhHhHh|",  # 14
    "|b,B;bhHh;..hHhHhHhH|",  # 15  SW blue clearing
    "|,;,b,hHh,..HhHhHhHh|",  # 16
    "|;,b,;,,,;..hHhHhHhH|",  # 17  path to the blue beds; Caroline (3,17)
    "|B,;,b,hHh..HhHhHhHh|",  # 18
    "|,b;B,;hHh..hHhHhHhH|",  # 19
    "|hHhHhHhH;..;HhHhHhH|",  # 20
    "|HhHhH,;,.....;,;hHh|",  # 21
    "|hHhH;,Z,.....,Z,;Hh|",  # 22
    "|HhHh,;z;.....;z,;hH|",  # 23
    "|hHh;,;,.......;,,Hh|",  # 24
    "|Hh;,,,,.123.,,;,;hH|",  # 25
    "_____________________",  # 26
]


def main():
    names = build_tileset()
    n = lambda k: names[k]
    write_metatile_defs('data/maps/EternaCity_Gym_sinnoh', 'EternaGym', names)
    legend = {
        ',': (0x204, 0, 3), ';': (0x205, 0, 3), 'h': (0x210, 1, 3), 'H': (0x217, 1, 3),
        '.': (0x226, 0, 3), '|': (0x221, 1, 0), '_': (0x200, 1, 0),
        'r': (n('flowers_r'), 0, 3), 'y': (n('flowers_y'), 0, 3), 'b': (n('flowers_b'), 0, 3),
        'R': (n('planter_r'), 1, 3), 'Y': (n('planter_y'), 1, 3), 'B': (n('planter_b'), 1, 3),
        'G': (n('gate_closed'), 1, 3), 's': (n('sign'), 1, 3), 'S': (n('sign_sand'), 1, 3),
        'Z': (0x236, 0, 3), 'z': (0x237, 1, 3),
        '1': (0x230, 0, 3), '2': (0x231, 0, 3), '3': (0x232, 0, 3),
        'a': (0x212, 1, 0), 'b0': (0x213, 1, 0), 'c': (0x206, 1, 0), 'd': (0x207, 1, 0), 'e': (0x214, 1, 0),
        'f': (0x215, 1, 0), 'A': (0x219, 1, 0), 'C': (0x21a, 1, 0), 'D': (0x20e, 1, 0), 'E': (0x20f, 1, 0),
        'F': (0x21b, 1, 0), 'I': (0x21c, 1, 0), 'L': (0x233, 1, 0), 'X': (0x201, 1, 0), 'V': (0x202, 1, 0),
        'W': (0x203, 1, 0),
        'gl': (n('glass_l'), 1, 0), 'gr': (n('glass_r'), 1, 0), 'k': (n('soil'), 0, 3), 'k2': (n('soil2'), 0, 3),
    }
    W = len(PLAN[0])
    rows = [list(r) for r in PLAN]
    top0 = ['a', 'b0'] + ['c', 'c', 'd', 'd'] * 5
    top0 = top0[:W - 2] + ['e', 'f']
    top0[W // 2] = 'L'
    top1 = ['A', 'C'] + ['D', 'D', 'E', 'E'] * 5
    top1 = top1[:W - 2] + ['F', 'I']
    rows[0], rows[1] = top0, top1
    rows[26][9:12] = ['X', 'V', 'W']
    for y in range(2, 26):                       # glass walls instead of the plain side walls
        if rows[y][0] == '|': rows[y][0] = 'gl'
        if rows[y][W - 1] == '|': rows[y][W - 1] = 'gr'
    for x, y in ((1, 11), (2, 11), (3, 11), (4, 11), (16, 11), (17, 11), (18, 11), (19, 11),
                 (1, 24), (2, 24), (17, 24), (18, 24), (4, 25), (5, 25), (6, 25), (14, 25), (15, 25), (16, 25)):
        if rows[y][x] in ',;':                   # cultivation beds along the paths
            rows[y][x] = 'k' if (x + y) % 2 else 'k2'
    keymap = {}
    out = []
    for r in rows:
        line = ''
        for k in r:
            if k not in keymap:
                keymap[k] = chr(0x100 + len(keymap))
            line += keymap[k]
        out.append(line)
    leg = {keymap[k]: v for k, v in legend.items() if k in keymap}
    assert all(k in legend for k in keymap), [k for k in keymap if k not in legend]
    build_map(LAYOUT, out, leg, border=0x200)
    d = json.load(open(MAP))
    d['warp_events'] = [{'x': x, 'y': 25, 'elevation': 0, 'dest_map': 'MAP_ETERNA_CITY_SINNOH', 'dest_warp_id': '2'}
                        for x in (9, 10, 11)]
    pos = {
        'EternaCity_Gym_EventScript_Angela': (3, 4, 'MOVEMENT_TYPE_FACE_DOWN', '3'),
        'EternaCity_Gym_EventScript_Jenna': (17, 4, 'MOVEMENT_TYPE_FACE_DOWN', '3'),
        'EternaCity_Gym_EventScript_Caroline': (3, 17, 'MOVEMENT_TYPE_FACE_RIGHT', '3'),
        'SE_EventScript_SinnohLeader_Gardenia': (10, 4, 'MOVEMENT_TYPE_FACE_DOWN', '0'),
        'EternaCity_Gym_EventScript_Guide': (13, 24, 'MOVEMENT_TYPE_FACE_DOWN', '0'),
    }
    for o in d['object_events']:
        x, y, mv, s = pos[o['script']]
        o['x'], o['y'], o['movement_type'], o['elevation'] = x, y, mv, 3
        if o['trainer_type'] != 'TRAINER_TYPE_NONE':
            o['trainer_sight_or_berry_tree_id'] = s
    any_ = 'BG_EVENT_PLAYER_FACING_ANY'
    d['bg_events'] = [
        {'type': 'sign', 'x': 7, 'y': 23, 'elevation': 0, 'player_facing_dir': any_, 'script': 'EternaCity_Gym_EventScript_GymStatue'},
        {'type': 'sign', 'x': 15, 'y': 23, 'elevation': 0, 'player_facing_dir': any_, 'script': 'EternaCity_Gym_EventScript_GymStatue'},
        {'type': 'sign', 'x': 9, 'y': 9, 'elevation': 0, 'player_facing_dir': any_, 'script': 'EternaCity_Gym_EventScript_GardenNotice'},
    ]
    d['coord_events'] = []
    open(MAP, 'w').write(json.dumps(d, indent=2, ensure_ascii=False) + '\n')


if __name__ == '__main__':
    main()
