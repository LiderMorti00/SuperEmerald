import sys, numpy as np
from PIL import Image
def load(png, binf, w=64):
    im = Image.open(png); pal = im.getpalette()
    a = np.asarray(im)
    tw = a.shape[1]//8
    tiles = [a[(i//tw)*8:(i//tw)*8+8,(i%tw)*8:(i%tw)*8+8] for i in range((a.shape[0]//8)*tw)]
    m = np.fromfile(binf, np.uint8).reshape(w, w)
    return tiles, m, pal
def render(png, binf, out, cols=30, rows=20, x0=0, y0=0):
    tiles, m, pal = load(png, binf)
    img = np.zeros((rows*8, cols*8), np.uint8)
    for r in range(rows):
        for c in range(cols):
            t = m[y0+r, x0+c]
            img[r*8:r*8+8, c*8:c*8+8] = tiles[t] if t < len(tiles) else 0
    o = Image.fromarray(img, 'P'); o.putpalette(pal); o.convert('RGB').save(out)
if __name__ == '__main__':
    render(sys.argv[1], sys.argv[2], sys.argv[3], *map(int, sys.argv[4:]))
