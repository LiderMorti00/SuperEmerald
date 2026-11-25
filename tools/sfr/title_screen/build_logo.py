#!/usr/bin/env python3
"""Super Emerald: the title screen logo "POKeMON SUPER EMERALD".

Hand-built pixel letters (strokes, outline, gradient fill, drop shadow), laid out as on
the 240x160 title screen and written as the 8bpp affine BG2 the title screen uses:
  graphics/title_screen/pokemon_logo.png  256x72, 8bpp, indices 0-223
  graphics/title_screen/pokemon_logo.pal  colours 0-223 used (row 14 belongs to Rayquaza)
  graphics/title_screen/pokemon_logo.bin  32x32 affine tilemap (1 byte per tile)
The BG sits at x = 29 and slides up to y = 0, so screen (x, y) is logo (x - 29, y).
Run from the repo root: python3 tools/sfr/title_screen/build_logo.py
"""
import numpy as np
from PIL import Image

BG_X = 29
OUT = 'graphics/title_screen/pokemon_logo'

def chamfer(m, c, corners):
    h, w = m.shape
    for y in range(h):
        for x in range(w):
            if ('tl' in corners and x + y < c) or ('tr' in corners and (w - 1 - x) + y < c) \
               or ('bl' in corners and x + (h - 1 - y) < c) or ('br' in corners and (w - 1 - x) + (h - 1 - y) < c):
                m[y, x] = False
    return m

def letter(ch, w, h, sv, sh, c=0):
    m = np.zeros((h, w), bool); mid = (h - sh) // 2
    def V(x0, y0=0, y1=h): m[y0:y1, x0:x0 + sv] = True
    def H(y0, x0=0, x1=w): m[y0:y0 + sh, x0:x1] = True
    if ch == 'E':
        V(0); H(0); H(h - sh); H(mid, 0, w - sv); chamfer(m, c, 'tl bl')
    elif ch == 'L':
        V(0); H(h - sh, 0, w - 1); chamfer(m, c, 'bl')
    elif ch == 'D':
        V(0); H(0, 0, w); H(h - sh, 0, w); V(w - sv, 0, h); chamfer(m, c + 4, 'tr br')
    elif ch == 'O':
        V(0); V(w - sv); H(0); H(h - sh); chamfer(m, c + 1, 'tl tr bl br')
    elif ch == 'U':
        V(0); V(w - sv); H(h - sh); chamfer(m, c + 1, 'bl br')
    elif ch == 'P':
        V(0); H(0, 0, w); H(mid, 0, w); V(w - sv, 0, mid + sh); chamfer(m, c, 'tl tr')
    elif ch == 'R':
        V(0); H(0, 0, w); V(w - sv, 0, mid); chamfer(m, c, 'tl tr')
        for y in range(mid + sh, h):
            t = (y - mid - sh) / max(1, h - 1 - mid - sh)
            x0 = min(w - sv, int(round((w - sv) * (0.45 + 0.55 * t))))
            m[y, x0:x0 + sv] = True
        m[mid:mid + sh, :w - 1] = True; m[mid:mid + sh, w - 1] = False
    elif ch == 'A':
        V(0); V(w - sv); H(0); H(mid + 1); chamfer(m, c + 2, 'tl tr')
    elif ch == 'M':
        V(0); V(w - sv)
        for y in range(int(h * 0.55)):
            for k in range(sv):
                x = sv + y + k - 1
                if x < w // 2 + (w % 2):
                    m[y, x] = True; m[y, w - 1 - x] = True
        chamfer(m, c, 'tl tr')
    elif ch == 'N':
        V(0); V(w - sv)
        for y in range(h):
            x = int(round(sv - 1 + (w - 2 * sv + 1) * y / (h - 1)))
            m[y, max(0, x - 1):x + sv - 1] = True
        chamfer(m, c, 'tl br')
    elif ch == 'S':
        H(0); H(mid); H(h - sh); V(0, 0, mid + sh); V(w - sv, mid, h); chamfer(m, c, 'tl tr bl br')
    elif ch == 'K':
        V(0)
        for y in range(h):
            d = abs(y - (h - 1) / 2) / ((h - 1) / 2)
            x = int(round(sv + (w - 2 * sv) * d)); m[y, x:x + sv] = True
    return m

def word(text, w, h, sv, sh, c=0, sp=2, widths=None):
    parts = []
    for i, ch in enumerate(text):
        parts.append(letter(ch, (widths or {}).get(ch, w), h, sv, sh, c))
        if i < len(text) - 1:
            parts.append(np.zeros((h, sp), bool))
    return np.concatenate(parts, 1)

def dilate(m):
    o = m.copy()
    for dy in (-1, 0, 1):
        for dx in (-1, 0, 1):
            o |= np.roll(np.roll(m, dy, 0), dx, 1)
    return o

