#!/usr/bin/env python3
"""Super Emerald: hook the imported Sinnoh maps up to data/scripts/se_sinnoh.inc.

Gym leaders, Elite Four, Rowan's lab, Canalave (Dawn and the sailor), Lucas,
legendary levels and Pokémon Center respawns. Run after import_maps.py; safe to run again."""
import json, os, re, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from common import ours, read, write

def mapdir(m): return ours('data/maps/%s_sinnoh' % m)

def load(m): return json.load(open(os.path.join(mapdir(m), 'map.json')))

def save(m, j):
    with open(os.path.join(mapdir(m), 'map.json'), 'w') as f:
        json.dump(j, f, indent=2)
        f.write('\n')

def scripts(m): return os.path.join(mapdir(m), 'scripts.inc')

def set_header(m, body):
    """Replace the map's empty MapScripts header (the importer drops the original one)."""
    p = scripts(m); s = read(p)
    s = re.sub(r'%s_sinnoh_MapScripts::\n(?:\t.*\n)*?\t\.byte 0\n' % m,
               '%s_sinnoh_MapScripts::\n%s\t.byte 0\n' % (m, body), s, count=1)
    write(p, s)

def drop_header(m):
    p = scripts(m); s = read(p)
    s = re.sub(r'%s_sinnoh_MapScripts::\n(?:\t.*\n)*?\t\.byte 0\n' % m, '', s, count=1)
    write(p, s)

def obj(j, gfx):
    for o in j['object_events']:
        if o['graphics_id'] == gfx:
            return o
    raise SystemExit('no %s' % gfx)

# --- gym leaders
GYMS = {'OreburghCity_Gym': 'ROARK', 'EternaCity_Gym': 'GARDENIA', 'VeilstoneCity_Gym': 'MAYLENE',
        'PastoriaCity_Gym': 'WAKE', 'HearthomeCity_Gym': 'FANTINA', 'CanalaveCity_Gym': 'BYRON',
        'SnowpointCity_Gym_1F': 'CANDICE', 'SunyshoreCity_Gym': 'VOLKNER'}
for m, n in GYMS.items():
    j = load(m); o = obj(j, 'OBJ_EVENT_GFX_SINNOH_' + n)
    o['script'] = 'SE_EventScript_SinnohLeader_' + n.capitalize()
    o['flag'] = '0'
    save(m, j)

# --- Elite Four
E4 = {'Aaron': ('SIDNEY', 'AARON'), 'Bertha': ('PHOEBE', 'BERTHA'), 'Flint': ('GLACIA', 'FLINT'), 'Lucian': ('DRAKE', 'LUCIAN')}
for room, (old, new) in E4.items():
    m = 'PokemonLeague_%sRoom' % room
    p = scripts(m); s = read(p)
    s = re.sub(r'\tgoto_if_set FLAG_SYS_GAME_CLEAR, \w+_SNRematchBattle\n', '', s)
    s = s.replace('TRAINER_%s_SINNOH' % old, 'TRAINER_SE_ELITE_FOUR_%s' % new)
    write(p, s)
    set_header(m, '\tmap_script MAP_SCRIPT_ON_LOAD, SE_Sinnoh%sRoom_OnLoad\n'
                  '\tmap_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, SE_SinnohLeague_OnWarp\n' % room)

m = 'PokemonLeague_NorthPokemonCenter_1F'
set_header(m, '\tmap_script MAP_SCRIPT_ON_TRANSITION, SE_SinnohNorthPC_OnTransition\n')
p = scripts(m); write(p, read(p).replace('FLAG_SINNOH_BADGE6_GET', 'FLAG_SINNOH_BADGE8_GET'))
j = load(m)
for o in j['object_events']:
    if o['graphics_id'] == 'OBJ_EVENT_GFX_SINNOH_BARRY':
        o['flag'] = 'FLAG_SN_HIDE_LEAGUE_BARRY'
save(m, j)

# Champion room and Hall of Fame: their scripts live in se_sinnoh.inc
for m, lid in (('PokemonLeague_ChampionRoom', 'LOCALID_SN_CHAMP_CYNTHIA'), ('PokemonLeague_HallOfFameRoom', 'LOCALID_SN_HOF_CYNTHIA')):
    drop_header(m)
    j = load(m); o = obj(j, 'OBJ_EVENT_GFX_SINNOH_CYNTHIA'); o['local_id'] = lid; save(m, j)
