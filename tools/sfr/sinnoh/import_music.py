#!/usr/bin/env python3
"""Super Emerald: import the Diamond/Pearl/Platinum songs used in Sinnoh from LiderMorti00's
Sinnoh repo (all of them use voicegroup sinnoh_gm, built from our own samples).
Song ids go right after the HGSS ones (DPP_MUSIC_START); the bard phonemes (PH_*) move up.
Common places (Pokemon Center, Mart, Gym...) keep our own music, as in Johto; the Team Galactic,
Battle Hall, title and credits songs are left out.

Usage (repo root): python3 -I tools/sfr/sinnoh/import_music.py [--sinnoh /path]"""
import os, re, shutil, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from common import sin, ours, read, write

SONGS = '''twinleaf lake route201 jubilife lab route203 oreburgh floaroma route205 eterna_forest eterna
old_chateau mt_coronet hearthome veilstone galactic_hq canalave snowpoint sunyshore route216 route210
route213 victory_road league_outside league_inside cycling vs_wild victory_wild vs_dialga_palkia
vs_cynthia sandgem pastoria route206 route209 route225 route228'''.split()
BEGIN, END = '@ Super Emerald: Sinnoh begin', '@ Super Emerald: Sinnoh end'


def strip_block(s):
    return re.sub(r'\n?' + re.escape(BEGIN) + r'.*?' + re.escape(END) + r'\n', '\n', s, flags=re.S)


scfg = read(sin('sound/songs/midi/midi.cfg'))
cfg = []
for s in SONGS:
    f = 'mus_dpp_%s.mid' % s
    shutil.copyfile(sin('sound/songs/midi', f), ours('sound/songs/midi', f))
    cfg.append(re.search(r'^%s:.*$' % re.escape(f), scfg, re.M).group(0))
p = ours('sound/songs/midi/midi.cfg'); t = read(p)
t = '\n'.join(l for l in t.split('\n') if not l.startswith('mus_dpp_')).rstrip('\n') + '\n' + '\n'.join(cfg) + '\n'
write(p, t)

p = ours('include/constants/songs.h'); t = read(p)
t = re.sub(r'\n// Super Emerald: Sinnoh begin.*?// Super Emerald: Sinnoh end\n', '\n', t, flags=re.S)
first_ph = int(re.search(r'#define PH_TRAP_BLEND\s+(\d+)', t).group(1))
base = int(re.search(r'#define MUS_HG_ENCOUNTER_RIVAL\s+(\d+)', t).group(1)) + 1
shift = base + len(SONGS) - first_ph
defs = '\n// Super Emerald: Sinnoh begin (Diamond/Pearl/Platinum music from LiderMorti00\'s Sinnoh repo)\n#define DPP_MUSIC_START %d\n' % base
defs += ''.join('#define MUS_DPP_%-24s %d\n' % (x.upper(), base + i) for i, x in enumerate(SONGS))
defs += '// Super Emerald: Sinnoh end\n'
t = t.replace('\n#define END_MUS', defs + '\n#define END_MUS', 1)
t = re.sub(r'#define END_MUS\s+\d+', '#define END_MUS                     %d' % (base + len(SONGS) - 1), t)
t = re.sub(r'(#define PH_\w+\s+)(\d+)', lambda m: m.group(1) + str(int(m.group(2)) + shift), t)
write(p, t)

p = ours('sound/song_table.inc'); t = strip_block(read(p))
anchor = re.search(r'^\tsong mus_hg_encounter_rival[^\n]*\n', t, re.M)
t = t[:anchor.end()] + BEGIN + '\n' + ''.join('\tsong mus_dpp_%s, MUSIC_PLAYER_BGM, 0\n' % x for x in SONGS) + END + '\n' + t[anchor.end():]
write(p, t)

shutil.copyfile(sin('sound/voicegroups/sinnoh_gm.inc'), ours('sound/voicegroups/sinnoh_gm.inc'))
p = ours('sound/voice_groups.inc'); t = strip_block(read(p))
t = t.rstrip('\n') + '\n' + BEGIN + '\n.include "sound/voicegroups/sinnoh_gm.inc"\n' + END + '\n'
write(p, t)
print('songs', len(SONGS), 'from', base)
