#!/usr/bin/env python3
"""Super Emerald: import the HnS trainer front pics and classes Johto needs.

Usage (repo root): python3 -I tools/sfr/hns/import_trainer_gfx.py [--hns /path]
Adds TRAINER_PIC_* / TRAINER_CLASS_* between "Super Emerald: HnS" markers. Safe to run again.
"""
import os, re, sys
from PIL import Image
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from common import hns, ours, read, write

# HnS file -> our pic name (party "Pic:" value)
PICS = {
    'sage_hns': 'Sage', 'sage_leader_hns': 'Sage Elder', 'officer_hns': 'Officer', 'skier_m_hns': 'Skier M',
    'skier_f_hns': 'Skier F', 'kimono_girl_hns': 'Kimono Girl', 'gold_hns': 'Gold',
    'leader_falkner_hns': 'Leader Falkner', 'leader_bugsy_hns': 'Leader Bugsy', 'leader_whitney_hns': 'Leader Whitney',
    'leader_morty_hns': 'Leader Morty', 'leader_chuck_hns': 'Leader Chuck', 'leader_jasmine_hns': 'Leader Jasmine',
    'leader_pryce_hns': 'Leader Pryce', 'leader_clair_hns': 'Leader Clair',
    'elite_four_will_hns': 'Elite Four Will', 'elite_four_koga_hns': 'Elite Four Koga Hgss',
    'elite_four_bruno_hns': 'Elite Four Bruno Hgss', 'elite_four_karen_hns': 'Elite Four Karen Hgss',
    'champion_lance_hns': 'Champion Lance Hgss',
}
# class name -> (displayed name, money)
CLASSES = {'Sage': ('SAGE', 8), 'Officer': ('OFFICER', 10), 'Skier': ('SKIER', 10), 'Kimono Girl': ('KIMONO GIRL', 20)}
BEGIN, END = '// Super Emerald: HnS begin', '// Super Emerald: HnS end'


def const(prefix, name):
    return prefix + re.sub(r'[^A-Z0-9]+', '_', name.upper()).strip('_')


def sym(name):
    return re.sub(r'[^A-Za-z0-9]', '', name.title())


def strip(s):
    return re.sub(r'\n?[ \t]*' + re.escape(BEGIN) + r'.*?' + re.escape(END) + r'\n', '\n', s, flags=re.S)


def read_pal(p):
    return [tuple(map(int, l.split())) for l in read(p).split('\n')[3:19] if l.strip()]


gfx_lines, table_lines, pic_enum = [], [], []
for f, name in PICS.items():
    src = hns('graphics/trainers/front_pics/%s.png' % f)
    im = Image.open(src)
    pal = hns('graphics/trainers/palettes/%s.pal' % f)
    if os.path.exists(pal):
        cols = read_pal(pal)
        im = im.convert('P') if im.mode != 'P' else im
        flat = [c for rgb in cols for c in rgb] + [0] * (768 - 3 * len(cols))
        im.putpalette(flat)
    dst = 'graphics/trainers/front_pics/%s.png' % f
    im.save(ours(dst))
    s = sym(name)
    gfx_lines.append('const u32 gTrainerFrontPic_%s[] = INCGFX_U32("%s", ".4bpp.smol");\n'
                     'const u16 gTrainerPalette_%s[] = INCGFX_U16("%s", ".gbapal");\n' % (s, dst, s, dst))
    c = const('TRAINER_PIC_', name)
    pic_enum.append('    %s,\n' % c)
    table_lines.append('    [%s] =\n    {\n        .frontPic = TRAINER_FRONT_PIC(gTrainerFrontPic_%s, gTrainerPalette_%s),\n    },\n' % (c, s, s))

p = ours('include/constants/trainers.h'); s = strip(read(p))
s = s.replace('    TRAINER_PIC_COUNT,', '    %s\n%s    %s\n    TRAINER_PIC_COUNT,' % (BEGIN, ''.join(pic_enum), END), 1)
cls_enum = ''.join('    %s,\n' % const('TRAINER_CLASS_', c) for c in CLASSES)
s = s.replace('    TRAINER_CLASS_COUNT,', '    %s\n%s    %s\n    TRAINER_CLASS_COUNT,' % (BEGIN, cls_enum, END), 1)
write(p, s)

p = ours('src/data/graphics/trainers.h'); s = strip(read(p))
i = s.index('const struct TrainerPicInfo gTrainerPicInfo')
s = s[:i] + '\n' + BEGIN + '\n' + ''.join(gfx_lines) + END + '\n' + s[i:]
# table entries: before the closing of the array that holds [TRAINER_PIC_...] entries
last = [m.end() for m in re.finditer(r'\n    \[TRAINER_PIC_\w+\] =\n    \{\n.*?\n    \},\n', s, re.S)][-1]
s = s[:last] + '    ' + BEGIN + '\n' + ''.join(table_lines) + '    ' + END + '\n' + s[last:]
write(p, s)

p = ours('src/battle_main.c'); s = strip(read(p))
anchor = re.search(r'\n    \[TRAINER_CLASS_PAINTER_FRLG\][^\n]*\n', s)
cls = ''.join('    [%s] = { _("%s"), %d },\n' % (const('TRAINER_CLASS_', c), n, m) for c, (n, m) in CLASSES.items())
s = s[:anchor.end()] + '    ' + BEGIN + '\n' + cls + '    ' + END + '\n' + s[anchor.end():]
write(p, s)
print('pics', len(PICS), 'classes', len(CLASSES))