j = load('PokemonLeague_HallOfFameRoom'); obj(j, 'OBJ_EVENT_GFX_SINNOH_CYNTHIA')['y'] = 15; save('PokemonLeague_HallOfFameRoom', j)

# --- Rowan's lab
m = 'SandgemTown_RowansLab'; j = load(m)
r = obj(j, 'OBJ_EVENT_GFX_SINNOH_ROWAN'); r['script'] = 'SE_EventScript_Rowan'
a = next(o for o in j['object_events'] if o['graphics_id'] in ('OBJ_EVENT_GFX_VAR_0', 'OBJ_EVENT_GFX_SINNOH_DAWN')); a.update(graphics_id='OBJ_EVENT_GFX_SINNOH_DAWN', script='SE_EventScript_RowanAssistant', flag='0')
save(m, j)

# --- Canalave: the sailor and Dawn
m = 'CanalaveCity'; drop_header(m); j = load(m)
obj(j, 'OBJ_EVENT_GFX_SAILOR_FRLG')['script'] = 'SE_EventScript_CanalaveSailor'
j['object_events'] = [o for o in j['object_events'] if o.get('local_id') != 'LOCALID_CANALAVE_SE_DAWN']
j['object_events'].append({'local_id': 'LOCALID_CANALAVE_SE_DAWN', 'graphics_id': 'OBJ_EVENT_GFX_SINNOH_DAWN',
    'x': 13, 'y': 46, 'elevation': 3, 'movement_type': 'MOVEMENT_TYPE_FACE_RIGHT', 'movement_range_x': 0,
    'movement_range_y': 0, 'trainer_type': 'TRAINER_TYPE_NONE', 'trainer_sight_or_berry_tree_id': '0',
    'script': '0x0', 'flag': 'FLAG_SE_HIDE_CANALAVE_DAWN'})
save(m, j)

# --- Lucas
LUCAS = {'SandgemTown': ('LOCALID_SANDGEM_SE_LUCAS', 9, 11, 'MOVEMENT_TYPE_FACE_UP', 'Sandgem', 'SANDGEM'),
         'HearthomeCity': ('LOCALID_HEARTHOME_SE_LUCAS', 16, 21, 'MOVEMENT_TYPE_FACE_LEFT', 'Hearthome', 'HEARTHOME'),
         'SinnohVictoryRoad_1F': ('LOCALID_VICTORYROAD_SE_LUCAS', 32, 7, 'MOVEMENT_TYPE_FACE_DOWN', 'VictoryRoad', 'VICTORY_ROAD')}
for m, (lid, x, y, mv, n, f) in LUCAS.items():
    j = load(m)
    j['object_events'] = [o for o in j['object_events'] if o.get('local_id') != lid]
    elev = 3
    j['object_events'].append({'local_id': lid, 'graphics_id': 'OBJ_EVENT_GFX_SINNOH_LUCAS', 'x': x, 'y': y,
        'elevation': elev, 'movement_type': mv, 'movement_range_x': 0, 'movement_range_y': 0,
        'trainer_type': 'TRAINER_TYPE_NONE', 'trainer_sight_or_berry_tree_id': '0',
        'script': 'SE_EventScript_Lucas' + n, 'flag': 'FLAG_SE_HIDE_LUCAS_' + f})
    save(m, j)

# --- Pokémon Center respawns
heals = [h['id'] for h in json.load(open(ours('src/data/heal_locations.json')))['heal_locations'] if h['id'].endswith('_SINNOH')]
for d in sorted(os.listdir(ours('data/maps'))):
    mm = re.match(r'(\w+)_PokemonCenter_1F_sinnoh$', d)
    if not mm: continue
    town = re.sub(r'(?<=[a-z])(?=[A-Z])', '_', mm.group(1)).upper()
    h = 'HEAL_LOCATION_%s_SINNOH' % town
    if h not in heals:
        print('no heal for', d); continue
    lbl = 'SE_%s_PC_OnTransition' % mm.group(1)
    p = scripts(mm.group(1) + '_PokemonCenter_1F'); s = read(p)
    if lbl not in s:
        s += '\n%s::\n\tsetrespawn %s\n\tend\n' % (lbl, h)
        write(p, s)
    set_header(mm.group(1) + '_PokemonCenter_1F', '\tmap_script MAP_SCRIPT_ON_TRANSITION, %s\n' % lbl)
