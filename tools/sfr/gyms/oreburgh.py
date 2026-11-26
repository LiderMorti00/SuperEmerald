#!/usr/bin/env python3
"""Super Emerald: Oreburgh City Gym (Roark) - a mine dig with two rock checkpoints.

Run from the repo root: python3 tools/sfr/gyms/oreburgh.py
The corridor narrows twice between rocks; a gym trainer watches each gap and a short
detour behind the rocks (out of the trainer's sight) lets the player avoid the battle.
"""
import json, os, sys
sys.path.insert(0, os.path.dirname(__file__))
from gymkit import Canvas, Tileset, build_map

TS = 'data/tilesets/secondary/oreburgh_gym_sinnoh'
MAP = 'data/maps/OreburghCity_Gym_sinnoh/map.json'
LAYOUT = 'LAYOUT_OREBURGH_CITY_GYM_SINNOH'

MINE = [(0, 0, 0), (30, 22, 18), (66, 54, 46), (102, 86, 72), (142, 124, 106), (184, 168, 148),
        (112, 80, 48), (150, 110, 66), (184, 144, 92), (212, 180, 124), (86, 52, 28), (136, 88, 48),
        (70, 74, 86), (128, 136, 152), (200, 206, 218), (244, 196, 70)]
PM = 10
K, RD, R, RL, RH, DD, D, DL, DH, WD, W, MD, M, MH, ORE = range(1, 16)


def noise(c, cols, seed, density):
    import random
    rnd = random.Random(seed)
    for y in range(16):
        for x in range(16):
            if rnd.random() < density:
                c.px(x, y, rnd.choice(cols))


def dirt(seed=1, dug=False):
    c = Canvas(DL if not dug else D)
    noise(c, [D, DH] if not dug else [DD, DL], seed, 0.18)
    if dug:   # freshly dug: loose clumps
        for x, y in ((2, 3), (9, 2), (5, 9), (12, 11), (1, 13)):
            c.rect(x, y, x + 2, y + 1, DD); c.hline(x, x + 2, y - 1, DH); c.px(x + 1, y + 2, DD)
    return c


def pebbles(seed=3):
    """Loose debris: small, flat, walkable - unlike the round boulders, which block."""
    c = dirt(seed)
    for x, y in ((3, 4), (11, 10), (6, 12), (12, 3), (8, 7)):
        c.px(x, y, RL); c.px(x + 1, y, RD)
    return c


def rock_wall_top(seed=5):
    """Rock mass seen from above: irregular chunks (tiling cells), lit on their north-west edge
    and split by dark cracks."""
    import random
    rnd = random.Random(seed)
    pts = [(rnd.uniform(0, 16), rnd.uniform(0, 16)) for _ in range(5)]
    def owner(x, y):
        best = None
        for i, (px, py) in enumerate(pts):
            dx = min(abs(x - px), 16 - abs(x - px)); dy = min(abs(y - py), 16 - abs(y - py))
            d = dx * dx + dy * dy
            if best is None or d < best[0]: best = (d, i)
        return best[1]
    c = Canvas(RD)
    for y in range(16):
        for x in range(16):
            o = owner(x, y)
            if owner((x + 1) % 16, y) != o or owner(x, (y + 1) % 16) != o:
                c.px(x, y, K)
            elif owner((x - 1) % 16, y) != o or owner(x, (y - 1) % 16) != o:
                c.px(x, y, R)
            elif (x * 7 + y * 3 + o) % 11 == 0:
                c.px(x, y, R)
    return c


def rock_wall_face(seed=7, ore=False):
    """Stratified dig face, after Oreburgh's cut walls: bands of rock, clay and coal-dark seams."""
    import random
    rnd = random.Random(seed)
    c = Canvas(R)
    bands = [(0, RL), (3, R), (6, DD), (8, RD), (10, D), (13, R)]
    for y in range(16):
        col = [b for y0, b in bands if y >= y0][-1]
        c.hline(0, 15, y, col)
    for y0, _ in bands[1:]:                      # wavy band boundaries
        for x in range(16):
            if rnd.random() < 0.35:
                c.px(x, y0 - 1 if rnd.random() < .5 else y0, K if y0 in (6, 10) else RD)
    noise(c, [RH, RD], seed + 1, 0.08)
    c.hline(0, 15, 15, K); c.hline(0, 15, 14, RD)
    if ore:
        for x, y in ((3, 4), (4, 5), (5, 5), (10, 9), (11, 8), (12, 9), (7, 11)):
            c.px(x, y, ORE); c.px(x + 1, y, RH)
    return c


