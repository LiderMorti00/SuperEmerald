# PokeNav world overview: thumbnails made from the regional maps' own coastlines.
# python3 world_map_gen.py export graphics/pokenav/region_map   (preview: no args)
import os, sys, numpy as np
from PIL import Image
from scipy import ndimage
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from thumbs import bands

W, H = 240, 160
# Emerald region map colours
BASE = [
    (0, 0, 0),         # 0 unused
    (156, 213, 255),   # 1 sea
    (164, 180, 255),   # 2 sea stripe
    (0, 115, 0),       # 3 land band 1 (coast)
    (57, 172, 8),      # 4 band 2
    (98, 213, 0),      # 5 band 3
    (172, 238, 49),    # 6 band 4
    (213, 255, 123),   # 7 band 5
    (255, 255, 255),   # 8 white
    (98, 98, 98),      # 9 dark grey
    (255, 57, 16),     # 10 red
    (230, 164, 0),     # 11 red highlight (orange)
    (148, 0, 0),       # 12 red shadow
    (41, 131, 230),    # 13-15 sea lanes
    (41, 131, 230),
    (41, 131, 230),
]
LANE_COLOR = (41, 131, 230)
OWN = ['HOENN', 'JOHTO', 'KANTO', 'SINNOH', 'SEVII1', 'SEVII2', 'SEVII3', 'SEVII_ALL']
O = {n: i + 1 for i, n in enumerate(OWN)}
PALS = [(5,'HOENN','ABE'),(6,'JOHTO','ABE'),(7,'KANTO','DBC'),(8,'SINNOH','ABC'),(9,'SEVII1','D--'),
        (10,'SEVII2','D--'),(11,'SEVII3','D--'),(12,'SEVII_ALL','D--'),(13,None,'ABE'),(14,None,'DBC')]

cls = np.zeros((H, W), np.int8)      # 0 sea, 1..5 bands
owner = np.zeros((H, W), np.int8)

def scaled(c, s, rows=None):
    """Downscale a band image by s: land where >=45% of the block is land, band = mode."""
    h, w = c.shape
    nh, nw = int(round(h * s)), int(round(w * s))
    out = np.zeros((nh, nw), np.int8)
    for y in range(nh):
        for x in range(nw):
            y0, y1 = int(y / s), max(int((y + 1) / s), int(y / s) + 1)
            x0, x1 = int(x / s), max(int((x + 1) / s), int(x / s) + 1)
            blk = c[y0:y1, x0:x1]
            land = blk[blk > 0]
            if land.size >= 0.45 * blk.size:
                out[y, x] = np.bincount(land).argmax()
    # drop one-pixel specks and fill one-pixel holes
    lm = out > 0
    lab, n = ndimage.label(lm)
    for i in range(1, n + 1):
        if (lab == i).sum() < 2: out[lab == i] = 0
    holes = ndimage.binary_fill_holes(out > 0) & (out == 0)
    lab, n = ndimage.label(holes)
    for i in range(1, n + 1):
        r = lab == i
        if r.sum() < 2:
            out[r] = np.bincount(out[ndimage.binary_dilation(r) & ~r]).argmax()
    return out

def keep_small_islands(src, s, out):
    """Islands that vanished when shrinking come back as one or two pixels."""
    lab, n = ndimage.label(src > 0)
    for i in range(1, n + 1):
        ys, xs = np.where(lab == i)
        if ys.size < 6: continue
        cy, cx = int(ys.mean() * s), int(xs.mean() * s)
        if 0 <= cy < out.shape[0] and 0 <= cx < out.shape[1] and not out[max(0,cy-1):cy+2, max(0,cx-1):cx+2].any():
            out[cy, cx] = 1
            if ys.size > 40 and cx + 1 < out.shape[1]: out[cy, cx + 1] = 1

def place(t, x0, y0, own, xmin=0, xmax=W):
    h, w = t.shape
    for y in range(h):
        for x in range(w):
            X, Y = x0 + x, y0 + y
            if 0 <= X < W and 0 <= Y < H and t[y, x] > 0 and xmin <= X < xmax:
                cls[Y, X] = t[y, x]; owner[Y, X] = O[own]

def round_cut(t, side):
    """Soften a straight edge where the regional map cuts the land off."""
    if side == 'left':
        col = np.where(t[:, 0] > 0)[0]
        if col.size:
            t[col.min(), 0] = 0; t[col.max(), 0] = 0
            t[col.min():col.min()+2, 0] = 0; t[col.max()-1:col.max()+1, 0] = 0
    return t