m = 'PokemonLeague_SouthPokemonCenter_1F'; p = scripts(m); s = read(p)
if 'SE_LeagueSouth_PC_OnTransition' not in s:
    write(p, s + '\nSE_LeagueSouth_PC_OnTransition::\n\tsetrespawn HEAL_LOCATION_POKEMON_LEAGUE_SOUTH_POKEMON_CENTER_1F_SINNOH\n\tend\n')
set_header(m, '\tmap_script MAP_SCRIPT_ON_TRANSITION, SE_LeagueSouth_PC_OnTransition\n')

# --- legendaries: post-game levels, always shown until caught
LV = {'REGICE': 65, 'REGIROCK': 65, 'REGISTEEL': 65, 'REGIGIGAS': 70, 'UXIE': 65, 'AZELF': 65,
      'DARKRAI': 70, 'HEATRAN': 70, 'GIRATINA': 70, 'SHAYMIN': 65, 'ROTOM': 50, 'SPIRITOMB': 50,
      'DRIFLOON': 45, 'DIALGA': 70, 'PALKIA': 70, 'ARCEUS': 80}
for d in sorted(os.listdir(ours('data/maps'))):
    if not d.endswith('_sinnoh'): continue
    p = os.path.join(ours('data/maps'), d, 'scripts.inc'); s = read(p)
    t = s.replace('\tspecial BattleSetup_StartLegendaryBattle\n\tclearflag', '\tspecial BattleSetup_StartLegendaryBattle\n\twaitstate\n\tclearflag')
    t = re.sub(r'setwildbattle SPECIES_(\w+), \d+', lambda mm: 'setwildbattle SPECIES_%s, %d' % (mm.group(1), LV[mm.group(1)]) if mm.group(1) in LV else mm.group(0), t)
    if t != s: write(p, t)

# Mesprit and Cresselia roamed in the Sinnoh repo; here they wait in their caves
for m, sp, scr in (('LakeVerity_Cavern', 'MESPRIT', 'SE_S_LakeVerity_Cavern_LakeVerity_Cavern_EventScript_SNMESPRIT'),
                   ('FullmoonIsland_Forest', 'CRESSELIA', 'SE_S_FullmoonIsland_Forest_FullmoonIsland_Forest_EventScript_SNCRESSELIA')):
    j = load(m); o = obj(j, 'OBJ_EVENT_GFX_SINNOH_MON_' + sp); o['script'] = 'SE_EventScript_Static' + sp.capitalize(); save(m, j)

flags = read(ours('include/constants/flags_sinnoh.h')) + read(ours('include/constants/flags_se_sinnoh.h'))
out = ['', '@ generated by tools/sfr/sinnoh/patch_sinnoh.py', 'SE_EventScript_SinnohLegendaries::']
for sp in ('REGICE', 'REGIROCK', 'REGISTEEL', 'REGIGIGAS', 'UXIE', 'AZELF', 'MESPRIT', 'CRESSELIA', 'DARKRAI',
           'HEATRAN', 'GIRATINA', 'SHAYMIN', 'DIALGA', 'PALKIA', 'DRIFLOON'):
    done = 'FLAG_SN_DONE_' + sp if 'FLAG_SN_DONE_%s ' % sp in flags else 'FLAG_SE_DONE_' + sp
    hide = 'FLAG_SN_HIDE_' + sp
    if hide + ' ' not in flags: continue
    out += ['\tclearflag %s' % hide, '\tcall_if_set %s, SE_EventScript_SinnohHide_%s' % (done, sp)]
# the Griseous Orb lies in Giratina's room once Giratina is gone
out += ['\tsetflag FLAG_SN_HIDE_GRISEOUS',
        '\tcall_if_set FLAG_SN_DONE_GIRATINA, SE_EventScript_SinnohShow_GRISEOUS']