def wall_rim(side):
    """Rock mass seen from above with a lit edge where it drops to the dig floor."""
    c = rock_wall_top(17 if side == 'w' else 19)
    for y in range(16):
        x0 = 13 if side == 'w' else 0
        for k in range(3):
            c.px(x0 + k, y, (RL, R, RD)[k] if side == 'w' else (RD, R, RL)[k])
    return c


def beam_face():
    """Rock face with a wooden mine support."""
    c = rock_wall_face(11)
    c.rect(2, 0, 4, 15, W); c.vline(2, 0, 15, WD); c.rect(11, 0, 13, 15, W); c.vline(13, 0, 15, WD)
    c.rect(2, 0, 13, 2, W); c.hline(2, 13, 2, WD)
    return c


def lantern_face():
    c = rock_wall_face(13)
    c.rect(6, 3, 9, 4, MD); c.rect(6, 5, 9, 9, ORE); c.rect(7, 6, 8, 8, MH); c.hline(6, 9, 10, MD)
    return c


def boulder():
    """Boulder on dirt (blocks)."""
    c = dirt(9)
    c.art(1, 1, ['....RRRRRR....',
                 '..RRLLLLLRRR..',
                 '.RLLHHLLLLLRR.',
                 '.RLHHLLLLLLLRD',
                 'RLLLLLLLLLLRRD',
                 'RLLLLLLLLRRRDD',
                 'RRLLLLLLRRRRDD',
                 'RRRLLLRRRRRDDD',
                 'DRRRRRRRRRDDDK',
                 '.DDRRRRRRDDDK.',
                 '..DDDDDDDDDK..',
                 '...KKKKKKKK...',
                 '..............'],
          {'R': R, 'L': RL, 'H': RH, 'D': RD, 'K': K})
    return c


def outcrop(face, w_open, e_open, n_open, seed=21):
    """Raised rock outcrop (blocks). Top: pale stratified rock in diagonal layers; where the dig
    floor lies south a short dig face with dark seams drops to a black foot line; the west side
    catches the light, the east side is in shadow."""
    import random
    rnd = random.Random(seed)
    c = Canvas(RL)
    for y in range(16):
        for x in range(16):
            band = (x + y * 2) // 5 % 3
            c.px(x, y, (RL, R, RH)[band] if rnd.random() > .12 else RD)
    if face:
        bands = [(9, RD), (10, R), (12, DD), (13, D), (15, K)]
        for y in range(9, 16):
            col = [b for y0, b in bands if y >= y0][-1]
            c.hline(0, 15, y, col)
        c.hline(0, 15, 8, RH)
        for x in range(0, 16, 5):
            c.px(x, 11, K); c.px(x + 1, 12, K)
    if n_open: c.hline(0, 15, 0, K); c.hline(0, 15, 1, RH)
    if w_open: c.vline(0, 0, 15, K); c.vline(1, 0, 15 if not face else 8, RH)
    if e_open: c.vline(15, 0, 15, K); c.vline(14, 0, 15 if not face else 8, RD)
    return c


def prop_face(seed=31):
    """Dig face held up by a timber prop and a cross beam."""
    c = rock_wall_face(seed)
    c.rect(6, 0, 9, 15, W); c.vline(6, 0, 15, WD); c.vline(9, 0, 15, K); c.hline(6, 9, 0, WD)
    c.rect(0, 1, 15, 3, W); c.hline(0, 15, 3, WD); c.hline(0, 15, 1, DH)
    return c


