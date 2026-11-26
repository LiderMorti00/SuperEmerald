#!/usr/bin/env python3
"""Super Emerald: Eterna City Gym (Gardenia) - a glass greenhouse with three gardeners' clearings.

Run from the repo root: python3 tools/sfr/gyms/eterna.py
After Diamond's Eterna gym, where the gardeners have to be found among the plants: a gardener
waits in each side clearing and each clearing has its own landmark so the player can tell them
apart from the paths - RED: rose bushes, red planters and a white bench (north-west); YELLOW:
a row of tall sunflowers and yellow planters (north-east); BLUE: a lily pond with blue planters
(south-west). The iron gate north of the central clearing (10,7) opens once all three are
beaten (their trainer flags): on load and right after each of those battles (scripts.inc).

Everything is drawn here: glass walls and roof in white iron frames, iron pillars, paved paths,
lawn, tilled beds, clipped hedges with a darker front face where they meet the path.
"""
import json, os, sys
sys.path.insert(0, os.path.dirname(__file__))
from gymkit import Canvas, Tileset, build_cells, write_metatile_defs, neighbours

TS = 'data/tilesets/secondary/eterna_gym_sinnoh'
MAP = 'data/maps/EternaCity_Gym_sinnoh/map.json'
LAYOUT = 'LAYOUT_ETERNA_CITY_GYM_SINNOH'

GARDEN = [(0, 0, 0), (34, 30, 26), (92, 58, 30), (140, 92, 48), (186, 134, 78), (226, 182, 120),
          (200, 40, 52), (248, 110, 110), (232, 184, 32), (252, 236, 120), (48, 96, 208), (132, 176, 252),
          (248, 248, 248), (36, 104, 52), (72, 160, 72), (96, 64, 40)]
P = 11
K, WD, W, WL, WH, RED, REDL, YEL, YELL, BLU, BLUL, WHT, GD, G, SOIL = range(1, 16)
GLASS = [(0, 0, 0), (24, 30, 26), (36, 80, 44), (72, 132, 60), (120, 180, 84), (176, 220, 120),
         (150, 128, 96), (196, 176, 136), (228, 214, 180), (110, 52, 40), (170, 90, 64), (110, 160, 190),
         (170, 212, 230), (244, 246, 240), (168, 178, 178), (84, 56, 36)]
Q = 12
GK, LD, LF, LL, LH, PD, PV, PL, BD, BR, GLD, GL, FR, FD, SD = range(1, 16)
FLOWER = {'r': (RED, REDL), 'y': (YEL, YELL), 'b': (BLU, BLUL)}


# ------------------------------------------------------------------ ground
def lawn(shadow=''):
    """Mown lawn: calm dark green with a few short blades (walkable)."""
    c = Canvas(LD)
    for x, y in ((2, 3), (9, 1), (13, 7), (5, 10), (11, 13), (1, 13), (7, 6), (14, 2)):
        c.px(x, y, LF); c.px(x, y - 1, LF)
    if 'n' in shadow:
        for x in range(16):
            c.px(x, 0, GK); c.px(x, 1, GK if x % 2 else LD)
    return c


def paving(shadow='', seed=0):
    """Square stone flags with dark joints - the paths."""
    c = Canvas(PV)
    for y in range(16):
        for x in range(16):
            if y in (7, 15) or x == (15 if y < 8 else 7):
                c.px(x, y, PD)
            elif y in (0, 8) or x == (0 if y < 8 else 8):
                c.px(x, y, PL)
    for x, y in ((3, 3), (11, 12), (12, 4)):
        c.px(x, y, PL)
    if 'n' in shadow:
        for x in range(16):
            c.px(x, 0, PD); c.px(x, 1, PD if x % 2 else PV)
    return c


def tilled(seed=0):
    """Tilled cultivation bed with seedlings (walkable)."""
    c = Canvas(SOIL)
    for y in (3, 7, 11, 15):
        c.hline(0, 15, y, WD)
    for i, x in enumerate(range(1 + seed, 16, 4)):
        for y in (1, 5, 9, 13):
            c.px(x, y, G); c.px(x + 1, y, GD); c.px(x, y - 1, G if i % 2 else GD)
    return c