out += ['\tsetflag FLAG_SN_HIDE_ARCEUS',
        '\tgoto_if_set FLAG_SN_DONE_ARCEUS, Common_EventScript_NopReturn',
        '\tcall_if_set FLAG_SE_SINNOH_LEAGUE_CLEARED, SE_EventScript_SinnohShow_ARCEUS', '\treturn', '',
        'SE_EventScript_SinnohShow_ARCEUS::', '\tclearflag FLAG_SN_HIDE_ARCEUS', '\treturn', '',
        'SE_EventScript_SinnohShow_GRISEOUS::', '\tgoto_if_set FLAG_SN_GOT_GRISEOUS_ORB, Common_EventScript_NopReturn',
        '\tclearflag FLAG_SN_HIDE_GRISEOUS', '\treturn']
for sp in ('REGICE', 'REGIROCK', 'REGISTEEL', 'REGIGIGAS', 'UXIE', 'AZELF', 'MESPRIT', 'CRESSELIA', 'DARKRAI',
           'HEATRAN', 'GIRATINA', 'SHAYMIN', 'DIALGA', 'PALKIA', 'DRIFLOON'):
    if 'FLAG_SN_HIDE_%s ' % sp in flags:
        out += ['', 'SE_EventScript_SinnohHide_%s::' % sp, '\tsetflag FLAG_SN_HIDE_%s' % sp, '\treturn']
for sp in ('MESPRIT', 'CRESSELIA'):
    out += ['', 'SE_EventScript_Static%s::' % sp.capitalize(), '\tlock', '\tfaceplayer', '\twaitse',
            '\tplaymoncry SPECIES_%s, CRY_MODE_ENCOUNTER' % sp, '\tdelay 40', '\twaitmoncry',
            '\tsetwildbattle SPECIES_%s, 65' % sp, '\tsetflag FLAG_SYS_CTRL_OBJ_DELETE',
            '\tspecial BattleSetup_StartLegendaryBattle', '\twaitstate', '\tclearflag FLAG_SYS_CTRL_OBJ_DELETE',
            '\tspecialvar VAR_RESULT, GetBattleOutcome',
            '\tgoto_if_eq VAR_RESULT, B_OUTCOME_RAN, SE_EventScript_Static%sRan' % sp.capitalize(),
            '\tgoto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, SE_EventScript_Static%sRan' % sp.capitalize(),
            '\tsetflag FLAG_SE_DONE_%s' % sp, '\tsetflag FLAG_SN_HIDE_%s' % sp,
            '\tgoto Common_EventScript_RemoveStaticPokemon', '',
            'SE_EventScript_Static%sRan::' % sp.capitalize(), '\tsetvar VAR_0x8004, SPECIES_%s' % sp,
            '\tgoto Common_EventScript_LegendaryFlewAway']
write(ours('data/scripts/se_sinnoh_legendaries.inc'), '\n'.join(out) + '\n')
print('patched')

# --- doors that led outside Sinnoh (Lilycove contest, Battle Frontier): make them solid
L = {l['id']: l for l in json.load(open(ours('data/layouts/layouts.json')))['layouts'] if 'id' in l}
for m in ('HearthomeCity', 'FightArea_FrontierGate'):
    j = load(m); lay = L[j['layout']]; w = lay['width']
    p = ours(lay['blockdata_filepath']); d = bytearray(open(p, 'rb').read())
    for wp in j['warp_events']:
        if wp['dest_map'] == j['id']:
            i = 2 * (wp['y'] * w + wp['x'])
            d[i + 1] |= 0x04      # collision bit (0x0400)
    open(p, 'wb').write(d)
print('blocked external doors')

# --- Veilstone Game Corner: the clerks use the Celadon Game Corner scripts (coins, prizes)
j = load('VeilstoneCity_GameCorner')
for o in j['object_events']:
    if o['script'].endswith('_EventScript_CoinsClerk'):
        o['script'] = 'CeladonCity_GameCorner_EventScript_CoinsClerk'
    elif o['script'].endswith('_EventScript_PrizeCornerDolls'):
        o['script'] = 'CeladonCity_GameCorner_PrizeRoom_EventScript_PrizeClerkMons'
    elif o['script'].endswith('_EventScript_PrizeCornerTMs'):
        o['script'] = 'CeladonCity_GameCorner_PrizeRoom_EventScript_PrizeClerkTMs'
save('VeilstoneCity_GameCorner', j)
print('game corner clerks')
