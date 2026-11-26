#!/usr/bin/env python3
"""Super Emerald: Hearthome City Gym (Fantina) - three symbol-door rooms and Fantina's hall.

Run from the repo root: python3 tools/sfr/gyms/hearthome.py
Rebuilds the gym's new metatiles (palettes 10-11 of its tileset), map.bin and map.json
warps/objects/bg events. Scripts live in data/maps/HearthomeCity_Gym_sinnoh/scripts.inc.
"""
import json, os, sys
sys.path.insert(0, os.path.dirname(__file__))
from gymkit import Canvas, Tileset, build_map

TS = 'data/tilesets/secondary/hearthome_city_gym_sinnoh'
MAP = 'data/maps/HearthomeCity_Gym_sinnoh/map.json'
LAYOUT = 'LAYOUT_HEARTHOME_CITY_GYM_SINNOH'

# ------------------------------------------------------------------ palettes
GHOST = [(0, 0, 0), (20, 14, 32), (46, 34, 70), (70, 54, 104), (98, 80, 140), (122, 102, 166),
         (176, 160, 214), (236, 228, 250), (58, 22, 42), (104, 36, 66), (156, 62, 96),
         (160, 116, 48), (228, 188, 92), (248, 136, 40), (252, 234, 140), (112, 220, 200)]
SYMB = GHOST[:8] + [(206, 50, 66), (248, 118, 124), (60, 96, 220), (132, 172, 255),
                    (228, 188, 92), (58, 164, 90), (140, 226, 146), (204, 204, 222)]
PG, PS = 10, 11
K1, K2, K3, K4, K5, K6, K7 = 1, 2, 3, 4, 5, 6, 7
MD, MM, ML, GD, GL, FO, FY, TEAL = 8, 9, 10, 11, 12, 13, 14, 15
# symbol palette
RED, REDL, BLU, BLUL, GOLD, GRN, GRNL, SIL = 8, 9, 10, 11, 12, 13, 14, 15


def floor(shadow=0):
    c = Canvas(K2)
    for y in range(16):
        for x in range(16):
            if x % 8 == 0 or y % 8 == 0:
                c.px(x, y, K1)
            elif x % 8 == 1 or y % 8 == 1:
                c.px(x, y, K3)
    # little cracks
    c.px(5, 4, K1); c.px(12, 12, K1); c.px(13, 13, K1); c.px(4, 11, K3)
    for y in range(shadow):
        for x in range(16):
            if c.p[y][x] != K1:
                c.p[y][x] = K1 if y < shadow - 2 else K2
    return c


def carpet(edge=None):
    c = Canvas(MM)
    for y in range(16):
        for x in range(16):
            if (x + y) % 8 == 0:
                c.px(x, y, ML)
            if (x - y) % 8 == 4:
                c.px(x, y, MD)
    if edge in ('l', 'lr'):
        c.vline(0, 0, 15, GD); c.vline(1, 0, 15, GL)
    if edge in ('r', 'lr'):
        c.vline(15, 0, 15, GD); c.vline(14, 0, 15, GL)
    return c


def wall_top():
    c = Canvas(K1)
    c.hline(0, 15, 13, K2); c.hline(0, 15, 14, K4); c.hline(0, 15, 15, K2)
    return c


def wallpaper():
    c = Canvas(K3)
    for x in range(0, 16, 4):
        c.vline(x, 0, 15, K2)
        c.vline(x + 2, 0, 15, K4)
    for y in (3, 11):
        for x in range(1, 16, 4):
            c.px(x, y, K5); c.px(x, y + 1, K4)
    c.hline(0, 15, 0, K1); c.hline(0, 15, 1, K2)
    return c


def wainscot():
    c = Canvas(MM)
    c.hline(0, 15, 0, GD); c.hline(0, 15, 1, GL); c.hline(0, 15, 2, GD)
    c.rect(2, 5, 13, 11, MD); c.rect(3, 6, 12, 10, MM); c.hline(3, 12, 6, ML)
    c.vline(0, 3, 13, MD); c.vline(15, 3, 13, MD)
    c.hline(0, 15, 13, K1); c.hline(0, 15, 14, K1); c.hline(0, 15, 15, K2)
    return c


def side_wall(right=False):
    c = Canvas(K1)
    c.vline(14, 0, 15, K2); c.vline(15, 0, 15, K4)
    return c.flip_h() if not right else c


def corner(kind):
    c = Canvas(K1)
    return c