# ------------------------------------------------------------------ plants & things
def hedge(face, edges):
    """Clipped hedge, clearly raised: a bright top of round leaf clumps lit from the north-west,
    a dark leafy front face where a path lies to the south, dark outline on open sides."""
    c = Canvas(LF)
    for cy0 in (0, 8):
        for cx0 in (0, 8):
            for y in range(8):
                for x in range(8):
                    r = ((x - 3.5) ** 2 + (y - 3.5) ** 2) ** 0.5
                    v = LH if r < 1.6 and x < 4 and y < 4 else LL if r < 3 else LF if r < 4.2 else LD
                    c.px(cx0 + x, cy0 + y, v)
    if face:
        for y in range(9, 16):
            for x in range(16):
                c.px(x, y, LD if (x * 3 + y) % 5 else LF)
        c.hline(0, 15, 8, LF)
        c.hline(0, 15, 15, GK)
    if 'n' in edges: c.hline(0, 15, 0, GK)
    if 'w' in edges: c.vline(0, 0, 15, GK)
    if 'e' in edges: c.vline(15, 0, 15, GK)
    return c


def crop_bed(row):
    """Cultivation beds behind the hedges: brick-edged soil with rows of greens (blocks)."""
    c = Canvas(SOIL)
    for y in range(16):
        if y % 8 in (0, 7):
            c.hline(0, 15, y, W if y % 8 == 0 else WD)
    for y in (2, 4):
        for x in range(1, 16, 3):
            c.px(x, y, G); c.px(x + 1, y, GD); c.px(x, y + 8, G); c.px(x + 1, y + 8, GD)
            c.px(x, y - 1, G); c.px(x, y + 7, G)
    return c


def flowers(col, seed=0):
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
    """Wooden planter box full of flowers: lit top rim, front face, shadow."""
    c = Canvas(0)
    c.rect(1, 6, 14, 14, W); c.hline(1, 14, 6, WH); c.hline(1, 14, 7, WL)
    c.hline(1, 14, 14, WD); c.vline(1, 6, 14, K); c.vline(14, 6, 14, K); c.hline(1, 14, 15, K)
    for x in (5, 10):
        c.vline(x, 8, 13, WD)
    c.rect(2, 4, 13, 6, SOIL)
    a, b = FLOWER[col]
    for x in range(2, 14, 3):
        c.rect(x, 1, x + 2, 3, a); c.px(x + 1, 2, b); c.px(x + 1, 0, a)
        c.px(x + 1, 4, G); c.px(x, 5, GD); c.px(x + 2, 5, G)
    return c


def rose_bush():
    c = Canvas(0)
    for y in range(1, 15):
        for x in range(1, 15):
            if (x - 7.5) ** 2 / 49 + (y - 8) ** 2 / 42 <= 1:
                c.px(x, y, GD if (x + y) % 3 == 0 else G)
    for x, y in ((4, 4), (9, 3), (11, 7), (5, 9), (8, 11), (12, 11), (3, 12)):
        c.px(x, y, RED); c.px(x + 1, y, REDL); c.px(x, y + 1, RED)
    c.hline(3, 12, 15, K)
    return c


def sunflower():
    """Tall sunflower: big yellow head, dark centre, stem and leaves (blocks)."""
    c = Canvas(0)
    for y in range(0, 9):
        for x in range(3, 13):
            r = ((x - 7.5) ** 2 + (y - 4) ** 2) ** 0.5
            if r <= 4.6:
                c.px(x, y, WD if r < 2 else W if r < 2.6 else YEL if (x + y) % 2 else YELL)
    c.vline(7, 9, 15, GD); c.vline(8, 9, 15, G)
    c.rect(4, 11, 6, 12, G); c.px(3, 11, GD); c.rect(9, 12, 11, 13, G); c.px(12, 13, GD)
    return c


