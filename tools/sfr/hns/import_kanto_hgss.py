#!/usr/bin/env python3
"""Super Emerald: Saffron City, Route 22, Route 23, Victory Road, Indigo Plateau and the Saffron
Magnet Train station with the HGSS look, from Pokemon Heart & Soul, in place of the FireRed maps.

The FireRed map ids (MAP_SAFFRON_CITY, MAP_ROUTE22, ...) are kept, so heal locations, Fly, wild
encounters and the warps of the FireRed interiors keep working; Victory Road gets the three HnS floors
in the places of the three FireRed floors.  NPCs keep their HnS texts.  Run after import_tilesets.py.
Safe to run again."""
import collections, glob, json, os, re, shutil, sys
if '--force' not in sys.argv:
    sys.exit('Kanto HGSS maps already imported and edited by hand in Porymap; running this again would undo those edits '
             '(use --force only on a fresh checkout).')
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from common import hns, ours, read, write

# HnS map -> (our map folder, our map id).  Victory Road replaces the FireRed floors in place
# (same group and number), entering from the reception gate on B2F as in HGSS.
SPEC = collections.OrderedDict([
    ('SaffronCity_hns',              ('SaffronCity_Frlg', 'MAP_SAFFRON_CITY')),
    ('SaffronCity_TrainStation_hns', ('SaffronCity_MagnetTrainStation_Frlg', 'MAP_SAFFRON_CITY_MAGNET_TRAIN_STATION')),
    ('Route22_hns',                  ('Route22_Frlg', 'MAP_ROUTE22')),
    ('Route23_hns',                  ('Route23_Frlg', 'MAP_ROUTE23')),
    ('IndigoPlateau_hns',            ('IndigoPlateau_Exterior_Frlg', 'MAP_INDIGO_PLATEAU_EXTERIOR')),
    ('VictoryRoadKanto_1F_hns',      ('VictoryRoadKanto_1F_hns', 'MAP_VICTORY_ROAD_KANTO_1F_HNS')),
    ('VictoryRoadKanto_B1F_hns',     ('VictoryRoadKanto_B1F_hns', 'MAP_VICTORY_ROAD_KANTO_B1F_HNS')),
    ('VictoryRoadKanto_B2F_hns',     ('VictoryRoadKanto_B2F_hns', 'MAP_VICTORY_ROAD_KANTO_B2F_HNS')),
])
REPLACED_VR = {'VictoryRoad_1F_Frlg': 'VictoryRoadKanto_1F_hns', 'VictoryRoad_2F_Frlg': 'VictoryRoadKanto_B1F_hns',
               'VictoryRoad_3F_Frlg': 'VictoryRoadKanto_B2F_hns'}
VR_IDS = {'MAP_VICTORY_ROAD_1F_FRLG': 'MAP_VICTORY_ROAD_KANTO_1F_HNS', 'MAP_VICTORY_ROAD_2F': 'MAP_VICTORY_ROAD_KANTO_B1F_HNS',
          'MAP_VICTORY_ROAD_3F': 'MAP_VICTORY_ROAD_KANTO_B2F_HNS'}
