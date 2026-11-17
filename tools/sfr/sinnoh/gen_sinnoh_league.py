#!/usr/bin/env python3
"""Super Emerald: hand-made Sinnoh trainers -> src/data/trainers_se_sinnoh.party and
include/constants/opponents_sinnoh.h.

* Gym Leaders: the Platinum rematch teams from LiderMorti00's Sinnoh repo (61-66).
* Elite Four: their Platinum teams + 12 levels (61-71); Cynthia + 8 (66-70).
* Lucas (rival): three battles, three variants (the starter strong against the player's).
Safe to run again (after tools/sfr/sinnoh/import_maps.py)."""
import os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from common import sin, ours, read, write

party = read(sin('src/data/trainers.party'))
BLOCKS = {re.match(r'=== (\w+) ===', b).group(1): b.rstrip() for b in re.split(r'\n(?==== )', party) if b.startswith('===')}

LEADERS = [('ROARK', 'TRAINER_CHARLOTTE', 'ROARK'), ('GARDENIA', 'TRAINER_DEANDRE', 'GARDENIA'),
           ('MAYLENE', 'TRAINER_GRUNT_MAGMA_HIDEOUT_2', 'MAYLENE'), ('WAKE', 'TRAINER_GRUNT_MAGMA_HIDEOUT_3', 'WAKE'),
           ('FANTINA', 'TRAINER_GRUNT_MAGMA_HIDEOUT_1', 'FANTINA'), ('BYRON', 'TRAINER_GRUNT_MAGMA_HIDEOUT_4', 'BYRON'),
           ('CANDICE', 'TRAINER_GRUNT_MAGMA_HIDEOUT_5', 'CANDICE'), ('VOLKNER', 'TRAINER_GRUNT_MAGMA_HIDEOUT_6', 'VOLKNER')]
ELITE = [('AARON', 'TRAINER_SIDNEY'), ('BERTHA', 'TRAINER_PHOEBE'), ('FLINT', 'TRAINER_GLACIA'), ('LUCIAN', 'TRAINER_DRAKE')]


def mons(block, add=0, ivs=31):
    out = []
    for mon in block.split('\n\n')[1:]:
        lines = [l for l in mon.split('\n') if l.strip()]
        if not lines:
            continue
        lines = [('Level: %d' % (int(l.split(': ')[1]) + add)) if l.startswith('Level: ') else l for l in lines
                 if not l.startswith('IVs:')]
        lines.insert(2 if len(lines) > 1 else 1, 'IVs: %d HP / %d Atk / %d Def / %d SpA / %d SpD / %d Spe' % ((ivs,) * 6))
        out.append('\n'.join(lines))
    return '\n\n'.join(out)


def head(const, name, cls, pic, gender, music, items):
    return ('=== %s ===\nName: %s\nClass: %s\nPic: %s\nGender: %s\nMusic: %s\nItems: %s\nDouble Battle: No\n'
            'AI: Check Bad Move / Try To Faint / Check Viability' % (const, name, cls, pic, gender, music, ' / '.join(items)))


FEMALE = {'GARDENIA', 'MAYLENE', 'FANTINA', 'CANDICE', 'BERTHA', 'CYNTHIA'}
out, ids = [], []
for name, src, pic in LEADERS:
    c = 'TRAINER_SE_LEADER_%s' % name
    ids.append(c)
    out.append(head(c, name, 'Leader', 'TRAINER_PIC_SINNOH_LEADER_%s' % pic,
                    'Female' if name in FEMALE else 'Male', 'Female' if name in FEMALE else 'Male',
                    ['Full Restore', 'Full Restore']) + '\n\n' + mons(BLOCKS[src]))
for name, src in ELITE:
    c = 'TRAINER_SE_ELITE_FOUR_%s' % name
    ids.append(c)
    out.append(head(c, name, 'Elite Four', 'TRAINER_PIC_SINNOH_ELITE_FOUR_%s' % name,
                    'Female' if name in FEMALE else 'Male', 'Female' if name in FEMALE else 'Male',
                    ['Full Restore', 'Full Restore']) + '\n\n' + mons(BLOCKS[src], 12))
ids.append('TRAINER_SE_CHAMPION_CYNTHIA')
out.append(head('TRAINER_SE_CHAMPION_CYNTHIA', 'CYNTHIA', 'Champion', 'TRAINER_PIC_SINNOH_CHAMPION_CYNTHIA', 'Female', 'Female',
                ['Full Restore', 'Full Restore', 'Full Restore', 'Full Restore']) + '\n\n' + mons(BLOCKS['TRAINER_WALLACE'], 8))

# Lucas: Staraptor / Luxray / Roserade / Gastrodon / Lucario + the starter strong against the player's
LUCAS = {1: [('Staraptor', 49), ('Luxray', 50)],
         2: [('Staraptor', 56), ('Luxray', 57), ('Roserade', 57), ('Gastrodon', 58)],
         3: [('Staraptor', 64), ('Luxray', 65), ('Roserade', 65), ('Gastrodon', 66), ('Lucario', 66)]}
START = {1: 52, 2: 60, 3: 68}
for n in (1, 2, 3):
    for st in ('Infernape', 'Empoleon', 'Torterra'):
        c = 'TRAINER_SE_LUCAS_%d_%s' % (n, st.upper())
        ids.append(c)
        team = [(('Floatzel' if (sp == 'Roserade' and st == 'Torterra') else sp), lv) for sp, lv in LUCAS[n]] + [(st, START[n])]
        body = '\n\n'.join('%s%s\nLevel: %d\nIVs: 25 HP / 25 Atk / 25 Def / 25 SpA / 25 SpD / 25 Spe' % (sp, ' @ Sitrus Berry' if sp == st else '', lv)
                           for sp, lv in team)
        out.append(head(c, 'LUCAS', 'Rival', 'TRAINER_PIC_SINNOH_LUCAS', 'Male', 'Male', ['Full Restore'] * n) + '\n\n' + body)