def bench():
    c = Canvas(0)
    c.rect(1, 3, 14, 5, WHT); c.hline(1, 14, 6, K); c.rect(1, 8, 14, 10, WHT); c.hline(1, 14, 11, K)
    for x in (2, 13):
        c.vline(x, 11, 15, K)
    return c


def pond(part):
    """2x2 lily pond (blocks): stone rim, water, pads. part = 'nw','ne','sw','se'."""
    c = Canvas(BLU)
    for y in range(16):
        for x in range(16):
            X = x + (16 if 'e' in part else 0); Y = y + (16 if 's' in part else 0)
            r = ((X - 15.5) ** 2 / 15.5 ** 2 + (Y - 15.5) ** 2 / 15.5 ** 2) ** 0.5
            if r > 1:
                c.px(x, y, 0)
            elif r > 0.86:
                c.px(x, y, WHT if Y < 16 else K)
            elif (X * 3 + Y) % 9 == 0:
                c.px(x, y, BLUL)
    for X, Y in ((10, 10), (20, 14), (13, 21)):
        for dx in range(-2, 3):
            for dy in range(-1, 2):
                x, y = X + dx - (16 if 'e' in part else 0), Y + dy - (16 if 's' in part else 0)
                if 0 <= x < 16 and 0 <= y < 16:
                    c.px(x, y, G if dx or dy else REDL)
    return c


def notice():
    c = Canvas(0)
    c.rect(1, 1, 14, 9, W); c.hline(1, 14, 1, WH); c.hline(1, 14, 9, WD); c.vline(1, 1, 9, K); c.vline(14, 1, 9, K)
    c.hline(3, 12, 3, WD); c.hline(3, 10, 5, WD); c.hline(3, 11, 7, WD)
    c.rect(7, 10, 8, 15, WD); c.px(7, 10, W)
    return c


def pillar(shadow=False):
    """White iron column with a stone foot (blocks)."""
    c = Canvas(0)
    c.rect(5, 0, 10, 13, FR); c.vline(9, 0, 13, FD); c.vline(10, 0, 13, FD); c.vline(5, 0, 13, GK); c.vline(10, 0, 13, GK)
    c.rect(4, 12, 11, 15, PL); c.hline(4, 11, 15, PD); c.vline(4, 12, 15, GK); c.vline(11, 12, 15, GK)
    for y in (3, 8):
        c.hline(5, 10, y, FD)
    return c


def gate(open_):
    """Iron gate between two stone posts. Shut: a row of black bars with gilded tips and a
    cross rail. Open: the leaves fold back against the posts and the path runs through."""
    c = Canvas(0)
    if not open_:
        for x in range(0, 16, 3):
            c.rect(x, 1, x + 1, 15, GK); c.px(x, 0, FR); c.px(x + 1, 0, FD)
        for y in (4, 11):
            c.hline(0, 15, y, GK); c.hline(0, 15, y + 1, FD)
        c.rect(6, 6, 9, 9, FR); c.rect(7, 7, 8, 8, GK)                       # lock plate
    else:
        for x in (0, 1, 14, 15):
            c.vline(x, 2, 15, GK)
        c.hline(0, 1, 5, FD); c.hline(14, 15, 5, FD); c.hline(0, 1, 11, FD); c.hline(14, 15, 11, FD)
    return c


def gate_post(cap):
    """Stone post with a ball cap. cap=True: just the cap, drawn above the post (walk-behind)."""
    c = Canvas(0)
    if cap:
        c.rect(4, 9, 11, 15, PL); c.vline(4, 9, 15, GK); c.vline(11, 9, 15, GK)
        c.rect(5, 4, 10, 8, FR); c.rect(6, 3, 9, 9, FR); c.px(9, 5, FD); c.px(10, 7, FD); c.hline(5, 10, 9, GK)
        return c
    c.rect(4, 0, 11, 15, PL); c.vline(4, 0, 15, GK); c.vline(11, 0, 15, GK)
    c.vline(10, 0, 14, PV); c.hline(4, 11, 15, GK)
    for y in (4, 9):
        c.hline(5, 10, y, PV)
    return c


