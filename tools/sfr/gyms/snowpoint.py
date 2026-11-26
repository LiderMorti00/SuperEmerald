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
from gymkit import Canvas, Tileset, write_metatile_defs, build_cells

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
OPEN = set('.iLoSTBHmCPAbd')       # everything that is not outer wall mass


def _ice_tex():
    """32x32 ice texture: smooth pale ice, a few long glints and one hairline crack, so the rink
    reads as one sheet instead of a repeated tile."""
    g = [[IC] * 32 for _ in range(32)]
    for x0, y0, n in ((3, 26, 9), (18, 12, 7), (25, 30, 5), (8, 9, 4)):
        for i in range(n):
            x, y = (x0 + i) % 32, (y0 - i) % 32
            g[y][x] = WH; g[(y + 1) % 32][x] = SH
    for x, y in ((12, 20), (13, 21), (14, 21), (15, 22), (16, 22), (28, 6), (29, 7)):
        g[y][x] = ICD
    for x, y in ((22, 3), (5, 16), (30, 18)):
        g[y][x] = SH
    return g


ICE_TEX = None


def ice_tile(shadow=False, v=(0, 0)):
    global ICE_TEX
    ICE_TEX = ICE_TEX or _ice_tex()
    c = Canvas(IC)
    for y in range(16):
        for x in range(16):
            c.px(x, y, ICE_TEX[v[1] * 16 + y][v[0] * 16 + x])
    if shadow:
        for y in range(3):
            c.hline(0, 15, y, ICD if y < 2 else S)
    return c


