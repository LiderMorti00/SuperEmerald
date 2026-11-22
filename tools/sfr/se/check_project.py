#!/usr/bin/env python3
"""Super Emerald: integration checks that the build doesn't catch.
Run from the repo root:  python3 tools/sfr/se/check_project.py
 - layouts without border size (Porymap with 'Custom Border Size' off)
 - heal locations without respawn map/NPC (Porymap with 'Respawn Map/NPC' off)
 - warps to missing maps or to warp ids the destination doesn't have
 - connections to missing maps / not mirrored
 - objects with unknown graphics
 - duplicated flag / var numbers among the Super Emerald constants
 - Hoenn-only things (secret bases...) outside Hoenn
 - silent Center/Mart music and lamppost halos on their entrances
 - direct trainer battles without a corresponding party
"""
import json, re, glob, os, sys
from collections import defaultdict

bad = []
def err(kind, msg): bad.append((kind, msg))

maps = {}
for f in glob.glob('data/maps/*/map.json'):
    j = json.load(open(f)); maps[j['id']] = j
groups = json.load(open('data/maps/map_groups.json'))
in_groups = {m for g in groups['group_order'] for m in groups[g]}
names = {j['name']: j for j in maps.values()}
for n in in_groups:
    if n not in names: err('map', 'map_groups.json lists %s but it has no map.json' % n)

# layouts
lay = json.load(open('data/layouts/layouts.json'))['layouts']
for l in lay:
    if 'id' not in l: continue
    if l.get('layout_version') == 'frlg' and ('border_width' not in l or 'border_height' not in l):
        err('porymap', '%s has no border size (Porymap: Maps > Enable Custom Border Size)' % l['id'])
    tiles = l.get('primary_tileset', '') + l.get('secondary_tileset', '')
    if ('_Hns' in tiles or 'Frlg' in tiles) and l.get('layout_version') != 'frlg':
        err('porymap', '%s uses HnS/FRLG tilesets but has no "layout_version": "frlg" (it will look garbled)' % l['id'])
    for k in ('blockdata_filepath', 'border_filepath'):
        if not os.path.exists(l[k]): err('layout', '%s: missing %s' % (l['id'], l[k]))

# heal locations
for h in json.load(open('src/data/heal_locations.json'))['heal_locations']:
    if 'respawn_map' not in h or 'respawn_npc' not in h:
        if not h['id'].endswith(('_2F',)):
            err('porymap', '%s has no respawn map/NPC (Porymap: Events > Respawn Map/NPC)' % h['id'])
    elif h['respawn_map'] not in maps:
        err('heal', '%s respawns in missing map %s' % (h['id'], h['respawn_map']))

# warps
DYN = {'WARP_ID_DYNAMIC', '0x7F', '127', 'WARP_ID_SECRET_BASE'}
for mid, j in maps.items():
    for i, w in enumerate(j.get('warp_events') or []):
        d = w['dest_map']
        if d in ('MAP_DYNAMIC', 'MAP_UNDEFINED'): continue
        if d not in maps:
            err('warp', '%s warp %d (%d,%d) -> missing map %s' % (j['name'], i, w['x'], w['y'], d)); continue
        wid = str(w['dest_warp_id'])
        if wid in DYN: continue
        try: n = int(wid, 0)
        except ValueError: continue
        if n >= len(maps[d].get('warp_events') or []):
            err('warp', '%s warp %d (%d,%d) -> %s warp %d, which doesn\'t exist' % (j['name'], i, w['x'], w['y'], d, n))

# one-way warps: A -> B[n] but B[n] leads somewhere else (you appear at the wrong door).
# Mazes and puzzle maps do this on purpose; they're listed here.
ONEWAY_OK = ('LostCave', 'TrickHouse', 'SeafoamIslands', 'DottedHole', 'CaveOfOrigin', 'SeafloorCavern', 'RuinsOfAlph',
             'RocketHideout', 'TurnbackCave', 'LakeVerity', 'LakeValor', 'NationalPark', 'AquaHideout', 'SSAqua',
             'MtSilver', 'BattleDome', 'WorldTournament', 'Lighthouse', 'NewBarkTown', 'EcruteakCity')
for mid, j in maps.items():
    if any(k in j['name'] for k in ONEWAY_OK): continue
    for i, w in enumerate(j.get('warp_events') or []):
        d = w['dest_map']
        if d not in maps: continue
        try: n = int(str(w['dest_warp_id']), 0)
        except ValueError: continue
        ws = maps[d].get('warp_events') or []
        if n >= len(ws) or n >= 127: continue
        if ws[n]['dest_map'] not in (mid, 'MAP_DYNAMIC'):
            err('warp', '%s warp %d -> %s warp %d, but that one leads to %s (wrong door?)' % (j['name'], i, d, n, ws[n]['dest_map']))

