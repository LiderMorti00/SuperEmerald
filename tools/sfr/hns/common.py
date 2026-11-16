"""Super Emerald: shared helpers for importing Johto from Pokemon Heart & Soul
(https://github.com/PokemonHnS-Development/pokehns-expansion). Pass the path of a
pokehns-expansion checkout with --hns or the HNS environment variable."""
import json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
HNS = os.environ.get('HNS', '/home/claude/hns/pokehns-expansion')
for i, a in enumerate(sys.argv):
    if a == '--hns':
        HNS = sys.argv[i + 1]


def hns(*p):
    return os.path.join(HNS, *p)


def ours(*p):
    return os.path.join(ROOT, *p)


def read(p):
    return open(p, encoding='utf-8').read()


def write(p, s):
    os.makedirs(os.path.dirname(p), exist_ok=True)
    open(p, 'w', encoding='utf-8').write(s)


def johto_mapsecs():
    d = json.load(open(ours('src/data/region_map/region_map_sections.json')))
    return {x['id'] for x in d['map_sections'] if x.get('region') == 'johto'}


def johto_maps():
    """HnS map folder names (in group order) whose map section is in Johto."""
    J = johto_mapsecs()
    g = json.load(open(hns('data/maps/map_groups.json')))
    out = []
    for grp in g['group_order']:
        if not grp.endswith('_Hns'):
            continue
        for m in g[grp]:
            j = json.load(open(hns('data/maps', m, 'map.json')))
            if j['region_map_section'] in J:
                out.append((grp, m))
    return out


def replace_block(text, begin, end, body):
    """Replace text between marker lines (inclusive markers kept); append if missing."""
    if begin in text:
        a = text.index(begin)
        b = text.index(end, a) + len(end)
        return text[:a] + begin + '\n' + body + end + text[b:]
    return None
