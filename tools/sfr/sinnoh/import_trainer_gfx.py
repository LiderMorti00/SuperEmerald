#!/usr/bin/env python3
"""Super Emerald: import the Sinnoh trainer front pics (TRAINER_PIC_SINNOH_*) and the trainer
classes the Sinnoh trainers use that we don't have, from LiderMorti00's Sinnoh repo.
Adds them between "Super Emerald: Sinnoh" markers. Safe to run again."""
import os, re, shutil, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from common import sin, ours, read, write

BEGIN, END = '// Super Emerald: Sinnoh begin', '// Super Emerald: Sinnoh end'


def strip(s):
    return re.sub(r'\n?[ \t]*' + re.escape(BEGIN) + r'.*?' + re.escape(END) + r'\n', '\n', s, flags=re.S)


S_TR = read(sin('include/constants/trainers.h'))
S_GFX = read(sin('src/data/graphics/trainers.h'))
pics = [p for p in re.findall(r'^\s+(TRAINER_PIC_SINNOH_\w+),', S_TR, re.M)
        if re.search(r'\[%s\] =\s*\{\s*\.frontPic' % p, S_GFX)]  # partners only have back pics
gfx_lines, table = [], []
for p in pics:
    m = re.search(r'\[%s\] =\s*\{\s*\.frontPic = TRAINER_FRONT_PIC\((\w+), (\w+)\)' % p, S_GFX)
    for sym in m.groups():
        line = re.search(r'const u(?:16|32) %s\[\] = [^\n]+' % sym, S_GFX).group(0)
        f = re.search(r'"([^"]+)"', line).group(1)
        os.makedirs(os.path.dirname(ours(f)), exist_ok=True)
        shutil.copyfile(sin(f), ours(f))
        gfx_lines.append(line)
    table.append('    [%s] =\n    {\n        .frontPic = TRAINER_FRONT_PIC(%s, %s),\n    },\n' % (p, m.group(1), m.group(2)))

# classes used by the imported Sinnoh trainers that we lack
O_TR = strip(read(ours('include/constants/trainers.h')))
used = set()
for c in re.findall(r'^Class: (.*)$', read(ours('src/data/trainers_sinnoh.party')), re.M):
    used.add(c if c.startswith('TRAINER_CLASS_') else 'TRAINER_CLASS_' + re.sub(r'[^A-Z0-9]+', '_', c.upper()).strip('_'))
missing = sorted(c for c in used if not re.search(r'\b%s\b' % c, O_TR))
S_BM = read(sin('src/battle_main.c'))
cls = []
for c in missing:
    m = re.search(r'\[%s\] = (\{[^}]*\}),' % c, S_BM)
    cls.append('    [%s] = %s,\n' % (c, m.group(1) if m else '{ _("TRAINER"), 10 }'))

p = ours('include/constants/trainers.h'); s = strip(read(p))
s = s.replace('    TRAINER_PIC_COUNT,', '    %s\n%s    %s\n    TRAINER_PIC_COUNT,' % (BEGIN, ''.join('    %s,\n' % x for x in pics), END), 1)
s = s.replace('    TRAINER_CLASS_COUNT,', '    %s\n%s    %s\n    TRAINER_CLASS_COUNT,' % (BEGIN, ''.join('    %s,\n' % c for c in missing), END), 1)
write(p, s)

p = ours('src/data/graphics/trainers.h'); s = strip(read(p))
i = s.index('const struct TrainerPicInfo gTrainerPicInfo')
s = s[:i] + '\n' + BEGIN + '\n' + '\n'.join(gfx_lines) + '\n' + END + '\n' + s[i:]
last = [m.end() for m in re.finditer(r'\n    \[TRAINER_PIC_\w+\] =\n    \{\n.*?\n    \},\n', s, re.S)][-1]
s = s[:last] + '    ' + BEGIN + '\n' + ''.join(table) + '    ' + END + '\n' + s[last:]
write(p, s)

p = ours('src/battle_main.c'); s = strip(read(p))
anchor = re.search(r'\n    \[TRAINER_CLASS_PAINTER_FRLG\][^\n]*\n', s)
s = s[:anchor.end()] + '    ' + BEGIN + '\n' + ''.join(cls) + '    ' + END + '\n' + s[anchor.end():]
write(p, s)
print('pics', len(pics), 'classes', len(missing), missing)
