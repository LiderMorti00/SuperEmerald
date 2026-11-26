#!/usr/bin/env python3
"""Super Emerald: Sunyshore City Gym (Volkner) - rotating walkway crosses over a night sea.

Run from the repo root: python3 tools/sfr/gyms/sunyshore.py
Adapted from the Platinum gym (pret/pokeplatinum src/overlay008/gym_features.c, SunyshoreGym_*):
floor buttons turn the walkway gears 90 degrees, a "reverse" button turns them back.
On GBA each gear is a 3x3 turntable drawn with metatiles: a round base, a hub that is always
walkable and three walkway arms (a T). The missing arm is the turntable's state:
0 = north, 1 = east, 2 = south, 3 = west. Pressing a normal button turns it clockwise (+1),
the reverse button counter-clockwise (-1). scripts.inc redraws arms and hub (graphics and
collision together) on every turn and on load. Turntable 1 (by the entrance, orange) is turned
by the button in the hall; turntable 2 (blue) by the two buttons on the hub. States live in
VAR_TEMP_1 / VAR_TEMP_2 and reset to 0 when the player leaves; check() below walks every
reachable (position, state) pair and asserts the player can always get back to the door and
VOLKNER is reachable.
"""
import json, os, sys
from collections import deque
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
    """Raised dark-metal walkway. Top: riveted plate (or grating on narrow catwalks), light rim
    where it meets the sea; on the south side the walkway's front face shows (rows 12-15)."""
    c = Canvas(PM)
    if grate:
        for y in range(16):
            for x in range(16):
                c.px(x, y, PD if (x % 4 == 0 or y % 4 == 0) else NV2 if (x + y) % 2 else PM)
    else:
        c.hline(0, 15, 0, PL); c.vline(0, 0, 15, PL); c.hline(0, 15, 15, PD); c.vline(15, 0, 15, PD)
        for x, y in ((2, 2), (13, 2), (2, 13), (13, 13)):
            c.px(x, y, PH); c.px(x + 1, y + 1, PD)
        for i in range(4, 12):
            c.px(i, 15 - i, PL if i % 2 else PM)
    if 'n' in edges:
        c.hline(0, 15, 0, BK); c.hline(0, 15, 1, PW); c.hline(0, 15, 2, PH)
    if 'w' in edges:
        c.vline(0, 0, 15, BK); c.vline(1, 0, 15, PW)
    if 'e' in edges:
        c.vline(15, 0, 15, BK); c.vline(14, 0, 15, PH)
    if 's' in edges:
        c.hline(0, 15, 11, PW)
        for y in range(12, 16):
            c.hline(0, 15, y, PD if y < 15 else BK)
        for x in range(1, 16, 5):
            c.px(x, 13, PL)
        if 'w' in edges: c.vline(0, 11, 15, BK)
        if 'e' in edges: c.vline(15, 11, 15, BK)
    return c


def sea_shadow(w=True, e=True):
    """Sea right below a walkway's front face: the cast shadow and a line of foam."""
    c = sea()
    for y in range(0, 4):
        c.hline(0, 15, y, BK if y < 2 else NV1)
    for x in range(0, 16, 3):
        c.px(x, 4, NV3); c.px(x + 1, 4, PH)
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



