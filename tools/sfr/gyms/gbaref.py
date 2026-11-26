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


GFX_ALIAS = {'data/tilesets/secondary/silph_co_frlg': 'data/tilesets/secondary/condominiums_frlg'}


def tsdir(ts, kind):
    import re
    name = re.sub(r'(?<!^)(?=[A-Z])', '_', ts.replace('gTileset_', '')).lower().replace('__', '_')
    for p in (f'data/tilesets/{kind}/{name}', f'data/tilesets/{kind}/{name}_frlg',
              f'data/tilesets/{kind}/{name.replace("_frlg", "")}_frlg'):
        if os.path.exists(p + '/metatiles.bin'):
            return p
    raise KeyError(name)


def layout_of(map_dir):
    d = json.load(open(f'data/maps/{map_dir}/map.json'))
    return [l for l in json.load(open('data/layouts/layouts.json'))['layouts'] if l.get('id') == d['layout']][0]


_SRC = {}


def source_for(map_dir):
    """SourceSet of the tileset pair a FRLG/Emerald map is built with (cached)."""
    l = layout_of(map_dir)
    k = (l['primary_tileset'], l['secondary_tileset'])
    if k not in _SRC:
        frlg = 'Frlg' in k[0]
        _SRC[k] = SourceSet(tsdir(k[0], 'primary'), tsdir(k[1], 'secondary'), frlg)
    return _SRC[k]


def at(map_dir, x, y):
    """Metatile id at (x, y) of a reference map."""
    return map_cells(map_dir)[y][x] & 0x3FF


