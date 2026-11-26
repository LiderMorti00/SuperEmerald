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


def gate(on):
    """Barrier across a north-south walkway; posts at both sides. On = blocks."""
    c = Canvas(0)
    for x0 in (0, 13):
        c.rect(x0, 2, x0 + 2, 13, D); c.vline(x0 + 1, 2, 13, M); c.rect(x0, 1, x0 + 2, 3, H if on else M)
        c.rect(x0, 1, x0 + 2, 2, C if on else L)
    if on:
        import random
        rnd = random.Random(7)
        for y0 in (4, 8, 11):
            y = y0
            for x in range(3, 13):
                y = max(y0 - 1, min(y0 + 1, y + rnd.choice((-1, 0, 1))))
                c.px(x, y, W); c.px(x, y + 1, C); c.px(x, y - 1, CD)
    else:
        c.hline(3, 12, 14, M)            # cold rail on the floor
    return c


def console(state):
    """Switch console: two lamps (left / right connection) and a lever pointing at the live side."""
    c = Canvas(0)
    c.rect(1, 2, 14, 15, D); c.rect(2, 3, 13, 14, M); c.hline(1, 14, 2, L); c.hline(1, 14, 15, K)
    for x0, live in ((3, state == 0), (10, state == 1)):
        c.rect(x0, 4, x0 + 2, 6, G if live else RD); c.px(x0, 4, W if live else R)
    c.rect(6, 10, 9, 13, K)
    if state == 0:
        c.rect(4, 8, 7, 9, H); c.rect(3, 8, 4, 9, Y)
    else:
        c.rect(8, 8, 11, 9, H); c.rect(11, 8, 12, 9, Y)
    c.rect(7, 9, 8, 11, L)
    return c


def build_tileset():
    ts = Tileset(TS)
    floor = ('mt', FLOOR, 1)
    ts.add('gate_on', [floor, (gate(True), P), None])
    ts.add('gate_off', [floor, (gate(False), P), None])
    ts.add('console0', [floor, (console(0), P), None])
    ts.add('console1', [floor, (console(1), P), None])
    ts.save({P: VOLT})
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


def main():
    names = build_tileset()
    n = lambda k: names[k]
    write_metatile_defs('data/maps/SunyshoreCity_Gym_sinnoh', 'SunyshoreGym', names)
    legend = {
        '#': (VOID, 1, 0), '.': (FLOOR, 0, 3), 'P': (FLOOR, 0, 3),
        'x': (n('gate_on'), 1, 3), '+': (n('gate_off'), 0, 3),
        '1': (n('console0'), 1, 3), '2': (n('console0'), 1, 3),
        'T': (0x216, 0, 3), 't': (0x21e, 1, 3), 'm': (0x006, 0, 3), 'M': (0x007, 0, 3),
        'A': (0x212, 1, 0), 'B': (0x213, 1, 0), 'C': (0x24a, 1, 0), 'D': (0x24b, 1, 0), 'E': (0x207, 1, 0),
        'F': (0x20d, 1, 0), 'G': (0x20e, 1, 0), 'H': (0x252, 1, 0), 'I': (0x253, 1, 0), 'J': (0x20f, 1, 0),
        'K': (0x20d, 1, 0), 'N': (0x20f, 1, 0),
    }
    plan = [r for r in PLAN]
    plan[21] = plan[21].replace('mm', 'mM')
    for r in plan:
        assert len(r) == 15, r
    build_map(LAYOUT, plan, legend, border=VOID)

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