# HnS warp destinations outside SPEC -> our maps
DEST = {
    'MAP_GATE_SAFFRON_CITY_ROUTE5_HNS': 'MAP_ROUTE5_SOUTH_ENTRANCE',
    'MAP_GATE_SAFFRON_CITY_ROUTE6_HNS': 'MAP_ROUTE6_NORTH_ENTRANCE',
    'MAP_GATE_SAFFRON_CITY_ROUTE7_HNS': 'MAP_ROUTE7_EAST_ENTRANCE',
    'MAP_GATE_SAFFRON_CITY_ROUTE8_HNS': 'MAP_ROUTE8_WEST_ENTRANCE',
    'MAP_SAFFRON_CITY_FIGHTING_DOJO_HNS': 'MAP_SAFFRON_CITY_DOJO',
    'MAP_SAFFRON_CITY_GYM_HNS': 'MAP_SAFFRON_CITY_GYM',
    'MAP_SAFFRON_CITY_MART_HNS': 'MAP_SAFFRON_CITY_MART',
    'MAP_SAFFRON_CITY_COPY_CATS_HOUSE_1F_HNS': 'MAP_SAFFRON_CITY_COPYCATS_HOUSE_1F',
    'MAP_SAFFRON_CITY_SILPH_CO_HNS': 'MAP_SILPH_CO_1F',
    'MAP_SAFFRON_CITY_POKEMON_CENTER_HNS': 'MAP_SAFFRON_CITY_POKEMON_CENTER_1F',
    'MAP_SAFFRON_CITY_HOUSE1_HNS': 'MAP_SAFFRON_CITY_MR_PSYCHICS_HOUSE',   # same spot as Mr. Psychic's house
    'MAP_INDIGO_PLATEAU_POKEMON_CENTER_HNS': 'MAP_INDIGO_PLATEAU_POKEMON_CENTER_1F',
    'MAP_RECEPTION_GATE_HNS': 'MAP_RECEPTION_GATE_HNS',
}
CONNECTIONS = {   # our connections for the replaced maps (FireRed neighbours)
    'SaffronCity_Frlg': [],            # none: the HnS city has its own gate buildings, the routes keep theirs
    'Route22_Frlg': [{'map': 'MAP_VIRIDIAN_CITY', 'offset': None, 'direction': 'right'}],
    'Route23_Frlg': [{'map': 'MAP_INDIGO_PLATEAU_EXTERIOR', 'offset': 0, 'direction': 'up'}],
    'IndigoPlateau_Exterior_Frlg': [{'map': 'MAP_ROUTE23', 'offset': 0, 'direction': 'down'}],
}

H_LAY = {l['id']: l for l in json.load(open(hns('data/layouts/layouts.json')))['layouts'] if 'id' in l}
OUR_CONST = set()
for f in glob.glob(ours('include/constants/*.h')):
    OUR_CONST |= set(re.findall(r'\b([A-Z][A-Z0-9_]{2,})\b', read(f)))

# HnS script/text index
H_LABELS = {}
for f in glob.glob(hns('data/**/*.inc'), recursive=True):
    cur = None
    for line in read(f).split('\n'):
        m = re.match(r'^(\w+):{1,2}\s*$', line)
        if m:
            cur = m.group(1); H_LABELS[cur] = []
        elif cur:
            H_LABELS[cur].append(line)

def text_block(label):
    lines = [l for l in H_LABELS.get(label, []) if l.strip().startswith('.string')]
    out = []
    for l in lines:
        out.append('\t' + l.strip())
        if l.rstrip().endswith('$"'):
            break
    return out

def find_text(label, seen=None):
    """First msgbox text reached from a HnS script label (follows goto/call)."""
    seen = seen or set()
    if label in seen or label not in H_LABELS:
        return None
    seen.add(label)
    for l in H_LABELS[label]:
        t = l.strip()
        m = re.match(r'(?:msgbox|message)\s+(\w+)', t)
        if m and text_block(m.group(1)):
            return m.group(1)
        m = re.match(r'(?:goto|call)(?:_if\w*)?\s+(?:[\w ]+,\s*)*(\w+)\s*$', t)
        if m:
            r = find_text(m.group(1), seen)
            if r:
                return r
        if t in ('end', 'return'):
            break
    return None

ITEMS = set(re.findall(r'\b(ITEM_\w+)\b', read(ours('include/constants/items.h'))))
TMS = read(ours('include/constants/tms_hms.h'))
def item_ok(it):
    if it.startswith('ITEM_TM_') or it.startswith('ITEM_HM_'):
        return 'F(%s)' % it[8:] in TMS
    return it in ITEMS

# ---------------------------------------------------------------- flags for the item balls
FLAG_BASE = 0x2760
FLAGS = collections.OrderedDict()
def item_flag(name):
    FLAGS.setdefault(name, FLAG_BASE + len(FLAGS))
    return name

# ---------------------------------------------------------------- layouts
lay_json = json.load(open(ours('data/layouts/layouts.json')))
have = {l.get('id') for l in lay_json['layouts']}
for hm in SPEC:
    lid = json.load(open(hns('data/maps', hm, 'map.json')))['layout']
    l = H_LAY[lid]
    if lid in have:
        continue
    d = os.path.dirname(l['blockdata_filepath'])
    if os.path.exists(ours(d)):
        shutil.rmtree(ours(d))
    shutil.copytree(hns(d), ours(d))
    lay_json['layouts'].append(collections.OrderedDict([
        ('id', lid), ('name', l['name']), ('width', l['width']), ('height', l['height']),
        ('border_width', l.get('border_width', 2)), ('border_height', l.get('border_height', 2)),
        ('primary_tileset', l['primary_tileset']), ('secondary_tileset', l['secondary_tileset']),
        ('border_filepath', l['border_filepath']), ('blockdata_filepath', l['blockdata_filepath']),
        ('layout_version', 'frlg')]))
