#!/usr/bin/env python3
"""Super Emerald: add the Sinnoh map sections (region "sinnoh") to region_map_sections.json."""
import json, os, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from common import sin, ours, sinnoh_maps, map_section

used = []
for grp, m in sinnoh_maps():
    j = json.load(open(sin('data/maps', m, 'map.json')))
    s = j['region_map_section']
    if s not in used:
        used.append(s)
hs = {x['id']: x for x in json.load(open(sin('src/data/region_map/region_map_sections.json')))['map_sections']}
p = ours('src/data/region_map/region_map_sections.json')
d = json.load(open(p))
d['map_sections'] = [x for x in d['map_sections'] if x.get('region') != 'sinnoh']
ids = {x['id'] for x in d['map_sections']}
n = 0
for s in used:
    if s in ('MAPSEC_NONE', 'MAPSEC_LITTLEROOT_TOWN'):
        continue
    e = dict(hs[s])
    e['id'] = map_section('', s)
    assert e['id'] not in ids, e['id']
    e['region'] = 'sinnoh'
    d['map_sections'].append(e); ids.add(e['id']); n += 1
open(p, 'w').write(json.dumps(d, indent=2) + '\n')
print('sinnoh sections', n)