def slab(shadow=False, dust=True, v=(0, 0)):
    """Firm ground: large blue-grey flagstones (32x16, laid in a running bond) with soft joints."""
    c = Canvas(ST4)
    for y in range(16):
        for x in range(16):
            X, Y = v[0] * 16 + x, v[1] * 16 + y
            off = 16 if (Y // 16) % 2 else 0
            if Y % 16 == 15 or (X + off) % 32 == 31:
                c.px(x, y, ST3)
            elif Y % 16 == 0 or (X + off) % 32 == 0:
                c.px(x, y, ST5)
    for x, y in ((5, 5), (11, 9), (3, 12)):
        c.px(x, y, ST3 if (x + v[0] + v[1]) % 2 else ST5)
    if dust:
        for x, y in ((9, 3) if v[0] else (2, 9),):
            c.px(x, y, WH)
    if shadow:
        for y in range(3):
            c.hline(0, 15, y, ST2 if y < 2 else ST3)
    return c


def ladder_hole():
    c = slab()
    c.rect(2, 2, 13, 13, K); c.rect(3, 3, 12, 12, SD)
    for y in (4, 7, 10):
        c.hline(4, 11, y, ST4); c.hline(4, 11, y + 1, ST2)
    c.vline(4, 3, 12, ST5); c.vline(11, 3, 12, ST5)
    c.hline(2, 13, 2, ST1)
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


# One big rink, after Diamond/Platinum's Snowpoint gym: a firm stone walkway runs all round, a low
# snowbank separates it from the ice and has openings in it ('.'), and CANDICE stands on a raised
# ice dais in the middle. The dais can only be entered from below, through its access tile A,
# so the player has to stop in column 9 under it and slide up. Mounds (o) are the stoppers.
# After the battle the ice under the dais turns into a snowy path down to the walkway (scripts).
RINK = [
    "###################",   # 0  top wall
    "###################",   # 1  wall face (windows)
    "#.................#",   # 2  walkway
    '#.bbb.bbbbbbb.bbb.#',   # 3  openings (5,3), (13,3)
    '#.biiiiioiioiiiib.#',   # 4
    '#..iioiioiiiiioi..#',   # 5  openings (2,5), (16,5)
    '#.biiiiiiiiiiioib.#',   # 6
    '#.biooiiiiiiiiiib.#',   # 7
    '#..iiiiiPPPiiiiib.#',   # 8  opening (2,8); CANDICE's dais
    '#.biiiiiPCPiiiii..#',   # 9  CANDICE (9,9); opening (16,9)
    '#.biiiiiPAPiiiiib.#',   # 10  access (9,10), from below only
    '#.biiiiiiiiiiiiib.#',   # 11
    '#.biiiiiiioiiiii..#',   # 12  opening (16,12)
    '#..iiooiiiiiiiiob.#',   # 13  opening (2,13): first slide - right to the mounds and back
    '#.boiiiiiiiiiiiib.#',   # 14
    "#.bbbbbbbbbbbbbbb.#",   # 15 closed: the first gap the player meets is (2,13), with CANDICE in view
    "#.....T.....T.....#",   # 16 walkway; statues (6,16) and (12,16)
    "#.....B.....B....H#",   # 17 foyer; ladder down to B1F (17,17)
    "########mm#########",   # 18 exit mat (8,18), (9,18)
]
PATH = [(9, 11), (9, 12), (9, 13), (9, 14), (9, 15)]     # the way back opened after the battle
ACCESS = (9, 10)


def rink_check():
    """Shortest way to CANDICE from the walkway, and no stop on the ice that can't get back to firm
    ground. Returns the list of moves."""
    g = [list(r) for r in RINK]
    H, W = len(g), len(g[0])
    D = {'U': (0, -1), 'D': (0, 1), 'L': (-1, 0), 'R': (1, 0)}
    solid = set('#boPCTBH')
    def moves(p):
        for k, (dx, dy) in D.items():
            x, y = p[0] + dx, p[1] + dy
            if not (0 <= y < H and 0 <= x < W) or g[y][x] in solid: continue
            while g[y][x] == 'i' and g[y + dy][x + dx] not in solid:
                x += dx; y += dy
            yield k, (x, y)
    def bfs(starts):
        prev = {s: None for s in starts}; q = deque(starts)
        while q:
            p = q.popleft()
            for k, n in moves(p):
                if n not in prev: prev[n] = (p, k); q.append(n)
        return prev
    firm = [(x, y) for y in range(H) for x in range(W) if g[y][x] in '.m']
    r = bfs(firm)
    assert ACCESS in r, 'CANDICE unreachable'
    for p in r:
        if g[p[1]][p[0]] in 'iA':
            assert any(g[q[1]][q[0]] == '.' for q in bfs([p])), f'stuck at {p}'
    path, p = [], ACCESS
    while r[p]:
        p, k = r[p]; path.append((k, p))
    start = path[-1][1]
    return start, ''.join(k for k, _ in path[::-1])


def plan_1f():
    return [r.replace('A', 'A') for r in RINK]


def bank(face, edges):
    """Low snowbank between the walkway and the rink (blocks): a rounded drift of snow on a
    stone kerb; its kerb face shows where the floor lies to the south."""
    c = Canvas(0)
    top = 1
    c.rect(0, top, 15, 11 if face else 15, WH)
    for x in range(16):
        c.px(x, top, SH); c.px(x, top + 1, WH)
        if (x * 5) % 7 == 0: c.px(x, top + 4, SH)
    for x, y in ((3, 6), (4, 6), (10, 4), (11, 4), (7, 9)):
        c.px(x, y, SL)
    if face:
        c.rect(0, 12, 15, 14, ST3); c.hline(0, 15, 12, ST4); c.hline(0, 15, 15, K)
        for x in range(0, 16, 4): c.px(x, 13, ST2)
    if 'w' in edges: c.vline(0, top, 15 if not face else 14, S)
    if 'e' in edges: c.vline(15, top, 15 if not face else 14, S)
    c.hline(0, 15, 0, 0)
    return c


def dais(n_in, s_in, w_in, e_in):
    """Border of CANDICE's raised ice dais (blocks): a thick block of blue ice with a snowy rim on
    top and a frozen front face; corners are rounded off."""
    c = Canvas(S)
    for y in range(16):
        for x in range(16):
            v = S if (x + y) % 5 else ICD
            if (x * 3 + y) % 11 == 0: v = SH
            c.px(x, y, v)
    if not n_in:
        c.hline(0, 15, 0, K); c.rect(0, 1, 15, 3, WH); c.hline(0, 15, 4, SH)
    if not s_in:
        c.rect(0, 10, 15, 14, ICD); c.hline(0, 15, 10, SH); c.hline(0, 15, 15, K)
        for x in range(1, 16, 4): c.px(x, 12, SL)
    if not w_in: c.vline(0, 0, 15, K); c.vline(1, 0, 15, SH)
    if not e_in: c.vline(15, 0, 15, K); c.vline(14, 0, 15, ICD)
    if not n_in and not w_in: c.px(0, 0, 0); c.px(1, 0, 0); c.px(0, 1, 0)
    if not n_in and not e_in: c.px(15, 0, 0); c.px(14, 0, 0); c.px(15, 1, 0)
    return c


def dais_floor(access):
    """Top of the dais: packed white snow with a snowflake; the access tile has a frozen lip."""
    c = Canvas(WH)
    for x, y in ((3, 3), (12, 4), (5, 12), (11, 11)):
        c.px(x, y, SH)
    for i in range(-3, 4):
        c.px(7 + i, 7, SL); c.px(7, 7 + i, SL); c.px(7 + i, 7 + i, SH); c.px(7 + i, 7 - i, SH)
    if access:
        c.hline(0, 15, 14, S); c.hline(0, 15, 15, ICD)
        c.vline(0, 0, 15, SH); c.vline(15, 0, 15, SH)
    return c


def snow_path():
    """Firm snow trail CANDICE opens over the ice after the battle (walkable, no sliding)."""
    c = Canvas(WH)
    for y in range(16):
        c.px(0, y, SH); c.px(15, y, SH)
    for x, y in ((4, 2), (10, 3), (5, 9), (11, 10), (4, 13), (10, 14)):
        c.px(x, y, SL); c.px(x + 1, y, SL); c.px(x, y + 1, SH)
    return c


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
            elif ch == 'b':
                fc = at(x, y + 1) not in 'b#'
                e = ''.join(k for k, dx, dy in D4[2:] if at(x + dx, y) not in 'b#')
                nm = 'bank_%d%s' % (fc, e or '0')
                out[(x, y)] = (nm, lambda f=fc, e=e: [(slab(False), P), (bank(f, e), P), None], 1, MB_NORMAL)
            elif ch == 'P':
                part = ('n' if at(x, y - 1) != 'P' else 's' if at(x, y + 1) not in 'PC' and at(x, y + 1) != 'A' and at(x, y - 1) == 'P' else 'm') if False else None
                X0 = min(i for i in range(W) if 'P' in plan[y]) if False else None
                key = (at(x, y - 1) == 'P', at(x, y + 1) in 'PA', at(x - 1, y) in 'PCA', at(x + 1, y) in 'PCA')
                nm = 'dais_%d%d%d%d' % key
                out[(x, y)] = (nm, lambda k=key: [(ice_tile(False), P), (dais(*k), P), None], 1, MB_NORMAL)
            elif ch in 'CA':
                nm = 'dais_floor_%s' % ch
                out[(x, y)] = (nm, lambda c=ch: [(dais_floor(c == 'A'), P), None, None], 0, MB_NORMAL)
            elif ch in '.L':
                v = (x % 2, y % 2)
                out[(x, y)] = ('slab%d_%d%d' % (shadow, *v), lambda s=shadow, v=v: [(slab(s, v=v), P), None, None], 0, MB_NORMAL)
            elif ch == 'H' and len(plan) == len(RINK):
                out[(x, y)] = ('ladder', lambda: [(ladder_hole(), P), None, None], 0, 0x61)
            elif ch == 'i':
                edges = ''.join(e for e, dx, dy in D4 if at(x + dx, y + dy) not in 'ioLPCA')
                edges = ''.join(e for e in 'nswe' if e in edges)
                v = (x % 2, y % 2)
                nm = 'ice_%s%d_%d%d' % (edges or '0', shadow, *v)
                out[(x, y)] = (nm, lambda e=edges, s=shadow, v=v: [(ice_tile(s, v), P), (drift(e), P) if e else None, None], 0, MB_ICE)
            elif ch == 'o':
                v = (x % 2, y % 2)
                out[(x, y)] = ('mound%d_%d%d' % (shadow, *v), lambda s=shadow, v=v: [(ice_tile(s, v), P), (mound(), P), None], 1, MB_NORMAL)
            elif ch == 'S':
                out[(x, y)] = ('stairs', lambda: [(stone_steps(), P), None, None], 0, MB_NORMAL)
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
    ts.add('path', [(snow_path(), P), None, None])
    print('rink: from', *rink_check())
    ts.save({P: SNOW})
    names = ts.names
    write_metatile_defs('data/maps/SnowpointCity_Gym_1F_sinnoh', 'SnowpointGym', names)
    for k, plan in plans.items():
        lay = lays[k]; w, h = len(plan[0]), len(plan)
        vals = []
        for y in range(h):
            for x in range(w):
                ch = plan[y][x]
                if (x, y) in cells[k]:
                    nm, fn, col, mb = cells[k][(x, y)]
                    vals.append((names[nm] & 0x3FF) | (col << 10) | (3 << 12 if not col else 0))
                elif ch == 'H':
                    vals.append(orig_b1f[y * w + x])
                elif ch == 'H' and k == LAYOUT:
                    vals.append(0x21c | (3 << 12))
                elif ch == 'm':
                    vals.append((0x006 if x == 8 else 0x007) | (3 << 12))
                else:
                    raise SystemExit(f'no tile for {ch!r} at {x},{y} in {k}')
        if k == LAYOUT:
            for x0 in (4, 13):
                for (dx, dy) in ((0, 0), (1, 0), (0, 1), (1, 1)):
                    vals[dy * w + x0 + dx] = (names['win_%d%d' % (dx, dy)] & 0x3FF) | (1 << 10)
        rows = [[(v & 0x3FF, (v >> 10) & 3, v >> 12) for v in vals[y * w:(y + 1) * w]] for y in range(h)]
        build_cells(k, rows)
    write_events()


def write_events():
    m = 'data/maps/SnowpointCity_Gym_1F_sinnoh/map.json'
    d = json.load(open(m))
    pos = {'SE_EventScript_SinnohLeader_Candice': (9, 9, 'MOVEMENT_TYPE_FACE_DOWN'),
           'SnowpointCity_Gym_1F_EventScript_Candice': (9, 9, 'MOVEMENT_TYPE_FACE_DOWN'),
           'SnowpointCity_Gym_1F_EventScript_PtGymGuide': (10, 17, 'MOVEMENT_TYPE_FACE_LEFT')}
    for o in d['object_events']:
        o['x'], o['y'], o['movement_type'] = pos[o['script']]
        o['elevation'] = 3
        if o['script'] == 'SE_EventScript_SinnohLeader_Candice':
            o['script'] = 'SnowpointCity_Gym_1F_EventScript_Candice'   # same object, local_id kept
    d['warp_events'] = [{'x': 8, 'y': 18, 'elevation': 3, 'dest_map': 'MAP_SNOWPOINT_CITY_SINNOH', 'dest_warp_id': '6'},
                        {'x': 9, 'y': 18, 'elevation': 3, 'dest_map': 'MAP_SNOWPOINT_CITY_SINNOH', 'dest_warp_id': '6'},
                        {'x': 17, 'y': 17, 'elevation': 3, 'dest_map': 'MAP_SNOWPOINT_CITY_GYM_B1F_SINNOH', 'dest_warp_id': '0'}]
    any_ = 'BG_EVENT_PLAYER_FACING_ANY'
    d['bg_events'] = [{'type': 'sign', 'x': x, 'y': 17, 'elevation': 0, 'player_facing_dir': any_,
                       'script': 'SnowpointCity_Gym_1F_EventScript_PtGymStatue'} for x in (6, 12)]
    d['coord_events'] = []
    open(m, 'w').write(json.dumps(d, indent=2, ensure_ascii=False) + '\n')


# ---------------------------------------------------------------- FRLG-based dressing
# Both floors are dressed with FireRed's Icefall Cave / Seafoam Islands graphics, which are already
# in the project (data/tilesets/secondary/seafoam_islands_frlg + primary/general_frlg): their walls
# are placed by example - for every wall/floor cell the metatile the original FRLG maps use for the
# same arrangement of neighbours (gbaref.learn) - and their ice, rocks and snow mounds are used as
# they are. New pixels are limited to the threshold of CANDICE's landing.
FRLG_P, FRLG_S = 'data/tilesets/primary/general_frlg', 'data/tilesets/secondary/seafoam_islands_frlg'
FRLG_MAPS = ['FourIsland_IcefallCave_Entrance_Frlg', 'FourIsland_IcefallCave_1F_Frlg', 'FourIsland_IcefallCave_B1F_Frlg',
             'FourIsland_IcefallCave_Back_Frlg', 'SeafoamIslands_1F_Frlg', 'SeafoamIslands_B1F_Frlg',
             'SeafoamIslands_B2F_Frlg', 'SeafoamIslands_B3F_Frlg', 'SeafoamIslands_B4F_Frlg']
REF = {'ice': 0x34B, 'mound': 0x33F, 'rock_a': 0x35F, 'rock_b': 0x35E, 'floor': 0x281, 'snow': 0x291,
       'ladder_down': 0x2AF, 'ladder_up': 0x296, 'ladder_top': 0x28E}


def threshold():
    """Lip of snow along the bottom of CANDICE's landing: where the slide ends."""
    c = Canvas(0)
    for x in range(16):
        h = 3 + (x * 7) % 3 // 2
        for y in range(16 - h, 16):
            c.px(x, y, WH if y < 15 else SH)
        c.px(x, 15 - h, SH)
    return c


def main_frlg():
    import gbaref as G
    ts = Tileset(TS)
    L = json.load(open('data/layouts/layouts.json'))
    lay_b1 = [l for l in L['layouts'] if l.get('id') == LAYOUT_B1F][0]
    orig_b1f = ts.state.get('orig_b1f')
    print('free tile slots:', ts.free_unused(set()))
    src = G.SourceSet(FRLG_P, FRLG_S, True)
    imp = G.Importer(ts, [6, 7, 8, 9, 11, 12])
    def cl(m, c, b):
        if b == 0x20: return 'I'
        if c: return 'W'
        return 'F' if b in (0x00, 0x08) else 'X'      # water, ladders, doors, currents: not learned
    table = G.learn(src, FRLG_MAPS, cl)

    def dress(plan, special):
        """plan chars -> rows of (metatile, collision, elevation)."""
        H, W = len(plan), len(plan[0])
        cls = [['W' if ch in '#P' else 'I' if ch in 'io' else 'F' for ch in r] for r in plan]
        rows = []
        for y in range(H):
            row = []
            for x in range(W):
                ch = plan[y][x]
                key = ''.join(k if k != '#' else 'W' for k in G.neigh(cls, x, y))   # beyond the map: more rock
                if (x, y) in special:
                    row.append(special[(x, y)]); continue
                if ch == '#' and set(key) == {'W'}:
                    row.append((0x000, 1, 0)); continue      # solid interior: the black void of Emerald gyms
                if ch in '#P':
                    mid, d = G.pick(table, 'W', key)
                    if mid == REF['snow'] and ch == '#':      # FRLG's snowy rock fill: void instead
                        row.append((0x000, 1, 0)); continue
                    if (d >= 4 or mid == 0x289) and ch == '#':   # 0x289: bare snow ledge, reads as floor         # no FRLG precedent for this wall shape: a boulder reads better
                        k = 'rock_a' if (x + y) % 2 else 'rock_b'
                        row.append((imp.add(k, src, REF[k], 0), 1, 3)); continue
                    row.append((imp.add('w_%x' % mid, src, mid, 0), 1, 0))
                elif ch == 'i':
                    row.append((imp.add('ice', src, REF['ice'], MB_ICE), 0, 3))
                elif ch == 'o':
                    row.append((imp.add('mound', src, REF['mound'], 0), 1, 3))
                elif ch == 'b':
                    k = 'rock_a' if (x + y) % 2 else 'rock_b'
                    row.append((imp.add(k, src, REF[k], 0), 1, 3))
                else:
                    mid, d = G.pick(table, 'F', key)
                    narrow = (x > 0 and x + 1 < W and plan[y][x-1] in '#P' and plan[y][x+1] in '#P')
                    if d or narrow or mid == REF['snow']:   # no exact precedent / 1-wide corridor / snow patch: plain floor
                        mid = REF['floor']
                    row.append((imp.add('f_%x' % mid, src, mid, 0), 0, 3))
            rows.append(row)
        return rows

    # ---- 1F
    plan = list(RINK)
    special = {}
    for x, y in ((8, 18), (9, 18)):
        special[(x, y)] = ((0x006 if x == 8 else 0x007), 0, 3)
    special[(17, 17)] = (imp.add('ladder_down', src, REF['ladder_down'], 0x61), 0, 3)
    fl = imp.layers(src, REF['floor'])
    ts.add('threshold', [fl[0], fl[1], (threshold(), P)], 0)
    special[ACCESS] = (ts.names['threshold'], 0, 3)
    special[(9, 9)] = (imp.add('floor', src, REF['floor'], 0), 0, 3)     # CANDICE stands on plain floor
    for sx in (6, 12):                     # gym statues (primary tiles) standing on the cave floor
        ts.add('statue_top', [fl[0], fl[1], ('raw', [0x0001, 0x0002, 0x0011, 0x0012])], 0) if 'statue_top' not in ts.names else None
        ts.add('statue_base', [fl[0], ('raw', [0x0021, 0x0022, 0x0031, 0x0032]), None], 0) if 'statue_base' not in ts.names else None
        special[(sx, 16)] = (ts.names['statue_top'], 0, 3)
        special[(sx, 17)] = (ts.names['statue_base'], 1, 3)
    rows1 = dress(plan, special)
    path = imp.add('path', src, REF['floor'], 0)          # the way back opened after the battle
    imp.add('snow', src, REF['snow'], 0)
    # ---- B1F, from its own collision
    w = 17
    b1 = []
    for y in range(len(orig_b1f) // w):
        r = ''
        for x in range(w):
            v = orig_b1f[y * w + x]
            r += '#' if (v >> 10) & 3 and (v & 0x3FF) != 0x214 else '.'
        b1.append(r)
    sp1 = {(11, 22): (imp.add('ladder_up', src, REF['ladder_up'], 0x61), 0, 3),
           (11, 21): (imp.add('ladder_top', src, REF['ladder_top'], 0), 1, 3)}
    rows2 = dress(b1, sp1)
    print('rink: from', *rink_check())
    pals = dict(imp.colors); pals[P] = SNOW
    print('palette slots used:', sorted(pals))
    ts.save(pals)
    write_metatile_defs('data/maps/SnowpointCity_Gym_1F_sinnoh', 'SnowpointGym', ts.names)
    border = 0x000                         # Building primary void (black), as in every Emerald gym
    build_cells(LAYOUT, rows1, border=border)
    build_cells(LAYOUT_B1F, rows2, border=border)
    write_events()


if __name__ == '__main__':
    main_frlg()
