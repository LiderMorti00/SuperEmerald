"""Super Emerald: small toolkit to build the Sinnoh gym interiors.

- Tileset: appends new metatiles (drawn as 16x16 index grids on a palette slot) to a
  secondary tileset: tiles.png (4bpp, 8x8 tiles deduplicated with flips), metatiles.bin
  (triple layer, 12 tiles per metatile), metatile_attributes.bin and palettes/NN.pal.
  Metatiles are named; a previous build of the same names is replaced, the gym's original
  metatiles are kept.
- Map: builds map.bin from a character plan and a legend (metatile, collision, elevation)
  and updates the layout size in data/layouts/layouts.json.
"""
import json, os, struct
from PIL import Image

T = 0  # transparent index


class Canvas:
    """16x16 grid of palette indices (0 = transparent)."""

    def __init__(self, fill=0):
        self.p = [[fill] * 16 for _ in range(16)]

    def px(self, x, y, c):
        if 0 <= x < 16 and 0 <= y < 16 and c is not None:
            self.p[y][x] = c

    def rect(self, x0, y0, x1, y1, c):          # inclusive
        for y in range(y0, y1 + 1):
            for x in range(x0, x1 + 1):
                self.px(x, y, c)

    def hline(self, x0, x1, y, c):
        self.rect(x0, y, x1, y, c)

    def vline(self, x, y0, y1, c):
        self.rect(x, y0, x, y1, c)

    def art(self, x0, y0, rows, legend):
        """rows: strings; legend: char -> index (missing / ' ' / '.' = skip)."""
        for j, r in enumerate(rows):
            for i, ch in enumerate(r):
                if ch in legend:
                    self.px(x0 + i, y0 + j, legend[ch])

    def copy(self):
        c = Canvas(); c.p = [r[:] for r in self.p]; return c

    def flip_h(self):
        c = Canvas(); c.p = [r[::-1] for r in self.p]; return c


def write_pal(path, cols):
    cols = list(cols) + [(0, 0, 0)] * (16 - len(cols))
    with open(path, 'w') as f:
        f.write('JASC-PAL\r\n0100\r\n16\r\n')
        for r, g, b in cols[:16]:
            f.write(f'{r} {g} {b}\r\n')


