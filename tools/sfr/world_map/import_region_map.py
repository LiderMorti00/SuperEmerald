# Turn an assembled 240x160 indexed region map (as edited in GIMP) back into
# the PokeNav tiles (8bpp, affine 64x64 map) and the Pokedex area tiles
# (8bpp, text 32x32 map). Same palette indices as the game files.
#   python3 import_region_map.py IN.png graphics/pokenav/region_map/map_sinnoh graphics/pokedex/region_map_sinnoh
import sys, collections, numpy as np
from PIL import Image
src = Image.open(sys.argv[1])
assert src.mode == 'P' and src.size == (240, 160), (src.mode, src.size)
a = np.asarray(src)
pal = src.getpalette()
cells = [[a[ty*8:ty*8+8, tx*8:tx*8+8] for tx in range(30)] for ty in range(20)]
count = collections.Counter(c.tobytes() for row in cells for c in row)
sea = np.frombuffer(count.most_common(1)[0][0], np.uint8).reshape(8, 8)
tiles, index = [sea], {sea.tobytes(): 0}
def tid(t):
    k = t.tobytes()
    if k not in index:
        index[k] = len(tiles); tiles.append(t)
    return index[k]
grid = np.zeros((20, 30), int)
for ty in range(20):
    for tx in range(30):
        grid[ty, tx] = tid(cells[ty][tx])
assert len(tiles) <= 256, 'too many tiles: %d (max 256)' % len(tiles)
rows = (len(tiles) + 15) // 16
sheet = np.zeros((rows * 8, 128), np.uint8)
for i, t in enumerate(tiles):
    sheet[(i // 16)*8:(i // 16)*8+8, (i % 16)*8:(i % 16)*8+8] = t
for prefix in sys.argv[2:4]:
    im = Image.fromarray(sheet, 'P'); im.putpalette(pal); im.save(prefix + '.png')
nav = np.zeros((64, 64), np.uint8); nav[:20, :30] = grid
nav.tofile(sys.argv[2] + '.bin')
dex = np.zeros((32, 32), '<u2'); dex[:20, :30] = grid
dex.tofile(sys.argv[3] + '.bin')
print('tiles', len(tiles))
