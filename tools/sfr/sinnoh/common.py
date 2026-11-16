"""Super Emerald: shared helpers for importing Sinnoh from LiderMorti00's
Sinnoh-pokeemerald-expansion (https://github.com/LiderMorti00/sinnoh-pokeemerald-expansion).
Pass the path of a checkout with --sinnoh or the SINNOH environment variable."""
import json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
SIN = os.environ.get('SINNOH', '/home/claude/lidermorti00/sinnoh-pokeemerald-expansion')
for i, a in enumerate(sys.argv):
    if a == '--sinnoh':
        SIN = sys.argv[i + 1]

# Map groups of the Sinnoh repo that hold Sinnoh (the rest are Emerald/FRLG leftovers).
SINNOH_GROUPS = 22
# Maps left out (Battle Frontier stays out of Sinnoh, as in Johto).
SKIP_MAPS = set()
# Section names that already exist here (Hoenn/Kanto) get a _SINNOH suffix.
SEC_RENAME = {'MAPSEC_VICTORY_ROAD': 'MAPSEC_VICTORY_ROAD_SINNOH',
              'MAPSEC_POKEMON_LEAGUE': 'MAPSEC_POKEMON_LEAGUE_SINNOH',
              'MAPSEC_POKEMON_MANSION': 'MAPSEC_POKEMON_MANSION_SINNOH'}
# Sinnoh maps whose section was a placeholder in the Sinnoh repo.
SEC_FIX = {'TwinleafTown_Haouse1': 'MAPSEC_TWINLEAF_TOWN', 'TwinleafTown_House2': 'MAPSEC_TWINLEAF_TOWN',
           'IronIsland_House': 'MAPSEC_IRON_ISLAND', 'HearthomeCity_Flat1_F2': 'MAPSEC_HEARTHOME_CITY',
           'HearthomeCity_Flat2_F2': 'MAPSEC_HEARTHOME_CITY', 'SunyshoreCity_VistaLighthouse': 'MAPSEC_SUNYSHORE_CITY',
           'ResortArea_RibbonSyndicate_F2': 'MAPSEC_RESORT_AREA'}


def sin(*p):
    return os.path.join(SIN, *p)


def ours(*p):
    return os.path.join(ROOT, *p)


def read(p):
    return open(p, encoding='utf-8').read()


def write(p, s):
    os.makedirs(os.path.dirname(p), exist_ok=True)
    open(p, 'w', encoding='utf-8').write(s)


# Sinnoh maps kept outside the Sinnoh groups in the Sinnoh repo: Rowan's lab is the repainted
# Birch's lab. Their scripts are not imported (they are Emerald labels); Super Emerald adds its own.
EXTRA_MAPS = [('gMapGroup_IndoorSandgem', 'LittlerootTown_ProfessorBirchsLab')]
NO_SCRIPTS = {m for _, m in EXTRA_MAPS}
SEC_FIX['LittlerootTown_ProfessorBirchsLab'] = 'MAPSEC_SANDGEM_TOWN'
# Warps to these maps stay as they are (link rooms we also have).
KEEP_WARPS = {'MAP_UNION_ROOM', 'MAP_TRADE_CENTER'}


def sinnoh_maps():
    """(group, map folder) for every Sinnoh map, in the Sinnoh repo's group order."""
    g = json.load(open(sin('data/maps/map_groups.json')))
    return [(grp, m) for grp in g['group_order'][:SINNOH_GROUPS] for m in g[grp] if m not in SKIP_MAPS] + EXTRA_MAPS


RENAME = {'LittlerootTown_ProfessorBirchsLab': ('SandgemTown_RowansLab', 'MAP_SANDGEM_TOWN_ROWANS_LAB')}


def new_map_name(m):
    return RENAME.get(m, (m,))[0] + '_sinnoh'


def new_map_id(i):
    for m, (n, mid) in RENAME.items():
        if i == 'MAP_' + re.sub(r'(?<!^)(?=[A-Z])', '_', m).upper().replace('__', '_') or i == 'MAP_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB':
            return mid + '_SINNOH'
    return i + '_SINNOH'


def map_section(m, sec):
    sec = SEC_FIX.get(m, sec)
    return SEC_RENAME.get(sec, sec)
