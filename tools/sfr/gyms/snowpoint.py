#!/usr/bin/env python3
"""Super Emerald: Snowpoint City Gym (Candice) - sliding ice with snow mounds as stoppers.

Run from the repo root: python3 tools/sfr/gyms/snowpoint.py
The old Sootopolis-style cracked ice (thin ice that broke after one step, locked ice stairs
that opened after 8/28/67 steps and a fall to B1F) is gone. The three ice rooms of 1F are
now MB_ICE: the player slides until a snow mound, a wall or a patch of packed snow stops
them. Room 3 (bottom) is a short practice slide; rooms 2 and 1 are the real puzzle. Each
room has a packed-snow landing at its entrance, and from every stop the player can still
reach both the exit stairs and the landing (checked by solve() below), so nobody gets stuck.
B1F stays reachable from the ladder by the entrance; its stair columns are now walkable
both ways, so its trainers can still be fought.
"""
import json, os, struct, sys
from collections import deque
sys.path.insert(0, os.path.dirname(__file__))
from gymkit import Canvas, Tileset, write_metatile_defs

TS = 'data/tilesets/secondary/sootopolis_gym_sinnoh'
LAYOUT = 'LAYOUT_SNOWPOINT_CITY_GYM_1F_SINNOH'
P = 10
SNOW = [(0, 0, 0), (40, 56, 96), (88, 120, 176), (136, 168, 216), (184, 208, 240), (224, 236, 252),
        (248, 252, 255), (160, 200, 232), (112, 152, 200), (52, 62, 78), (88, 102, 120), (128, 142, 158),
        (170, 182, 196), (208, 216, 226), (120, 176, 224), (24, 40, 72)]
K, SD, S, SL, SH, WH, IC, ICD, ST1, ST2, ST3, ST4, ST5, GL, NIGHT = range(1, 16)
import colorsys
MB_ICE, MB_NORMAL = 0x20, 0x00
ICE, ICE_SHADE, STAIRS, LOCKED_STAIRS = 0x20d, 0x215, 0x207, 0x20f

# Rooms: (x0, y0, rows) of the ice area; 'o' = snow mound, 'L' = packed-snow landing.
ROOMS = {
    'room1': (3, 6, ["....o..o...",        # 10 moves: R U R U L D L U L U
                     "o..........",
                     ".....o.....",
                     "....oL..o.."]),
    'room2': (5, 12, ["o...o.o",            # 6 moves: L U R U R U
                      "...o...",
                      "...L..."]),
    'room3': (7, 17, ["o..",                 # practice, 4 moves: R U L U
                      "oo.",
                      ".L."]),
}
STAIR_TILES = [(8, 4), (8, 5), (8, 10), (8, 11), (8, 15), (8, 16)]


def mound():
    """A tall heap of snow: the stopper. Round, white, with a dark shadow on the ice."""
    c = Canvas(0)
    for y in range(16):
        for x in range(16):
            dx, dy = (x - 7.5) / 7.5, (y - 8.5) / 7.0
            r2 = dx * dx + dy * dy
            if r2 <= 1:
                shade = dx * 0.7 + dy * 0.7
                c.px(x, y, S if r2 > 0.78 else WH if shade < -0.1 else SH if shade < 0.45 else SL)
    for x in range(1, 15):
        c.px(x, 15, SD); c.px(x, 14, S if c.p[14][x] == 0 else c.p[14][x])
    c.px(4, 4, WH); c.px(5, 3, WH); c.px(9, 10, SH)
    return c


def big(w, h, fill=0):
    return [[fill] * w for _ in range(h)]


def cut(g, cx, cy):
    c = Canvas(0)
    c.p = [row[cx * 16:cx * 16 + 16] for row in g[cy * 16:cy * 16 + 16]]
    return c