def turntable(missing, sector):
    """48x48 picture of a turntable whose arm `missing` (0 N, 1 E, 2 S, 3 W) is retracted."""
    col, dk = CABLE[sector]
    g = [[0] * 48 for _ in range(48)]
    sea_c = sea()
    for y in range(48):
        for x in range(48):
            g[y][x] = sea_c.p[y % 16][x % 16]
            r = ((x - 23.5) ** 2 + (y - 21.5) ** 2) ** 0.5
            rf = ((x - 23.5) ** 2 + (y - 24.5) ** 2) ** 0.5
            if r > 21.5 and rf <= 21.5 and y > 21:          # the base's front face (thickness 3px)
                g[y][x] = BK if rf > 20.5 else PD if (x % 6) else PL
            if r <= 21.5:
                g[y][x] = PW if r > 20.5 else YS if r > 19 and ((x + y) // 3) % 2 else BK if r > 19 else PD if r > 16 else PM
                if 16 < r <= 19 and (x * 7 + y * 3) % 11 == 0:
                    g[y][x] = PL
    arms = {0: (19, 0, 28, 18), 1: (30, 19, 47, 28), 2: (19, 30, 28, 47), 3: (0, 19, 18, 28)}
    for d, (x0, y0, x1, y1) in arms.items():
        if d == missing:                          # retracted arm: an open slot in the base
            for y in range(y0, y1 + 1):
                for x in range(x0, x1 + 1):
                    r = ((x - 23.5) ** 2 + (y - 21.5) ** 2) ** 0.5
                    if r <= 20.5:
                        g[y][x] = BK if (x in (x0, x1) or y in (y0, y1)) else NV1 if (x + y) % 3 else NV2
            continue
        for y in range(y0, y1 + 1):
            for x in range(x0, x1 + 1):
                edge = (x in (x0, x1)) if d in (0, 2) else (y == y0)
                g[y][x] = PW if edge else (PD if (x % 4 == 0 or y % 4 == 0) else PM)
                if d in (1, 3) and y >= y1 - 2:          # side arms show their front face
                    g[y][x] = BK if y == y1 else PD
                if d in (0, 2) and x == x1:
                    g[y][x] = BK
    for y in range(16, 32):                  # hub
        for x in range(16, 32):
            r = ((x - 23.5) ** 2 + (y - 23.5) ** 2) ** 0.5
            if r <= 8:
                g[y][x] = PW if r > 7 else dk if r > 5.5 else col
    # arrow in the hub pointing at the retracted arm, so the state reads at a glance
    tip = {0: [(23, 18), (24, 18), (22, 19), (25, 19)], 1: [(29, 23), (29, 24), (28, 22), (28, 25)],
           2: [(23, 29), (24, 29), (22, 28), (25, 28)], 3: [(18, 23), (18, 24), (19, 22), (19, 25)]}.get(missing, [])
    for x, y in tip:
        g[y][x] = BK
    return g


def cut(g, cx, cy):
    c = Canvas(0)
    c.p = [row[cx * 16:cx * 16 + 16] for row in g[cy * 16:cy * 16 + 16]]
    return c


def floor_button(sector, reverse):
    """A raised round switch on the walkway: hazard-striped ring, dark collar, coloured cap
    with a turning arrow (backwards for the reverse switch) and a shadow on its south side."""
    c = plate('', False)
    col, dk = CABLE[sector]
    for y in range(16):
        for x in range(16):
            r = ((x - 7.5) ** 2 + (y - 7.0) ** 2) ** 0.5
            rs = ((x - 7.5) ** 2 + (y - 9.0) ** 2) ** 0.5
            if r > 7.5 and rs <= 7.5:
                c.px(x, y, BK)                                   # shadow / side of the base
            if r <= 7.5:
                ang = (x - 7.5) + (y - 7)
                c.px(x, y, BK if r > 6.8 else (YS if int((x + y) / 2) % 2 else BK) if r > 5.3
                     else PD if r > 4.6 else dk if r > 3.6 else col)
    c.px(6, 5, PW); c.px(5, 6, PW)                               # highlight on the cap
    arrow = [(9, 5), (10, 6), (10, 7), (9, 8)]
    for x, y in arrow:
        c.px(15 - x if reverse else x, y, PW)
    tip = [(9, 9), (10, 9), (8, 8)] if not reverse else [(6, 9), (5, 9), (7, 8)]
    for x, y in tip:
        c.px(x, y, PW)
    return c


def room(cx, cy):
    """VOLKNER's control room shell, 8x6 tiles (x5-12, y0-5): steel wall with a lightning
    emblem and lamps on its face, steel pillars down the sides."""
    c = Canvas(0)
    for y in range(16):
        for x in range(16):
            X, Y = cx * 16 + x, cy * 16 + y
            if cy == 0:                                   # wall top
                v = BK if Y in (0, 15) else PD if Y < 4 else PM if Y < 13 else PD
                if 4 <= Y < 13 and X % 16 in (0, 15): v = PD
            elif cy == 1:                                 # wall face
                v = PL if Y == 16 else PM if Y < 26 else PD
                if X % 32 in (0, 31) or Y == 31: v = BK
                if 27 <= Y <= 29: v = YS if ((X + Y) // 2) % 2 else BK       # safety band
                if 19 <= Y <= 23 and X % 32 in (6, 7, 24, 25): v = CY         # wall lamps
            else:                                         # side pillars
                v = PM
                left = cx == 0
                edge = 15 if left else 0
                if x == edge: v = BK
                elif (left and x >= 12) or (not left and x <= 3): v = PL if x in (12, 3) else PD
                if y % 8 == 0: v = PD
            c.px(x, y, v)
    if cy == 1 and cx in (3, 4):                          # lightning emblem across the middle
        bolt = [(10, 1), (9, 2), (8, 3), (7, 4), (6, 5), (7, 6), (8, 6), (9, 6), (8, 7), (7, 8), (6, 9), (5, 10)]
        for bx, by in bolt:
            X = 16 + bx - (cx - 3) * 16
            for dx in (0, 1, 2):
                if 0 <= X - 8 + dx < 16:
                    c.px(X - 8 + dx, by + 1, PW if dx == 1 else CY)
    return c


def build_tileset(walk_kinds, cables):
    ts = Tileset(TS)
    print('free tile slots:', ts.free_unused({0x216, 0x21e, 0x212, 0x213, 0x24a, 0x24b, 0x207, 0x20d, 0x20e,
                                               0x252, 0x253, 0x20f}))
    for kind in sorted(walk_kinds):
        grate, edges, stripe = kind
        c = plate(edges, grate)
        if stripe:
            stripes(c, 12, 15)
        ts.add('walk_%s%s%s' % ('g' if grate else 'p', edges or '0', '_y' if stripe else ''), [(c, P2), None, None])
    ts.add('sea', [(sea(), P2), None, None])
    ts.add('sea_sh', [(sea_shadow(), P2), None, None])
    for cy in range(6):
        for cx in range(8):
            if cy < 2 or cx in (0, 7):
                ts.add('room_%d_%d' % (cx, cy), [(room(cx, cy), P2), None, None])
    ts.replace(0x216, [(plate('', False), P2), None, ('mt', 0x216, 2)])      # statues stand on metal
    ts.replace(0x21e, [(plate('', False), P2), ('mt', 0x21e, 1), None])
    for (dirs, sector, on_walk) in sorted(cables):
        base = plate('we', True) if on_walk else None
        ts.add('cable%d_%s%s' % (sector, dirs, '_w' if on_walk else ''), [(cable(dirs, sector, base), P2), None, None])
    pos = {'nw': (0, 0), 'n': (1, 0), 'ne': (2, 0), 'w': (0, 1), 'c': (1, 1), 'e': (2, 1),
           'sw': (0, 2), 's': (1, 2), 'se': (2, 2)}
    for sector in (1, 2):
        ts.add('button%d' % sector, [(floor_button(sector, False), P2), None, None])
        ts.add('button%d_rev' % sector, [(floor_button(sector, True), P2), None, None])
        for missing in range(4):
            g = turntable(missing, sector)
            ts.add('tt%d_c%d' % (sector, missing), [(cut(g, 1, 1), P2), None, None])
        g_all = turntable(-1, sector)            # all arms out
        g_none = [row[:] for row in g_all]
        for d in range(4):                       # arms in: take each arm from a picture missing it
            gm = turntable(d, sector)
            k = 'nesw'[d]
            cx, cy = pos[k]
            ts.add('tt%d_%s_on' % (sector, k), [(cut(g_all, cx, cy), P2), None, None])
            ts.add('tt%d_%s_off' % (sector, k), [(cut(gm, cx, cy), P2), None, None])
        for k in ('nw', 'ne', 'sw', 'se'):
            ts.add('tt%d_%s' % (sector, k), [(cut(g_all, *pos[k]), P2), None, None])
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


# '#' sea, '.' walkway, '1'/'2' turntable centres (3x3 around them), b/B buttons (b normal, B reverse;
# sector from the turntable they sit nearest), T/t statue, m exit mat, letters A-N VOLKNER's room walls.
PLAN = [
    "#####ABBCDBBE##",   # 0  wall top
    "#####FGGHIGGJ##",   # 1  wall face
    "#####K......N##",   # 2  VOLKNER (8,2)
    "#####K......N##",   # 3
    "#####K......N##",   # 4
    "#####K......N##",   # 5
    "########..#####",   # 6  ZACHERY alcove (9,6) watches (8,6)
    "#.....##.##...#",   # 7  west platform 2 x1-5 rows 7-10, east platform 2 x11-13
    "#.....#~~~#...#",   # 8  turntable 2 (centre 8,9)
    "#......~2~....#",   # 9
    "#.....#~~~#...#",   # 10
    "########.######",   # 11
    "####.b.....B.##",   # 12 hub x4-12: button (5,12), reverse button (11,12)
    "######.#.#.####",   # 13 alcoves: DESTINY (6,13), JERRY (10,13)
    "########.######",   # 14
    "#.....#~~~#...#",   # 15 turntable 1 (centre 8,16); west platform 1 x1-5 rows 15-16
    "#......~1~....#",   # 16 east platform 1 x11-13
    "#######~~~#####",   # 17
    "###.......b...#",   # 18 hall x3-13: button (10,18), right beside turntable 1
    "###.T.......T.#",   # 19 statues (4,19) and (12,19)
    "###.t.......t.#",   # 20
    "#######mm######",   # 21 exit mat
]
TURNTABLES = {1: (8, 16), 2: (8, 9)}
BUTTONS = {(10, 18): ('Button1', 1, False), (5, 12): ('Button2', 2, False), (11, 12): ('Button2Rev', 2, True)}
CABLES = {   # (x, y): (dirs, sector) - each button wired to its turntable
    (10, 17): ('sw', 1),
    (5, 11): ('se', 2), (6, 11): ('we', 2), (7, 11): ('nw', 2),
    (11, 11): ('sw', 2), (10, 11): ('we', 2), (9, 11): ('ne', 2),
}
STRIPES = {(8, 18), (8, 14), (8, 11), (8, 13), (8, 7), (6, 9), (10, 9), (6, 16), (10, 16)}
ARM = {0: (0, -1), 1: (1, 0), 2: (0, 1), 3: (-1, 0)}


def walkable(plan, x, y, st):
    """Is (x, y) walkable with turntable states st = {1: s1, 2: s2}?"""
    H, W = len(plan), len(plan[0])
    if not (0 <= x < W and 0 <= y < H):
        return False
    for t, (cx, cy) in TURNTABLES.items():
        if abs(x - cx) <= 1 and abs(y - cy) <= 1:
            if (x, y) == (cx, cy):
                return True
            for d, (dx, dy) in ARM.items():
                if (x, y) == (cx + dx, cy + dy):
                    return d != st[t]
            return False
    return plan[y][x] in '.bBTm'


def check(plan):
    """Every reachable (position, states) can get back to the door; VOLKNER is reachable."""
    start = ((7, 21), 0, 0)
    def nxt(node):
        (x, y), s1, s2 = node
        for dx, dy in ARM.values():
            nx, ny = x + dx, y + dy
            if not walkable(plan, nx, ny, {1: s1, 2: s2}):
                continue
            a, b = s1, s2
            if (nx, ny) in BUTTONS:
                _, t, rev = BUTTONS[(nx, ny)]
                if t == 1: a = (a + (3 if rev else 1)) % 4
                else: b = (b + (3 if rev else 1)) % 4
            yield ((nx, ny), a, b)
    seen = {start}; q = deque([start])
    while q:
        n = q.popleft()
        for m in nxt(n):
            if m not in seen:
                seen.add(m); q.append(m)
    assert any(p == (8, 3) for p, _, _ in seen), 'VOLKNER unreachable'
    for n in seen:            # can each state get home?
        s2 = {n}; q2 = deque([n]); ok = False
        while q2 and not ok:
            for m in nxt(q2.popleft()):
                if m[0] == (7, 21):
                    ok = True; break
                if m not in s2:
                    s2.add(m); q2.append(m)
        assert ok, f'trapped at {n}'
    return len(seen)


def main():
    plan = [list(r) for r in PLAN]
    for r in plan:
        assert len(r) == 15, ''.join(r)
    print('reachable states checked:', check(PLAN))
    H, W = len(plan), len(plan[0])
    st0 = {1: 0, 2: 0}
    kinds, cells = set(), {}
    for y in range(H):
        for x in range(W):
            if plan[y][x] == '.' and (x, y) not in CABLES:
                edges = ''.join(e for e, (dx, dy) in (('n', (0, -1)), ('s', (0, 1)), ('w', (-1, 0)), ('e', (1, 0)))
                                if not (walkable(PLAN, x + dx, y + dy, {1: -1, 2: -1}) or
                                        (0 <= x + dx < W and 0 <= y + dy < H and PLAN[y + dy][x + dx] in 'KNtT~12')))
                grate = 'w' in edges and 'e' in edges or 'n' in edges and 's' in edges
                k = (grate, edges, (x, y) in STRIPES)
                kinds.add(k); cells[(x, y)] = k
    cab = {(d, sec, False) for (x, y), (d, sec) in CABLES.items()}
    names = build_tileset(kinds, cab)
    n = lambda k: names[k]
    write_metatile_defs('data/maps/SunyshoreCity_Gym_sinnoh', 'SunyshoreGym', names)
    legend = {
        '#': (n('sea'), 1, 0),
        'T': (0x216, 0, 3), 't': (0x21e, 1, 3), 'm': (0x006, 0, 3), 'M': (0x007, 0, 3),
        'A': (0x212, 1, 0), 'B': (0x213, 1, 0), 'C': (0x24a, 1, 0), 'D': (0x24b, 1, 0), 'E': (0x207, 1, 0),
        'F': (0x20d, 1, 0), 'G': (0x20e, 1, 0), 'H': (0x252, 1, 0), 'I': (0x253, 1, 0), 'J': (0x20f, 1, 0),
        'K': (0x20d, 1, 0), 'N': (0x20f, 1, 0),
    }
    plan[21][8] = 'M'
    out = []
    def key(m, col, el):
        ch = chr(0x100 + len(legend)); legend[ch] = (m, col, el); return ch
    for y in range(H):
        line = ''
        for x in range(W):
            ch = plan[y][x]
            tt = [t for t, (cx, cy) in TURNTABLES.items() if abs(x - cx) <= 1 and abs(y - cy) <= 1]
            if tt:
                t = tt[0]; cx, cy = TURNTABLES[t]
                dx, dy = x - cx, y - cy
                if (dx, dy) == (0, 0):
                    line += key(n('tt%d_c0' % t), 0, 3)
                elif dx and dy:
                    line += key(n('tt%d_%s%s' % (t, 'n' if dy < 0 else 's', 'w' if dx < 0 else 'e')), 1, 3)
                else:
                    d = [k for k, v in ARM.items() if v == (dx, dy)][0]
                    on = d != st0[t]
                    line += key(n('tt%d_%s_%s' % (t, 'nesw'[d], 'on' if on else 'off')), 0 if on else 1, 3)
            elif (x, y) in BUTTONS:
                _, t, rev = BUTTONS[(x, y)]
                line += key(n('button%d%s' % (t, '_rev' if rev else '')), 0, 3)
            elif (x, y) in CABLES:
                d_, sec = CABLES[(x, y)]
                line += key(n('cable%d_%s' % (sec, d_)), 1, 0)
            elif ch in 'ABCDEFGHIJKN':
                line += key(n('room_%d_%d' % (x - 5, y)), 1, 0)
            elif ch == '#' and y > 0 and (plan[y - 1][x] in '.bBTtmM' or (x, y - 1) in cells):
                line += key(n('sea_sh'), 1, 0)
            elif (x, y) in cells:
                grate, edges, s_ = cells[(x, y)]
                line += key(n('walk_%s%s%s' % ('g' if grate else 'p', edges or '0', '_y' if s_ else '')), 0, 3)
            else:
                line += ch
        out.append(line)
    build_map(LAYOUT, out, legend, border=n('sea'))

    d = json.load(open(MAP))
    d['warp_events'] = [{'x': x, 'y': 21, 'elevation': 0, 'dest_map': 'MAP_SUNYSHORE_CITY_SINNOH', 'dest_warp_id': '8'}
                        for x in (7, 8)]
    pos = {
        'SunyshoreCity_Gym_EventScript_Meghan': (2, 16, 'MOVEMENT_TYPE_FACE_RIGHT', '3'),   # west platform 1
        'SunyshoreCity_Gym_EventScript_Forrest': (1, 15, 'MOVEMENT_TYPE_FACE_RIGHT', '2'),
        'SunyshoreCity_Gym_EventScript_Lonnie': (12, 16, 'MOVEMENT_TYPE_FACE_LEFT', '1'),   # east platform 1
        'SunyshoreCity_Gym_EventScript_Destiny': (6, 13, 'MOVEMENT_TYPE_FACE_UP', '1'),     # hub, by the button
        'SunyshoreCity_Gym_EventScript_Jerry': (10, 13, 'MOVEMENT_TYPE_FACE_UP', '1'),      # hub, by the reverse button
        'SunyshoreCity_Gym_EventScript_Preston': (2, 9, 'MOVEMENT_TYPE_FACE_RIGHT', '3'),   # west platform 2
        'SunyshoreCity_Gym_EventScript_Tiera': (12, 9, 'MOVEMENT_TYPE_FACE_LEFT', '1'),     # east platform 2
        'SunyshoreCity_Gym_EventScript_Zachery': (9, 6, 'MOVEMENT_TYPE_FACE_LEFT', '1'),    # VOLKNER's walkway
        'SE_EventScript_SinnohLeader_Volkner': (8, 2, 'MOVEMENT_TYPE_FACE_DOWN', '0'),
        'SunyshoreCity_Gym_EventScript_PtGymGuide': (6, 20, 'MOVEMENT_TYPE_FACE_RIGHT', '0'),
    }
    for o in d['object_events']:
        x, y, mv, s = pos[o['script']]
        o['x'], o['y'], o['movement_type'], o['elevation'] = x, y, mv, 3
        if o['trainer_type'] != 'TRAINER_TYPE_NONE':
            o['trainer_sight_or_berry_tree_id'] = s
    any_ = 'BG_EVENT_PLAYER_FACING_ANY'
    sign = lambda x, y, s: {'type': 'sign', 'x': x, 'y': y, 'elevation': 0, 'player_facing_dir': any_,
                            'script': 'SunyshoreCity_Gym_EventScript_' + s}
    d['bg_events'] = [sign(4, 20, 'PtGymStatue'), sign(12, 20, 'PtGymStatue')]
    d['coord_events'] = [{'type': 'trigger', 'x': x, 'y': y, 'elevation': 3, 'var': 'VAR_TEMP_0', 'var_value': '0',
                          'script': 'SunyshoreCity_Gym_EventScript_' + s} for (x, y), (s, _, _) in BUTTONS.items()]
    open(MAP, 'w').write(json.dumps(d, indent=2, ensure_ascii=False) + '\n')


if __name__ == '__main__':
    main()