def rail_v(edge=None):
    c = dirt(15)
    for y in range(1, 16, 4):
        c.rect(3, y, 12, y + 1, W); c.hline(3, 12, y + 1, WD)
    c.vline(5, 0, 15, M); c.vline(4, 0, 15, MD); c.vline(10, 0, 15, M); c.vline(11, 0, 15, MD)
    return c


def rail_end():
    c = rail_v()
    c.rect(3, 0, 12, 4, W); c.rect(4, 1, 11, 3, WD); c.hline(3, 12, 4, K)
    return c


def cart():
    """Mine cart on the rails (blocks)."""
    c = rail_v()
    c.art(1, 2, ['..MMMMMMMMMMMM..',
                 '.MHHHHHHHHHHHHM.',
                 '.MKRRKRRKRRKRKM.',
                 '.MRLRRLRRRLRRRM.',
                 '.MMMMMMMMMMMMMM.',
                 '.MDMMMMMMMMMMDM.',
                 '.MDMMMMMMMMMMDM.',
                 '.MMMMMMMMMMMMMM.',
                 '..KK........KK..',
                 '.KMMK......KMMK.',
                 '..KK........KK..'],
          {'M': M, 'H': MH, 'K': K, 'R': R, 'L': RL, 'D': MD})
    return c


def bottom():
    c = Canvas(K)
    c.hline(0, 15, 0, RD)
    return c


def build_tileset():
    ts = Tileset(TS)
    p = lambda c: (c, PM)
    ts.add('dirt', [p(dirt(1)), None, None])
    ts.add('dirt2', [p(dirt(2)), None, None])
    ts.add('dug', [p(dirt(4, True)), None, None])
    ts.add('pebbles', [p(pebbles()), None, None])
    ts.add('wall_top', [p(rock_wall_top()), None, None])
    ts.add('wall_face', [p(rock_wall_face()), None, None])
    ts.add('wall_rim_w', [p(wall_rim('w')), None, None])
    ts.add('wall_rim_e', [p(wall_rim('e')), None, None])
    ts.add('wall_ore', [p(rock_wall_face(8, True)), None, None])
    ts.add('wall_beam', [p(beam_face()), None, None])
    ts.add('wall_lamp', [p(lantern_face()), None, None])
    ts.add('boulder', [p(boulder()), None, None])
    ts.add('wall_prop', [p(prop_face()), None, None])
    for face in (0, 1):
        for w in (0, 1):
            for e in (0, 1):
                for nn in (0, 1):
                    ts.add('crop_%d%d%d%d' % (face, w, e, nn), [p(outcrop(face, w, e, nn)), None, None])
    ts.add('rail', [p(rail_v()), None, None])
    ts.add('rail_end', [p(rail_end()), None, None])
    ts.add('cart', [p(cart()), None, None])
    ts.add('bottom', [p(bottom()), None, None])
    ts.save({PM: MINE})
    return ts.names


# ------------------------------------------------------------------ plan
# X: rock wall, T: wall top, f/o/b/l: wall faces, . dirt, , dirt2, d dug, p pebbles,
# B boulder, = rail, ^ rail end, C cart, 1-3 exit mat, 4-6 bottom of the mat,
# s statue top, t statue bottom, _ bottom wall.
PLAN = [
    "TTTTTTTTTTTTTTTTT",   # 0
    "TTfofbfflfbfofTTT",   # 1
    "TTd.,.......,.dTT",   # 2   Roark's dig face
    "TT.p...,....p..TT",   # 3   Roark at (8,3)
    "TT,......,.....TT",   # 4
    "TTT..,.......,TTT",   # 5
    "TTTd.BB,.,BBBTTTT",   # 6   checkpoint 2: gap at x=8 (Darius at 10,8 looks left)
    "TTT.,BB...BBBTTTT",   # 7
    "TTT..BB.,..BBTTTT",   # 8
    "TTTp.BB...BBBTTTT",   # 9
    "TTT.,BBd.,BBBTTTT",   # 10
    "TTTT...,....TTTTT",   # 11
    "TTTTT..^...,.TTTT",   # 12
    "TTTTd..=..BB..TTT",   # 13  checkpoint 1: gap at x=8 (Jonathon at 6,16 looks right)
    "TTTTT..=.,BB,.TTT",   # 14
    "TTTTTBB=..BB.pTTT",   # 15
    "TTTTT..=.,BB..TTT",   # 16
    "TTTTTBB=..BB,.TTT",   # 17
    "TTTTd..=...,..TTT",   # 18
    "TTTT,..=.....dTTT",   # 19
    "TTT....=..,....TT",   # 20
    "TTT.p..C.....,.TT",   # 21
    "TT.,...=...,...TT",   # 22
    "TT..s..=...s...TT",   # 23
    "TT..t..=...t.,.TT",   # 24
    "TT,....=.......TT",   # 25
    "TT.....123.....TT",   # 26
    "_______456_______",   # 27
]


