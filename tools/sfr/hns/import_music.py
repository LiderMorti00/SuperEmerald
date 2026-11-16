#!/usr/bin/env python3
"""Super Emerald: import the HeartGold/SoulSilver songs used in Johto from Pokemon Heart & Soul.

Copies the midis (and their midi.cfg lines), the HGSS voicegroups (voicegroup229 and the
ones after it, kept in the same order because songs index past the end of 229), their
key split tables and samples. Song ids go right after MUS_RG_TEACHY_TV_MENU
(HG_MUSIC_START), the bard phonemes (PH_*) move up accordingly.
Common places (Pokemon Center, Mart, Gym, Game Corner, Victory Road) keep our own music
for every region, so those HGSS songs are not imported.

Usage (repo root): python3 -I tools/sfr/hns/import_music.py [--hns /path]
"""
import os, re, shutil, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from common import hns, ours, read, write

SONGS = '''new_bark cherrygrove violet azalea goldenrod ecruteak cianwood route29 route30 route34 route38
route42 route26 route47 elm_lab dance_theater sprout_tower union_cave ruins_of_alph national_park
burned_tower bell_tower lighthouse team_rocket_hq ice_path dragons_den ss_aqua safari_zone_gate
safari_zone bug_catching_contest bug_contest_prep magnet_train mt_moon_square vs_wild vs_trainer
vs_gym_leader vs_rival vs_suicune vs_entei vs_raikou vs_ho_oh vs_lugia victory_trainer victory_wild
victory_gym_leader encounter_rival'''.split()
VGROUPS = ['voicegroup216', 'voicegroup219', 'voicegroup220'] + ['voicegroup%d' % i for i in range(229, 274)]
BEGIN, END = '@ Super Emerald: HnS begin', '@ Super Emerald: HnS end'


def strip_block(s):
    return re.sub(r'\n?' + re.escape(BEGIN) + r'.*?' + re.escape(END) + r'\n', '\n', s, flags=re.S)


# ---- midis
hcfg = read(hns('sound/songs/midi/midi.cfg'))
cfg_lines = []
for s in SONGS:
    f = 'mus_hg_%s.mid' % s
    shutil.copyfile(hns('sound/songs/midi', f), ours('sound/songs/midi', f))
    line = re.search(r'^%s:.*$' % re.escape(f), hcfg, re.M).group(0)
    cfg_lines.append(line)
p = ours('sound/songs/midi/midi.cfg'); s = read(p)
s = '\n'.join(l for l in s.split('\n') if not l.startswith('mus_hg_')).rstrip('\n') + '\n' + '\n'.join(cfg_lines) + '\n'
write(p, s)

# ---- constants: HG songs after MUS_RG_TEACHY_TV_MENU, PH_* shifted
p = ours('include/constants/songs.h'); s = read(p)
s = re.sub(r'\n// Super Emerald: HnS begin.*?// Super Emerald: HnS end\n', '\n', s, flags=re.S)
first_ph = int(re.search(r'#define PH_TRAP_BLEND\s+(\d+)', s).group(1))
base = int(re.search(r'#define MUS_RG_TEACHY_TV_MENU\s+(\d+)', s).group(1)) + 1
shift = base + len(SONGS) - first_ph
defs = '\n// Super Emerald: HnS begin (HeartGold/SoulSilver music from Pokemon Heart & Soul)\n#define HG_MUSIC_START %d\n' % base
defs += ''.join('#define MUS_HG_%-24s %d\n' % (x.upper(), base + i) for i, x in enumerate(SONGS))
defs += '// Super Emerald: HnS end\n'
s = s.replace('\n#define END_MUS', defs + '\n#define END_MUS', 1)
s = re.sub(r'#define END_MUS\s+\d+', '#define END_MUS                     %d' % (base + len(SONGS) - 1), s)
s = re.sub(r'(#define PH_\w+\s+)(\d+)', lambda m: m.group(1) + str(int(m.group(2)) + shift), s)
write(p, s)

# ---- song table
p = ours('sound/song_table.inc'); s = strip_block(read(p))
anchor = re.search(r'^\tsong [^\n]*mus_rg_teachy_tv_menu[^\n]*\n', s, re.M)
s = s[:anchor.end()] + BEGIN + '\n' + ''.join('\tsong mus_hg_%s, MUSIC_PLAYER_BGM, 0\n' % x for x in SONGS) + END + '\n' + s[anchor.end():]
write(p, s)

# ---- voicegroups
hvg = read(hns('sound/voice_groups.inc'))
used_samples, used_ks, inc = set(), set(), []
for v in VGROUPS:
    path = 'sound/voicegroups/%s.inc' % v
    shutil.copyfile(hns(path), ours(path))
    t = read(hns(path))
    used_samples |= set(re.findall(r'DirectSoundWaveData_\w+', t))
    used_ks |= set(re.findall(r'KeySplitTable\d+', t))
    inc.append('.include "%s"' % path)
p = ours('sound/voice_groups.inc'); s = strip_block(read(p))
s = s.rstrip('\n') + '\n' + BEGIN + '\n' + '\n'.join(inc) + '\n' + END + '\n'
write(p, s)

# ---- key split tables
hks = read(hns('sound/keysplit_tables.inc'))
blocks = []
for k in sorted(used_ks, key=lambda x: int(x[len('KeySplitTable'):])):
    m = re.search(r'^\.set %s,.*?(?=^\.set |\Z)' % k, hks, re.M | re.S)
    blocks.append(m.group(0).rstrip() + '\n')
p = ours('sound/keysplit_tables.inc'); s = strip_block(read(p))
s = s.rstrip('\n') + '\n\n' + BEGIN + '\n' + '\n'.join(blocks) + END + '\n'
write(p, s)

# ---- samples
hds = read(hns('sound/direct_sound_data.inc'))
ods = strip_block(read(ours('sound/direct_sound_data.inc')))
entries = []
for smp in sorted(used_samples):
    if re.search(r'^%s::' % smp, ods, re.M):
        continue
    m = re.search(r'^(%s::\s*\n\s*\.incbin "([^"]+)"\n)' % smp, hds, re.M)
    entries.append(m.group(1))
    wav = re.sub(r'\.bin$', '.wav', m.group(2))
    shutil.copyfile(hns(wav), ours(wav))
s = ods.rstrip('\n') + '\n\n' + BEGIN + '\n\t.align 2\n' + '\t.align 2\n'.join(entries) + END + '\n'
write(ours('sound/direct_sound_data.inc'), s)
print('songs', len(SONGS), 'voicegroups', len(VGROUPS), 'keysplits', len(used_ks), 'new samples', len(entries))