src = {n: bands(n, w=30, h=20) for n in ['map', 'map_johto', 'map_kanto', 'map_sinnoh',
                                        'map_sevii_123', 'map_sevii_45', 'map_sevii_67']}
# Johto + Kanto: the Kanto map continues the Johto map to the east
JK_S = 0.36
src_j = src['map_johto'][:144]; src_k = src['map_kanto'][:144]
tj = scaled(src_j, JK_S); tk = scaled(src_k, JK_S)
JX, JY = 2, 0
SEAM = 88                                   # Johto | Kanto, on a tile boundary
KX = SEAM
place(tj, JX, JY, 'JOHTO', xmax=SEAM)
place(tk, KX, JY, 'KANTO', xmin=SEAM)
# Hoenn
HO_S = 0.5
th = scaled(src['map'][:150], HO_S); keep_small_islands(src['map'][:150], HO_S, th)
HX, HY = 0, 66
place(th, HX, HY, 'HOENN')
# Sinnoh
SI_S = 0.4
ts = round_cut(scaled(src['map_sinnoh'], SI_S), 'left'); keep_small_islands(src['map_sinnoh'], SI_S, ts)
SX, SY = 144, 14
place(ts, SX, SY, 'SINNOH')
# Sevii inset: tiles cols 21..29, rows 9..17
BX0, BY0, BX1, BY1 = 144, 80, 239, 143
cls[BY0:BY1+1, BX0:BX1+1] = 0; owner[BY0:BY1+1, BX0:BX1+1] = 0
SV_S = 0.22
def sevii(name, own, rect, s=SV_S):
    c = src[name]
    ys, xs = np.where(c > 0)
    c = c[ys.min():ys.max()+1, xs.min():xs.max()+1]
    x0, y0, x1, y1 = rect
    s = min((x1 - x0 - 2) / c.shape[1], (y1 - y0 - 2) / c.shape[0])
    t = scaled(c, s); keep_small_islands(c, s, t)
    ox = x0 + (x1 - x0 - t.shape[1]) // 2; oy = y0 + (y1 - y0 - t.shape[0]) // 2
    for y in range(t.shape[0]):
        for x in range(t.shape[1]):
            X, Y = ox + x, oy + y
            if t[y, x] and x0 <= X < x1 and y0 <= Y < y1:
                cls[Y, X] = t[y, x]; owner[Y, X] = O[own]
    return ox, oy, ys.min(), xs.min(), s
SV1 = sevii('map_sevii_123', 'SEVII1', (152, 88, 200, 112))
SV2 = sevii('map_sevii_45', 'SEVII2', (200, 88, 232, 112))
SV3 = sevii('map_sevii_67', 'SEVII3', (152, 112, 232, 136))

# ---- colours ----
idx = np.zeros((H, W), np.uint8)
yy = np.arange(H)[:, None].repeat(W, 1)
idx[:] = np.where(yy % 2 == 0, 1, 2)
land = cls > 0
idx[land] = (cls[land] + 2).astype(np.uint8)

def setpx(x, y, v, own):
    if 0 <= x < W and 0 <= y < H:
        idx[y, x] = v; owner[y, x] = O[own] if own else 0
# inset frame + title bar
for x in range(BX0 + 2, BX1 - 1):
    for y in (BY1 - 3, BY1 - 2): setpx(x, y, 9, 'SEVII_ALL')
for y in range(BY0 + 2, BY1 - 1):
    for x in (BX0 + 2, BX0 + 3, BX1 - 3, BX1 - 2): setpx(x, y, 9, 'SEVII_ALL')
for y in range(BY0 + 2, BY0 + 8):
    for x in range(BX0 + 2, BX1 - 1): setpx(x, y, 9, 'SEVII_ALL')