def main():
    names = build_tileset()
    n = lambda k: names[k]
    legend = {
        'T': (n('wall_top'), 1, 0), 'f': (n('wall_face'), 1, 0), 'o': (n('wall_ore'), 1, 0),
        'b': (n('wall_beam'), 1, 0), 'l': (n('wall_lamp'), 1, 0),
        '.': (n('dirt'), 0, 3), ',': (n('dirt2'), 0, 3), 'd': (n('dug'), 0, 3), 'p': (n('pebbles'), 0, 3),
        'B': (n('boulder'), 1, 3), '=': (n('rail'), 0, 3), '^': (n('rail_end'), 0, 3), 'C': (n('cart'), 1, 3),
        's': (0x235, 1, 3), 't': (0x23b, 1, 3), '_': (n('bottom'), 1, 0),
        '1': (0x207, 0, 3), '2': (0x208, 0, 3), '3': (0x209, 0, 3),
        '4': (0x201, 1, 0), '5': (0x202, 1, 0), '6': (0x203, 1, 0),
    }
    legend.update({'F': (n('wall_face'), 1, 0), 'W': (n('wall_rim_w'), 1, 0), 'E': (n('wall_rim_e'), 1, 0)})
    plan = [list(r) for r in PLAN]
    floor = set('.,dpB=^Cst123')
    for y in range(len(plan) - 1):           # cliff faces and rims where the rock meets the dig floor
        for x in range(len(plan[y])):
            if PLAN[y][x] != 'T':
                continue
            if PLAN[y + 1][x] in floor:
                plan[y][x] = 'F'
            elif x + 1 < len(plan[y]) and PLAN[y][x + 1] in floor:
                plan[y][x] = 'W'
            elif x > 0 and PLAN[y][x - 1] in floor:
                plan[y][x] = 'E'
    fl = lambda ch: ch in floor - {'B'}
    for y in range(len(plan)):
        for x in range(len(plan[y])):
            if PLAN[y][x] == 'B':
                key = (int(y + 1 < len(PLAN) and fl(PLAN[y + 1][x])), int(fl(PLAN[y][x - 1])),
                       int(fl(PLAN[y][x + 1])), int(fl(PLAN[y - 1][x])))
                k = 'K%d%d%d%d' % key
                legend[k] = (n('crop_%d%d%d%d' % key), 1, 3)
                plan[y][x] = k
    for x, y in ((5, 1), (11, 1)):
        plan[y][x] = 'P'
    legend['P'] = (n('wall_prop'), 1, 0)
    from gymkit import build_cells
    build_cells(LAYOUT, [[legend[ch] for ch in r] for r in plan], border=n('wall_top'))
    d = json.load(open(MAP))
    d['warp_events'] = [{'x': x, 'y': 26, 'elevation': 0, 'dest_map': 'MAP_OREBURGH_CITY_SINNOH', 'dest_warp_id': '6'}
                        for x in (7, 8, 9)]
    pos = {
        'SE_EventScript_SinnohLeader_Roark': (8, 3, 'MOVEMENT_TYPE_FACE_DOWN', '0'),
        'OreburghCity_Gym_EventScript_Jonathon': (6, 16, 'MOVEMENT_TYPE_FACE_RIGHT', '3'),
        'OreburghCity_Gym_EventScript_Darius': (10, 8, 'MOVEMENT_TYPE_FACE_LEFT', '3'),
        'OreburghCity_Gym_EventScript_Guide': (10, 25, 'MOVEMENT_TYPE_FACE_DOWN', '0'),
    }
    for o in d['object_events']:
        x, y, mv, s = pos[o['script']]
        o['x'], o['y'], o['movement_type'], o['elevation'] = x, y, mv, 3
        if o['trainer_type'] != 'TRAINER_TYPE_NONE':
            o['trainer_sight_or_berry_tree_id'] = s
    d['bg_events'] = [{'type': 'sign', 'x': x, 'y': 23, 'elevation': 0, 'player_facing_dir': 'BG_EVENT_PLAYER_FACING_ANY',
                       'script': 'OreburghCity_Gym_EventScript_GymStatue'} for x in (4, 11)]
    open(MAP, 'w').write(json.dumps(d, indent=2, ensure_ascii=False) + '\n')


