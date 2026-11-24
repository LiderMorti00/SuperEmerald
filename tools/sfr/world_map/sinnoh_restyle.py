# Redraw the Sinnoh PokeNav region map in the Emerald/HnS region map style.
# Keeps the cell grid (cursor positions) of the current map.
# One-off conversion: run it on the old pastel map (commit a3f4f591db),
#   python3 sinnoh_restyle.py OLD_PNG OLD_BIN OUT_PREFIX
import os, sys, numpy as np
from PIL import Image
from scipy import ndimage
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from render import load
RM = os.path.join(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', '..'), 'graphics', 'pokenav', 'region_map') + '/'
tiles, m, spal = load(sys.argv[1], sys.argv[2])
S = np.zeros((256, 512), np.uint8)
for r in range(32):
    for c in range(64): S[r*8:r*8+8, c*8:c*8+8] = tiles[m[r, c]]
H, W = 256, 512
SEA = np.isin(S, [120, 0])
LANDC = {127: 126, 124: 126, 121: 125, 118: 124, 125: 126, 119: 122, 113: 129, 117: 122}
ROUTE = np.isin(S, [115, 116])
RED = np.isin(S, [122, 128]); BLUE = np.isin(S, [123, 126]); CYAN = (S == 114)
landpx = np.isin(S, list(LANDC))
known = SEA | landpx
# fill under routes/markers with the nearest known class/colour
d, (iy, ix) = ndimage.distance_transform_edt(~known, return_indices=True)
base = S[iy, ix]
issea = np.isin(base, [120, 0])
out = np.zeros((H, W), np.uint8)
yy = np.arange(H)[:, None].repeat(W, 1)
out[:] = np.where(yy % 2 == 0, 113, 114)
lm = np.vectorize(lambda v: LANDC.get(int(v), 124))(base)
out[~issea] = lm[~issea]
# cells
cls = {}
for ty in range(32):
    for tx in range(64):
        sl = (slice(ty*8, ty*8+8), slice(tx*8, tx*8+8))
        f = lambda mask: mask[sl].mean()
        if f(RED) > 0.3: cls[(tx, ty)] = 'R'
        elif f(BLUE) > 0.3: cls[(tx, ty)] = 'T'      # towns -> red too
        elif f(CYAN) > 0.3 and f(SEA) < 0.5: cls[(tx, ty)] = 'L'
        elif f(ROUTE) > 0.3: cls[(tx, ty)] = '='
for (tx, ty), c in cls.items():
    if c != '=': continue
    sl = (slice(ty*8, ty*8+8), slice(tx*8, tx*8+8))
    seafrac = issea[max(0, ty*8-8):ty*8+16, max(0, tx*8-8):tx*8+16].mean()
    if issea[sl].mean() > 0.5:
        out[sl] = np.where(yy[sl] % 2 == 0, 116, 117)
    else:
        out[sl] = 132
# markers
RED_STYLE = {'hl': 134, 'body': 136, 'shadow': 138}
BLUE_STYLE = {'hl': 115, 'body': 120, 'shadow': 120}
def draw_marker(cells, style):
    mask = np.zeros((H, W), bool)
    for (tx, ty) in cells: mask[ty*8:ty*8+8, tx*8:tx*8+8] = True
    ys, xs = np.where(mask)
    y0, x0 = ys.min(), xs.min()
    for y, x in zip(ys, xs):
        up = mask[y-1, x]; dn = mask[y+1, x]; lf = mask[y, x-1]; rt = mask[y, x+1]
        up2 = mask[y-2, x]; dn2 = mask[y+2, x]; lf2 = mask[y, x-2]; rt2 = mask[y, x+2]
        ring_t, ring_b, ring_l, ring_r = not up, not dn, not lf, not rt
        if (ring_t or ring_b) and (ring_l or ring_r):
            continue                                   # corner pixel keeps the background
        if ring_t or ring_l:
            near_corner = (ring_t and (not lf2 or not rt2)) or (ring_l and (not up2 or not dn2))
            v = 140 if near_corner else 129
        elif ring_b or ring_r:
            near_corner = (ring_b and (not lf2 or not rt2)) or (ring_r and (not up2 or not dn2))
            v = 140 if near_corner else 139
        else:
            in_t, in_b, in_l, in_r = not up2, not dn2, not lf2, not rt2
            if (in_t and in_l):
                v = 129
            elif (in_t and in_r) or (in_b and in_l) or (in_b and in_r):
                v = 139 if not (in_t and in_r) else 139
            elif in_r or in_b:
                v = style['shadow']
            elif in_l or in_t:
                v = style['hl']
            else:
                v = style['body']
        out[y, x] = v
    # glint on the first cell
    gx, gy = x0 + 2, y0 + 2
    out[gy:gy+2, gx:gx+2] = 129
    out[gy-1, gx:gx+2] = style['hl']; out[gy+2, gx:gx+2] = style['hl']
    out[gy:gy+2, gx-1] = style['hl']; out[gy:gy+2, gx+2] = style['hl']
seen = set()
for (tx, ty), c in sorted(cls.items()):
    if c not in 'RT' or (tx, ty) in seen: continue
    comp = [(tx, ty)]; stack = [(tx, ty)]; seen.add((tx, ty))
    while stack:
        a, b = stack.pop()
        for n in ((a+1, b), (a-1, b), (a, b+1), (a, b-1)):
            if cls.get(n) == 'R' and c == 'R' and n not in seen:
                seen.add(n); comp.append(n); stack.append(n)
    draw_marker(comp, RED_STYLE)
for (tx, ty), c in cls.items():
    if c == 'L': draw_marker([(tx, ty)], BLUE_STYLE)
np.save('/tmp/sinnoh_new.npy', out)
# preview with the Emerald palette
pim = Image.open(RM + 'map.png'); epal = pim.getpalette()
o = Image.fromarray(out[:256, :256], 'P'); o.putpalette(epal); o.convert('RGB').save('/tmp/sinnoh_new.png')
# tiles
uniq = {}
for ty in range(32):
    for tx in range(64):
        uniq.setdefault(out[ty*8:ty*8+8, tx*8:tx*8+8].tobytes(), 0)
print('unique tiles', len(uniq))

def export(prefix):
    tl = []; idx = {}
    tm = np.zeros((64, 64), np.uint8)
    blank = np.where(np.arange(8)[:, None].repeat(8, 1) % 2 == 0, 113, 114).astype(np.uint8)
    def get(t):
        k = t.tobytes()
        if k not in idx:
            idx[k] = len(tl); tl.append(t.copy())
        return idx[k]
    get(blank)
    for ty in range(64):
        for tx in range(64):
            if ty < 32:
                tm[ty, tx] = get(out[ty*8:ty*8+8, tx*8:tx*8+8])
            else:
                tm[ty, tx] = 0
    assert len(tl) <= 256, len(tl)
    rows = (len(tl) + 15) // 16
    sheet = np.zeros((rows*8, 128), np.uint8)
    for i, t in enumerate(tl):
        sheet[(i//16)*8:(i//16)*8+8, (i%16)*8:(i%16)*8+8] = t
    im = Image.fromarray(sheet, 'P'); im.putpalette(epal); im.save(prefix + '.png')
    tm.tofile(prefix + '.bin')
    print('exported', len(tl), 'tiles')
if len(sys.argv) > 3:
    export(sys.argv[3])