class Tileset:
    def __init__(self, path):
        self.path = path
        self.meta_path = path + '/se_gymkit.json'
        self.state = json.load(open(self.meta_path)) if os.path.exists(self.meta_path) else None
        im = Image.open(path + '/tiles.png')
        assert im.mode == 'P'
        self.src_pal = im.getpalette()
        w = im.width // 8
        px = im.load()
        tiles = []
        for i in range((im.width // 8) * (im.height // 8)):
            x, y = (i % w) * 8, (i // w) * 8
            tiles.append(tuple(tuple(px[x + a, y + b] & 15 for a in range(8)) for b in range(8)))
        mt = open(path + '/metatiles.bin', 'rb').read()
        at = open(path + '/metatile_attributes.bin', 'rb').read()
        if self.state:      # restore the gym's original part before rebuilding ours
            tiles = tiles[:self.state['orig_tiles']]
            mt = mt[:self.state['orig_metatiles'] * 24]
            at = at[:self.state['orig_metatiles'] * 2]
            if 'orig_mt' in self.state:       # original metatiles may have been redrawn by replace()
                mt = bytes.fromhex(self.state['orig_mt'])
            else:
                self.state['orig_mt'] = mt.hex()
        else:
            # drop trailing empty tiles of the sheet
            while len(tiles) > 1 and all(v == 0 for r in tiles[-1] for v in r):
                tiles.pop()
            self.state = {'orig_tiles': len(tiles), 'orig_metatiles': len(mt) // 24}
        self.tiles = tiles
        self.mt = bytearray(mt)
        self.at = bytearray(at)
        self.index = {}
        for i, t in enumerate(self.tiles):
            self._remember(t, i)
        self.names = {}
        self.state.setdefault('orig_pals', {})

    def free_unused(self, live, redrawn=()):
        """Reuse the slots of original tiles that no live metatile draws any more.
        live: metatile ids still used by maps or scripts; redrawn: ids replace() will redraw."""
        used = {0}
        for mid in live:
            if mid < 0x200 or mid in redrawn or (mid - 0x200) * 24 >= self.state['orig_metatiles'] * 24:
                continue
            for e in struct.unpack_from('<12H', self.mt, (mid - 0x200) * 24):
                if e & 0x3FF >= 0x200:
                    used.add((e & 0x3FF) - 0x200)
        self.free = [i for i in range(self.state['orig_tiles']) if i not in used]
        self.index = {k: v for k, v in self.index.items() if v[0] not in self.free}
        blank = tuple(tuple(0 for _ in range(8)) for _ in range(8))
        for i in self.free:
            self.tiles[i] = blank
        return len(self.free)

    def orig_pal(self, slot):
        """The gym's original colours of a palette slot (remembered the first time)."""
        k = str(slot)
        if k not in self.state['orig_pals']:
            lines = open(f'{self.path}/palettes/{slot:02d}.pal').read().split()
            vals = list(map(int, lines[3:3 + 48]))
            self.state['orig_pals'][k] = [vals[i:i + 3] for i in range(0, 48, 3)]
        return [tuple(c) for c in self.state['orig_pals'][k]]

    def replace(self, mid, layers, behavior=None):
        """Redraw an existing metatile in place (same id, so maps and scripts keep working)."""
        n = len(self.mt) // 24
        self.add('_tmp', layers, 0)
        ent = self.mt[-24:]
        del self.mt[-24:]; del self.at[-2:]; del self.names['_tmp']
        assert len(self.mt) // 24 == n
        i = mid - 0x200
        self.mt[i * 24:i * 24 + 24] = ent
        if behavior is not None:
            struct.pack_into('<H', self.at, i * 2, (struct.unpack_from('<H', self.at, i * 2)[0] & 0xFF00) | behavior)

    def _remember(self, t, i):
        for hf in (0, 1):
            for vf in (0, 1):
                v = t
                if hf:
                    v = tuple(r[::-1] for r in v)
                if vf:
                    v = tuple(v[::-1])
                self.index.setdefault(v, (i, hf, vf))

    def tile_entry(self, grid, pal):
        t = tuple(tuple(v for v in r) for r in grid)
        if all(v == 0 for r in t for v in r):
            return 0 | (pal << 12)          # secondary tile 0 is blank
        if t not in self.index:
            if getattr(self, 'free', None):
                i = self.free.pop(0)
                self.tiles[i] = t
                self._remember(t, i)
            else:
                self.tiles.append(t)
                self._remember(t, len(self.tiles) - 1)
        i, hf, vf = self.index[t]
        return (0x200 + i) | (hf << 10) | (vf << 11) | (pal << 12)

    def add(self, name, layers, behavior=0):
        """layers: [(Canvas, pal) or None] * 3 (bottom, middle, top)."""
        ents = []
        for L in layers:
            if isinstance(L, tuple) and L and L[0] == 'mt':      # ('mt', metatile id, layer): copy
                _, mid0, li = L
                ents.extend(struct.unpack_from('<4H', self.mt, (mid0 - 0x200) * 24 + li * 8))
                continue
            if isinstance(L, tuple) and L and L[0] == 'raw':     # ('raw', [4 tile entries])
                ents.extend(L[1])
                continue
            for q in range(4):
                if L is None:
                    ents.append(0)
                    continue
                c, pal = L
                ox, oy = (q % 2) * 8, (q // 2) * 8
                grid = [c.p[oy + y][ox:ox + 8] for y in range(8)]
                ents.append(self.tile_entry(grid, pal))
        mid = len(self.mt) // 24
        self.mt += struct.pack('<12H', *ents)
        self.at += struct.pack('<H', behavior & 0xFF)
        self.names[name] = 0x200 + mid
        return 0x200 + mid

    def save(self, pals):
        """pals: {slot: [(r,g,b)...16]}"""
        assert len(self.tiles) <= 512, len(self.tiles)
        assert len(self.mt) // 24 <= 512
        w = 16
        h = (len(self.tiles) + w - 1) // w
        im = Image.new('P', (w * 8, h * 8), 0)
        im.putpalette(self.src_pal)
        px = im.load()
        for i, t in enumerate(self.tiles):
            x, y = (i % w) * 8, (i // w) * 8
            for b in range(8):
                for a in range(8):
                    px[x + a, y + b] = t[b][a]
        im.save(self.path + '/tiles.png')
        open(self.path + '/metatiles.bin', 'wb').write(bytes(self.mt))
        open(self.path + '/metatile_attributes.bin', 'wb').write(bytes(self.at))
        for slot, cols in pals.items():
            write_pal(f'{self.path}/palettes/{slot:02d}.pal', cols)
        self.state['names'] = {k: hex(v) for k, v in self.names.items()}
        json.dump(self.state, open(self.meta_path, 'w'), indent=1)


def build_map(layout_id, plan, legend, border=None):
    """plan: list of strings; legend: char -> (metatile, collision, elevation)."""
    L = json.load(open('data/layouts/layouts.json'))
    lay = [l for l in L['layouts'] if l.get('id') == layout_id][0]
    h = len(plan); w = max(len(r) for r in plan)
    data = bytearray()
    for r in plan:
        r = r.ljust(w, r[-1])
        for ch in r:
            m, c, e = legend[ch]
            data += struct.pack('<H', (m & 0x3FF) | ((c & 3) << 10) | ((e & 15) << 12))
    open(lay['blockdata_filepath'], 'wb').write(bytes(data))
    if border is not None:
        open(lay['border_filepath'], 'wb').write(struct.pack('<4H', *[border | (1 << 10)] * 4))
    if lay['width'] != w or lay['height'] != h:
        raw = open('data/layouts/layouts.json').read()
        lay['width'], lay['height'] = w, h
        open('data/layouts/layouts.json', 'w').write(json.dumps(L, indent=2, ensure_ascii=False) + '\n')
    return w, h


def find(plan, ch):
    return [(x, y) for y, r in enumerate(plan) for x, c in enumerate(r) if c == ch]


def write_metatile_defs(map_dir, prefix, names):
    """data/maps/<map>/gym_metatiles.inc: .set METATILE_<prefix>_<Name>, id (for setmetatile)."""
    lines = ['@ Generated by tools/sfr/gyms (gymkit.write_metatile_defs); do not edit.']
    for k, v in sorted(names.items(), key=lambda kv: kv[1]):
        lines.append(f'.set METATILE_{prefix}_{k}, 0x{v:03x}')
    open(f'{map_dir}/gym_metatiles.inc', 'w').write('\n'.join(lines) + '\n')


def build_cells(layout_id, cells, border=None):
    """cells: rows of (metatile, collision, elevation) tuples; writes map.bin (and border)."""
    chars, legend, plan = {}, {}, []
    for row in cells:
        line = ''
        for v in row:
            if v not in chars:
                chars[v] = chr(0x100 + len(chars)); legend[chars[v]] = v
            line += chars[v]
        plan.append(line)
    return build_map(layout_id, plan, legend, border)


def neighbours(plan, x, y, pred):
    """'nswe' letters of the 4 neighbours (x, y) for which pred(char) is true (outside = '#')."""
    H, W = len(plan), len(plan[0])
    out = ''
    for e, dx, dy in (('n', 0, -1), ('s', 0, 1), ('w', -1, 0), ('e', 1, 0)):
        X, Y = x + dx, y + dy
        ch = plan[Y][X] if 0 <= X < W and 0 <= Y < H else '#'
        if pred(ch):
            out += e
    return out
