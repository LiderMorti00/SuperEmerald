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

Both floors are drawn from a character plan by autotile(): walls are stone masses that step
down to the rooms (deep snow, cold stone, snowy rim), with an ice-block face wherever a floor
lies to the south and a cast shadow on that floor; firm floor is blue-grey stone slab, ice is
glossy and banked with snow at its edges, mounds are round outlined heaps.
"""
import json, os, struct, sys
from collections import deque
sys.path.insert(0, os.path.dirname(__file__))
from gymkit import Canvas, Tileset, write_metatile_defs

TS = 'data/tilesets/secondary/sootopolis_gym_sinnoh'
LAYOUT = 'LAYOUT_SNOWPOINT_CITY_GYM_1F_SINNOH'
LAYOUT_B1F = 'LAYOUT_SNOWPOINT_CITY_GYM_B1F_SINNOH'
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


# ---------------------------------------------------------------- floors and walls
OPEN = set('.iLoSTBHmCP')         # everything that is not wall mass


def ice_tile(shadow=False):
    """Glossy ice: pale cyan with long glints and a few hairline cracks (no tiles, no grid)."""
    c = Canvas(IC)
    for x, y in ((2, 13), (3, 12), (4, 11), (5, 10), (9, 5), (10, 4), (11, 3), (12, 2), (8, 14), (9, 13)):
        c.px(x, y, WH)
    for x, y in ((3, 13), (4, 12), (10, 5), (11, 4), (6, 3), (7, 3), (13, 9), (13, 10), (1, 6)):
        c.px(x, y, SH)
    for x, y in ((6, 8), (7, 9), (8, 9), (14, 13)):
        c.px(x, y, ICD)
    if shadow:
        for y in range(3):
            c.hline(0, 15, y, ICD if y < 2 else S)
    return c


def slab(shadow=False, dust=True):
    """Firm ground: big blue-grey stone slabs; a wall face to the north casts a shadow."""
    c = Canvas(ST4)
    c.hline(0, 15, 15, ST2); c.vline(15, 0, 15, ST2); c.hline(0, 14, 0, ST5); c.vline(0, 0, 14, ST5)
    for x, y in ((4, 4), (11, 9), (6, 12), (12, 3)):
        c.px(x, y, ST3)
    if dust:
        for x, y in ((2, 9), (9, 2), (13, 12)):
            c.px(x, y, WH)
    if shadow:
        for y in range(4):
            c.hline(0, 15, y, ST1 if y < 2 else ST2)
    return c


def face(w_open, e_open, window=None):
    """Wall face (a floor lies south): ice blocks under a snow cap, icicles, dark foot line."""
    c = Canvas(SL)
    for y in range(16):
        for x in range(16):
            v = SL if (y // 5 + x // 8) % 2 else SH
            if y % 5 == 4 or (x + (4 if (y // 5) % 2 else 0)) % 8 == 7:
                v = ICD
            c.px(x, y, v)
    c.hline(0, 15, 0, K); c.hline(0, 15, 1, WH); c.hline(0, 15, 2, WH); c.hline(0, 15, 3, SH)
    for x in (2, 6, 11, 14):                                       # icicles
        c.px(x, 4, WH); c.px(x, 5, SH)
    c.px(6, 6, SH)
    c.hline(0, 15, 14, S); c.hline(0, 15, 15, SD)
    if w_open: c.vline(0, 0, 15, K)
    if e_open: c.vline(15, 0, 15, K)
    return c


TIER = {1: (WH, SH), 2: (ST3, ST2), 3: (ST2, ST1)}


def top(d, sides, steps):
    """Top of a wall mass seen from above. d = distance to the nearest floor (1 snowy rim,
    2 cold stone, 3+ dark stone). sides: open floor at n/w/e (a cliff edge there);
    steps: neighbouring tiers that are lower (drawn as a step line)."""
    t = min(d, 3)
    a, b = TIER[t]
    c = Canvas(a)
    for x, y in ((3, 4), (10, 2), (6, 11), (13, 9), (1, 14)):
        c.px(x, y, b)
    if t == 3:
        for x, y in ((5, 6), (6, 6), (11, 12), (12, 12)):
            c.px(x, y, SH)                                         # snow caught on the stone
    for e in steps:                                                # step down towards a lower tier
        for i in range(16):
            px = {'n': (i, 0), 's': (i, 15), 'w': (0, i), 'e': (15, i)}[e]
            c.px(*px, ST1 if t > 1 else SH)
    for e in sides:                                                # cliff edge to the floor
        for i in range(16):
            px, px2 = {'n': ((i, 0), (i, 1)), 'w': ((0, i), (1, i)), 'e': ((15, i), (14, i)),
                       's': ((i, 15), (i, 14))}[e]
            c.px(*px, K); c.px(*px2, S)
    return c


def crystal():
    """Ice crystal on a stone foot (decoration that blocks)."""
    c = slab()
    pts = [(7, 1), (8, 1), (6, 3), (9, 3), (5, 6), (10, 6), (5, 10), (10, 10), (6, 12), (9, 12)]
    for y in range(1, 13):
        w = min(y, 13 - y, 4)
        for x in range(8 - w, 8 + w):
            c.px(x, y, SH if x < 8 else S)
    for y in range(2, 12):
        c.px(7, y, WH)
    c.hline(4, 11, 13, K); c.hline(5, 10, 14, ST1)
    return c


def plan_1f():
    W, H = 17, 26
    g = [['#'] * W for _ in range(H)]
    def fill(x0, y0, x1, y1, ch):
        for y in range(y0, y1 + 1):
            for x in range(x0, x1 + 1):
                g[y][x] = ch
    fill(3, 2, 13, 3, '.')                     # CANDICE's floor
    g[2][4] = g[2][12] = 'P'                   # ice crystals
    for name, (x0, y0, rows) in ROOMS.items():
        for j, r in enumerate(rows):
            for i, ch in enumerate(r):
                g[y0 + j][x0 + i] = {'.': 'i'}.get(ch, ch)
    for x, y in STAIR_TILES + [(8, 20), (8, 21)]:
        g[y][x] = 'S'
    fill(5, 22, 11, 25, '.')                   # entrance hall
    g[23][6] = g[23][10] = 'T'; g[24][6] = g[24][10] = 'B'
    g[22][11] = 'H'                            # ladder down to B1F
    g[25][8] = g[25][9] = 'm'
    return [''.join(r) for r in g]


def plan_b1f(orig):
    """Basement plan from its current collision: floor stays floor, the stair columns stay stairs."""
    W, H = 17, len(orig) // 17
    g = []
    for y in range(H):
        row = ''
        for x in range(W):
            v = orig[y * W + x]
            m, col = v & 0x3FF, (v >> 10) & 3
            row += 'H' if m == 0x214 else 'S' if m == LOCKED_STAIRS else '#' if col else '.'
        g.append(row)
    return g


def autotile(plan):
    """Return {(x, y): (name, canvas_layers, collision, behavior)} for every cell of a plan."""
    H, W = len(plan), len(plan[0])
    at = lambda x, y: plan[y][x] if 0 <= x < W and 0 <= y < H else '#'
    op = lambda x, y: at(x, y) in OPEN
    dist = {}
    q = deque()
    for y in range(H):
        for x in range(W):
            if op(x, y):
                dist[(x, y)] = 0; q.append((x, y))
    while q:
        x, y = q.popleft()
        for dx in (-1, 0, 1):
            for dy in (-1, 0, 1):
                n = (x + dx, y + dy)
                if 0 <= n[0] < W and 0 <= n[1] < H and n not in dist:
                    dist[n] = dist[(x, y)] + 1; q.append(n)
    out = {}
    D4 = (('n', 0, -1), ('s', 0, 1), ('w', -1, 0), ('e', 1, 0))
    for y in range(H):
        for x in range(W):
            ch = at(x, y)
            shadow = at(x, y - 1) == '#'
            if ch == '#':
                if op(x, y + 1):
                    key = ('face', op(x - 1, y) or at(x - 1, y + 1) == '#', op(x + 1, y) or at(x + 1, y + 1) == '#')
                    key = ('face', op(x - 1, y), op(x + 1, y))
                    out[(x, y)] = ('wf_%d%d' % key[1:], lambda k=key: [(face(k[1], k[2]), P), None, None], 1, 0)
                else:
                    d = dist[(x, y)]; t = min(d, 3)
                    sides = ''.join(e for e, dx, dy in D4 if op(x + dx, y + dy))
                    steps = ''.join(e for e, dx, dy in D4 if not op(x + dx, y + dy) and
                                    0 <= x + dx < W and 0 <= y + dy < H and min(dist[(x + dx, y + dy)], 3) < t)
                    nm = 'wt%d_%s_%s' % (t, sides or '0', steps or '0')
                    out[(x, y)] = (nm, lambda t=t, a=sides, b=steps: [(top(t, a, b), P), None, None], 1, 0)
            elif ch in '.CL':
                out[(x, y)] = ('slab%d' % shadow, lambda s=shadow: [(slab(s), P), None, None], 0, MB_NORMAL)
            elif ch == 'i':
                edges = ''.join(e for e, dx, dy in D4 if at(x + dx, y + dy) not in 'ioL')
                edges = ''.join(e for e in 'nswe' if e in edges)
                nm = 'ice_%s%d' % (edges or '0', shadow)
                out[(x, y)] = (nm, lambda e=edges, s=shadow: [(ice_tile(s), P), (drift(e), P) if e else None, None], 0, MB_ICE)
            elif ch == 'o':
                out[(x, y)] = ('mound%d' % shadow, lambda s=shadow: [(ice_tile(s), P), (mound(), P), None], 1, MB_NORMAL)
            elif ch == 'S':
                out[(x, y)] = ('stairs', lambda: [(stone_steps(), P), None, None], 0, MB_NORMAL)
            elif ch == 'P':
                out[(x, y)] = ('crystal', lambda: [(crystal(), P), None, None], 1, MB_NORMAL)
            elif ch == 'T':
                out[(x, y)] = ('statue_top', lambda: [(slab(False), P), None, ('mt', 0x217, 2)], 0, MB_NORMAL)
            elif ch == 'B':
                out[(x, y)] = ('statue_base', lambda: [(slab(False), P), ('mt', 0x21f, 1), None], 1, MB_NORMAL)
    return out


def main():
    ts = Tileset(TS)
    s_orig = json.load(open(TS + '/se_gymkit.json'))
    L = json.load(open('data/layouts/layouts.json'))
    lays = {k: [l for l in L['layouts'] if l.get('id') == k][0] for k in (LAYOUT, LAYOUT_B1F)}
    b1 = open(lays[LAYOUT_B1F]['blockdata_filepath'], 'rb').read()
    if 'orig_b1f' not in s_orig:
        s_orig['orig_b1f'] = list(struct.unpack('<%dH' % (len(b1) // 2), b1))
        ts.state['orig_b1f'] = s_orig['orig_b1f']
    orig_b1f = ts.state.get('orig_b1f', s_orig.get('orig_b1f'))
    ts.state['orig_b1f'] = orig_b1f
    print('free tile slots:', ts.free_unused({0x217, 0x21f, 0x21c, 0x214, 0x20c}))
    plans = {LAYOUT: plan_1f(), LAYOUT_B1F: plan_b1f(orig_b1f)}
    cells = {k: autotile(v) for k, v in plans.items()}
    made = {}
    for k in plans:
        for (x, y), (nm, fn, col, mb) in sorted(cells[k].items()):
            if nm not in made:
                ts.add(nm, fn(), mb); made[nm] = True
    win = frost_window()                       # snowed-in windows in the top wall of 1F
    for (cx, cy) in ((0, 0), (1, 0), (0, 1), (1, 1)):
        ts.add('win_%d%d' % (cx, cy), [(cut(win, cx, cy + 1), P), None, None])
    for name, (x0, y0, rows) in ROOMS.items():  # check every room still solves and can't trap
        grid = [['#'] * (len(rows[0]) + 2) for _ in range(len(rows) + 4)]
        for j, r in enumerate(rows):
            for i, ch in enumerate(r):
                grid[j + 2][i + 1] = {'o': 'o', 'L': 'L'}.get(ch, 'i')
        mid = 8 - x0 + 1
        grid[1][mid] = 'E'; grid[len(rows) + 2][mid] = 'S'
        print(name, ''.join(solve([''.join(r) for r in grid])))
    ts.save({P: SNOW})
    names = ts.names
    write_metatile_defs('data/maps/SnowpointCity_Gym_1F_sinnoh', 'SnowpointGym', names)
    for k, plan in plans.items():
        lay = lays[k]; w, h = lay['width'], lay['height']
        assert (w, h) == (len(plan[0]), len(plan)), (k, w, h)
        vals = []
        for y in range(h):
            for x in range(w):
                ch = plan[y][x]
                if (x, y) in cells[k]:
                    nm, fn, col, mb = cells[k][(x, y)]
                    vals.append((names[nm] & 0x3FF) | (col << 10) | (3 << 12 if not col else 0))
                elif ch == 'H':
                    v = (s_orig['orig_map'][y * w + x] if k == LAYOUT else orig_b1f[y * w + x])
                    vals.append(v)
                elif ch == 'm':
                    vals.append((0x006 if x == 8 else 0x007) | (3 << 12))
                else:
                    raise SystemExit(f'no tile for {ch!r} at {x},{y} in {k}')
        if k == LAYOUT:
            for (wx, wy), cx, cy in (((4, 0), 0, 0), ((5, 0), 1, 0), ((4, 1), 0, 1), ((5, 1), 1, 1),
                                     ((11, 0), 0, 0), ((12, 0), 1, 0), ((11, 1), 0, 1), ((12, 1), 1, 1)):
                vals[wy * w + wx] = (names['win_%d%d' % (cx, cy)] & 0x3FF) | (1 << 10)
        open(lay['blockdata_filepath'], 'wb').write(struct.pack('<%dH' % (w * h), *vals))


if __name__ == '__main__':
    main()