def bottom_wall():
    c = Canvas(K1)
    c.hline(0, 15, 0, K4); c.hline(0, 15, 1, K2)
    return c


def door_north():
    """Arched opening in the wainscot row; walking up into it warps."""
    c = wainscot()
    c.rect(2, 0, 13, 15, GD)
    c.rect(3, 1, 12, 15, GL)
    c.rect(4, 2, 11, 15, K1)
    c.rect(5, 3, 10, 15, 0 if False else K1)
    for x in range(4, 12):
        c.px(x, 2, K2)
    c.hline(4, 11, 14, K2); c.hline(4, 11, 15, K3)
    return c


def door_north_top():
    """Wallpaper with the top of the arch, under the symbol plaque."""
    c = wallpaper()
    c.rect(3, 12, 12, 15, GD)
    c.rect(4, 13, 11, 15, GL)
    c.rect(5, 14, 10, 15, K1)
    return c


def door_south():
    """Gap in the south wall: floor fading into darkness, walking down warps."""
    c = floor()
    for y in range(16):
        for x in range(16):
            if y > 8:
                c.p[y][x] = K1 if y > 12 else (K2 if c.p[y][x] != K1 else K1)
    c.vline(0, 0, 15, K4); c.vline(15, 0, 15, K4)
    return c


def plaque(sym):
    """Wallpaper with a framed symbol plaque (symbol palette)."""
    c = wallpaper()
    c.rect(2, 2, 13, 13, GOLD)
    c.rect(3, 3, 12, 12, K1)
    draw_symbol(c, sym, 3, 3)
    return c


def painting(sym):
    c = wallpaper()
    c.rect(1, 2, 14, 14, GOLD)
    c.rect(2, 3, 13, 13, K2)
    c.hline(2, 13, 13, K1)
    if sym == 'ghost':
        c.art(4, 4, ['..WWWW..', '.WWWWWW.', '.WKWWKW.', '.WWWWWW.', '.WWWWWW.', '.WWWWWW.', '.W.WW.W.', '........'],
              {'W': SIL, 'K': K1})
    else:
        draw_symbol(c, sym, 4, 4)
    return c


SYMBOLS = {
    'star': (['....GG....', '....GG....', '...GGGG...', 'GGGGGGGGGG', '.GGGGGGGG.', '..GGGGGG..',
              '..GGGGGG..', '.GGG..GGG.', '.GG....GG.', '..........'], {'G': GOLD}),
    'moon': (['...BBBB...', '..BBB.....', '.BBB......', '.BBB......', '.BBB......', '.BBB......',
              '..BBB.....', '...BBBB...', '..........', '..........'], {'B': BLUL}),
    'flame': (['....R.....', '....RR....', '...RRR.R..', '..RRYRRR..', '..RRYYRR..', '.RRYYYYRR.',
               '.RRYYYYRR.', '..RRYYRR..', '...RRRR...', '..........'], {'R': RED, 'Y': REDL}),
    'eye': (['..........', '...GGGG...', '.GG....GG.', 'G...GG...G', 'G..GKKG..G', 'G...GG...G',
             '.GG....GG.', '...GGGG...', '..........', '..........'], {'G': GRNL, 'K': K1}),
}


def draw_symbol(c, sym, x0, y0):
    rows, leg = SYMBOLS[sym]
    c.art(x0, y0, rows, leg)


def pedestal_base(sym=None):
    """Floor with a stone pedestal; its front shows a symbol (symbol palette)."""
    c = floor()
    c.rect(3, 0, 12, 13, K4)
    c.rect(4, 0, 11, 12, K5)
    c.hline(2, 13, 13, K4); c.hline(2, 13, 14, K2)
    if sym:
        c.rect(5, 3, 10, 10, K1)
        rows, leg = SYMBOLS[sym]
        small = {'star': ['..G...', '.GGG..', 'GGGGG.', '.G.G..'], 'flame': ['..R...', '.RRR..', '.RYR..', '..R...'],
                 'moon': ['.BB...', 'B.....', 'B.....', '.BB...'], 'eye': ['.GGG..', 'G.K.G.', '.GGG..', '......']}[sym]
        c.art(5, 5, small, {'G': GOLD if sym == 'star' else GRNL, 'R': RED, 'Y': REDL, 'B': BLUL, 'K': K1})
    return c


