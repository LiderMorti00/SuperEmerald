#!/usr/bin/env python3
"""Super Emerald: Sunyshore City Gym (Volkner) - electric walkways over the dark, two switch sectors.

Run from the repo root: python3 tools/sfr/gyms/sunyshore.py
Sector 1 (switch console at 7,18, by the entrance): toggles the barriers at (3,17) and
(11,16). State 0 = left walkway on (to a side platform), right walkway off; state 1 = the
right walkway on (up to the hub), left off. Stored in VAR_SE_SUNYSHORE_GYM_STATE.
Sector 2 (console at 12,12, on the hub): toggles (4,10) and (9,9). Clear = side path on,
VOLKNER's walkway off; set = VOLKNER's walkway on, side path off. FLAG_SE_SUNYSHORE_GYM_BARRIERS.
Both consoles are on ground that never depends on their own switch, so they stay reachable.
The console lamps show which side is live; scripts.inc reapplies both states on load.
"""
import json, os, sys
sys.path.insert(0, os.path.dirname(__file__))
from gymkit import Canvas, Tileset, build_map, write_metatile_defs

TS = 'data/tilesets/secondary/mauville_gym_sinnoh'
MAP = 'data/maps/SunyshoreCity_Gym_sinnoh/map.json'
LAYOUT = 'LAYOUT_SUNYSHORE_CITY_GYM_SINNOH'
P = 10
VOLT = [(0, 0, 0), (12, 12, 20), (44, 48, 64), (88, 96, 120), (144, 152, 176), (208, 216, 232),
        (248, 248, 248), (248, 224, 64), (200, 160, 24), (96, 232, 255), (32, 160, 232), (64, 216, 96),
        (24, 120, 56), (232, 72, 64), (128, 32, 32), (255, 255, 160)]
K, D, M, L, H, W, Y, YD, C, CD, G, GD, R, RD, YL = range(1, 16)
FLOOR, VOID = 0x20a, 0x001


P2 = 11
SEA = [(0, 0, 0), (10, 18, 34), (18, 32, 58), (30, 52, 88), (52, 84, 128), (36, 40, 48), (62, 68, 80),
       (96, 104, 118), (150, 158, 172), (210, 216, 226), (232, 196, 40), (24, 24, 28), (240, 130, 40),
       (150, 70, 20), (90, 200, 250), (30, 110, 170)]
NV1, NV2, NV3, NV4, PD, PM, PL, PH, PW, YS, BK, OR, ORD, CY, CYD = range(1, 16)
CABLE = {1: (OR, ORD), 2: (CY, CYD)}


def plate(edges, grate=False):
    """Dark metal walkway; light trim where it meets the void, grating on the narrow catwalks."""
    c = Canvas(PM)
    if grate:
        for y in range(16):
            for x in range(16):
                c.px(x, y, PD if (x % 4 == 0 or y % 4 == 0) else NV2 if (x + y) % 2 else PM)
    else:
        for y in (0, 8):
            c.hline(0, 15, y, PD)
        c.vline(7, 1, 7, PD); c.vline(15, 9, 15, PD)
        for x, y in ((2, 2), (12, 2), (5, 11), (10, 13)):
            c.px(x, y, PL)
    trim = {'n': lambda i: (i, 0), 's': lambda i: (i, 15), 'w': lambda i: (0, i), 'e': lambda i: (15, i)}
    inner = {'n': lambda i: (i, 1), 's': lambda i: (i, 14), 'w': lambda i: (1, i), 'e': lambda i: (14, i)}
    for e in edges:
        for i in range(16):
            c.px(*trim[e](i), PW); c.px(*inner[e](i), PH)
    return c