# ------------------------------------------------------------------ FRLG dressing (Mt. Moon)
# Base: FRLG Mt. Moon (gTileset_Cave_Frlg). Its rock ridges become Oreburgh's raised rock
# outcrops (top + face + rounded ends, all from the cave), its sand patches the excavated
# ground, its craters the decorative gravel (walkable). The rail and the cart are the only new
# pixels: drawn on a transparent layer over the cave floor so the floor stays FRLG's own.
CAVE_MAPS = ['MtMoon_1F_Frlg', 'MtMoon_B1F_Frlg', 'MtMoon_B2F_Frlg']
CAVE = {'floor': 641, 'sand': 764, 'crater': (725, 726, 733, 734)}


def rail_overlay(end=False, cart_=False):
    c = Canvas(0)
    for y in range(1, 16, 4):
        c.rect(3, y, 12, y + 1, W); c.hline(3, 12, y + 1, WD)
    c.vline(5, 0, 15, M); c.vline(4, 0, 15, MD); c.vline(10, 0, 15, M); c.vline(11, 0, 15, MD)
    if end:      # buffer stop: a timber beam across both rails
        c.rect(2, 0, 13, 4, W); c.rect(3, 1, 12, 3, WD); c.hline(2, 13, 4, K); c.vline(2, 0, 4, K); c.vline(13, 0, 4, K)
    if cart_:     # a loaded ore cart, as wide as the tile
        c.art(0, 1, ['.KKKKKKKKKKKKKK.',
                     'KMHHHHHHHHHHHHMK',
                     'KMRLRHLRRLRHRRMK',
                     'KMLRRLRRLRRLRLMK',
                     'KMMMMMMMMMMMMMMK',
                     'KMDMMMMMMMMMMDMK',
                     'KMDMMHMMMMHMMDMK',
                     'KMDMMMMMMMMMMDMK',
                     'KMMMMMMMMMMMMMMK',
                     '.KKKKKKKKKKKKKK.',
                     '.KMK........KMK.',
                     '..K..........K..'],
              {'M': M, 'H': MH, 'K': K, 'R': R, 'L': RL, 'D': MD})
    return c


FPLAN = [r for r in PLAN[:27]] + ["TTTTTTTT12TTTTTTT"]