# Rematches (after the first Sinnoh League win): the second Platinum rematch teams of the
# Sinnoh repo, six Pokemon each. Gym Leaders 61-66 -> 74-79, Elite Four 65-75 -> 73-83,
# Cynthia 74-78 -> 82-86. Added after the other ids so those stay the same.
LEADERS2 = [('ROARK', 'TRAINER_ISAIAH_4'), ('GARDENIA', 'TRAINER_ISAIAH_5'), ('MAYLENE', 'TRAINER_KATELYN_2'),
            ('WAKE', 'TRAINER_KATELYN_3'), ('FANTINA', 'TRAINER_KATELYN_1'), ('BYRON', 'TRAINER_KATELYN_4'),
            ('CANDICE', 'TRAINER_KATELYN_5'), ('VOLKNER', 'TRAINER_NICOLAS_1')]
ELITE2 = [('AARON', 'TRAINER_NICOLAS_2'), ('BERTHA', 'TRAINER_NICOLAS_3'), ('FLINT', 'TRAINER_NICOLAS_4'),
          ('LUCIAN', 'TRAINER_NICOLAS_5')]
for name, src in LEADERS2:
    c = 'TRAINER_SE_LEADER_%s_REMATCH' % name
    ids.append(c)
    out.append(head(c, name, 'Leader', 'TRAINER_PIC_SINNOH_LEADER_%s' % name,
                    'Female' if name in FEMALE else 'Male', 'Female' if name in FEMALE else 'Male',
                    ['Full Restore', 'Full Restore', 'Full Restore']) + '\n\n' + mons(BLOCKS[src], 13))
for name, src in ELITE2:
    c = 'TRAINER_SE_ELITE_FOUR_%s_REMATCH' % name
    ids.append(c)
    out.append(head(c, name, 'Elite Four', 'TRAINER_PIC_SINNOH_ELITE_FOUR_%s' % name,
                    'Female' if name in FEMALE else 'Male', 'Female' if name in FEMALE else 'Male',
                    ['Full Restore', 'Full Restore', 'Full Restore']) + '\n\n' + mons(BLOCKS[src], 8))
ids.append('TRAINER_SE_CHAMPION_CYNTHIA_REMATCH')
out.append(head('TRAINER_SE_CHAMPION_CYNTHIA_REMATCH', 'CYNTHIA', 'Champion', 'TRAINER_PIC_SINNOH_CHAMPION_CYNTHIA', 'Female', 'Female',
                ['Full Restore'] * 4) + '\n\n' + mons(BLOCKS['TRAINER_ROBERT_1'], 8))

# Lucas, daily rematch at the Survival Area after the Sinnoh League (hand-made teams)
import re as _re
for blk in _re.split(r'\n(?==== )', open(ours('tools/sfr/rival_rematch_lucas.party')).read().strip()):
    ids.append(_re.match(r'=== (\w+) ===', blk).group(1))
    out.append(blk.rstrip())

write(ours('src/data/trainers_se_sinnoh.party'), '\n\n'.join(out) + '\n')
n_import = int(re.search(r'TRAINERS_COUNT_SINNOH_IMPORT (\d+)', read(ours('include/constants/opponents_sinnoh_list.h'))).group(1))
start = 2144 + n_import
h = ['#ifndef GUARD_CONSTANTS_OPPONENTS_SINNOH_H', '#define GUARD_CONSTANTS_OPPONENTS_SINNOH_H', '',
     '// Super Emerald: Sinnoh trainers (LiderMorti00\'s Sinnoh repo) go after the Johto ones.',
     '// Plain numbers on purpose (scripts pass them to macros). Generated by tools/sfr/sinnoh/gen_sinnoh_league.py.',
     '#define SINNOH_TRAINER_ID_START   2144 // == JOHTO_TRAINER_ID_START + MAX_TRAINERS_COUNT_JOHTO',
     '#define MAX_TRAINERS_COUNT_SINNOH 1024', '', '#include "constants/opponents_sinnoh_list.h"', '']
h += ['#define %-36s %d' % (c, start + i) for i, c in enumerate(ids)]
h += ['#define SE_SINNOH_TRAINERS_COUNT %d' % len(ids),
      '#define TRAINERS_COUNT_SINNOH (TRAINERS_COUNT_SINNOH_IMPORT + SE_SINNOH_TRAINERS_COUNT)', '',
      '#if SINNOH_TRAINER_ID_START != JOHTO_TRAINER_ID_START + MAX_TRAINERS_COUNT_JOHTO',
      '#error "Super Emerald: SINNOH_TRAINER_ID_START must follow the Johto trainers"', '#endif',
      '#if %d != SINNOH_TRAINER_ID_START + TRAINERS_COUNT_SINNOH_IMPORT' % start,
      '#error "Super Emerald: run tools/sfr/sinnoh/gen_sinnoh_league.py again"', '#endif', '',
      '#endif // GUARD_CONSTANTS_OPPONENTS_SINNOH_H', '']
write(ours('include/constants/opponents_sinnoh.h'), '\n'.join(h))
print('se sinnoh trainers', len(ids), 'from', start)