def stripes(c, y0, y1):
    for y in range(y0, y1 + 1):
        for x in range(16):
            c.px(x, y, YS if ((x + y) // 2) % 2 == 0 else BK)
    return c


def sea():
    c = Canvas(NV1)
    for x, y in ((2, 3), (3, 3), (9, 6), (10, 6), (11, 6), (5, 11), (6, 11), (13, 13), (14, 13)):
        c.px(x, y, NV3)
    c.px(10, 5, NV2); c.px(4, 10, NV2)
    return c


def cable(dirs, sector, base=None):
    """A power cable from this tile's centre towards each direction in dirs."""
    c = base.copy() if base else sea()
    col, dk = CABLE[sector]
    if 'n' in dirs: c.rect(6, 0, 9, 9, dk); c.rect(7, 0, 8, 9, col)
    if 's' in dirs: c.rect(6, 6, 9, 15, dk); c.rect(7, 6, 8, 15, col)
    if 'w' in dirs: c.rect(0, 6, 9, 9, dk); c.rect(0, 7, 9, 8, col)
    if 'e' in dirs: c.rect(6, 6, 15, 9, dk); c.rect(6, 7, 15, 8, col)
    for x in (1, 13):
        if 'w' in dirs or 'e' in dirs:
            if c.p[7][x] == col: c.px(x, 6, PH); c.px(x, 9, PH)       # clamps
    return c


def gate(on, sector):
    """Barrier across a north-south catwalk. Shut: tall pylons with a crackling field and a red bar.
    Open: the pylons sink into the floor, the field is gone and green chevrons point the way."""
    c = Canvas(0)
    col, dk = CABLE[sector]
    if on:
        for x0 in (0, 12):
            c.rect(x0, 0, x0 + 3, 15, PD); c.rect(x0 + 1, 0, x0 + 2, 15, PL); c.rect(x0, 0, x0 + 3, 2, col)
        for y in range(2, 14, 4):
            for x in range(4, 12):
                c.px(x, y + (x % 3 == 0), CY); c.px(x, y + 1 + (x % 2), PW)
        c.rect(4, 7, 11, 8, OR)
    else:
        for x0 in (0, 12):
            c.rect(x0, 6, x0 + 3, 9, PD); c.rect(x0 + 1, 7, x0 + 2, 8, col)
        for y0 in (3, 9):
            for i in range(4):
                c.px(5 + i, y0 + i, PW); c.px(10 - i, y0 + i, PW)
    return c


def console(state, sector):
    c = Canvas(0)
    col, dk = CABLE[sector]
    c.rect(1, 1, 14, 15, PD); c.rect(2, 2, 13, 13, PM); c.hline(1, 14, 1, PL); c.hline(1, 14, 15, BK)
    c.rect(2, 2, 13, 3, col)                               # sector colour band
    for x0, live in ((3, state == 0), (10, state == 1)):
        c.rect(x0, 5, x0 + 2, 7, CY if live else ORD); c.px(x0, 5, PW if live else OR)
    c.rect(6, 10, 9, 13, BK)
    if state == 0:
        c.rect(4, 9, 7, 10, PH); c.rect(3, 9, 4, 10, YS)
    else:
        c.rect(8, 9, 11, 10, PH); c.rect(11, 9, 12, 10, YS)
    c.rect(7, 10, 8, 12, PL)
    c.vline(7, 14, 15, col); c.vline(8, 14, 15, dk)     # cable out of the bottom
    return c


def build_tileset(walk_kinds, cables):
    ts = Tileset(TS)
    live = set()
    b = open('data/layouts/SunyshoreCity_Gym_sinnoh/map.bin', 'rb').read()
    print('free tile slots:', ts.free_unused({0x216, 0x21e, 0x212, 0x213, 0x24a, 0x24b, 0x207, 0x20d, 0x20e,
                                               0x252, 0x253, 0x20f}))
    for kind in sorted(walk_kinds):
        grate, edges, stripe = kind
        c = plate(edges, grate)
        if stripe:
            stripes(c, 12, 15)
        ts.add('walk_%s%s%s' % ('g' if grate else 'p', edges or '0', '_y' if stripe else ''), [(c, P2), None, None])
    ts.add('sea', [(sea(), P2), None, None])
    ts.replace(0x216, [(plate('', False), P2), None, ('mt', 0x216, 2)])      # statues stand on metal now
    ts.replace(0x21e, [(plate('', False), P2), ('mt', 0x21e, 1), None])
    for (dirs, sector, on_walk) in sorted(cables):
        base = plate('we', True) if on_walk else None
        ts.add('cable%d_%s%s' % (sector, dirs, '_w' if on_walk else ''), [(cable(dirs, sector, base), P2), None, None])
    for sector in (1, 2):
        g = ('mt', 0, 0)
        for on in (True, False):
            ts.add('gate%d_%s' % (sector, 'on' if on else 'off'), [(plate('we', True), P2), (gate(on, sector), P2), None])
        for st in (0, 1):
            ts.add('console%d_%d' % (sector, st), [(sea(), P2), (console(st, sector), P2), None])
    pals = {P2: SEA}
    import colorsys
    for slot in (6, 7):                   # purple walls of VOLKNER's room -> steel blue
        cols = []
        for i, (r, g, bb) in enumerate(ts.orig_pal(slot)):
            h, sat, v = colorsys.rgb_to_hsv(r / 255, g / 255, bb / 255)
            if i and sat > 0.08 and 0.70 < h < 0.95:
                h, sat = 0.60, min(sat, 0.30)
                r, g, bb = (round(x * 255) for x in colorsys.hsv_to_rgb(h, sat, v))
            cols.append((r, g, bb))
        pals[slot] = cols
    ts.save(pals)
    return ts.names


# '#' dark void, '.' walkway, G gate (drawn in state 0: '+' open, 'x' shut), 1/2 consoles,
# T statue top, t statue base, m exit mat. Walls of VOLKNER's room use the original tiles.
PLAN = [
    "#####ABBCDBBE##",   # 0  wall top (C D = emblem)
    "#####FGGHIGGJ##",   # 1  wall face
    "#####K......N##",   # 2  VOLKNER (9,2)
    "#####K......N##",   # 3
    "#####K......N##",   # 4
    "#####K......N##",   # 5
    "#.....###.#####",   # 6  side platform x1-5 rows 6-8; VOLKNER's walkway x9
    "#.....###..####",   # 7  ZACHERY alcove (10,7)
    "#.....###.#####",   # 8
    "####.####x#####",   # 9  sector-2 gate to VOLKNER (9,9), shut in state 0
    "####+####.#####",   # 10 sector-2 gate to the side path (4,10), open in state 0
    "####.####.#####",   # 11
    "####........2##",   # 12 hub x4-11, console 2 (12,12)
    "#####.####..###",   # 13 DESTINY alcove (5,13), JERRY alcove (10,13); right walkway x11
    "#....######..##",   # 14 left platform x1-4 rows 14-15; LONNIE alcove (12,14)
    "#....######.###",   # 15
    "###.#######x###",   # 16 sector-1 gate on the right walkway (11,16), shut in state 0
    "###+#######.###",   # 17 sector-1 gate on the left walkway (3,17), open in state 0
    "###.###1###.###",   # 18 console 1 (7,18)
    "###..T....T..##",   # 19 entrance hall x3-11, statues (5,19) and (10,19)
    "###.Pt....t..##",   # 20 guide (4,20)
    "#######mm######",   # 21 exit mat (7,21),(8,21)
]


WALKABLE = set('.PxT+')
CABLES = {   # (x, y): (dirs, sector)
    (6, 18): ('we', 1), (5, 18): ('we', 1), (4, 18): ('ne', 1), (4, 17): ('sw', 1),
    (8, 18): ('we', 1), (9, 18): ('we', 1), (10, 18): ('nw', 1), (10, 17): ('ns', 1), (10, 16): ('se', 1),
    (12, 11): ('nsw', 2), (11, 11): ('we', 2), (10, 11): ('we', 2), (9, 11): ('we', 2), (8, 11): ('we', 2),
    (7, 11): ('we', 2), (6, 11): ('we', 2), (5, 11): ('ne', 2), (5, 10): ('sw', 2),
    (12, 10): ('ns', 2), (12, 9): ('sw', 2), (11, 9): ('we', 2), (10, 9): ('we', 2),
}
STRIPES = {(7, 19), (11, 12), (3, 16), (3, 18), (11, 15), (11, 17), (4, 9), (4, 11), (9, 8), (9, 10)}


def main():
    plan = [list(r) for r in PLAN]
    H, W = len(plan), len(plan[0])
    ok = lambda x, y: 0 <= x < W and 0 <= y < H and plan[y][x] in WALKABLE | set('1mM2Tt')
    kinds, cells = set(), {}
    for y in range(H):
        for x in range(W):
            if plan[y][x] in '.P' and (x, y) not in CABLES:
                edges = ''.join(e for e, (dx, dy) in (('n', (0, -1)), ('s', (0, 1)), ('w', (-1, 0)), ('e', (1, 0)))
                                if not ok(x + dx, y + dy))
                grate = 'w' in edges and 'e' in edges
                k = (grate, edges, (x, y) in STRIPES)
                kinds.add(k); cells[(x, y)] = k
    cab = {(d, sec, plan[y][x] in '.P') for (x, y), (d, sec) in CABLES.items()}
    names = build_tileset(kinds, cab)
    n = lambda k: names[k]
    write_metatile_defs('data/maps/SunyshoreCity_Gym_sinnoh', 'SunyshoreGym', names)
    legend = {
        '#': (n('sea'), 1, 0), 'x': (n('gate1_on'), 1, 3), '+': (n('gate1_off'), 0, 3),
        'X': (n('gate2_on'), 1, 3), '=': (n('gate2_off'), 0, 3),
        '1': (n('console1_0'), 1, 3), '2': (n('console2_0'), 1, 3),
        'T': (0x216, 0, 3), 't': (0x21e, 1, 3), 'm': (0x006, 0, 3), 'M': (0x007, 0, 3),
        'A': (0x212, 1, 0), 'B': (0x213, 1, 0), 'C': (0x24a, 1, 0), 'D': (0x24b, 1, 0), 'E': (0x207, 1, 0),
        'F': (0x20d, 1, 0), 'G': (0x20e, 1, 0), 'H': (0x252, 1, 0), 'I': (0x253, 1, 0), 'J': (0x20f, 1, 0),
        'K': (0x20d, 1, 0), 'N': (0x20f, 1, 0),
    }
    plan[9][9] = 'X'; plan[10][4] = '='          # sector-2 gates
    plan[21][8] = 'M'
    out = []
    for y in range(H):
        line = ''
        for x in range(W):
            ch = plan[y][x]
            if (x, y) in CABLES:
                d_, sec = CABLES[(x, y)]
                key = 'cable%d_%s%s' % (sec, d_, '_w' if ch in '.P' else '')
                ch2 = chr(0x100 + len(legend)); legend[ch2] = (n(key), 0 if ch in '.P' else 1, 3 if ch in '.P' else 0)
                ch = ch2
            elif (x, y) in cells:
                grate, edges, st = cells[(x, y)]
                key = 'walk_%s%s%s' % ('g' if grate else 'p', edges or '0', '_y' if st else '')
                ch2 = chr(0x100 + len(legend)); legend[ch2] = (n(key), 0, 3)
                ch = ch2
            line += ch
        out.append(line)
    build_map(LAYOUT, out, legend, border=n('sea'))

    d = json.load(open(MAP))
    d['warp_events'] = [{'x': x, 'y': 21, 'elevation': 0, 'dest_map': 'MAP_SUNYSHORE_CITY_SINNOH', 'dest_warp_id': '8'}
                        for x in (7, 8)]
    pos = {
        'SunyshoreCity_Gym_EventScript_Meghan': (1, 15, 'MOVEMENT_TYPE_FACE_RIGHT', '3'),   # left platform
        'SunyshoreCity_Gym_EventScript_Forrest': (4, 14, 'MOVEMENT_TYPE_FACE_LEFT', '3'),
        'SunyshoreCity_Gym_EventScript_Lonnie': (12, 14, 'MOVEMENT_TYPE_FACE_LEFT', '1'),   # right walkway
        'SunyshoreCity_Gym_EventScript_Destiny': (5, 13, 'MOVEMENT_TYPE_FACE_UP', '1'),     # hub, west
        'SunyshoreCity_Gym_EventScript_Jerry': (10, 13, 'MOVEMENT_TYPE_FACE_UP', '1'),      # hub, east
        'SunyshoreCity_Gym_EventScript_Preston': (2, 7, 'MOVEMENT_TYPE_FACE_RIGHT', '2'),   # side platform
        'SunyshoreCity_Gym_EventScript_Tiera': (5, 6, 'MOVEMENT_TYPE_FACE_DOWN', '2'),
        'SunyshoreCity_Gym_EventScript_Zachery': (10, 7, 'MOVEMENT_TYPE_FACE_LEFT', '1'),   # VOLKNER's walkway
        'SE_EventScript_SinnohLeader_Volkner': (9, 2, 'MOVEMENT_TYPE_FACE_DOWN', '0'),
        'SunyshoreCity_Gym_EventScript_PtGymGuide': (4, 20, 'MOVEMENT_TYPE_FACE_RIGHT', '0'),
    }
    for o in d['object_events']:
        x, y, mv, s = pos[o['script']]
        o['x'], o['y'], o['movement_type'], o['elevation'] = x, y, mv, 3
        if o['trainer_type'] != 'TRAINER_TYPE_NONE':
            o['trainer_sight_or_berry_tree_id'] = s
    any_ = 'BG_EVENT_PLAYER_FACING_ANY'
    sign = lambda x, y, s: {'type': 'sign', 'x': x, 'y': y, 'elevation': 0, 'player_facing_dir': any_,
                            'script': 'SunyshoreCity_Gym_EventScript_' + s}
    d['bg_events'] = [sign(5, 20, 'PtGymStatue'), sign(10, 20, 'PtGymStatue'),
                      sign(7, 18, 'Console1'), sign(12, 12, 'Console2')]
    d['coord_events'] = []
    open(MAP, 'w').write(json.dumps(d, indent=2, ensure_ascii=False) + '\n')


if __name__ == '__main__':
    main()
