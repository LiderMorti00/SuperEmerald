# Turn the assembled 480x160 Johto + Kanto PokeNav map (indexed, region map palette
# indices 113+) into a 4bpp text background: tiles, a 64x32 tilemap in two
# screenblocks, and 3 BG palettes (loaded at BG palette 7).
#   python3 import_joint_map.py IN.png OUT_PREFIX
import sys, numpy as np
from PIL import Image
src = Image.open(sys.argv[1]); OUT = sys.argv[2]
assert src.mode == 'P' and src.size == (480, 160), (src.mode, src.size)
A = np.asarray(src); P = src.getpalette()
TW, TH = 60, 20
cells = [[A[ty*8:ty*8+8, tx*8:tx*8+8] for tx in range(TW)] for ty in range(TH)]
sets = sorted({frozenset(np.unique(c).tolist()) for row in cells for c in row}, key=lambda s: (-len(s), sorted(s)))
pals = []
for s in sets:
    best = None
    for i, p in enumerate(pals):
        if s <= p: best = (0, i); break
        u = p | s
        if len(u) <= 15 and (best is None or len(u) - len(p) < best[0]): best = (len(u) - len(p), i)
    if best is None: pals.append(set(s))
    else: pals[best[1]] |= s
assert len(pals) <= 3, len(pals)
pals = [sorted(p) for p in pals]
sea = cells[TH - 1][TW - 1]
tiles, lookup = [], {}
def add(t):
    for hf in (0, 1):
        for vf in (0, 1):
            tt = t[:, ::-1] if hf else t
            tt = tt[::-1, :] if vf else tt
            k = tt.tobytes()
            if k in lookup: return lookup[k], hf, vf
    tiles.append(t); lookup[t.tobytes()] = len(tiles) - 1
    return len(tiles) - 1, 0, 0
def encode(c):
    s = set(np.unique(c).tolist())
    k = next(i for i, p in enumerate(pals) if s <= set(p))
    local = np.zeros((8, 8), np.uint8)
    for j, v in enumerate(pals[k]): local[c == v] = j + 1
    i, hf, vf = add(local)
    return i | (hf << 10) | (vf << 11) | ((7 + k) << 12)
seaentry = encode(sea)
tm = np.full((32, 64), seaentry, np.uint16)
for ty in range(TH):
    for tx in range(TW):
        tm[ty, tx] = encode(cells[ty][tx])
# text BG 512x256: screenblock 0 = columns 0-31, screenblock 1 = columns 32-63
out = np.concatenate([tm[:, :32].reshape(-1), tm[:, 32:].reshape(-1)]).astype('<u2')
out.tofile(OUT + '.bin')
rows = (len(tiles) + 15) // 16
sheet = np.zeros((rows * 8, 128), np.uint8)
for i, t in enumerate(tiles):
    sheet[(i // 16)*8:(i // 16)*8+8, (i % 16)*8:(i % 16)*8+8] = t
im = Image.fromarray(sheet, 'P')
flat = [0, 0, 0]
for v in pals[0]: flat += P[3*v:3*v+3]
flat += [0] * (768 - len(flat)); im.putpalette(flat); im.save(OUT + '.png', bits=4)
with open(OUT + '.pal', 'w') as f:
    f.write('JASC-PAL\r\n0100\r\n48\r\n')
    for k in range(3):
        cols = [(0, 0, 0)] + [tuple(P[3*v:3*v+3]) for v in (pals[k] if k < len(pals) else [])]
        cols += [(0, 0, 0)] * (16 - len(cols))
        for c in cols: f.write('%d %d %d\r\n' % c)
print('tiles', len(tiles), 'palettes', len(pals))
