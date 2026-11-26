#!/usr/bin/env python3
"""Super Emerald: Pastoria City Gym (Crasher Wake) - two water tanks, a floodgate and a bridge.

Run from the repo root: python3 tools/sfr/gyms/pastoria.py
Button 1 (4,14) in the lower tank opens the floodgate (8,12) to the upper tank; button 2
(11,6) in the upper tank lowers the bridge (8,5) to WAKE's platform. Both are solved on
foot (the water blocks). States: VAR_TEMP_1 / VAR_TEMP_2, applied again on load.
"""
import json, os, struct, sys
sys.path.insert(0, os.path.dirname(__file__))
from gymkit import Canvas, Tileset, build_map, write_metatile_defs

TS = 'data/tilesets/secondary/pastoria_city_gym_sinnoh'
MAP = 'data/maps/PastoriaCity_Gym_sinnoh/map.json'
LAYOUT = 'LAYOUT_PASTORIA_CITY_GYM_SINNOH'

WATERWORKS = [(0, 0, 0), (24, 28, 40), (72, 84, 104), (120, 136, 156), (176, 188, 204), (228, 234, 240),
              (40, 96, 176), (96, 152, 224), (168, 208, 248), (200, 48, 48), (248, 120, 104), (40, 160, 72),
              (128, 232, 128), (232, 196, 64), (120, 84, 48), (176, 132, 80)]
P = 10
K, MD, M, ML, MH, BD, B, BL, RED, REDL, GRN, GRNL, YEL, WD, W = range(1, 16)
WATER, WALK, DECK = 0x211, 0x21c, 0x205


def gate(open_):
    c = Canvas(0)
    c.rect(0, 0, 1, 15, MD); c.rect(14, 0, 15, 15, MD); c.vline(1, 0, 15, M); c.vline(14, 0, 15, M)
    if not open_:
        c.rect(2, 1, 13, 14, M)
        for y in range(2, 14, 3):
            c.hline(2, 13, y, ML); c.hline(2, 13, y + 1, MD)
        c.rect(6, 6, 9, 9, YEL); c.rect(7, 7, 8, 8, MD)
    else:
        c.rect(2, 0, 13, 2, M); c.hline(2, 13, 2, MD); c.hline(2, 13, 0, ML)     # raised gate edge
    return c


def wall(lamp=None):
    c = Canvas(ML)
    c.hline(0, 15, 0, MH); c.hline(0, 15, 1, ML)
    c.rect(0, 6, 15, 8, B); c.hline(0, 15, 6, BL)
    for x in (0, 8):
        c.vline(x, 2, 15, M)
    c.hline(0, 15, 15, MD)
    if lamp:
        col, hi = (RED, REDL) if lamp == 'off' else (GRN, GRNL)
        c.rect(5, 3, 10, 12, MD); c.rect(6, 4, 9, 11, col); c.rect(7, 5, 8, 7, hi)
    return c


def lamp_post(state):
    """A lamp on a post standing in the water (blocks)."""
    c = Canvas(0)
    col, hi = (RED, REDL) if state == 'off' else (GRN, GRNL)
    c.rect(6, 6, 9, 15, MD); c.vline(7, 6, 15, M)
    c.rect(4, 0, 11, 6, MD); c.rect(5, 1, 10, 5, col); c.rect(6, 2, 7, 3, hi)
    return c


def bridge():
    c = Canvas(0)
    c.rect(2, 0, 13, 15, W)
    for y in range(0, 16, 4):
        c.hline(2, 13, y, WD)
    c.vline(1, 0, 15, MD); c.vline(14, 0, 15, MD)
    return c


def bridge_off():
    """Retracted bridge: just the two rail stubs above the water."""
    c = Canvas(0)
    c.rect(1, 0, 2, 3, MD); c.rect(13, 0, 14, 3, MD)
    c.rect(1, 12, 2, 15, MD); c.rect(13, 12, 14, 15, MD)
    return c


def button(on):
    c = Canvas(0)
    c.rect(2, 2, 13, 13, MD); c.rect(3, 3, 12, 12, M)
    if on:
        c.rect(5, 5, 10, 10, GRN); c.rect(6, 6, 8, 7, GRNL)
    else:
        c.rect(4, 4, 11, 11, RED); c.rect(5, 4, 10, 6, REDL); c.hline(4, 11, 11, MD)
    return c