# the FireRed layouts that nothing uses any more
OLD_LAYOUTS = {'LAYOUT_SAFFRON_CITY', 'LAYOUT_ROUTE22', 'LAYOUT_ROUTE23', 'LAYOUT_INDIGO_PLATEAU_EXTERIOR',
               'LAYOUT_VICTORY_ROAD_1F_FRLG', 'LAYOUT_VICTORY_ROAD_2F', 'LAYOUT_VICTORY_ROAD_3F'}

VR_TEMPLATE = {'music': 'MUS_RG_MT_MOON', 'region': 'REGION_KANTO', 'region_map_section': 'MAPSEC_KANTO_VICTORY_ROAD',
               'requires_flash': False, 'weather': 'WEATHER_NONE', 'map_type': 'MAP_TYPE_UNDERGROUND', 'allow_cycling': True,
               'allow_escaping': True, 'allow_running': True, 'show_map_name': True, 'battle_scene': 'MAP_BATTLE_SCENE_NORMAL'}
# ---------------------------------------------------------------- map groups (Victory Road in place)
grp = json.load(open(ours('data/maps/map_groups.json')))
for g in grp['group_order']:
    grp[g] = [REPLACED_VR.get(m, m) for m in grp[g]]
for old in REPLACED_VR:
    if os.path.exists(ours('data/maps', old)):
        shutil.rmtree(ours('data/maps', old))

def lay_size(lid):
    for l in lay_json['layouts']:
        if l.get('id') == lid:
            return l['width'], l['height']