# ------------------------------------------------------------------ glass structure
def glass_side(east, pillar_row):
    """Side wall: glass panes in white frames, leaves pressed behind; a white iron upright
    every few rows. The inner edge (towards the room) is lit."""
    c = Canvas(GL)
    for y in range(16):
        for x in range(16):
            if (x + y * 2) % 11 == 0: c.px(x, y, FR)
            if (x * 2 + y) % 13 == 0: c.px(x, y, GLD)
    for x, y in ((3, 4), (4, 5), (10, 10), (11, 11), (2, 12)):
        c.px(x, y, LF); c.px(x + 1, y, LD)
    for x in (0, 15):
        c.vline(x, 0, 15, FR)
    c.vline(7, 0, 15, FD); c.vline(8, 0, 15, FR)
    c.hline(0, 15, 0, FR)
    if pillar_row:
        c.rect(5, 0, 10, 15, FR); c.vline(10, 0, 15, FD)
    inner = 0 if east else 15
    c.vline(inner, 0, 15, GK)
    return c


def glass_top(cx, cy, w):
    """Back wall, 2 rows: row 0 the roof truss over the sky, row 1 the glass face."""
    c = Canvas(GL)
    for y in range(16):
        for x in range(16):
            X, Y = cx * 16 + x, cy * 16 + y
            if cy == 0:
                v = GL if (X + Y) % 9 else FR
                if Y in (0, 1): v = FD
                if (X - Y * 2) % 32 in (0, 1) or (X + Y * 2) % 32 in (0, 1): v = FR       # truss
                if Y >= 13: v = FR if Y == 13 else FD
            else:
                v = GL
                if (X + Y * 2) % 11 == 0: v = FR
                if X % 32 in (0, 1) or Y in (16, 17): v = FR
                if X % 32 == 16: v = FD
                if Y >= 26: v = LF if (X + Y) % 3 else LL                              # plants behind
                if Y >= 30: v = BD if Y == 31 else BR
            c.px(x, y, v)
    if cx == 0: c.vline(0, 0, 15, FD)
    if cx == w - 1: c.vline(15, 0, 15, FD)
    return c


def leaf_emblem():
    c = Canvas(0)
    for y in range(3, 14):
        for x in range(3, 13):
            if abs(x - 7.5) + abs(y - 8) * 0.8 <= 5: c.px(x, y, LL if x < 8 else LF)
    c.vline(7, 3, 14, LD)
    return c