def candle_top():
    """Candelabra on top of the pedestal (top layer, drawn over the player)."""
    c = Canvas(0)
    c.art(0, 0, ['................',
                 '..F.....F.....F.',
                 '.FYF...FYF...FYF',
                 '..Y.....Y.....Y.',
                 '..W.....W.....W.',
                 '..W.....W.....W.',
                 '..W.....W.....W.',
                 '.GGG...GGG...GGG',
                 '..G.....G.....G.',
                 '..GGGGGGGGGGGGG.',
                 '........G.......',
                 '........G.......',
                 '.......GGG......',
                 '...LLLLLLLLLL...',
                 '...LLLLLLLLLL...',
                 '................'],
          {'F': FO, 'Y': FY, 'W': K7, 'G': GL, 'L': K5})
    return c


def lectern():
    c = Canvas(0)
    c.art(0, 0, ['................',
                 '................',
                 '...WWWWWWWWWW...',
                 '..WPPPPWWPPPPW..',
                 '..WPKKPWWPKKPW..',
                 '..WPPPPWWPPPPW..',
                 '...MMMMMMMMMM...',
                 '......MMMM......',
                 '......MDDM......',
                 '......MDDM......',
                 '......MDDM......',
                 '......MDDM......',
                 '.....MMMMMM.....',
                 '....DDDDDDDD....',
                 '................',
                 '................'],
          {'W': K7, 'P': K6, 'K': K3, 'M': MM, 'D': MD})
    return c


def shadow_ghost():
    c = floor()
    c.art(3, 3, ['..TTTT....', '.TTTTTT...', '.T1TT1T...', '.TTTTTT...', '.TTTTTT...', '.T.TT.T...'],
          {'T': K3, '1': K1})
    return c