def styled(mask, grad, outline, shadow, hilite, pad=3, shadow_off=(1, 2)):
    h, w = mask.shape
    m = np.zeros((h + 2 * pad, w + 2 * pad), bool); m[pad:pad + h, pad:pad + w] = mask
    out = np.zeros(m.shape + (4,), np.uint8)
    ol = dilate(m) & ~m
    sh = np.roll(np.roll(m | ol, shadow_off[1], 0), shadow_off[0], 1) & ~(m | ol)
    out[sh] = shadow + (255,); out[ol] = outline + (255,)
    for y in range(m.shape[0]):
        if m[y].any():
            t = (y - pad) / max(1, h - 1); i = min(len(grad) - 1, int(t * len(grad)))
            out[y, m[y]] = grad[i] + (255,)
    out[m & ~np.roll(m, 1, 0)] = hilite + (255,)
    return Image.fromarray(out, 'RGBA')

GREEN = [(176, 248, 184), (128, 232, 144), (80, 208, 112), (40, 176, 96), (24, 144, 80), (16, 112, 72)]
SILVER = [(255, 255, 255), (232, 240, 248), (200, 216, 232), (168, 188, 212)]
GOLD = [(255, 240, 128), (252, 216, 72), (240, 176, 40), (216, 136, 24)]

def logo_layers():
    pk = word('POKEMON', 7, 9, 2, 2, c=1, sp=1, widths={'M': 9, 'N': 8})
    p = np.zeros((pk.shape[0] + 3, pk.shape[1]), bool); p[3:] = pk
    ex = 7 + 1 + 7 + 1 + 7 + 1 + 3          # the accent sits over the E
    p[0, ex:ex + 2] = True; p[1, ex - 1:ex + 1] = True
    su = word('SUPER', 12, 15, 3, 3, c=1, sp=2)
    em = word('EMERALD', 17, 22, 5, 4, c=2, sp=2, widths={'M': 21})
    P = styled(p, GOLD, (72, 40, 8), (24, 16, 8), (255, 255, 210), shadow_off=(1, 1))
    S = styled(su, SILVER, (16, 40, 72), (0, 16, 40), (255, 255, 255))
    E = styled(em, GREEN, (8, 48, 40), (0, 20, 28), (232, 255, 232))
    return P, S, E

def screen_logo():
    """The logo on a transparent 240x160 screen, as laid out on the title screen."""
    P, S, E = logo_layers()
    im = Image.new('RGBA', (240, 160), (0, 0, 0, 0))
    im.alpha_composite(P, ((240 - P.width) // 2, 6))
    im.alpha_composite(S, ((240 - S.width) // 2, 23))   # SUPER close to EMERALD: one title
    im.alpha_composite(E, ((240 - E.width) // 2, 40))
    return im

def main():
    scr = np.array(screen_logo())
    h = 72
    area = np.zeros((h, 256, 4), np.uint8)
    w = min(256, 240 - BG_X)
    area[:, :w] = scr[:h, BG_X:BG_X + w]
    assert not scr[h:, :, 3].any(), 'logo taller than the BG area'
    old = open(OUT + '.pal').read().split('\n')
    colors = [tuple(map(int, old[3].split()))]   # keep colour 0 (backdrop)
    index = np.zeros((h, 256), np.uint8)
    for y in range(h):
        for x in range(256):
            if area[y, x, 3]:
                c = tuple(int(v) for v in area[y, x, :3])
                if c not in colors:
                    colors.append(c)
                index[y, x] = colors.index(c)
    assert len(colors) <= 224, len(colors)
    pal = colors + [(0, 0, 0)] * (256 - len(colors))
    tiles, tmap = [np.zeros((8, 8), np.uint8)], np.zeros((32, 32), np.uint8)
    seen = {tiles[0].tobytes(): 0}
    for ty in range(h // 8):
        for tx in range(32):
            t = index[ty * 8:ty * 8 + 8, tx * 8:tx * 8 + 8]
            k = t.tobytes()
            if k not in seen:
                seen[k] = len(tiles); tiles.append(t.copy())
            tmap[ty, tx] = seen[k]
    assert len(tiles) <= 256, len(tiles)
    rows = (len(tiles) + 31) // 32
    sheet = np.zeros((rows * 8, 256), np.uint8)
    for i, t in enumerate(tiles):
        sheet[(i // 32) * 8:(i // 32) * 8 + 8, (i % 32) * 8:(i % 32) * 8 + 8] = t
    img = Image.fromarray(sheet, 'P')
    img.putpalette([v for c in pal for v in c] + [0] * (3 * (256 - len(pal))))
    img.save(OUT + '.png')
    with open(OUT + '.pal', 'w') as f:
        f.write('JASC-PAL\r\n0100\r\n256\r\n' + ''.join('%d %d %d\r\n' % c for c in pal))
    tmap.tofile(OUT + '.bin')
    print('colours', len(colors), 'tiles', len(tiles))

if __name__ == '__main__':
    main()