def build_tileset():
    ts = Tileset(TS)
    p = lambda c: (c, P)
    water = ('mt', WATER, 1)
    cream = struct.unpack_from('<4H', ts.mt, (0x221 - 0x200) * 24 + 8)[2]   # plain cream tile of the walkway
    ts.add('walk', [('mt', WALK, 0), ('raw', [cream] * 4), None])
    walk = ('raw', [cream] * 4)
    ts.add('gate_closed', [walk, p(gate(False)), None])
    ts.add('gate_open', [walk, p(gate(True)), None])
    ts.add('wall', [p(wall()), None, None])
    ts.add('wall_lamp_off', [p(wall('off')), None, None])
    ts.add('wall_lamp_on', [p(wall('on')), None, None])
    ts.add('post_off', [water, p(lamp_post('off')), None])
    ts.add('post_on', [water, p(lamp_post('on')), None])
    ts.add('bridge_off', [water, p(bridge_off()), None])
    ts.add('bridge_on', [water, p(bridge()), None])
    ts.add('button_off', [walk, p(button(False)), None])
    ts.add('button_on', [walk, p(button(True)), None])
    ts.save({P: WATERWORKS})
    return ts.names


# rows 0-2: the original top wall; D deck, ~ water (blocks), w walkway, W divider wall,
# G floodgate, l/r gate lamps, b bridge slot, p/q bridge lamps, 1/2 buttons,
# Z statue top, z statue base, m exit mat, _ bottom wall.
PLAN = [
    None, None, None,
    "|DDDDDDDDDDDDDDD|",  # 3   WAKE (8,3)
    "|DDDDDDDDDDDDDDD|",  # 4   ERICK (5,4) watches (8,4); WALTER (12,4)
    "|~~~~~~pbq~~~~~~|",  # 5   bridge (8,5) between lamp posts (7,5) and (9,5)
    "|~wwwwwwwww2www~|",  # 6   button 2 at (11,6)
    "|~w~~~~~~~~~~~w~|",  # 7
    "|~ww~~~~~~~~~ww~|",  # 8   DAMIAN (3,8) / SAMSON (13,8) watch the side columns
    "|~w~~~~~~~~~~~w~|",  # 9
    "|~wwwwwwwwwwwww~|",  # 10
    "|~~~~~~~w~~~~~~~|",  # 11
    "|WWWWWWlGrWWWWWW|",  # 12  floodgate (8,12) between lamps (7,12) and (9,12)
    "|~~~~~~~w~~~~~~~|",  # 13
    "|~ww1wwwwwwwwww~|",  # 14  button 1 at (4,14), in sight of the floodgate
    "|~w~~~~~~~~~~~w~|",  # 15
    "|~ww~~~~~~~~~ww~|",  # 16  CAITLYN (3,16) / JACKY (13,16) watch the side columns
    "|~w~~~~~~~~~~~w~|",  # 17
    "|~wwwwwwwwwwwww~|",  # 18
    "|~~~~~~~w~~~~~~~|",  # 19
    "|DDDDwwwwwwwDDDD|",  # 20
    "|DDDDwZwwwYwDDDD|",  # 21  statues (6,21) and (10,21)
    "|DDDDwzwwwzwDDDD|",  # 22
    "|DDDDDDmmmDDDDDD|",  # 23  exit mat
    None,                 # 24  bottom wall with the exit
]


