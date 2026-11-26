"""Super Emerald: reuse FireRed/Emerald map graphics that are already in the project.

SourceSet loads a primary+secondary tileset pair (FRLG pairs have 640 primary tiles/metatiles and
7 primary palettes). Importer copies whole metatiles from a SourceSet into a gym's own tileset:
the 8x8 tiles go through Tileset.tile_entry (deduplicated, flips kept) and each source palette is
given one of the gym's free palette slots. learn() reads real FRLG/Emerald maps built with that
tileset and records, for every wall / floor / ice cell, which metatile the original mappers used
for each arrangement of neighbours - so a new plan can be dressed the same way (autotiling by
example) instead of drawing new walls.
"""
import json, os, struct
from collections import Counter, defaultdict
from PIL import Image


def _pal(f):
    ls = open(f).read().split('\n')[3:19]
    return [tuple(int(v) for v in l.split()[:3]) for l in ls if l.strip()]


class SourceSet:
    def __init__(self, primary, secondary, frlg):
        self.np = 640 if frlg else 512
        self.ps = 7 if frlg else 6
        self.tiles = []
        for d, n in ((primary, self.np), (secondary, 1024 - self.np)):
            im = Image.open(d + '/tiles.png'); w = im.width // 8; px = im.load()
            for i in range(n):
                x, y = (i % w) * 8, (i // w) * 8
                if y >= im.height:
                    self.tiles.append(None); continue
                self.tiles.append(tuple(tuple(px[x + a, y + b] & 15 for a in range(8)) for b in range(8)))
        self.pals = [_pal(f'{primary}/palettes/{i:02d}.pal') if i < self.ps else _pal(f'{secondary}/palettes/{i:02d}.pal')
                     for i in range(13)]
        self.mtP = open(primary + '/metatiles.bin', 'rb').read(); self.mtS = open(secondary + '/metatiles.bin', 'rb').read()
        aw = 4 if frlg else 2
        self.atP = open(primary + '/metatile_attributes.bin', 'rb').read(); self.atS = open(secondary + '/metatile_attributes.bin', 'rb').read()
        self.aw = aw

    def entries(self, mid):
        data, i = (self.mtP, mid) if mid < self.np else (self.mtS, mid - self.np)
        return struct.unpack_from('<12H', data, i * 24)

    def behavior(self, mid):
        data, i = (self.atP, mid) if mid < self.np else (self.atS, mid - self.np)
        v = struct.unpack_from('<I' if self.aw == 4 else '<H', data, i * self.aw)[0]
        return v & (0x1FF if self.aw == 4 else 0xFF)


class Importer:
    def __init__(self, ts, slots):
        self.ts = ts
        self.free = list(slots)
        self.slot_of = {}            # palette colours -> slot
        self.colors = {}             # slot -> colours

    def slot(self, cols):
        key = tuple(cols)
        if key not in self.slot_of:
            assert self.free, 'out of palette slots'
            s = self.free.pop(0)
            self.slot_of[key] = s; self.colors[s] = list(cols) + [(0, 0, 0)] * (16 - len(cols))
        return self.slot_of[key]

    def layers(self, src, mid):
        """The three layers of source metatile `mid` as ('raw', entries) for Tileset.add."""
        out = []
        ents = src.entries(mid)
        for L in range(3):
            row = []
            for q in range(4):
                e = ents[L * 4 + q]
                ti, hf, vf, pal = e & 0x3FF, (e >> 10) & 1, (e >> 11) & 1, e >> 12
                t = src.tiles[ti] if ti < len(src.tiles) else None
                if t is None or all(v == 0 for r in t for v in r):
                    row.append(0); continue
                if hf: t = tuple(r[::-1] for r in t)
                if vf: t = tuple(t[::-1])
                row.append(self.ts.tile_entry(t, self.slot(src.pals[pal])))
            out.append(('raw', row))
        return out

    def add(self, name, src, mid, behavior=None):
        if name in self.ts.names:
            return self.ts.names[name]
        b = src.behavior(mid) if behavior is None else behavior
        return self.ts.add(name, self.layers(src, mid), b)


def map_cells(map_dir):
    d = json.load(open(f'data/maps/{map_dir}/map.json'))
    L = [l for l in json.load(open('data/layouts/layouts.json'))['layouts'] if l.get('id') == d['layout']][0]
    b = open(L['blockdata_filepath'], 'rb').read(); w, h = L['width'], L['height']
    return [[struct.unpack_from('<H', b, (y * w + x) * 2)[0] for x in range(w)] for y in range(h)]


def learn(src, maps, classify):
    """classify(metatile, collision, behaviour) -> class char. Returns {class: {key: Counter(mt)}}
    where key is the 8-neighbour class string N,NE,E,SE,S,SW,W,NW (outside = '#')."""
    table = defaultdict(lambda: defaultdict(Counter))
    for m in maps:
        g = map_cells(m)
        H, W = len(g), len(g[0])
        cls = [[classify(v & 0x3FF, (v >> 10) & 3, src.behavior(v & 0x3FF)) for v in r] for r in g]
        for y in range(H):
            for x in range(W):
                table[cls[y][x]][neigh(cls, x, y)][g[y][x] & 0x3FF] += 1
    return table


DIRS = ((0, -1), (1, -1), (1, 0), (1, 1), (0, 1), (-1, 1), (-1, 0), (-1, -1))


def neigh(cls, x, y):
    H, W = len(cls), len(cls[0])
    return ''.join(cls[y + dy][x + dx] if 0 <= x + dx < W and 0 <= y + dy < H else '#' for dx, dy in DIRS)


def pick(table, c, key, weights=(4, 1, 4, 1, 4, 1, 4, 1)):
    """Best source metatile of class c for a neighbour key: exact match, else closest key."""
    t = table[c]
    if key in t:
        return t[key].most_common(1)[0][0], 0
    best = None
    for k, cnt in t.items():
        d = sum(w for a, b, w in zip(k, key, weights) if a != b)
        score = (d, -sum(cnt.values()))
        if best is None or score < best[0]:
            best = (score, cnt.most_common(1)[0][0])
    return best[1], best[0][0]
