import os, sys, numpy as np
from PIL import Image
from scipy import ndimage
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from render import load
RM = os.path.join(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', '..'), 'graphics', 'pokenav', 'region_map') + '/'
GREENS = [(0,115,0),(57,172,8),(98,213,0),(172,238,49),(213,255,123)]
def full(name, w=30, h=18):
    tiles, m, pal = load(RM + name + '.png', RM + name + '.bin')
    img = np.zeros((h*8, w*8), np.uint8)
    for r in range(h):
        for c in range(w):
            t = m[r, c]; img[r*8:r*8+8, c*8:c*8+8] = tiles[t] if t < len(tiles) else 0
    p = np.array(pal[:768]).reshape(-1, 3)
    return p[img].astype(int)
def png_rgb(path, h=18):
    im = Image.open(path)
    p = np.array(im.getpalette()[:768]).reshape(-1, 3)
    return p[np.asarray(im)[:h*8]].astype(int)
def bands(name, **kw):
    if name.endswith('.png'):
        rgb = png_rgb(RM + name, kw.get('h', 18))
    else:
        rgb = full(name, **kw)
    r, g, b = rgb[..., 0], rgb[..., 1], rgb[..., 2]
    sea = (b > g) & (b > r + 30)
    land = (g > b + 20) & (g > r + 15)   # greens only; routes, markers and text are filled from around them
    cls = np.full(r.shape, -1)
    cls[sea] = 0
    # nearest green band
    gi = np.argmin([((rgb - np.array(c))**2).sum(-1) for c in GREENS], axis=0) + 1
    cls[land] = gi[land]
    white = (r > 240) & (g > 240) & (b > 240)
    known = cls >= 0
    d, (iy, ix) = ndimage.distance_transform_edt(~known, return_indices=True)
    cls = cls[iy, ix]
    return cls
if __name__ == '__main__':
    out = []
    for n in ['map', 'map_johto', 'map_kanto', 'map_sinnoh', 'map_sevii_123', 'map_sevii_45', 'map_sevii_67']:
        c = bands(n); np.save('/tmp/b_%s.npy' % n, c)
        pal = [(156,213,255)] + GREENS
        img = np.array(pal)[c].astype(np.uint8)
        out.append(Image.fromarray(img))
    W = Image.new('RGB', (250*4, 150*2), 'white')
    for i, im in enumerate(out): W.paste(im, ((i % 4)*250, (i//4)*150))
    W.save('/tmp/bands.png')
