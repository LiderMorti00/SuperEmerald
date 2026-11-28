#!/usr/bin/env python3
# Super Emerald: trainer card badge titles ("KANTO BADGES"...) in the same 2-px block letters as the
# card's original "BADGES" label (6 px tall, white, no outline). Writes graphics/trainer_card/titles/*.png
# (index 0 transparent, 1 white) and prints the widths for src/trainer_card.c.
import os
from PIL import Image
G = {
 'A': ['..11..', '.1111.', '11..11', '111111', '11..11', '11..11'],
 'B': ['11111.', '11..11', '11111.', '11..11', '11..11', '11111.'],
 'D': ['11111.', '11..11', '11..11', '11..11', '11..11', '11111.'],
 'E': ['11111', '11...', '1111.', '11...', '11...', '11111'],
 'G': ['.11111', '11....', '11.111', '11..11', '11..11', '.11111'],
 'H': ['11..11', '11..11', '111111', '11..11', '11..11', '11..11'],
 'I': ['11', '11', '11', '11', '11', '11'],
 'J': ['....11', '....11', '....11', '....11', '11..11', '.1111.'],
 'K': ['11..11', '11.11.', '1111..', '11.11.', '11..11', '11..11'],
 'N': ['11..11', '111.11', '111111', '11.111', '11..11', '11..11'],
 'O': ['.1111.', '11..11', '11..11', '11..11', '11..11', '.1111.'],
 'S': ['.1111', '11...', '.111.', '...11', '...11', '1111.'],
 'T': ['111111', '..11..', '..11..', '..11..', '..11..', '..11..'],
 ' ': ['...', '...', '...', '...', '...', '...'],
 '<': ['..11', '.111', '1111', '1111', '.111', '..11'],
 '>': ['11..', '111.', '1111', '1111', '111.', '11..'],
}
OUT = os.path.join(os.path.dirname(__file__), '..', '..', '..', 'graphics', 'trainer_card', 'titles')

def render(text, width):
    im = Image.new('P', (width, 8), 0)
    im.putpalette([0, 0, 0, 255, 255, 255] + [0] * 42)
    x = 0
    for ch in text:
        g = G[ch]
        for y, row in enumerate(g):
            for dx, c in enumerate(row):
                if c == '1':
                    im.putpixel((x + dx, 1 + y), 1)
        x += len(g[0]) + 1
    return im, x - 1

for name, text in (('kanto', 'KANTO BADGES'), ('johto', 'JOHTO BADGES'), ('hoenn', 'HOENN BADGES'), ('sinnoh', 'SINNOH BADGES')):
    im, w = render(text, 88)
    im.save(os.path.join(OUT, name + '.png'), bits=4)
    print(name, w)
for name, text in (('arrow_left', '<'), ('arrow_right', '>')):
    im, w = render(text, 8)
    im.save(os.path.join(OUT, name + '.png'), bits=4)