class SourceSet:
    def __init__(self, primary, secondary, frlg):
        self.np = 640 if frlg else 512
        self.ps = 7 if frlg else 6
        self.tiles = []
        self.name = secondary.split('/')[-1]
        for d, n in ((primary, self.np), (secondary, 1024 - self.np)):
            g = GFX_ALIAS.get(d, d)
            im = Image.open(g + '/tiles.png'); w = im.width // 8; px = im.load()
            for i in range(n):
                x, y = (i % w) * 8, (i // w) * 8
                if y >= im.height:
                    self.tiles.append(None); continue
                self.tiles.append(tuple(tuple(px[x + a, y + b] & 15 for a in range(8)) for b in range(8)))
        sg = GFX_ALIAS.get(secondary, secondary)
        self.pals = [_pal(f'{primary}/palettes/{i:02d}.pal') if i < self.ps else _pal(f'{sg}/palettes/{i:02d}.pal')
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
    """Copies source metatiles into a gym tileset. Colours are packed: each 8x8 tile goes to a
    palette slot that already holds the colours it uses (pixels are re-indexed), or to the slot
    with room that shares most of them, so pieces from several FRLG/Emerald sets fit in the
    gym's few slots."""
    def __init__(self, ts, slots, tint=None):
        self.ts = ts
        self.order = list(slots)
        self.colors = {}             # slot -> [colour, ...] (index 0 = transparent)
        self.tint = tint             # optional colour transform (r, g, b) -> (r, g, b)

    def _fit(self, cols):
        best = None
        for s in self.order:
            if s not in self.colors:
                continue
            have = self.colors[s]
            miss = [c for c in cols if c not in have[1:]]
            if len(have) + len(miss) <= 16:
                score = (len(miss), self.order.index(s))
                if best is None or score < best[0]:
                    best = (score, s, miss)
        if best is None or best[0][0] > 0:
            free = [s for s in self.order if s not in self.colors]
            if free and (best is None or best[0][0] > 3):
                s = free[0]; self.colors[s] = [(0, 0, 0)]
                best = ((len(cols), 0), s, list(cols))
        assert best is not None, 'out of palette room'
        _, s, miss = best
        self.colors[s].extend(miss)
        return s

    def tile(self, t, pal):
        used = sorted({v for r in t for v in r if v})
        cols = []
        tc = (lambda c: tuple(self.tint(c))) if self.tint else (lambda c: tuple(c))
        for v in used:
            c = tc(pal[v])
            if c not in cols: cols.append(c)
        s = self._fit(cols)
        have = self.colors[s]
        remap = {v: have.index(tc(pal[v]), 1) for v in used}
        t2 = tuple(tuple(remap.get(v, 0) for v in r) for r in t)
        return self.ts.tile_entry(t2, s)

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
                row.append(self.tile(t, src.pals[pal]))
            out.append(('raw', row))
        return out

    def flat(self, src, mid, layers=(0, 1, 2), drop=()):
        """One ('raw', 4 entries) layer: the source metatile's layers composited (8x8 tile by
        tile, upper layers over lower), for pieces that must sit under a drawn overlay."""
        ents = src.entries(mid)
        tc = (lambda c: tuple(self.tint(c))) if self.tint else (lambda c: tuple(c))
        row = []
        for q in range(4):
            rgb = [[None] * 8 for _ in range(8)]
            for L in layers:
                e = ents[L * 4 + q]
                ti, hf, vf, pal = e & 0x3FF, (e >> 10) & 1, (e >> 11) & 1, e >> 12
                t = src.tiles[ti] if ti < len(src.tiles) else None
                if t is None:
                    continue
                if hf: t = tuple(r[::-1] for r in t)
                if vf: t = tuple(t[::-1])
                for y in range(8):
                    for x in range(8):
                        v = t[y][x]
                        if v:
                            c_ = tc(src.pals[pal][v])
                            rgb[y][x] = None if c_ in drop else c_
                        elif L == layers[0] and rgb[y][x] is None and not drop:
                            rgb[y][x] = tc(src.pals[0][0])
            cols = []
            for r in rgb:
                for c in r:
                    if c is not None and c not in cols:
                        cols.append(c)
            if not cols:
                row.append(0); continue
            s_ = self._fit(cols)
            have = self.colors[s_]
            grid = tuple(tuple(have.index(c, 1) if c is not None else 0 for c in r) for r in rgb)
            row.append(self.ts.tile_entry(grid, s_))
        return ('raw', row)

    def colours_of(self, src, mid):
        """Set of (tinted) colours a source metatile draws."""
        tc = (lambda c: tuple(self.tint(c))) if self.tint else (lambda c: tuple(c))
        out = set()
        for e in src.entries(mid):
            t = src.tiles[e & 0x3FF] if (e & 0x3FF) < len(src.tiles) else None
            if t:
                out |= {tc(src.pals[e >> 12][v]) for r in t for v in r if v}
        return out

    def palettes(self):
        return {s: list(c) + [(0, 0, 0)] * (16 - len(c)) for s, c in self.colors.items()}

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


def learn(src, maps, classify, ext=False, edge='#'):
    """classify(metatile, collision, behaviour) -> class char. Returns {class: {key: Counter(mt)}}
    where key is the 8-neighbour class string N,NE,E,SE,S,SW,W,NW (outside = '#')."""
    table = defaultdict(lambda: defaultdict(Counter))
    for m in maps:
        g = map_cells(m)
        H, W = len(g), len(g[0])
        cls = [[classify(v & 0x3FF, (v >> 10) & 3, src.behavior(v & 0x3FF)) for v in r] for r in g]
        for y in range(H):
            for x in range(W):
                table[cls[y][x]][neigh(cls, x, y, ext).replace('#', edge)][g[y][x] & 0x3FF] += 1
    return table


DIRS = ((0, -1), (1, -1), (1, 0), (1, 1), (0, 1), (-1, 1), (-1, 0), (-1, -1))


def neigh(cls, x, y, ext=False):
    """ext: also the cells two below and two above (tall FRLG building walls)."""
    H, W = len(cls), len(cls[0])
    d = DIRS + (((0, 2), (0, -2)) if ext else ())
    return ''.join(cls[y + dy][x + dx] if 0 <= x + dx < W and 0 <= y + dy < H else '#' for dx, dy in d)


def pick(table, c, key, weights=(4, 1, 4, 1, 4, 1, 4, 1, 2, 1)):
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


def dress(cls, table, imp, src, special=None, ext=False, floor=None, wall_fallback=None,
          void=0x000, avoid=(), elev=3, solid=('W', 'T'), tol=None):
    """cls: grid of 'W' (blocking structure) / 'F' (floor). Returns rows of (metatile, collision,
    elevation) dressed with the source mappers' own picks. special: {(x, y): cell} wins.
    floor: source metatile for floors with no exact precedent; wall_fallback(x, y) -> cell for
    walls with no close precedent; solid wall interior becomes `void`; avoid: source metatiles
    never used (decorations the mappers placed by hand)."""
    special = special or {}
    H, W = len(cls), len(cls[0])
    rows = []
    for y in range(H):
        row = []
        for x in range(W):
            if (x, y) in special:
                row.append(special[(x, y)]); continue
            c = cls[y][x]
            key = ''.join(k if k != '#' else 'W' for k in neigh(cls, x, y, ext))
            if c == 'W':
                if set(key) == {'W'} and void is not None:
                    row.append((void, 1, 0)); continue
                mid, d = pick(table, 'W', key)
                if (d >= 4 or mid in avoid) and wall_fallback:
                    row.append(wall_fallback(x, y)); continue
                row.append((imp.add('w_%x_%s' % (mid, src.name), src, mid, 0), 1, 0))
            else:
                t = c if c in table else 'F'
                mid, d = pick(table, t, key)
                fl = floor.get(c) if isinstance(floor, dict) else floor
                if (d > (tol or {}).get(c, 0) or mid in avoid) and fl is not None:
                    mid = fl
                row.append((imp.add('f_%x_%s' % (mid, src.name), src, mid, 0), 1 if c in solid else 0, elev))
        rows.append(row)
    return rows


def classify_basic(m, c, b):
    if c:
        return 'W'
    return 'F' if b in (0x00, 0x08) else 'X'


def slots_of(ts, mids):
    """Palette slots drawn by existing (original) secondary metatiles."""
    out = set()
    for mid in mids:
        if mid < 0x200:
            continue
        for e in struct.unpack_from('<12H', ts.mt, (mid - 0x200) * 24):
            if e & 0x3FF:
                out.add(e >> 12)
    return out


def free_slots(used, first=6, last=12):
    return [s for s in range(first, last + 1) if s not in used]


def base(layers):
    """The drawn layer of an imported floor (FRLG floors sit in the middle layer)."""
    for L in layers:
        if L and any(e & 0x3FF for e in L[1]):
            return L
    return layers[0]