def frost_window():
    """2x3 metatiles: a snowed-in window set in blue-grey stone (replaces the old waterfalls)."""
    g = big(32, 48, ST3)
    for y in range(48):                      # stone courses
        for x in range(32):
            if y % 8 == 7 or (x + (8 if (y // 8) % 2 else 0)) % 16 == 15:
                g[y][x] = ST2
    for y in range(0, 3):
        for x in range(32):
            g[y][x] = (ST5, ST4, ST2)[y]
    for y in range(6, 41):                   # frame
        for x in range(4, 28):
            g[y][x] = ST1 if (x in (4, 27) or y in (6, 40)) else ST4 if (x in (5, 26) or y in (7, 39)) else NIGHT
    for y in range(8, 39):                   # glass: night sky with falling snow
        for x in range(6, 26):
            g[y][x] = NIGHT if y < 20 else SD if y < 30 else S
    for x in range(6, 26):
        g[8][x] = SD
    for y in range(8, 39):
        g[y][15] = g[y][16] = ST4            # mullion
    for x in range(6, 26):
        g[23][x] = ST4
    import random
    rnd = random.Random(3)
    for _ in range(26):
        x, y = rnd.randrange(6, 26), rnd.randrange(9, 32)
        if g[y][x] not in (ST4,):
            g[y][x] = WH if rnd.random() < .6 else SH
    for y in range(31, 39):                  # snow piled against the glass
        for x in range(6, 26):
            if y >= 35 - int(2 * abs(((x - 6) % 10) - 5) / 5):
                g[y][x] = WH if y > 33 else SH
    for (x0, sx) in ((6, 1), (25, -1)):      # frost in the corners
        for i in range(5):
            for j in range(5 - i):
                g[9 + i][x0 + sx * j] = SH if (i + j) % 2 else WH
    for y in range(40, 44):                  # snowy sill
        for x in range(2, 30):
            g[y][x] = WH if y < 42 else SL if y == 42 else ST1
    return g


def stone_steps():
    c = Canvas(ST3)
    for y in range(16):
        c.hline(0, 15, y, (ST5, ST4, ST3, ST2)[y % 4])
    c.vline(0, 0, 15, ST1); c.vline(15, 0, 15, ST1)
    for x, y in ((1, 0), (2, 0), (13, 4), (14, 4), (1, 8), (14, 12), (13, 12)):
        c.px(x, y, WH)
    return c


def stone_slab():
    """Firm ground: rough blue-grey slabs dusted with snow, nothing like the glossy ice."""
    c = Canvas(ST4)
    c.hline(0, 15, 7, ST2); c.hline(0, 15, 15, ST2); c.vline(7, 0, 7, ST2); c.vline(15, 8, 15, ST2)
    c.vline(0, 0, 15, ST1); c.vline(15, 0, 15, ST1); c.hline(0, 15, 0, ST5)
    for x, y in ((3, 3), (11, 2), (5, 11), (12, 10), (2, 13), (9, 5)):
        c.px(x, y, ST3); c.px(x + 1, y, WH)
    return c


def drift(edges):
    """Snow banked against the walls on the given edges of an ice tile ('n','s','w','e')."""
    c = Canvas(0)
    wave = [6, 7, 7, 6, 5, 5, 6, 7, 7, 6, 5, 6, 7, 6, 5, 6]
    for i in range(16):
        d = wave[i]
        if 'n' in edges:
            for y in range(d):
                c.px(i, y, WH)
            c.px(i, d, S); c.px(i, d - 1, SH)
        if 's' in edges:
            for y in range(16 - d + 1, 16):
                c.px(i, y, WH)
            c.px(i, 15 - d, S); c.px(i, 16 - d, SH)
        if 'w' in edges:
            for x in range(d - 1):
                c.px(x, i, WH)
            c.px(d - 1, i, S); c.px(d - 2, i, SH)
        if 'e' in edges:
            for x in range(17 - d, 16):
                c.px(x, i, WH)
            c.px(16 - d, i, S); c.px(17 - d, i, SH)
    return c


def packed_snow():
    c = Canvas(SH)
    for x, y in ((2, 3), (9, 1), (13, 6), (5, 9), (11, 12), (1, 13), (7, 14)):
        c.px(x, y, SL); c.px(x + 1, y, WH)
    c.hline(0, 15, 0, WH)
    c.vline(0, 0, 15, SL); c.vline(15, 0, 15, SL); c.hline(0, 15, 15, SL)
    return c


def solve(grid):
    """grid: rows with '#', 'i' ice, 'o' mound, 'L' landing, 'E' exit, 'S' entrance stairs.
    Returns the shortest solution from L, or raises if some reachable stop can't get out."""
    D = {'U': (0, -1), 'D': (0, 1), 'L': (-1, 0), 'R': (1, 0)}

    def moves(p):
        for k, (dx, dy) in D.items():
            x, y = p[0] + dx, p[1] + dy
            if grid[y][x] in '#o':
                continue
            while grid[y][x] == 'i' and grid[y + dy][x + dx] not in '#o':
                x += dx; y += dy
            yield k, (x, y)

    def bfs(s):
        prev = {s: None}; q = deque([s])
        while q:
            p = q.popleft()
            for k, n in moves(p):
                if n not in prev:
                    prev[n] = (p, k); q.append(n)
        return prev
    find = lambda ch: [(x, y) for y, r in enumerate(grid) for x, c in enumerate(r) if c == ch][0]
    L, E, S = find('L'), find('E'), find('S')
    reach = bfs(L)
    assert E in reach, 'no solution'
    for p in reach:
        r = bfs(p)
        assert S in r and E in r, f'stuck at {p}'
    path, p = [], E
    while reach[p]:
        p, k = reach[p]; path.append(k)
    return path[::-1]


def main():
    ts = Tileset(TS)
    ice = ('mt', ICE, 1)
    live = set()
    for m in ('SnowpointCity_Gym_1F_sinnoh', 'SnowpointCity_Gym_B1F_sinnoh'):
        b = open(f'data/layouts/{m}/map.bin', 'rb').read() + open(f'data/layouts/{m}/border.bin', 'rb').read()
        live |= {v & 0x3FF for v in struct.unpack('<%dH' % (len(b) // 2), b)}
    live |= {ICE, ICE_SHADE, STAIRS, LOCKED_STAIRS}
    redrawn = {0x268, 0x269, 0x270, 0x271, 0x278, 0x279, STAIRS}
    print('free tile slots:', ts.free_unused(live, redrawn))
    ts.add('mound', [ice, (mound(), P), None])
    ts.add('mound_shade', [ice, (mound(), P), None])
    ts.add('snow', [(stone_slab(), P), None, None])
    # mountain pavilion: frosted windows instead of the Sootopolis waterfalls, stone stairs
    win = frost_window()
    for (cx, cy), mid in {(0, 0): 0x268, (1, 0): 0x269, (0, 1): 0x270, (1, 1): 0x271,
                          (0, 2): 0x278, (1, 2): 0x279}.items():
        ts.replace(mid, [(cut(win, cx, cy), P), None, None], MB_NORMAL)
    ts.replace(STAIRS, [(stone_steps(), P), None, None])
    for k in ('n', 's', 'w', 'e', 'nw', 'ne', 'sw', 'se'):
        ts.add('ice_' + k, [ice, (drift(k), P), None], MB_ICE)
    # behaviours: ice slides now; the old locked ice stairs (still used as B1F's stair columns)
    # no longer push the player south
    for m, b in ((ICE, MB_ICE), (ICE_SHADE, MB_ICE), (LOCKED_STAIRS, MB_NORMAL)):
        i = (m - 0x200) * 2
        ts.at[i:i + 2] = struct.pack('<H', (struct.unpack_from('<H', ts.at, i)[0] & 0xFF00) | b)
    pals = {P: SNOW}
    for slot in (6, 7, 8, 9):            # purple mouldings -> blue-grey stone
        cols = []
        for i, (r, g, b) in enumerate(ts.orig_pal(slot)):
            h, sat, v = colorsys.rgb_to_hsv(r / 255, g / 255, b / 255)
            if i and sat > 0.06 and 0.62 < h < 0.92:
                h, sat = 0.58, min(sat, 0.22)
                r, g, b = (round(c * 255) for c in colorsys.hsv_to_rgb(h, sat, v))
            cols.append((r, g, b))
        pals[slot] = cols
    ts.save(pals)
    names = ts.names
    write_metatile_defs('data/maps/SnowpointCity_Gym_1F_sinnoh', 'SnowpointGym', names)

    L = json.load(open('data/layouts/layouts.json'))
    lay = [l for l in L['layouts'] if l.get('id') == LAYOUT][0]
    w, h = lay['width'], lay['height']
    data = bytearray(open(lay['blockdata_filepath'], 'rb').read())
    state = json.load(open(TS + '/se_gymkit.json'))
    if 'orig_map' not in state:
        state['orig_map'] = list(struct.unpack('<%dH' % (w * h), data))
        json.dump(state, open(TS + '/se_gymkit.json', 'w'), indent=1)
    cells = list(state['orig_map'])
    put = lambda x, y, m, col: cells.__setitem__(y * w + x, (m & 0x3FF) | (col << 10))
    for name, (x0, y0, rows) in ROOMS.items():
        grid = [['#'] * (len(rows[0]) + 2) for _ in range(len(rows) + 4)]
        for j, r in enumerate(rows):
            for i, ch in enumerate(r):
                x, y = x0 + i, y0 + j
                shade = j == 0
                if ch == 'o':
                    put(x, y, names['mound_shade' if shade else 'mound'], 1)
                elif ch == 'L':
                    put(x, y, names['snow'], 0)
                else:
                    edges = ''.join(e for e, (dx, dy) in (('n', (0, -1)), ('s', (0, 1)), ('w', (-1, 0)), ('e', (1, 0)))
                                    if not (0 <= i + dx < len(r) and 0 <= j + dy < len(rows)))
                    put(x, y, names['ice_' + edges] if edges else ICE, 0)
                grid[j + 2][i + 1] = {'o': 'o', 'L': 'L'}.get(ch, 'i')
        mid = 8 - x0 + 1
        grid[1][mid] = 'E'; grid[len(rows) + 2][mid] = 'S'
        print(name, ''.join(solve([''.join(r) for r in grid])))
    for x, y in STAIR_TILES:
        put(x, y, STAIRS, 0)
    open(lay['blockdata_filepath'], 'wb').write(struct.pack('<%dH' % (w * h), *cells))


if __name__ == '__main__':
    main()
