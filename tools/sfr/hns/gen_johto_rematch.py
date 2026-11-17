#!/usr/bin/env python3
"""Super Emerald: Johto Gym Leader rematches (after beating Red), with the HeartGold /
SoulSilver rematch teams, moves and held items. HGSS 48-62 -> 70-75, like the Kanto ones.

Usage (repo root): python3 tools/sfr/hns/gen_johto_rematch.py <pokeheartgold>/files/poketool/trainer/trainers.json
Writes TRAINER_SE_LEADER_<NAME>_REMATCH into src/data/trainers_se_johto.party."""
import json, os, re, sys
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
import gen_se_kanto_league as k

JOHTO = [(712, 'FALKNER'), (713, 'BUGSY'), (714, 'WHITNEY'), (715, 'MORTY'),
         (718, 'CHUCK'), (717, 'JASMINE'), (716, 'PRYCE'), (719, 'CLAIR')]


def main(src):
    hg = json.load(open(src))['trainers']
    valid_moves = set(re.findall(r'^\s*(MOVE_\w+)\s*=', open('include/constants/moves.h').read(), re.M))
    valid_items = set(re.findall(r'^\s*(ITEM_\w+)\s*=', open('include/constants/items.h').read(), re.M))
    se = open(k.SE_JOHTO_PARTY).read()
    for idx, name in JOHTO:
        header = k.header_of(se, 'TRAINER_SE_LEADER_' + name,
                             {'Items': 'Full Restore / Full Restore / Full Restore'})
        body = '\n\n'.join(k.mon_lines(p, k.leader2, valid_moves, valid_items) for p in hg[idx]['party'])
        se = k.set_block(se, 'TRAINER_SE_LEADER_%s_REMATCH' % name, header, body)
    open(k.SE_JOHTO_PARTY, 'w').write(se.rstrip('\n') + '\n')
    print('Johto Gym Leader rematches written')


if __name__ == '__main__':
    main(sys.argv[1])