def main_frlg():
    import gbaref as G
    from gymkit import write_metatile_defs, build_cells
    ts = Tileset(TS)
    ts.free_unused(set())
    src = G.source_for(CAVE_MAPS[0])
    imp = G.Importer(ts, G.free_slots({PM}))

    def cl(m, c, b):
        if 755 <= m <= 773: return 'S'
        return G.classify_basic(m, c, b)
    table = G.learn(src, CAVE_MAPS, cl)
    plan = [r.replace('1', '.').replace('2', '.').replace('3', '.') if y < 27 else r for y, r in enumerate(FPLAN)]
    plan = [r.replace('4', 'T').replace('5', 'T').replace('6', 'T') for r in plan]
    H, Wd = len(plan), len(plan[0])
    cls = [['W' if ch in 'TfoblB_' else 'S' if ch == 'd' else 'F' for ch in r] for r in plan]
    fl = imp.layers(src, CAVE['floor'])
    fb = G.base(fl)
    special = {}
    ts.add('rail', [fb, (rail_overlay(), PM), None], 0)
    ts.add('rail_end', [fb, (rail_overlay(end=True), PM), None], 0)
    ts.add('cart', [fb, (rail_overlay(cart_=True), PM), None], 0)
    ts.add('statue_top', [fb, None, ('raw', [0x0001, 0x0002, 0x0011, 0x0012])], 0)
    ts.add('statue_base', [fb, ('raw', [0x0021, 0x0022, 0x0031, 0x0032]), None], 0)
    for y, r in enumerate(plan):
        for x, ch in enumerate(r):
            if ch == '=': special[(x, y)] = (ts.names['rail'], 0, 3)
            elif ch == '^': special[(x, y)] = (ts.names['rail_end'], 0, 3)
            elif ch == 'C': special[(x, y)] = (ts.names['cart'], 1, 3)
            elif ch == 's': special[(x, y)] = (ts.names['statue_top'], 0, 3)
            elif ch == 't': special[(x, y)] = (ts.names['statue_base'], 1, 3)
            elif ch in '12': special[(x, y)] = ((0x006 if ch == '1' else 0x007), 0, 3)
    # walkable gravel: whole FRLG craters (2x2), where 'p' marks their top-left corner
    for y, r in enumerate(plan):
        for x, ch in enumerate(r):
            if ch == 'p' and all(plan[y + j][x + i] in '.,p' for i in (0, 1) for j in (0, 1)):
                for k, (i, j) in enumerate(((0, 0), (1, 0), (0, 1), (1, 1))):
                    special[(x + i, y + j)] = (imp.add('crater%d' % k, src, CAVE['crater'][k], 0), 0, 3)
    def wall_fb(x, y):
        return (imp.add('w_%x_%s' % (665, src.name), src, 665, 0), 1, 0)
    rows = G.dress(cls, table, imp, src, special, floor=CAVE['floor'], wall_fallback=wall_fb,
                   avoid=(667, 750, 751))      # cave pieces with blue water marks
    print('palette slots:', sorted(imp.colors), '+', PM)
    pals = imp.palettes(); pals[PM] = MINE
    ts.save(pals)
    write_metatile_defs('data/maps/OreburghCity_Gym_sinnoh', 'OreburghGym', ts.names)
    build_cells(LAYOUT, rows, border=0x000)
    write_events(mat_y=27)


def write_events(mat_y=26):
    d = json.load(open(MAP))
    d['warp_events'] = [{'x': x, 'y': mat_y, 'elevation': 0, 'dest_map': 'MAP_OREBURGH_CITY_SINNOH', 'dest_warp_id': '6'}
                        for x in (8, 9)]
    pos = {
        'SE_EventScript_SinnohLeader_Roark': (8, 3, 'MOVEMENT_TYPE_FACE_DOWN', '0'),
        'OreburghCity_Gym_EventScript_Jonathon': (6, 16, 'MOVEMENT_TYPE_FACE_RIGHT', '3'),
        'OreburghCity_Gym_EventScript_Darius': (10, 8, 'MOVEMENT_TYPE_FACE_LEFT', '3'),
        'OreburghCity_Gym_EventScript_Guide': (10, 25, 'MOVEMENT_TYPE_FACE_DOWN', '0'),
    }
    for o in d['object_events']:
        x, y, mv, s = pos[o['script']]
        o['x'], o['y'], o['movement_type'], o['elevation'] = x, y, mv, 3
        if o['trainer_type'] != 'TRAINER_TYPE_NONE':
            o['trainer_sight_or_berry_tree_id'] = s
    d['bg_events'] = [{'type': 'sign', 'x': x, 'y': 24, 'elevation': 0, 'player_facing_dir': 'BG_EVENT_PLAYER_FACING_ANY',
                       'script': 'OreburghCity_Gym_EventScript_GymStatue'} for x in (4, 11)]
    open(MAP, 'w').write(json.dumps(d, indent=2, ensure_ascii=False) + '\n')


if __name__ == '__main__':
    main_frlg()