def base_wall():
    c = Canvas(BR)
    for y in range(16):
        for x in range(16):
            if y % 4 == 3 or (x + (4 if (y // 4) % 2 else 0)) % 8 == 7:
                c.px(x, y, BD)
    c.hline(0, 15, 0, PL); c.hline(0, 15, 1, PV)
    return c


# ------------------------------------------------------------------ plan
# '.' paving  ',' lawn  k tilled bed  H hedge  r/y/b flowers  R/Y/B planters  Q rose bush
# U sunflower  W bench  O pond (2x2)  P iron pillar  S notice  G gate  p gate post  c post cap
# Z/z statue  1-3 exit mat  | glass side wall (top rows and bottom row drawn separately)
PLAN = [
    '#####################',  # 0
    '#####################',  # 1
    '|rR,WQHHH,,,,HHUH,Yy|',  # 2
    '|,,r,Qb,,,,,,,rU,,,y|',  # 3
    '|,,,,Q,,,,,,,,,U,,,,|',  # 4
    '|R,,,Q,y,,,,,y,U,,,Y|',  # 5
    '|,r,,Q,,,c,c,,,U,,y,|',  # 6
    '|HH.HHHHHpGpHHHHH.HH|',  # 7
    '|HH.HHP,......PHH.HH|',  # 8
    '|HH.HHH,.S....,HH.HH|',  # 9
    '|HH.HH,.......,HH.HH|',  # 10
    '|...................|',  # 11
    '|HHHHH,.......,HHHHH|',  # 12
    '|HHHHHH,,....,HHHHHH|',  # 13
    '|HHHHHHHH,..HHHHHHHH|',  # 14
    '|b,B,bOOH,..HHHHHHHH|',  # 15
    '|,,,b,OOH,..HHHHHHHH|',  # 16
    '|,,b,....,..HHHHHHHH|',  # 17
    '|B,,,b,HHH..HHHHHHHH|',  # 18
    '|,b,B,,HHH..HHHHHHHH|',  # 19
    '|HHHHHHHH,..,HHHHHHH|',  # 20
    '|HHHHH,,,.....,,,HHH|',  # 21
    '|HHHH,,Z,.....,Z,,HH|',  # 22
    '|HHHH,,z,.....,z,,HH|',  # 23
    '|HHHk,,,.......,k,HH|',  # 24
    '|HHkkk,,.123.,,kk,HH|',  # 25
    '#####################',  # 26
]

WALK = set('.,krybcZ123')


def main():
    plan = list(PLAN)
    for r in plan:
        assert len(r) == 21, r
    H, Wd = len(plan), 21
    ts = Tileset(TS)
    print('free tile slots:', ts.free_unused({0x236, 0x237, 0x230, 0x231, 0x232}))
    cells = [[None] * Wd for _ in range(H)]
    adds = {}

    def put(x, y, name, layers, col, elev=3, mb=0):
        if name not in adds:
            adds[name] = (layers, mb)
        cells[y][x] = (name, col, elev)

    walk = lambda ch: ch in WALK
    ground = lambda x, y, sh: ('pave' if plan[y][x] in '.123S' else 'lawn')
    for y in range(H):
        for x in range(Wd):
            ch = plan[y][x]
            north = plan[y - 1][x] if y else '#'
            sh = 'n' if north in 'H#|' or (y == 2) else ''
            base_nm = ('pave' if ch in '.S123' else 'lawn') + sh
            base = (paving(sh) if ch in '.S123' else lawn(sh), Q)
            if y < 2:
                put(x, y, 'top_%d_%d' % (x, y), [(glass_top(x, y, Wd), Q), None, None], 1, 0)
            elif y == H - 1:
                put(x, y, 'base', [(base_wall(), Q), None, None], 1, 0)
            elif ch == '|':
                east = x == Wd - 1
                pr = y % 6 == 2
                put(x, y, 'side_%d%d' % (east, pr), [(glass_side(east, pr), Q), None, None], 1, 0)
            elif ch == 'H' and not any(walk(plan[yy][xx]) for yy in range(max(0, y - 1), min(H, y + 2))
                                       for xx in range(max(0, x - 1), min(Wd, x + 2))) and y > 2:
                put(x, y, 'crop', [(crop_bed(0), P), None, None], 1)
            elif ch == 'H':
                face = walk(plan[y + 1][x]) if y + 1 < H else False
                edges = neighbours(plan, x, y, walk)
                edges = ''.join(e for e in edges if e != 's')
                put(x, y, 'hedge_%d_%s' % (face, edges or '0'), [(hedge(face, edges), Q), None, None], 1)
            elif ch in '.,':
                put(x, y, base_nm, [base, None, None], 0)
            elif ch == 'k':
                put(x, y, 'tilled', [(tilled(), P), None, None], 0)
            elif ch in 'ryb':
                put(x, y, 'fl_%s%s' % (ch, sh), [base, (flowers(ch, (x + y) % 2), P), None], 0)
                cells[y][x] = ('fl_%s%s' % (ch, sh), 0, 3)
            elif ch in 'RYB':
                put(x, y, 'planter_%s' % ch.lower(), [(lawn(), Q), (planter(ch.lower()), P), None], 1)
            elif ch == 'Q':
                put(x, y, 'rose', [(lawn(), Q), (rose_bush(), P), None], 1)
            elif ch == 'U':
                put(x, y, 'sunflower', [(lawn(), Q), (sunflower(), P), None], 1)
            elif ch == 'W':
                put(x, y, 'bench', [(lawn(sh), Q), (bench(), P), None], 1)
            elif ch == 'O':
                part = ('n' if plan[y + 1][x] == 'O' else 's') + ('w' if plan[y][x + 1] == 'O' else 'e')
                put(x, y, 'pond_' + part, [(lawn(), Q), (pond(part), P), None], 1)
            elif ch == 'P':
                put(x, y, 'pillar', [(paving() if plan[y][x - 1] in '.' else lawn(), Q), (pillar(), Q), None], 1)
                cells[y][x] = ('pillar', 1, 3)
            elif ch == 'S':
                put(x, y, 'notice', [(paving(), Q), (notice(), P), None], 1)
            elif ch == 'G':
                put(x, y, 'gate_closed', [(paving(), Q), None, (gate(False), Q)], 1)
                adds['gate_open'] = ([(paving(), Q), None, (gate(True), Q)], 0)
            elif ch == 'p':
                put(x, y, 'gatepost', [(paving(), Q), (gate_post(False), Q), None], 1)
            elif ch == 'c':
                put(x, y, 'postcap', [(lawn(), Q), None, (gate_post(True), Q)], 0)
            elif ch == 'Z':
                put(x, y, 'statue_top', [(paving(sh), Q), None, ('mt', 0x236, 2)], 0)
            elif ch == 'z':
                put(x, y, 'statue_base', [(paving(), Q), ('mt', 0x237, 1), None], 1)
            elif ch in '123':
                cells[y][x] = (0x22f + int(ch), 0, 3)
            else:
                raise SystemExit(f'no tile for {ch!r} at {x},{y}')
    # fix the pillar base: paving under the pillars that stand on the paths
    for name, (layers, mb) in adds.items():
        ts.add(name, layers, mb)
    for i, mid in enumerate((0x230, 0x231, 0x232)):                     # door mat on paving
        mat = Canvas(0)
        mat.rect(0, 3, 15, 15, LD); mat.hline(0, 15, 3, LF); mat.hline(0, 15, 15, GK)
        for x in range(1, 15, 3):
            mat.vline(x, 5, 13, LF)
        ts.replace(mid, [(paving(), Q), (mat, Q), None])
    ts.add('emblem', [(glass_top(10, 1, Wd), Q), (leaf_emblem(), P), None])
    ts.save({P: GARDEN, Q: GLASS})
    names = ts.names
    write_metatile_defs('data/maps/EternaCity_Gym_sinnoh', 'EternaGym', names)
    rows = []
    for y in range(H):
        row = []
        for x in range(Wd):
            v = cells[y][x]
            if y == H - 1 and 9 <= x <= 11:
                row.append((names['base'], 1, 0)); continue
            nm, col, el = v
            mid = names[nm] if isinstance(nm, str) else nm
            row.append((mid, col, el))
        rows.append(row)
    rows[1][10] = (names['emblem'], 1, 0)
    build_cells(LAYOUT, rows, border=names['top_0_0'])

    d = json.load(open(MAP))
    d['warp_events'] = [{'x': x, 'y': 25, 'elevation': 0, 'dest_map': 'MAP_ETERNA_CITY_SINNOH', 'dest_warp_id': '2'}
                        for x in (9, 10, 11)]
    pos = {
        'EternaCity_Gym_EventScript_Angela': (3, 4, 'MOVEMENT_TYPE_FACE_DOWN', '3'),     # red clearing
        'EternaCity_Gym_EventScript_Jenna': (17, 4, 'MOVEMENT_TYPE_FACE_DOWN', '3'),     # yellow clearing
        'EternaCity_Gym_EventScript_Caroline': (3, 17, 'MOVEMENT_TYPE_FACE_RIGHT', '3'),  # blue clearing
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