# ---------------------------------------------------------------- maps
our_ids = {hm: v[1] for hm, v in SPEC.items()}
HNS_TO_OURS = {json.load(open(hns('data/maps', hm, 'map.json')))['id']: v[1] for hm, v in SPEC.items()}
scripts_out = {}
for hm, (om, oid) in SPEC.items():
    j = json.load(open(hns('data/maps', hm, 'map.json')))
    p = ours('data/maps', om, 'map.json')
    old = json.load(open(p)) if os.path.exists(p) else None
    out = collections.OrderedDict()
    out['id'] = oid
    out['name'] = om
    out['layout'] = j['layout']
    keep = old or VR_TEMPLATE
    out['music'] = keep.get('music')
    out['region_map_section'] = keep.get('region_map_section')
    for k in ('requires_flash', 'weather', 'map_type', 'allow_cycling', 'allow_escaping', 'allow_running', 'show_map_name', 'battle_scene'):
        out[k] = keep.get(k, j.get(k))
    if out['weather'] not in OUR_CONST:
        out['weather'] = 'WEATHER_NONE'
    if out['battle_scene'] not in OUR_CONST:
        out['battle_scene'] = 'MAP_BATTLE_SCENE_NORMAL'
    if 'region' in keep:
        out['region'] = keep['region']
    elif old is None:
        out['region'] = 'REGION_KANTO'
    # connections
    if om in CONNECTIONS and CONNECTIONS[om] is None:
        out['connections'] = keep.get('connections')
    elif om in CONNECTIONS:
        out['connections'] = [dict(c) for c in CONNECTIONS[om]] or None
    else:
        out['connections'] = None
    # objects
    lines = []
    objs = []
    for o in j['object_events']:
        o = collections.OrderedDict(o)
        if o['graphics_id'] in ('OBJ_EVENT_GFX_SILVER_HNS', 'OBJ_EVENT_GFX_GIOVANNI_HNS'):
            continue   # HGSS story scenes
        if o['graphics_id'] not in OUR_CONST and not o['graphics_id'].startswith('OBJ_EVENT_GFX_MON_BASE+'):
            continue
        scr = o.get('script', 'NULL')
        o['flag'] = '0'
        o.pop('local_id', None)
        if o.get('movement_type') not in OUR_CONST:
            o['movement_type'] = 'MOVEMENT_TYPE_NONE'
        if scr in ('EventScript_RockSmash', 'EventScript_StrengthBoulder', 'NULL', '0x0'):
            pass
        elif scr.startswith('SaffronStation_EventScript_Attendant'):
            o['script'] = 'SE_EventScript_MagnetTrainSaffron'
            o['local_id'] = 'LOCALID_SAFFRON_TRAIN_STATION_ATTENDANT'
        elif 'Item' in scr:
            it = next((re.match(r'\s*finditem\s+(\w+)', l).group(1) for l in H_LABELS.get(scr, []) if re.match(r'\s*finditem\s+(\w+)', l)), None)
            if not it:
                continue
            if not item_ok(it):
                it = 'ITEM_PP_UP' if it.startswith('ITEM_TM') else 'ITEM_ULTRA_BALL'
            lbl = 'SE_KH_%s_%s' % (om, re.sub(r'\W', '', scr.split('Item_')[-1]))
            o['script'] = lbl
            o['flag'] = item_flag('FLAG_SE_KH_ITEM_%s_%s' % (om.upper(), re.sub(r'\W', '', scr.split('Item_')[-1]).upper()))
            lines += ['%s::' % lbl, '\tfinditem %s' % it, '\tend', '']
        else:
            t = find_text(scr)
            if not t:
                o['script'] = '0x0'
            else:
                lbl = 'SE_KH_%s_%s' % (om, scr.split('EventScript_')[-1])
                o['script'] = lbl
                if lbl + '::' not in '\n'.join(lines):
                    lines += ['%s::' % lbl, '\tmsgbox %s_Text, MSGBOX_NPC' % lbl, '\tend', '',
                              '%s_Text:' % lbl] + text_block(t) + ['']
        new = collections.OrderedDict([('type', 'object')]); new.update(o)
        objs.append(new)
    # FireRed objects that stay (Indigo credits, Oro on Route 23)
    if old:
        for o in old['object_events']:
            if o.get('local_id') in ('LOCALID_CREDITS_RIVAL', 'LOCALID_CREDITS_PROF_OAK'):
                objs.append(o)
            if o.get('local_id') == 'LOCALID_ROUTE23_SE_ORO':
                o = dict(o); o['x'], o['y'], o['movement_type'] = 20, 21, 'MOVEMENT_TYPE_FACE_LEFT'
                objs.append(o)
    out['object_events'] = objs
    # warps
    warps = []
    for w in j['warp_events']:
        d = w['dest_map']
        if d in HNS_TO_OURS:
            d2 = HNS_TO_OURS[d]
        elif d in DEST:
            d2 = DEST[d]
        else:
            continue
        if hm == 'SaffronCity_TrainStation_hns' and d2 == oid:
            continue    # the train door
        warps.append(collections.OrderedDict([('x', w['x']), ('y', w['y']), ('elevation', w['elevation']),
                                              ('dest_map', d2), ('dest_warp_id', str(w['dest_warp_id']))]))
    out['warp_events'] = warps
    out['coord_events'] = []
    # signs
    bgs = []
    for b in j['bg_events']:
        if b['type'] == 'sign':
            t = find_text(b['script'])
            if not t:
                continue
            lbl = 'SE_KH_%s_%s' % (om, b['script'].split('EventScript_')[-1])
            if lbl + '::' not in '\n'.join(lines):
                lines += ['%s::' % lbl, '\tmsgbox %s_Text, MSGBOX_SIGN' % lbl, '\tend', '',
                          '%s_Text:' % lbl] + text_block(t) + ['']
            bgs.append(collections.OrderedDict([('type', 'sign'), ('x', b['x']), ('y', b['y']), ('elevation', b['elevation']),
                                                ('player_facing_dir', b.get('player_facing_dir', 'BG_EVENT_PLAYER_FACING_ANY')),
                                                ('script', lbl)]))
        elif b['type'] == 'hidden_item' and item_ok(b['item']):
            nb = collections.OrderedDict(b)
            nb['flag'] = item_flag('FLAG_SE_KH_HIDDEN_%s_%d_%d' % (om.upper(), b['x'], b['y']))
            bgs.append(nb)
    out['bg_events'] = bgs
    for k in ('shared_events_map', 'shared_scripts_map'):
        if k in keep:
            out[k] = keep[k]
    write(p, json.dumps(out, indent=2) + '\n')
    scripts_out[om] = lines