def curtain(right=False):
    c = Canvas(0)
    for x in range(16):
        for y in range(16):
            band = (x // 3) % 2
            c.px(x, y, MM if band else MD)
    c.vline(0, 0, 15, K1)
    c.hline(0, 15, 0, GL); c.hline(0, 15, 1, GD)
    return c.flip_h() if right else c


# ------------------------------------------------------------------ tileset
def build_tileset():
    ts = Tileset(TS)
    N = 0x00; DOOR = 0x60; S_ARROW = 0x60
    g = lambda c: (c, PG)
    s = lambda c: (c, PS)
    ts.add('floor', [g(floor()), None, None])
    ts.add('floor_sh', [g(floor(6)), None, None])
    ts.add('floor_ghost', [g(shadow_ghost()), None, None])
    ts.add('carpet', [g(carpet('lr')), None, None])
    ts.add('carpet_sh', [g(carpet('lr')), None, None])
    ts.add('wall_top', [g(wall_top()), None, None])
    ts.add('wallpaper', [g(wallpaper()), None, None])
    ts.add('wainscot', [g(wainscot()), None, None])
    ts.add('side_l', [g(side_wall(False)), None, None])
    ts.add('side_r', [g(side_wall(True)), None, None])
    ts.add('void', [g(Canvas(K1)), None, None])
    ts.add('bottom', [g(bottom_wall()), None, None])
    ts.add('door_n', [g(door_north()), None, None], DOOR)
    ts.add('door_n_top', [g(door_north_top()), None, None])
    ts.add('door_s', [g(door_south()), None, None], 0x65)
    for sym in ('star', 'moon', 'flame', 'eye'):
        ts.add('plaque_' + sym, [s(plaque(sym)), None, None])
        ts.add('painting_' + sym, [s(painting(sym)), None, None])
        ts.add('ped_' + sym, [s(pedestal_base(sym)), None, None])
    ts.add('painting_ghost', [s(painting('ghost')), None, None])
    ts.add('ped', [g(pedestal_base()), None, None])
    ts.add('candle', [g(floor()), None, g(candle_top())])
    ts.add('lectern', [g(floor()), g(lectern()), None])
    ts.add('curtain_l', [g(curtain(False)), None, None])
    ts.add('curtain_r', [g(curtain(True)), None, None])
    ts.save({PG: GHOST, PS: SYMB})
    return ts.names


# ------------------------------------------------------------------ plan
# Main column x 12..24, side rooms x 1..9 (left) and 27..35 (right).
#   F  y 0..11   Fantina's hall (rooms are 2 void rows apart)
#   R3 y 14..23  choice: STAR (left, correct) / FLAME (right) - candles show FLAME
#   R2 y 26..35  choice: FLAME (left) / EYE (right, correct) - painting shows EYE
#   R1 y 38..47  choice: STAR (left, correct) / MOON (right) - MOON appears twice
#   E  y 50..59  entrance hall
W, H = 37, 60
X0 = 12
YF, Y3, Y2, Y1, YE = 0, 14, 26, 38, 50


def blank():
    return [['#'] * W for _ in range(H)]


def room(g, x0, y0, w, h, wall_rows=3):
    """Outline of a room: north wall (top, wallpaper, wainscot), sides, south wall."""
    for y in range(y0, y0 + h):
        for x in range(x0, x0 + w):
            if y == y0:
                g[y][x] = 't'
            elif y == y0 + 1:
                g[y][x] = 'p'
            elif y == y0 + 2:
                g[y][x] = 'w'
            elif y == y0 + h - 1:
                g[y][x] = 'b'
            elif y == y0 + 3:
                g[y][x] = 'h'      # floor in the wall's shadow
            else:
                g[y][x] = '.'
        if y > y0:
            g[y][x0] = 'L'; g[y][x0 + w - 1] = 'R'
        else:
            g[y][x0] = 't'; g[y][x0 + w - 1] = 't'


def plan():
    g = blank()
    # rooms
    room(g, X0, YF, 13, 12)                      # F
    for y0 in (Y3, Y2, Y1):
        room(g, X0, y0, 13, 10)
    room(g, X0, YE, 13, 10)                      # E
    room(g, 27, Y1, 9, 10)                       # S1 (right of R1)
    room(g, 1, Y2, 9, 10)                        # S2 (left of R2)
    room(g, 27, Y3, 9, 10)                       # S3 (right of R3)
    cx = X0 + 6                                  # 18
    # carpet runner up the middle of every main room
    for y in range(3, YE + 9):
        if g[y][cx] in '.h':
            g[y][cx] = 'c'
    # doors
    for y0 in (Y3, Y2, Y1):
        g[y0 + 2][X0 + 3] = 'D'; g[y0 + 2][X0 + 9] = 'D'       # north doors
        g[y0 + 1][X0 + 3] = 'A'; g[y0 + 1][X0 + 9] = 'B'       # plaques (set per room below)
        g[y0 + 9][cx] = 'S'                                     # south door
    g[YE + 2][cx] = 'D'; g[YE + 1][cx] = 'n'                     # entrance hall -> R1 (no symbol)
    g[YF + 11][cx] = 'S'                                         # F -> R3
    for x0, y0 in ((27, Y1), (1, Y2), (27, Y3)):
        g[y0 + 9][x0 + 4] = 'S'
    # entrance exit mat (existing metatiles)
    g[YE + 8][cx - 1:cx + 2] = ['1', '2', '3']
    g[YE + 9][cx - 1:cx + 2] = ['4', '5', '6']
    return g


def main():
    names = build_tileset()
    n = lambda k: int(names[k]) if isinstance(names[k], int) else names[k]
    g = plan()
    cx = 18
    # per-room symbols, paintings, pedestals, lecterns, shadows
    sym = {Y1: ('star', 'moon'), Y2: ('flame', 'eye'), Y3: ('star', 'flame')}
    extra = {}
    for y0, (a, b) in sym.items():
        g[y0 + 1][X0 + 3] = 'A' + str(y0)
        g[y0 + 1][X0 + 9] = 'B' + str(y0)
        extra['A' + str(y0)] = (n('plaque_' + a), 1, 0)
        extra['B' + str(y0)] = (n('plaque_' + b), 1, 0)
        g[y0 + 8][cx - 2] = 'Q'                                   # lectern by the entrance
    # R1: a MOON painting in the middle of the wall (MOON twice, STAR once)
    g[Y1 + 1][cx] = 'P1'; extra['P1'] = (n('painting_moon'), 1, 0)
    # R2: the EYE painting shows the way
    g[Y2 + 1][cx] = 'P2'; extra['P2'] = (n('painting_eye'), 1, 0)
    # R3: candles on two FLAME pedestals (the false door)
    for x in (X0 + 1, X0 + 11):
        g[Y3 + 3][x] = 'C'; g[Y3 + 4][x] = 'F3'
    g[Y3 + 1][cx] = 'P3'; extra['P3'] = (n('painting_ghost'), 1, 0)
    extra['F3'] = (n('ped_flame'), 1, 3)
    # Fantina's hall: curtains, ghost paintings, candles, ghostly floor
    for x in (X0 + 2, X0 + 10):
        g[1][x] = 'G'
    g[1][X0 + 1] = 'K'; g[1][X0 + 11] = 'J'
    for x in (X0 + 2, X0 + 10):
        g[4][x] = 'C'; g[5][x] = 'E'
        g[8][x] = 'C'; g[9][x] = 'E'
    g[6][X0 + 4] = 'g'; g[7][X0 + 8] = 'g'
    # side rooms: ghost paintings and shadows
    for x0, y0 in ((27, Y1), (1, Y2), (27, Y3)):
        g[y0 + 1][x0 + 2] = 'G'; g[y0 + 1][x0 + 6] = 'G'
        g[y0 + 5][x0 + 2] = 'g'
    # entrance hall: statues + ghost paintings
    g[YE + 1][X0 + 2] = 'G'; g[YE + 1][X0 + 10] = 'G'
    g[YE + 6][cx - 3] = 'Z'; g[YE + 6][cx + 3] = 'Z'
    # R1 decoration: a ghost shadow on the floor
    g[Y1 + 5][X0 + 2] = 'g'
    g[Y2 + 5][X0 + 10] = 'g'
    legend = {
        '#': (n('void'), 1, 0), 't': (n('wall_top'), 1, 0), 'p': (n('wallpaper'), 1, 0),
        'w': (n('wainscot'), 1, 0), 'L': (n('side_l'), 1, 0), 'R': (n('side_r'), 1, 0),
        'b': (n('bottom'), 1, 0), '.': (n('floor'), 0, 3), 'h': (n('floor_sh'), 0, 3),
        'c': (n('carpet'), 0, 3), 'g': (n('floor_ghost'), 0, 3),
        'D': (n('door_n'), 0, 3), 'n': (n('door_n_top'), 1, 0), 'S': (n('door_s'), 0, 3),
        'Q': (n('lectern'), 1, 3), 'C': (n('candle'), 1, 3), 'E': (n('ped'), 1, 3),
        'G': (n('painting_ghost'), 1, 0), 'K': (n('curtain_l'), 1, 0), 'J': (n('curtain_r'), 1, 0),
        'Z': (0x21b, 1, 3),
        '1': (0x205, 0, 3), '2': (0x206, 0, 3), '3': (0x207, 0, 3),
        '4': (0x20d, 1, 0), '5': (0x20e, 1, 0), '6': (0x20f, 1, 0),
    }
    legend.update(extra)
    # the door_n_top under each plaque: plaques sit right above the arch -> keep plaque
    rows = []
    keymap = {}
    for y in range(H):
        row = []
        for x in range(W):
            k = g[y][x]
            if k not in keymap:
                keymap[k] = chr(0x100 + len(keymap))
            row.append(keymap[k])
        rows.append(''.join(row))
    leg2 = {keymap[k]: v for k, v in legend.items() if k in keymap}
    missing = [k for k in keymap if k not in legend]
    assert not missing, missing
    build_map(LAYOUT, rows, leg2, border=n('void'))
    write_events(g)


def write_events(g):
    d = json.load(open(MAP))
    cx = 18
    warps = []      # (name, x, y, dest_name)

    def W_(name, x, y, dest):
        warps.append((name, x, y, dest))
    # 0-2: exit to Hearthome City (warp 12 of the city points to warp 0)
    for i, x in enumerate((cx - 1, cx, cx + 1)):
        warps.append(('exit%d' % i, x, YE + 8, None))
    # entrance hall <-> R1
    W_('E_n', cx, YE + 2, 'R1_s')
    W_('R1_s', cx, Y1 + 9, 'E_n')
    # R1: left (STAR) correct -> R2, right (MOON) -> S1 (trainer room, right)
    W_('R1_l', X0 + 3, Y1 + 2, 'R2_s'); W_('R2_s', cx, Y2 + 9, 'R1_l')
    W_('R1_r', X0 + 9, Y1 + 2, 'S1_s'); W_('S1_s', 31, Y1 + 9, 'R1_r')
    # R2: right (EYE) correct -> R3, left (FLAME) -> S2 (left)
    W_('R2_r', X0 + 9, Y2 + 2, 'R3_s'); W_('R3_s', cx, Y3 + 9, 'R2_r')
    W_('R2_l', X0 + 3, Y2 + 2, 'S2_s'); W_('S2_s', 5, Y2 + 9, 'R2_l')
    # R3: left (STAR) correct -> Fantina, right (FLAME) -> S3 (right)
    W_('R3_l', X0 + 3, Y3 + 2, 'F_s'); W_('F_s', cx, YF + 11, 'R3_l')
    W_('R3_r', X0 + 9, Y3 + 2, 'S3_s'); W_('S3_s', 31, Y3 + 9, 'R3_r')
    idx = {w[0]: i for i, w in enumerate(warps)}
    out = []
    for name, x, y, dest in warps:
        if dest is None:
            out.append({'x': x, 'y': y, 'elevation': 0, 'dest_map': 'MAP_HEARTHOME_CITY_SINNOH', 'dest_warp_id': '12'})
        else:
            out.append({'x': x, 'y': y, 'elevation': 0, 'dest_map': 'MAP_HEARTHOME_CITY_GYM_SINNOH',
                        'dest_warp_id': str(idx[dest])})
    d['warp_events'] = out
    # objects: keep order (local IDs), move them
    objs = d['object_events']
    pos = {
        'HearthomeCity_Gym_EventScript_Chance': (X0 + 10, Y1 + 5, 'MOVEMENT_TYPE_FACE_LEFT', '3'),     # R1
        'HearthomeCity_Gym_EventScript_Donny': (31, Y1 + 4, 'MOVEMENT_TYPE_FACE_DOWN', '4'),          # S1
        'HearthomeCity_Gym_EventScript_Catherine': (X0 + 2, Y2 + 4, 'MOVEMENT_TYPE_FACE_RIGHT', '3'), # R2
        'HearthomeCity_Gym_EventScript_Molly': (5, Y2 + 4, 'MOVEMENT_TYPE_FACE_DOWN', '4'),           # S2
        'HearthomeCity_Gym_EventScript_Allen': (X0 + 4, Y3 + 5, 'MOVEMENT_TYPE_FACE_DOWN', '2'),     # R3
        'HearthomeCity_Gym_EventScript_Mackenzie': (31, Y3 + 4, 'MOVEMENT_TYPE_FACE_DOWN', '4'),      # S3
        'SE_EventScript_SinnohLeader_Fantina': (cx, 4, 'MOVEMENT_TYPE_FACE_DOWN', '0'),
        'HearthomeCity_Gym_EventScript_PtGymGuide': (cx + 2, YE + 7, 'MOVEMENT_TYPE_FACE_DOWN', '0'),
    }
    for o in objs:
        x, y, mv, sight = pos[o['script']]
        o['x'], o['y'], o['movement_type'] = x, y, mv
        o['elevation'] = 3
        if o['trainer_type'] != 'TRAINER_TYPE_NONE':
            o['trainer_sight_or_berry_tree_id'] = sight
    # bg events: statues + hint lecterns
    bg = [
        {'type': 'sign', 'x': cx - 3, 'y': YE + 6, 'elevation': 0, 'player_facing_dir': 'BG_EVENT_PLAYER_FACING_ANY', 'script': 'HearthomeCity_Gym_EventScript_PtGymStatue'},
        {'type': 'sign', 'x': cx + 3, 'y': YE + 6, 'elevation': 0, 'player_facing_dir': 'BG_EVENT_PLAYER_FACING_ANY', 'script': 'HearthomeCity_Gym_EventScript_PtGymStatue'},
        {'type': 'sign', 'x': cx - 2, 'y': Y1 + 8, 'elevation': 0, 'player_facing_dir': 'BG_EVENT_PLAYER_FACING_ANY', 'script': 'HearthomeCity_Gym_EventScript_HintRoom1'},
        {'type': 'sign', 'x': cx - 2, 'y': Y2 + 8, 'elevation': 0, 'player_facing_dir': 'BG_EVENT_PLAYER_FACING_ANY', 'script': 'HearthomeCity_Gym_EventScript_HintRoom2'},
        {'type': 'sign', 'x': cx - 2, 'y': Y3 + 8, 'elevation': 0, 'player_facing_dir': 'BG_EVENT_PLAYER_FACING_ANY', 'script': 'HearthomeCity_Gym_EventScript_HintRoom3'},
    ]
    d['bg_events'] = bg
    d['coord_events'] = []
    open(MAP, 'w').write(json.dumps(d, indent=2, ensure_ascii=False) + '\n')
    print('warps:')
    for i, (name, x, y, dest) in enumerate(warps):
        print(' ', i, name, (x, y), '->', dest)


if __name__ == '__main__':
    main()