# connections
OPP = {'up': 'down', 'down': 'up', 'left': 'right', 'right': 'left', 'dive': 'emerge', 'emerge': 'dive'}
for mid, j in maps.items():
    for c in j.get('connections') or []:
        if c['map'] not in maps:
            err('connection', '%s connects to missing %s' % (j['name'], c['map'])); continue
        back = [x for x in (maps[c['map']].get('connections') or []) if x['map'] == mid and x['direction'] == OPP.get(c['direction'])]
        if not back:
            err('connection', '%s -> %s (%s) is not mirrored' % (j['name'], c['map'], c['direction']))

# object graphics
gfx = set(re.findall(r'\b(OBJ_EVENT_GFX_\w+)', open('include/constants/event_objects.h').read()))
for mid, j in maps.items():
    for o in j.get('object_events') or []:
        g = o.get('graphics_id', '')
        if g.startswith('OBJ_EVENT_GFX_') and g not in gfx and '+' not in g and '(' not in g:
            err('object', '%s: unknown graphics %s' % (j['name'], g))

# duplicated SE flags / vars
for files, pre in ((glob.glob('include/constants/flags_se*.h'), 'FLAG_'), (['include/constants/vars.h'], 'VAR_SE_')):
    seen = defaultdict(set)
    for f in files:
        for name, val in re.findall(r'#define\s+(%s\w+)\s+(0x[0-9A-Fa-f]+)\b' % pre, open(f).read()):
            seen[int(val, 16)].add(name)
    for v, ns in seen.items():
        ns = [n for n in ns if not n.endswith(('_START', '_END'))]
        if len(ns) > 1: err('constants', '%s share 0x%X' % (', '.join(sorted(ns)), v))

# Hoenn-only things outside Hoenn
HOENN_ONLY = r'secretbase|SecretBase|SECRET_BASE'
for mid, j in maps.items():
    reg = j.get('region', '')
    if reg in ('', 'REGION_HOENN') and not mid.endswith(('_SINNOH', '_HNS', '_FRLG')): continue
    for ev in (j.get('object_events') or []) + (j.get('bg_events') or []):
        t = json.dumps(ev)
        if re.search(HOENN_ONLY, t): err('hoenn', '%s: %s' % (j['name'], ev.get('script', ev.get('type'))))

# Music for Pokémon Centers and Marts, including the legacy IDs.
indoor_tracks = {'MUS_POKE_CENTER', 'MUS_RG_POKE_CENTER', 'MUS_DPP_PC', 'MUS_POKE_MART', 'MUS_DPP_MART'}
song_ids = {name: int(number) for name, number in re.findall(
    r'^#define (MUS_\w+)\s+(\d+)\b', open('include/constants/songs.h').read(), re.M
)}
song_table = re.findall(r'^\s*song (\w+),', open('sound/song_table.inc').read(), re.M)
for track in sorted(indoor_tracks):
    index = song_ids[track]
    if index >= len(song_table) or song_table[index] == 'mus_dummy':
        err('music', '%s has no playable song in the table' % track)

# A ball light belongs to a lamppost. Glass doors are illuminated by their palette.
for j in maps.values():
    doors = {
        (w['x'], w['y']) for w in j.get('warp_events', []) or []
        if '_POKEMON_CENTER_' in w['dest_map'] or w['dest_map'].endswith('_MART')
    }
    for obj in j.get('object_events', []) or []:
        if (obj.get('graphics_id') == 'OBJ_EVENT_GFX_LIGHT_SPRITE'
                and str(obj.get('trainer_sight_or_berry_tree_id')) in ('LIGHT_TYPE_BALL', '0')
                and (obj['x'], obj['y']) in doors):
            err('light', '%s has a lamp halo over the shop or center door at (%d,%d)'
                % (j['name'], obj['x'], obj['y']))

# Check direct trainer battles referenced by map and shared event scripts.
trainer_parties = set()
for f in glob.glob('src/data/trainers*.party'):
    with open(f) as party_file:
        trainer_parties.update(re.findall(r'^=== (TRAINER_\w+) ===$', party_file.read(), re.M))

for f in glob.glob('data/maps/*/scripts.inc') + glob.glob('data/scripts/*.inc'):
    with open(f) as scripts:
        trainers = set(re.findall(r'^\s*trainerbattle_\w+\s+(TRAINER_\w+)\b', scripts.read(), re.M))
    for trainer in sorted(trainers - trainer_parties):
        err('trainer', '%s references %s without a party' % (f, trainer))

for k, m in sorted(bad): print('[%s] %s' % (k, m))
print('%d problems' % len(bad))
sys.exit(1 if bad else 0)
