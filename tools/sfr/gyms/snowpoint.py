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
        (248, 252, 255), (160, 200, 232), (112, 152, 200), (0, 0, 0), (0, 0, 0), (0, 0, 0),
        (0, 0, 0), (0, 0, 0), (0, 0, 0), (0, 0, 0)]
K, SD, S, SL, SH, WH, IC, ICD = range(1, 9)
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
    c = Canvas(0)
    c.rect(3, 6, 12, 13, WH); c.rect(2, 8, 13, 12, WH); c.rect(5, 4, 10, 5, WH)
    c.rect(4, 5, 11, 6, WH)
    c.hline(5, 10, 4, SH); c.hline(3, 5, 6, SH)
    c.rect(9, 9, 13, 12, SL); c.rect(11, 7, 12, 9, SH)
    c.hline(2, 13, 13, S); c.hline(3, 12, 14, SD)
    c.px(6, 7, SH); c.px(7, 6, SH)
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
    ts.add('mound', [ice, (mound(), P), None])
    ts.add('mound_shade', [('mt', ICE_SHADE, 1), (mound(), P), None])
    ts.add('snow', [(packed_snow(), P), None, None])
    # behaviours: ice slides now; the old locked ice stairs (still used as B1F's stair columns)
    # no longer push the player south
    for m, b in ((ICE, MB_ICE), (ICE_SHADE, MB_ICE), (LOCKED_STAIRS, MB_NORMAL)):
        i = (m - 0x200) * 2
        ts.at[i:i + 2] = struct.pack('<H', (struct.unpack_from('<H', ts.at, i)[0] & 0xFF00) | b)
    ts.save({P: SNOW})
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
                    put(x, y, ICE_SHADE if shade else ICE, 0)
                grid[j + 2][i + 1] = {'o': 'o', 'L': 'L'}.get(ch, 'i')
        mid = 8 - x0 + 1
        grid[1][mid] = 'E'; grid[len(rows) + 2][mid] = 'S'
        print(name, ''.join(solve([''.join(r) for r in grid])))
    for x, y in STAIR_TILES:
        put(x, y, STAIRS, 0)
    open(lay['blockdata_filepath'], 'wb').write(struct.pack('<%dH' % (w * h), *cells))


if __name__ == '__main__':
    main()