# Route 22 meets Viridian City where the road does (HnS offset is for the HnS Viridian)
def road_rows(lid, col):
    l = next(x for x in lay_json['layouts'] if x.get('id') == lid)
    w = l['width']; d = open(ours(l['blockdata_filepath']), 'rb').read()
    return [y for y in range(l['height']) if not (int.from_bytes(d[2 * (y * w + col):2 * (y * w + col) + 2], 'little') >> 10) & 3]
r22 = json.load(open(ours('data/maps/Route22_Frlg/map.json')))
vir = json.load(open(ours('data/maps/ViridianCity_Frlg/map.json')))
# HnS: Route 22 row r meets HnS Viridian row r - offset; find the road's first row on Route 22 that way,
# then put it next to the first open row of our (FireRed) Viridian City's west edge.
hv = json.load(open(hns('data/maps/ViridianCity_hns/map.json')))
hv_l = H_LAY[hv['layout']]; hd = open(hns(hv_l['blockdata_filepath']), 'rb').read()
hv_rows = [y for y in range(hv_l['height']) if not (int.from_bytes(hd[2 * y * hv_l['width']:2 * y * hv_l['width'] + 2], 'little') >> 10) & 3]
h22 = json.load(open(hns('data/maps/Route22_hns/map.json')))
h_off = next(c['offset'] for c in h22['connections'] if c['map'] == 'MAP_VIRIDIAN_CITY_HNS')
a = [min(hv_rows) + h_off]
b = road_rows(vir['layout'], 0)
off = min(b) - a[0]
r22['connections'][0]['offset'] = -off
json.dump(r22, open(ours('data/maps/Route22_Frlg/map.json'), 'w'), indent=2); open(ours('data/maps/Route22_Frlg/map.json'), 'a').write('\n')
for c in vir['connections']:
    if c['map'] == 'MAP_ROUTE22':
        c['offset'] = off
json.dump(vir, open(ours('data/maps/ViridianCity_Frlg/map.json'), 'w'), indent=2); open(ours('data/maps/ViridianCity_Frlg/map.json'), 'a').write('\n')
print('route 22 <-> viridian offset', off, a[:3], b[:3])

# Routes 5-8 no longer show Saffron City across their edge: each side keeps its own gate building
for m in ('Route5_Frlg', 'Route6_Frlg', 'Route7_Frlg', 'Route8_Frlg'):
    p_ = ours('data/maps', m, 'map.json'); j_ = json.load(open(p_))
    j_['connections'] = [c for c in (j_.get('connections') or []) if c['map'] not in ('MAP_SAFFRON_CITY', 'MAP_SAFFRON_CITY_CONNECTION')] or None
    json.dump(j_, open(p_, 'w'), indent=2); open(p_, 'a').write('\n')

# the warps of the other maps that lead into the replaced maps
maps = {}
for f in glob.glob(ours('data/maps/*/map.json')):
    maps[f] = json.load(open(f))
by_id = {j['id']: (f, j) for f, j in maps.items()}
for f, j in maps.items():
    changed = False
    for i, w in enumerate(j.get('warp_events') or []):
        if w['dest_map'] in VR_IDS:
            w['dest_map'] = VR_IDS[w['dest_map']]; changed = True
        tgt = by_id.get(w['dest_map'])
        if not tgt or tgt[1]['name'] not in [v[0] for v in SPEC.values()] or j['name'] in [v[0] for v in SPEC.values()]:
            continue
        idx = [k for k, x in enumerate(tgt[1]['warp_events']) if x['dest_map'] == j['id']]
        if idx and w['dest_warp_id'] != str(idx[0]):
            w['dest_warp_id'] = str(idx[0]); changed = True
    if changed:
        json.dump(j, open(f, 'w'), indent=2); open(f, 'a').write('\n')
# the reception gate leads to Victory Road B2F (HGSS)
f, rg = by_id['MAP_RECEPTION_GATE_HNS']
for w in rg['warp_events']:
    if w['dest_map'] == 'MAP_ROUTE23':
        w['dest_map'] = 'MAP_VICTORY_ROAD_KANTO_B2F_HNS'; w['dest_warp_id'] = '0'
json.dump(rg, open(f, 'w'), indent=2); open(f, 'a').write('\n')