def main():
    names = build_tileset()
    n = lambda k: names[k]
    write_metatile_defs('data/maps/PastoriaCity_Gym_sinnoh', 'PastoriaGym', names)
    import struct
    L = json.load(open('data/layouts/layouts.json'))
    lay = [l for l in L['layouts'] if l.get('id') == LAYOUT][0]
    old = open(lay['blockdata_filepath'], 'rb').read()
    ow = lay['width']
    oldrow = lambda y: [struct.unpack_from('<H', old, (y * ow + x) * 2)[0] for x in range(ow)]
    state = json.load(open(TS + '/se_gymkit.json'))
    if 'orig_rows' not in state:      # remember the original top and bottom rows once
        state['orig_rows'] = {'0': oldrow(0), '1': oldrow(1), '2': oldrow(2), 'bottom': oldrow(lay['height'] - 1),
                              'mat': oldrow(lay['height'] - 2)}
        json.dump(state, open(TS + '/se_gymkit.json', 'w'), indent=1)
    rows = state['orig_rows']
    legend = {
        '|': (0x22e, 1, 0), 'D': (DECK, 0, 3), '~': (WATER, 1, 3), 'w': (n('walk'), 0, 3), 's': (0x23a, 1, 3),
        'W': (n('wall'), 1, 0), 'G': (n('gate_closed'), 1, 3), 'l': (n('wall_lamp_off'), 1, 0),
        'r': (n('wall_lamp_off'), 1, 0), 'b': (n('bridge_off'), 1, 3), 'p': (n('post_off'), 1, 3),
        'q': (n('post_off'), 1, 3), '1': (n('button_off'), 0, 3), '2': (n('button_off'), 0, 3),
        'Z': (0x24a, 0, 3), 'Y': (0x24b, 0, 3), 'z': (0x24c, 1, 3),
    }
    W = 17
    out = []
    keymap = {}

    def raw(vals):
        line = ''
        for v in vals:
            k = ('raw', v)
            if k not in keymap:
                keymap[k] = chr(0x100 + len(keymap))
                legend[keymap[k]] = (v & 0x3FF, (v >> 10) & 3, v >> 12)
            line += keymap[k]
        return line
    plan = [r for r in PLAN]
    for y in range(4, len(plan)):         # shade the water just below a walkway or deck
        if plan[y] is None or plan[y - 1] is None:
            continue
        plan[y] = ''.join('s' if c == '~' and plan[y - 1][x] in 'wD12G' else c for x, c in enumerate(plan[y]))
    for y, r in enumerate(plan):
        if r is None:
            src = rows[str(y)] if y < 3 else rows['bottom']
            out.append(raw(src))
            continue
        r = r[:16] + '|'
        line = ''
        for x, ch in enumerate(r):
            if ch == 'm':
                line += raw([rows['mat'][x]])
            elif ch == '|' and x == 16:
                line += raw([0x062f])
            else:
                line += ch
        out.append(line)
    build_map(LAYOUT, out, legend, border=0x201)
    d = json.load(open(MAP))
    d['warp_events'] = [{'x': x, 'y': 23, 'elevation': 0, 'dest_map': 'MAP_PASTORIA_CITY_SINNOH', 'dest_warp_id': '1'}
                        for x in (7, 8, 9)]
    pos = {
        'PastoriaCity_Gym_EventScript_Caitlyn': (3, 16, 'MOVEMENT_TYPE_FACE_LEFT', '1'),
        'PastoriaCity_Gym_EventScript_Jacky': (13, 16, 'MOVEMENT_TYPE_FACE_RIGHT', '1'),
        'PastoriaCity_Gym_EventScript_Damian': (3, 8, 'MOVEMENT_TYPE_FACE_LEFT', '1'),
        'PastoriaCity_Gym_EventScript_Samson': (13, 8, 'MOVEMENT_TYPE_FACE_RIGHT', '1'),
        'PastoriaCity_Gym_EventScript_Erick': (5, 4, 'MOVEMENT_TYPE_FACE_RIGHT', '3'),
        'PastoriaCity_Gym_EventScript_Walter': (12, 4, 'MOVEMENT_TYPE_FACE_LEFT', '2'),
        'SE_EventScript_SinnohLeader_Wake': (8, 3, 'MOVEMENT_TYPE_FACE_DOWN', '0'),
        'PastoriaCity_Gym_EventScript_PtGymGuide': (11, 22, 'MOVEMENT_TYPE_FACE_DOWN', '0'),
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
        {'type': 'trigger', 'x': 4, 'y': 14, 'elevation': 3, 'var': 'VAR_TEMP_1', 'var_value': '0',
         'script': 'PastoriaCity_Gym_EventScript_Button1'},
        {'type': 'trigger', 'x': 11, 'y': 6, 'elevation': 3, 'var': 'VAR_TEMP_2', 'var_value': '0',
         'script': 'PastoriaCity_Gym_EventScript_Button2'},
    ]
    open(MAP, 'w').write(json.dumps(d, indent=2, ensure_ascii=False) + '\n')


if __name__ == '__main__':
    main()