FONT = {
 'A': ["###","#.#","###","#.#","#.#"], 'D': ["##.","#.#","#.#","#.#","##."],
 'E': ["###","#..","##.","#..","###"], 'H': ["#.#","#.#","###","#.#","#.#"],
 'I': ["###",".#.",".#.",".#.","###"], 'J': ["..#","..#","..#","#.#","###"],
 'K': ["#.#","#.#","##.","#.#","#.#"], 'L': ["#..","#..","#..","#..","###"],
 'N': ["#..#","##.#","#.##","#..#","#..#"], 'O': ["###","#.#","#.#","#.#","###"],
 'S': ["###","#..","###","..#","###"], 'T': ["###",".#.",".#.",".#.",".#."],
 'V': ["#.#","#.#","#.#","#.#",".#."], ' ': ["..","..","..","..",".."],
 '1': [".#","##",".#",".#",".#"], '2': ["###","..#","###","#..","###"], '3': ["###","..#",".##","..#","###"],
 '4': ["#.#","#.#","###","..#","..#"], '5': ["###","#..","###","..#","###"], '6': ["###","#..","###","#.#","###"],
 '7': ["###","..#","..#",".#.",".#."], '-': ["..","..","##","..",".."],
}
def text(s, x, y, own, outline=True):
    cx = x; pix = []
    for ch in s:
        g = FONT[ch]
        for r, row in enumerate(g):
            for c, v in enumerate(row):
                if v == '#': pix.append((cx + c, y + r))
        cx += len(g[0]) + 1
    if outline:
        for (px, py) in pix:
            for dx in (-1, 0, 1):
                for dy in (-1, 0, 1):
                    q = (px + dx, py + dy)
                    if q not in pix: setpx(q[0], q[1], 9, own)
    for (px, py) in pix: setpx(px, py, 8, own)

# ports: mapsec cell -> thumbnail pixel
def cell(gx, gy):
    return ((gx + 1) * 8 + 4, (gy + 2) * 8 + 4)
def to_thumb(p, s, ox, oy):
    return (ox + int(p[0] * s), oy + int(p[1] * s))
PORTS = {
    'SLATEPORT': ('HOENN', to_thumb(cell(8, 10.5), HO_S, HX, HY)),
    'OLIVINE':   ('JOHTO', to_thumb(cell(6, 4), JK_S, JX, JY)),
    'VERMILION': ('KANTO', to_thumb(cell(14, 9), JK_S, KX, JY)),
    'CANALAVE':  ('SINNOH', to_thumb(cell(0, 10.5), SI_S, SX, SY)),
}
oi = cell(1, 8)
PORTS['ONE'] = ('SEVII1', (SV1[0] + int((oi[0] - SV1[3]) * SV1[4]), SV1[1] + int((oi[1] - SV1[2]) * SV1[4])))
def marker(cx, cy, own):
    # 5x5 Emerald-style red marker
    shape = ["9WW9.", "WOR R".replace(' ', 'R'), "WRRRS", "9SSS9"]
    art = [".999.", "9WOR9", "9ORR9", "9RRS9", ".999."]
    col = {'9': 9, 'W': 8, 'O': 11, 'R': 10, 'S': 12}
    for dy, row in enumerate(art):
        for dx, ch in enumerate(row):
            if ch != '.': setpx(cx - 2 + dx, cy - 2 + dy, col[ch], own)
for name, (own, (x, y)) in PORTS.items():
    marker(x, y, own)

lane_px = {}
def lane(name, pts, dash=(3, 2)):
    k = 0
    for (x0, y0), (x1, y1) in zip(pts, pts[1:]):
        n = max(abs(x1 - x0), abs(y1 - y0))
        for i in range(n + 1):
            x = round(x0 + (x1 - x0) * i / n); y = round(y0 + (y1 - y0) * i / n)
            if y % 2: continue
            if idx[y, x] != 1: continue
            k += 1
            if k % (dash[0] + dash[1]) >= dash[0]: continue
            lane_px[(x, y)] = name

# ======== labels ========
text('JOHTO', 30, 50, 'JOHTO')
text('KANTO', 96, 47, 'KANTO')
text('HOENN', 44, 60, 'HOENN')
text('SINNOH', 200, 70, 'SINNOH')
text('SEVII ISLANDS', BX0 + 4, BY0 + 3, 'SEVII_ALL', outline=False)

# ======== sea lanes ========
lane('E', [(20,24),(19,30),(19,52)])
lane('A', [(19,52),(19,58),(100,58),(100,90),(84,106),(60,112),(44,118)])
lane('B', [(19,52),(22,54),(112,54),(122,44),(127,40)])
lane('C', [(131,40),(136,48),(143,56)])
lane('D', [(130,40),(136,62),(140,92),(146,98),(154,98)])
for (x, y), n in lane_px.items():
    if idx[y, x] == 1:
        idx[y, x] = 100 + 'ABCDE'.index(n)