# ---------------------------------------------------------------- scripts
HEADERS = {
    'SaffronCity_Frlg': ['SaffronCity_Frlg_MapScripts::', '\tmap_script MAP_SCRIPT_ON_TRANSITION, SaffronCity_OnTransition', '\t.byte 0', '',
                         'SaffronCity_OnTransition::', '\tsetworldmapflag FLAG_WORLD_MAP_SAFFRON_CITY', '\tend', ''],
    'Route22_Frlg': ['Route22_Frlg_MapScripts::', '\t.byte 0', ''],
    'Route23_Frlg': ['Route23_Frlg_MapScripts::', '\tmap_script MAP_SCRIPT_ON_TRANSITION, Route23_OnTransition', '\t.byte 0', '',
                     'Route23_OnTransition::', '\tcall SE_EventScript_OroVictoryRoadOnTransition', '\tend', ''],
    'SaffronCity_MagnetTrainStation_Frlg': ['SaffronCity_MagnetTrainStation_Frlg_MapScripts::', '\t.byte 0', ''],
}
for om, lines in scripts_out.items():
    p = ours('data/maps', om, 'scripts.inc')
    if om == 'IndigoPlateau_Exterior_Frlg':
        s = read(p)
        s = re.sub(r'\n@ Super Emerald: HGSS look.*', '', s, flags=re.S)
        write(p, s.rstrip('\n') + '\n\n@ Super Emerald: HGSS look (tools/sfr/hns/import_kanto_hgss.py)\n' + '\n'.join(lines) + '\n')
        continue
    head = HEADERS.get(om, ['%s_MapScripts::' % om, '\t.byte 0', ''])
    write(p, '\n'.join(head + ['@ Super Emerald: HGSS look, texts from Pokemon Heart & Soul (tools/sfr/hns/import_kanto_hgss.py)', ''] + lines) + '\n')

# event_scripts.s: Victory Road script files
p = ours('data/event_scripts.s'); s = read(p)
for old, new in REPLACED_VR.items():
    s = s.replace('data/maps/%s/scripts.inc' % old, 'data/maps/%s/scripts.inc' % new)
write(p, s)

# flags
p = ours('include/constants/flags_se_johto.h'); s = read(p)
s = re.sub(r'\n// Kanto HGSS maps \(generated\).*?// end Kanto HGSS maps\n', '\n', s, flags=re.S)
block = '\n// Kanto HGSS maps (generated by tools/sfr/hns/import_kanto_hgss.py)\n' + \
        ''.join('#define %-50s 0x%04X\n' % (n, v) for n, v in FLAGS.items()) + '// end Kanto HGSS maps\n'
s = s.replace('\n#endif', block + '\n#endif', 1) if '#endif' in s else s + block
write(p, s)
assert FLAG_BASE + len(FLAGS) <= 0x2780

# wild encounters and heal location
p = ours('src/data/wild_encounters.json'); s = read(p)
for a_, b_ in VR_IDS.items():
    s = s.replace('"map": "%s"' % a_, '"map": "%s"' % b_)
write(p, s)
p = ours('src/data/heal_locations.json'); hl = json.load(open(p))
sf = json.load(open(ours('data/maps/SaffronCity_Frlg/map.json')))
pc = next(w for w in sf['warp_events'] if w['dest_map'] == 'MAP_SAFFRON_CITY_POKEMON_CENTER_1F')
for h in hl['heal_locations']:
    if h['id'] == 'HEAL_LOCATION_SAFFRON_CITY':
        h['x'], h['y'] = pc['x'], pc['y'] + 1
write(p, json.dumps(hl, indent=2) + '\n')

# drop the old layouts and their folders
keep_lay = []
for l in lay_json['layouts']:
    if l.get('id') in OLD_LAYOUTS:
        d = os.path.dirname(l['blockdata_filepath'])
        if os.path.exists(ours(d)):
            shutil.rmtree(ours(d))
        continue
    keep_lay.append(l)
lay_json['layouts'] = keep_lay
write(ours('data/layouts/layouts.json'), json.dumps(lay_json, indent=2) + '\n')
write(ours('data/maps/map_groups.json'), json.dumps(grp, indent=2) + '\n')
print('maps', len(SPEC), 'flags', len(FLAGS))