tile_pal = np.zeros((20, 30), int)
errors = []
for ty in range(20):
    for tx in range(30):
        sl = (slice(ty*8, ty*8+8), slice(tx*8, tx*8+8))
        owners = set(np.unique(owner[sl]).tolist()) - {0}
        lanes = set('ABCDE'[v - 100] for v in np.unique(idx[sl]) if v >= 100)
        cands = []
        for slot, own, lm in PALS:
            if owners and (len(owners) > 1 or O.get(own) not in owners): continue
            if not owners and own is not None: continue
            if not lanes <= set(lm): continue
            cands.append((slot, lm))
        if not cands:
            errors.append((tx, ty, owners, lanes)); cands = [(13, 'ABE')]
        slot, lm = cands[0]
        tile_pal[ty, tx] = slot
        sub = idx[sl]
        for v in range(100, 105):
            n = 'ABCDE'[v - 100]
            sub[sub == v] = (13 + lm.index(n)) if n in lm else 1
for e in errors: print('TILE CONFLICT', e)
assert idx.max() <= 15 and idx.min() >= 1

OWNER_OF_SLOT = {s: o for s, o, l in PALS}
LANES_OF_SLOT = {s: l for s, o, l in PALS}
def palette_for(slot, sel, unlocked):
    own = OWNER_OF_SLOT[slot]
    p = [list(c) for c in BASE]
    for i, n in enumerate(LANES_OF_SLOT[slot]):
        p[13 + i] = list(LANE_COLOR) if (n in unlocked) else list(BASE[1])
    lit = own is None or own == sel or (own == 'SEVII_ALL' and sel.startswith('SEVII'))
    if not lit:
        for i in range(3, 13):
            r, g, b = p[i]
            p[i] = [int((r * 7 + 16 * 9) / 16), int((g * 7 + 32 * 9) / 16), int((b * 7 + 64 * 9) / 16)]
    return [tuple((c >> 3) << 3 for c in col) for col in p]
def render(sel, unlocked, path):
    out = np.zeros((H, W, 3), np.uint8)
    for ty in range(20):
        for tx in range(30):
            pal = palette_for(tile_pal[ty, tx], sel, unlocked)
            out[ty*8:ty*8+8, tx*8:tx*8+8] = np.array(pal, np.uint8)[idx[ty*8:ty*8+8, tx*8:tx*8+8]]
    Image.fromarray(out).save(path)

def export(outdir):
    tiles = []; lookup = {}
    tmap = np.zeros((32, 32), np.uint16)
    def add_tile(t):
        for hf in (0, 1):
            for vf in (0, 1):
                tt = t
                if hf: tt = tt[:, ::-1]
                if vf: tt = tt[::-1, :]
                k = tt.tobytes()
                if k in lookup: return lookup[k], hf, vf
        tiles.append(t.copy()); lookup[t.tobytes()] = len(tiles) - 1
        return len(tiles) - 1, 0, 0
    seaid, _, _ = add_tile(np.where(np.arange(8)[:, None].repeat(8, 1) % 2 == 0, 1, 2).astype(np.uint8))
    for ty in range(32):
        for tx in range(32):
            if ty < 20 and tx < 30:
                i, hf, vf = add_tile(idx[ty*8:ty*8+8, tx*8:tx*8+8]); pal = tile_pal[ty, tx]
            else:
                i, hf, vf, pal = seaid, 0, 0, 13
            tmap[ty, tx] = i | (hf << 10) | (vf << 11) | (pal << 12)
    n = len(tiles); rows = (n + 15) // 16
    sheet = np.full((rows * 8, 128), 1, np.uint8)
    for i, t in enumerate(tiles):
        sheet[(i // 16)*8:(i // 16)*8+8, (i % 16)*8:(i % 16)*8+8] = t
    img = Image.fromarray(sheet, 'P'); flat = []
    for c in BASE: flat += list(c)
    img.putpalette(flat + [0] * (768 - len(flat))); img.save(outdir + '/world_map.png', bits=4)
    with open(outdir + '/world_map.pal', 'w') as f:
        f.write('JASC-PAL\r\n0100\r\n16\r\n')
        for c in BASE: f.write('%d %d %d\r\n' % c)
    tmap.astype('<u2').tofile(outdir + '/world_map.bin')
    print('tiles', n, 'bytes4bpp', n * 32)

if __name__ == '__main__':
    if len(sys.argv) > 2 and sys.argv[1] == 'export':
        export(sys.argv[2])
    else:
        render('KANTO', 'ABCDE', '/tmp/p_kanto.png')
        render('SEVII1', 'ABCDE', '/tmp/p_sevii1.png')
        render('HOENN', '', '/tmp/p_early.png')
