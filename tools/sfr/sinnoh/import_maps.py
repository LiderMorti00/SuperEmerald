#!/usr/bin/env python3
"""Super Emerald: import the Sinnoh maps from LiderMorti00's Sinnoh-pokeemerald-expansion
as a post-story free world (like Johto).

For every Sinnoh map (common.sinnoh_maps):
  * renamed with a _sinnoh / _SINNOH suffix (map folder, MAP_ id, layout id and folder),
    because the Sinnoh repo is built on Emerald and reuses many Emerald names;
  * layout copied (Emerald format, Sinnoh tilesets renamed *_Sinnoh);
  * map.json converted: Sinnoh-only flags/trainers/maps renamed, coord events dropped,
    warps to maps we don't import pointed back at their own map (fixed by hand later).
Scripts: an object/sign script is copied only if every command and constant it uses exists
here; scripts that need the Sinnoh story (story vars, specials we lack...) are replaced by a
plain trainer battle / first line of text, as for Johto. A script that falls through into the
next label of the Sinnoh file gets an explicit goto, so moving labels around is safe.
Also writes include/constants/flags_sinnoh.h, opponents_sinnoh_list.h,
src/data/trainers_sinnoh.party, the Sinnoh berry tree ids, wild encounters, heal locations
and tools/sfr/sinnoh/import_report.txt.

Usage (repo root): python3 -I tools/sfr/sinnoh/import_maps.py [--sinnoh /path]
One-time import: once Sinnoh maps are edited by hand, running it again overwrites them.
"""
import collections, glob, json, os, re, shutil, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from common import sin, ours, read, write, sinnoh_maps, new_map_name, new_map_id, map_section, NO_SCRIPTS, KEEP_WARPS

MAPS = sinnoh_maps()
NAMES = [m for _, m in MAPS]
SJ = {m: json.load(open(sin('data/maps', m, 'map.json'))) for m in NAMES}
IDS = {SJ[m]['id'] for m in NAMES}
MAPREN = {SJ[m]['id']: new_map_id(SJ[m]['id']) for m in NAMES}
SL = {l['id']: l for l in json.load(open(sin('data/layouts/layouts.json')))['layouts'] if 'primary_tileset' in l}

# ---------------------------------------------------------------- our known symbols
def our_constants():
    s = set()
    for f in glob.glob(ours('include/**/*.h'), recursive=True) + glob.glob(ours('asm/macros/*.inc')) \
            + [ours('data/specials.inc')]:
        if os.path.basename(f) in ('flags_sinnoh.h', 'opponents_sinnoh_list.h'):
            continue
        s |= set(re.findall(r'\b([A-Z][A-Z0-9_]{2,})\b', read(f)))
    return s

OUR_CONST = our_constants()
OUR_MACROS = set()
for f in glob.glob(ours('asm/macros/*.inc')):
    t = read(f)
    OUR_MACROS |= set(re.findall(r'^\s*\.macro\s+(\w+)', t, re.M))
    OUR_MACROS |= set(re.findall(r'create_movement_action\s+(\w+)', t))
OUR_MACROS |= {'.string', '.byte', '.2byte', '.4byte', '.align', '.braille'}
OUR_LABELS = set()
for f in glob.glob(ours('data/**/*.inc'), recursive=True) + glob.glob(ours('data/*.s')):
    if '/maps/' in f and f.endswith('_sinnoh/scripts.inc'):
        continue
    if f.endswith('se_sinnoh_import.inc'):
        continue
    OUR_LABELS |= set(re.findall(r'^(\w+)::?', read(f), re.M))
OUR_SPECIALS = set(re.findall(r'def_special (\w+)', read(ours('data/specials.inc'))))
OUR_SONGS = set(re.findall(r'#define\s+(MUS_\w+)', read(ours('include/constants/songs.h'))))
BATTLE_SCENES = set(c for c in OUR_CONST if c.startswith('MAP_BATTLE_SCENE_'))
_items = read(ours('include/constants/items.h'))
VALID_ITEMS = set(re.findall(r'^\s+(ITEM_\w+)\s*[=,]', _items, re.M)) | set(re.findall(r'#define (ITEM_\w+)', _items))
_tms = read(ours('include/constants/tms_hms.h'))
VALID_ITEMS |= {'ITEM_TM_' + m for m in re.findall(r'F\((\w+)\)', _tms.split('FOREACH_HM')[0])}
VALID_ITEMS |= {'ITEM_HM_' + m for m in re.findall(r'F\((\w+)\)', _tms.split('FOREACH_HM')[1])} if 'FOREACH_HM' in _tms else set()

def item_sub(it):
    """Items the Sinnoh repo has but we don't (Platinum TMs, ...) become PP Ups / Ultra Balls."""
    if it in VALID_ITEMS:
        return it
    STATS['item_substituted'] += 1
    return 'ITEM_PP_UP' if it.startswith(('ITEM_TM', 'ITEM_HM')) else 'ITEM_ULTRA_BALL'

# ---------------------------------------------------------------- Sinnoh label index
S_FILES = sorted(glob.glob(sin('data/maps/*/scripts.inc')) + glob.glob(sin('data/scripts/*.inc'))
                 + glob.glob(sin('data/text/*.inc')))
LABELS = {}   # name -> (file, [lines])
NEXT = {}     # name -> next label in the same file
for f in S_FILES:
    cur = None; prev = None
    for line in read(f).split('\n'):
        m = re.match(r'^(\w+)::?\s*(@.*)?$', line)
        if m:
            name = m.group(1)
            if prev and prev in LABELS and LABELS[prev][0] == f:
                NEXT.setdefault(prev, name)
            if name not in LABELS:
                LABELS[name] = (f, []); cur = name
            else:
                cur = None
            prev = name
            continue
        if cur:
            LABELS[cur][1].append(line)

TERMINATORS = re.compile(r'^\s*(end|return|goto|step_end|releaseall\s*$|waitstate\s*$|\.byte\s+0|\.2byte\s+0|'
                         r'goto_if_\w+|warp\w*|special\s+\w+$|trainerbattle\w*)\b')
END_CMDS = re.compile(r'^\s*(end|return|goto\s|step_end|\.byte\s|\.2byte\s|\.4byte\s|\.align|\.string|pokemartlistend|'
                      r'warp|warpsilent|warpdoor|warphole|warpteleport)')

def falls_through(label):
    code = [l.split('@')[0].rstrip() for l in LABELS[label][1]]
    code = [l for l in code if l.strip() and not l.strip().startswith('//')]
    if not code:
        return False
    last = code[-1].strip()
    if last.startswith(('.string', '.byte', '.2byte', '.4byte', '.align')) or last.endswith('_end') or last == 'step_end':
        return False
    return not re.match(r'^(end|return|goto\s|warp\w*\s|releaseall$|pokemartlistend|step_end)', last)

def owner_map(label):
    f = LABELS[label][0]
    m = re.search(r'data/maps/(\w+)/scripts.inc$', f)
    return m.group(1) if m and m.group(1) in SJ else None

# ---------------------------------------------------------------- constants remaps
S_FLAGS = set()
for f in glob.glob(sin('include/constants/*.h')):
    S_FLAGS |= set(re.findall(r'#define\s+(FLAG_\w+)', read(f)))
S_TRAINERS = set(re.findall(r'#define\s+(TRAINER_\w+)\s+\d+', read(sin('include/constants/opponents.h'))))
BADGES = {'FLAG_BADGE0%d_GET' % i: 'FLAG_SINNOH_BADGE%d_GET' % i for i in range(1, 9)}
ALLOWED_VARS = {'VAR_RESULT', 'VAR_FACING', 'VAR_LAST_TALKED', 'VAR_ITEM_ID'} | {'VAR_0x80%02X' % i for i in range(0x0C)} \
               | {'VAR_TEMP_%X' % i for i in range(16)} \
               | {'VAR_SN_HONEY_TREE', 'VAR_SN_HONEY_DAY', 'VAR_SN_TROPHY_SPECIES', 'VAR_POKELOT_PRIZE_ITEM',
                  'VAR_SLATEPORT_FAN_CLUB_STATE', 'VAR_DAYS', 'VAR_POKELOT_PRIZE_PLACE', 'VAR_OBJ_GFX_ID_0'}
# Sinnoh repo vars that live under another name here (include/constants/vars.h)
VAR_RENAME = {'VAR_SINNOH_STORY': 'VAR_SN_SINNOH_STORY', 'VAR_STARTER_MON': 'VAR_SN_STARTER_MON'}
ALLOWED_VARS |= set(VAR_RENAME)
SAFE_OUR_FLAGS = {'FLAG_TEMP_%X' % i for i in range(1, 0x20)} | {'FLAG_SYS_POKEMON_GET', 'FLAG_SYS_POKEDEX_GET',
                  'FLAG_SYS_GAME_CLEAR', 'FLAG_SYS_CTRL_OBJ_DELETE', 'FLAG_SYS_NATIONAL_DEX', 'FLAG_SYS_POKENAV_GET',
                  'FLAG_SYS_PC_LANETTE'}
MUSIC_MAP = {'MUS_DPP_POKECENTER': 'MUS_POKE_CENTER', 'MUS_LITTLEROOT_TEST': 'MUS_DPP_TWINLEAF', 'MUS_NONE': 'MUS_DPP_TWINLEAF'}
SKIP_GFX = set()

sinnoh_flags = collections.OrderedDict()
sinnoh_trainers = collections.OrderedDict()
BERRY_IDS = collections.OrderedDict()

def flag_name(f):
    if f in BADGES:
        return BADGES[f]
    if f in SAFE_OUR_FLAGS or f.startswith('FLAG_TEMP_'):
        return f
    n = 'FLAG_SN' + f[len('FLAG'):] if f in OUR_CONST else f
    sinnoh_flags.setdefault(f, n)
    return n

def trainer_name(t):
    n = t + '_SINNOH'
    sinnoh_trainers.setdefault(t, n)
    return n

def song(m):
    return MUSIC_MAP.get(m, m)

TOKEN = re.compile(r'\b([A-Za-z_]\w*)\b')

def closure(entry):
    seen, stack = [], [entry]
    while stack:
        l = stack.pop()
        if l in seen or l not in LABELS or l in OUR_LABELS:
            continue
        seen.append(l)
        if falls_through(l) and l in NEXT:
            stack.append(NEXT[l])
        for line in LABELS[l][1]:
            if line.strip().startswith('.string'):
                continue
            for t in TOKEN.findall(line.split('@')[0]):
                if t in LABELS and t not in OUR_LABELS:
                    stack.append(t)
    return seen

def check_line(line, local_ids):
    code = line.split('@')[0].split('//')[0].strip()
    if not code or code.startswith('.string'):
        return None
    cmd = code.split()[0].rstrip(',')
    if cmd not in OUR_MACROS:
        return 'cmd ' + cmd
    args = code[len(cmd):]
    if cmd in ('special', 'specialvar'):
        sp = args.split(',')[-1].strip()
        if sp not in OUR_SPECIALS:
            return 'special ' + sp
    if cmd in ('callnative', 'gotonative'):
        return 'native'
    for t in TOKEN.findall(args):
        if t in LABELS or t in OUR_LABELS or t in local_ids:
            continue
        if t.startswith('VAR_'):
            if t not in ALLOWED_VARS:
                return 'var ' + t
            continue
        if t.startswith('FLAG_'):
            if t in SAFE_OUR_FLAGS:
                continue
            if t.startswith('FLAG_SYS_'):
                return 'flag ' + t
            if t in S_FLAGS or t in BADGES:
                continue
            return 'flag ' + t
        if t.startswith('TRAINER_') and t in S_TRAINERS:
            continue
        if t.startswith('MUS_'):
            if song(t) in OUR_SONGS:
                continue
            return 'music ' + t
        if t.startswith('MAP_'):
            if t in IDS or t in BATTLE_SCENES or t.startswith('MAP_TYPE_') or t.startswith('MAP_SCRIPT_'):
                continue
            return 'map ' + t      # an Emerald map in a Sinnoh script
        if t.startswith('ITEM_') and t not in VALID_ITEMS and not t.startswith(('ITEM_USE_', 'ITEM_NONE')):
            continue          # replaced by convert_line (item_sub)
        if t.startswith('LOCALID_') and t not in OUR_CONST:
            return 'localid ' + t
        if t in ('TRUE', 'FALSE', 'YES', 'NO', 'ON', 'OFF'):
            continue
        if t.startswith('ITEM_'):
            continue      # valid, or replaced by convert_line
        if re.fullmatch(r'[A-Z][A-Z0-9_]+', t) and t not in OUR_CONST:
            return 'const ' + t
    return None

def convert_line(line):
    def rep(m):
        t = m.group(1)
        if t in VAR_RENAME:
            return VAR_RENAME[t]
        if t.startswith('FLAG_') and (t in S_FLAGS or t in BADGES) and t not in SAFE_OUR_FLAGS and not t.startswith('FLAG_TEMP_'):
            return flag_name(t)
        if t.startswith('MUS_'):
            return song(t)
        if t.startswith('TRAINER_') and t in S_TRAINERS:
            return trainer_name(t)
        if t in MAPREN:
            return MAPREN[t]
        if t.startswith('ITEM_') and t not in VALID_ITEMS and not t.startswith(('ITEM_USE_', 'ITEM_NONE')):
            return item_sub(t)
        return t
    if line.strip().startswith('.string'):
        return line
    code, sep, cmt = line.partition('@')
    return TOKEN.sub(rep, code) + sep + cmt

def first(labels, pattern):
    for l in labels:
        for line in LABELS[l][1]:
            m = re.search(pattern, line)
            if m:
                return m
    return None

# ---------------------------------------------------------------- per map
OUT = collections.defaultdict(list)
EMITTED = set()
STATS = collections.Counter()
REJECTS = collections.Counter()
FALLBACKS = []
FB_DONE = set()

def dest_file(label):
    om = owner_map(label)
    return ours('data/maps', new_map_name(om), 'scripts.inc') if om else ours('data/scripts/se_sinnoh_import.inc')

def emit_label(label):
    if label in EMITTED:
        return
    EMITTED.add(label)
    body = [convert_line(x) for x in LABELS[label][1]]
    while body and not body[-1].strip():
        body.pop()
    if falls_through(label) and label in NEXT:
        body.append('\tgoto %s' % NEXT[label])
        emit_label(NEXT[label])
    OUT[dest_file(label)].append('%s::\n%s\n' % (label, '\n'.join(body)))

def emit_text(label):
    if label in OUR_LABELS:
        return label
    emit_label(label)
    return label

def resolve(entry, kind, local_ids, mapname):
    if entry in ('', '0x0', 'NULL', None, '0'):
        return entry or '0x0'
    if entry in OUR_LABELS:
        return entry
    if entry not in LABELS:
        STATS['missing'] += 1
        return '0x0'
    cl = closure(entry)
    reason = None
    for l in cl:
        for line in LABELS[l][1]:
            reason = check_line(line, local_ids)
            if reason:
                break
        if reason:
            break
    if not reason:
        for l in cl:
            emit_label(l)
        STATS['kept'] += 1
        return entry
    REJECTS[' '.join(reason.split()[:2])] += 1
    fb = 'SE_S_%s_%s' % (mapname, entry)
    if fb in FB_DONE:
        return fb
    FB_DONE.add(fb)
    lines = None
    if kind == 'trainer':
        m = first(cl, r'trainerbattle_(single|double|no_intro)\s+(TRAINER_\w+)\s*,\s*(\w+)(?:\s*,\s*(\w+))?(?:\s*,\s*(\w+))?')
        after = first(cl, r'msgbox\s+(\w+)\s*,\s*MSGBOX_AUTOCLOSE')
        if m and m.group(2) in S_TRAINERS:
            t = trainer_name(m.group(2))
            if m.group(1) == 'no_intro':
                lines = ['\ttrainerbattle_no_intro %s, %s' % (t, emit_text(m.group(3)))]
            elif m.group(1) == 'double' and m.group(5):
                lines = ['\ttrainerbattle_double %s, %s, %s, %s' % (t, emit_text(m.group(3)), emit_text(m.group(4)), emit_text(m.group(5)))]
            else:
                lines = ['\ttrainerbattle_single %s, %s, %s' % (t, emit_text(m.group(3)), emit_text(m.group(4)))]
            if after:
                lines.append('\tmsgbox %s, MSGBOX_AUTOCLOSE' % emit_text(after.group(1)))
            lines.append('\tend')
    if lines is None:
        m = first(cl, r'(?:msgbox|message)\s+(\w+)')
        if m and m.group(1) in LABELS and LABELS[m.group(1)][1] and any('.string' in x for x in LABELS[m.group(1)][1]):
            txt = emit_text(m.group(1))
            lines = ['\tmsgbox %s, %s' % (txt, 'MSGBOX_SIGN' if kind == 'sign' else 'MSGBOX_NPC'), '\tend']
        else:
            m = first(cl, r'finditem\s+(ITEM_\w+)')
            if m:
                lines = ['\tfinditem %s' % item_sub(m.group(1)), '\tend']
            else:
                lines = ['\tend']
    OUT[ours('data/maps', new_map_name(mapname), 'scripts.inc')].append('%s::\n%s\n' % (fb, '\n'.join(lines)))
    FALLBACKS.append((mapname, entry, reason))
    STATS['fallback'] += 1
    return fb

# ---------------------------------------------------------------- layouts + maps
lay_json = json.load(open(ours('data/layouts/layouts.json')))
lay_json['layouts'] = [l for l in lay_json['layouts'] if not l.get('id', '').endswith('_SINNOH')]
grp_json = json.load(open(ours('data/maps/map_groups.json')))
for g in [g for g in grp_json['group_order'] if g.endswith('_Sinnoh')]:
    grp_json['group_order'].remove(g); del grp_json[g]
for d in glob.glob(ours('data/maps/*_sinnoh')) + glob.glob(ours('data/layouts/*_sinnoh')):
    shutil.rmtree(d)

added = {}
hidden_objects = []
for grp, m in MAPS:
    j = SJ[m]
    lid = j['layout']; l = SL[lid]
    nlid = lid + '_SINNOH'
    if lid not in added:
        d = os.path.dirname(l['blockdata_filepath'])
        nd = d + '_sinnoh'
        shutil.copytree(sin(d), ours(nd))
        added[lid] = nlid
        lay_json['layouts'].append(collections.OrderedDict([
            ('id', nlid), ('name', l['name'] + '_Sinnoh'), ('width', l['width']), ('height', l['height']),
            ('border_width', l.get('border_width', 2)), ('border_height', l.get('border_height', 2)),
            ('primary_tileset', l['primary_tileset'] + '_Sinnoh'), ('secondary_tileset', l['secondary_tileset'] + '_Sinnoh'),
            ('border_filepath', l['border_filepath'].replace(d, nd)), ('blockdata_filepath', l['blockdata_filepath'].replace(d, nd)),
            ('layout_version', 'emerald')]))
    nm = new_map_name(m)
    local_ids = {o['local_id'] for o in j['object_events'] if o.get('local_id')}
    out = collections.OrderedDict()
    out['id'] = MAPREN[j['id']]
    out['name'] = nm
    out['layout'] = nlid
    out['music'] = song(j['music']) if song(j['music']) in OUR_SONGS else 'MUS_DPP_TWINLEAF'
    out['region_map_section'] = map_section(m, j['region_map_section'])
    for k in ('requires_flash', 'weather', 'map_type', 'allow_cycling', 'allow_escaping', 'allow_running', 'show_map_name'):
        out[k] = j[k]
    if out['weather'] not in OUR_CONST:
        out['weather'] = 'WEATHER_SUNNY'
    out['battle_scene'] = j['battle_scene'] if j['battle_scene'] in BATTLE_SCENES else 'MAP_BATTLE_SCENE_NORMAL'
    conns = [dict(c, map=MAPREN[c['map']]) for c in (j.get('connections') or []) if c['map'] in IDS]
    out['connections'] = conns or None
    objs = []
    for o in j['object_events']:
        o = collections.OrderedDict(o)
        o.pop('type', None)
        tt = str(o.get('trainer_type', 'TRAINER_TYPE_NONE'))
        if str(o.get('trainer_sight_or_berry_tree_id', '')).startswith('ITEM_'):
            o['trainer_sight_or_berry_tree_id'] = item_sub(o['trainer_sight_or_berry_tree_id'])
        if str(o.get('trainer_sight_or_berry_tree_id', '')).startswith('BERRY_TREE_'):
            v = o['trainer_sight_or_berry_tree_id']
            o['trainer_sight_or_berry_tree_id'] = BERRY_IDS.setdefault(v, 'BERRY_TREE_SINNOH_' + v[len('BERRY_TREE_'):])
        if o.get('movement_type') not in OUR_CONST:
            o['movement_type'] = 'MOVEMENT_TYPE_FACE_DOWN'
        gid = o['graphics_id']
        if not (gid in OUR_CONST or gid.startswith('OBJ_EVENT_GFX_SPECIES(') or gid.startswith('OBJ_EVENT_GFX_SINNOH_')):
            o['graphics_id'] = 'OBJ_EVENT_GFX_BOY_1'
        kind = 'trainer' if tt not in ('TRAINER_TYPE_NONE', '0') else 'npc'
        o['script'] = '0x0' if m in NO_SCRIPTS else resolve(o.get('script'), kind, local_ids, m)
        if o.get('flag') not in (None, '0', ''):
            o['flag'] = flag_name(o['flag'])
            if 'ITEM_BALL' not in o['graphics_id']:
                hidden_objects.append((m, o['flag'], o['graphics_id'], o.get('local_id', '')))
        new = collections.OrderedDict([('type', 'object')]); new.update(o)
        objs.append(new)
    out['object_events'] = objs
    warps = []
    for w in j['warp_events']:
        w = dict(w)
        if w['dest_map'] in MAPREN:
            w['dest_map'] = MAPREN[w['dest_map']]
        elif w['dest_map'] not in ('MAP_DYNAMIC',) and w['dest_map'] not in KEEP_WARPS:
            STATS['warp_external'] += 1
            FALLBACKS.append((m, 'warp %s' % w['dest_map'], 'external warp'))
            w['dest_map'] = out['id']; w['dest_warp_id'] = '0'
        warps.append(w)
    out['warp_events'] = warps
    out['coord_events'] = []
    bgs = []
    for b in j['bg_events']:
        b = collections.OrderedDict(b)
        if b['type'] == 'hidden_item':
            b['flag'] = flag_name(b['flag'])
            b['item'] = item_sub(b['item'])
        elif b.get('script'):
            if m in NO_SCRIPTS:
                continue
            b['script'] = resolve(b['script'], 'sign', local_ids, m)
        bgs.append(b)
    out['bg_events'] = bgs
    write(ours('data/maps', nm, 'map.json'), json.dumps(out, indent=2) + '\n')
    OUT.setdefault(ours('data/maps', nm, 'scripts.inc'), [])
    OUT[ours('data/maps', nm, 'scripts.inc')].insert(0, '%s_MapScripts::\n\t.byte 0\n\n' % nm)
    ng = grp + '_Sinnoh'
    if ng not in grp_json['group_order']:
        grp_json['group_order'].append(ng); grp_json[ng] = []
    grp_json[ng].append(nm)

write(ours('data/layouts/layouts.json'), json.dumps(lay_json, indent=2) + '\n')
write(ours('data/maps/map_groups.json'), json.dumps(grp_json, indent=2) + '\n')
for f, blocks in OUT.items():
    write(f, '\n'.join(blocks))
if ours('data/scripts/se_sinnoh_import.inc') not in OUT:
    write(ours('data/scripts/se_sinnoh_import.inc'), '@ Super Emerald: generated by tools/sfr/sinnoh/import_maps.py\n')
else:
    p = ours('data/scripts/se_sinnoh_import.inc')
    write(p, '@ Super Emerald: generated by tools/sfr/sinnoh/import_maps.py\n' + read(p))

# ---------------------------------------------------------------- flags
lines = ['#ifndef GUARD_CONSTANTS_FLAGS_SINNOH_H', '#define GUARD_CONSTANTS_FLAGS_SINNOH_H', '',
         '// GENERATED by tools/sfr/sinnoh/import_maps.py - do not edit by hand.',
         '// Super Emerald: Sinnoh flags (from LiderMorti00\'s Sinnoh repo), in the extended flag block.',
         '// Plain numbers on purpose (scripts pass flags to macros).', '']
n = 0
for i in range(1, 9):
    lines.append('#define %-55s 0x%04x' % ('FLAG_SINNOH_BADGE%d_GET' % i, 0x2A00 + n)); n += 1
lines.append('#define %-55s 0x%04x' % ('FLAG_SE_SINNOH_INITIALIZED', 0x2A00 + n)); n += 1
for h, o in sinnoh_flags.items():
    if o.startswith('FLAG_SINNOH_BADGE'):
        continue
    lines.append('#define %-55s 0x%04x // Sinnoh repo %s' % (o, 0x2A00 + n, h)); n += 1
assert n < 0x400, n   # 0x2A00-0x2DFF (hand-made Super Emerald Sinnoh flags are at 0x3200+)
lines += ['', '#endif // GUARD_CONSTANTS_FLAGS_SINNOH_H', '']
write(ours('include/constants/flags_sinnoh.h'), '\n'.join(lines))

# ---------------------------------------------------------------- berry trees (SaveBlock3 ids 128+)
p = ours('include/constants/berry.h'); t = read(p)
t = re.sub(r'\n// Super Emerald: Sinnoh begin.*?// Super Emerald: Sinnoh end\n', '\n', t, flags=re.S)
ids = list(BERRY_IDS.values())[:112]
blk = '\n// Super Emerald: Sinnoh begin (Sinnoh berry trees, in SaveBlock3)\n' + ''.join('#define %-30s %d\n' % (v, 128 + i) for i, v in enumerate(ids)) + '// Super Emerald: Sinnoh end\n'
t = t.replace('\n// Remainder are unused', blk + '\n// Remainder are unused', 1)
write(p, t)
STATS['berry_trees'] = len(BERRY_IDS)

# ---------------------------------------------------------------- trainers
# Sinnoh is a post-story region at the Kanto/Johto level: story levels are spread over 47-62
# and the Pokemon evolve. Leaders, Elite Four and Cynthia get their own levels in
# tools/sfr/sinnoh/gen_sinnoh_league.py.
LOW, HIGH = 47, 62
SPECIES = set(re.findall(r'\b(SPECIES_\w+)\b', read(ours('include/constants/species.h'))))
EVOS = {}
for f in glob.glob(ours('src/data/pokemon/species_info/*.h')):
    for mm in re.finditer(r'\[(SPECIES_\w+)\]\s*=\s*\{(.*?)\n    \},', read(f), re.S):
        e = re.search(r'\.evolutions = EVOLUTION\((.*?)\),(?:\n|$)', mm.group(2), re.S)
        if e:
            EVOS.setdefault(mm.group(1), re.findall(r'\{(EVO_\w+),\s*([^,]+),\s*(SPECIES_\w+)', e.group(1)))

def species_const(name):
    n = name.strip()
    if n.startswith('SPECIES_'):
        return n
    n = n.replace('♂', '_M').replace('♀', '_F').replace('é', 'E').replace('’', '').replace("'", '')
    n = re.sub(r'[^A-Za-z0-9]+', '_', n).strip('_').upper()
    return 'SPECIES_' + n

def evolve(sp, lvl):
    for _ in range(3):
        nxt = None
        for meth, param, tgt in EVOS.get(sp, []):
            if tgt not in SPECIES:
                continue
            if meth == 'EVO_LEVEL' and param.strip().isdigit() and int(param) <= lvl:
                nxt = tgt; break
            if meth in ('EVO_ITEM', 'EVO_TRADE') and lvl >= 45:
                nxt = tgt; break
            if meth == 'EVO_LEVEL' and not param.strip().isdigit() and lvl >= 45:
                nxt = tgt; break
        if not nxt:
            return sp
        sp = nxt
    return sp

def scale(L):
    if L <= 55:
        return round(LOW + (L - 2) * (HIGH - LOW) / 53.0)
    return min(70, round(HIGH + (L - 55) * 0.3))

OUR_TR = read(ours('include/constants/trainers.h'))
def has(c):
    return re.search(r'\b%s\b' % c, OUR_TR) is not None
def tconst(prefix, name):
    return prefix + re.sub(r'[^A-Z0-9]+', '_', name.upper()).strip('_')

MISSING = collections.Counter()
def fix_value(kind, v):
    if kind == 'Class':
        c = v if v.startswith('TRAINER_CLASS_') else tconst('TRAINER_CLASS_', v)
        if has(c):
            return v
        MISSING[('class', c)] += 1
        return v      # import_trainer_gfx.py adds the missing classes
    if kind == 'Pic':
        c = v if v.startswith('TRAINER_PIC_') else tconst('TRAINER_PIC_', v)
        if not has(c):
            MISSING[('pic', c)] += 1
        return v
    if kind == 'Music':
        c = v if v.startswith('TRAINER_ENCOUNTER_MUSIC_') else tconst('TRAINER_ENCOUNTER_MUSIC_', v)
        return v if has(c) else 'Male'
    return v

def fix_block(b, newname):
    mons = b.split('\n\n')
    head = mons[0].split('\n')
    out = ['=== %s ===' % newname]
    for line in head[1:]:
        k, sep, v = line.partition(': ')
        if k == 'Mugshot':
            continue
        out.append(k + sep + fix_value(k, v) if sep and k in ('Class', 'Pic', 'Music') else line)
    res = ['\n'.join(out)]
    for mon in mons[1:]:
        lines = mon.split('\n')
        if not lines or not lines[0].strip():
            continue
        lv = re.search(r'^Level: (\d+)', mon, re.M)
        L = scale(int(lv.group(1))) if lv else 50
        m = re.match(r'^(?:(.*?) \()?([^()@]+?)\)?(\s*\([MF]\))?(\s*@.*)?$', lines[0])
        first_ = lines[0]
        if m:
            sp = species_const(m.group(2))
            if sp in SPECIES:
                sp2 = evolve(sp, L)
                nick = m.group(1)
                first_ = ('%s (%s)' % (nick, sp2) if nick else sp2) + (m.group(3) or '') + (m.group(4) or '')
        lines[0] = first_
        lines = [('Level: %d' % L) if l.startswith('Level: ') else l for l in lines if not l.startswith('IVs: 0 HP / 0 Atk')]
        res.append('\n'.join(lines))
    return '\n\n'.join(res)

party = read(sin('src/data/trainers.party'))
blocks = {re.match(r'=== (\w+) ===', b).group(1): b for b in re.split(r'\n(?==== )', party) if b.startswith('===')}
tl = ['// Super Emerald: generated by tools/sfr/sinnoh/import_maps.py - do not edit by hand.']
pb = []
for i, (t, n) in enumerate(sinnoh_trainers.items()):
    tl.append('#define %-40s %d' % (n, 2144 + i))
    if t in blocks:
        pb.append(fix_block(blocks[t].rstrip(), n) + '\n')
    else:
        pb.append('=== %s ===\nName: TRAINER\nClass: Pkmn Trainer 1\nPic: Youngster Frlg\nGender: Male\nMusic: Male\nDouble Battle: No\nAI: Check Bad Move\n\nBidoof\nLevel: 50\n' % n)
        STATS['trainer_missing_party'] += 1
print("sinnoh trainers", len(sinnoh_trainers)); assert len(sinnoh_trainers) < 1024 - 32
tl.append('#define TRAINERS_COUNT_SINNOH_IMPORT %d' % len(sinnoh_trainers))
write(ours('include/constants/opponents_sinnoh_list.h'), '\n'.join(tl) + '\n')
write(ours('src/data/trainers_sinnoh.party'), '\n'.join(pb))

# ---------------------------------------------------------------- battle partners (NPC followers)
sp_party = read(sin('src/data/battle_partners.party'))
sp_blocks = [b for b in re.split(r'\n(?==== )', sp_party) if b.startswith('===')]
names, out_p = [], []
for b in sp_blocks:
    n = re.match(r'=== (\w+) ===', b).group(1)
    if n in ('PARTNER_NONE', 'PARTNER_STEVEN'):
        continue
    names.append(n)
    out_p.append(fix_block(b.rstrip(), n) + '\n')
p_ = ours('src/data/battle_partners.party')
keep = [b.rstrip() + '\n' for b in re.split(r'\n(?==== )', read(p_)) if re.match(r'=== (PARTNER_NONE|PARTNER_STEVEN) ===', b)]
write(p_, '\n'.join(keep + out_p))
h_ = ours('include/constants/battle_partner.h'); s_ = read(h_)
s_ = re.sub(r'#define PARTNER_STEVEN 1\n.*?#define PARTNER_COUNT \d+\n', '#define PARTNER_STEVEN 1\n' + ''.join('#define %s %d // Super Emerald: Sinnoh\n' % (n, 2 + i) for i, n in enumerate(names)) + '#define PARTNER_COUNT %d\n' % (2 + len(names)), s_, flags=re.S)
write(h_, s_)

# ---------------------------------------------------------------- wild encounters
def curve(L):
    return int(45 + L * 0.55 + 0.5)
sw = json.load(open(sin('src/data/wild_encounters.json')))
ow = json.load(open(ours('src/data/wild_encounters.json')))
og = ow['wild_encounter_groups'][0]
og['encounters'] = [e for e in og['encounters'] if not e.get('map', '').endswith('_SINNOH')]
n = 0
for e in sw['wild_encounter_groups'][0]['encounters']:
    if e.get('map') not in IDS:
        continue
    e = json.loads(json.dumps(e))
    e['map'] = MAPREN[e['map']]
    e['base_label'] = e['base_label'] + '_Sinnoh'
    for k, v in e.items():
        if isinstance(v, dict) and 'mons' in v:
            v['mons'] = [dict(mm, min_level=curve(mm['min_level']), max_level=max(curve(mm['min_level']), curve(mm['max_level'])),
                              species=mm['species'] if mm['species'] in SPECIES else 'SPECIES_BIDOOF') for mm in v['mons']]
    og['encounters'].append(e); n += 1
write(ours('src/data/wild_encounters.json'), json.dumps(ow, indent=2) + '\n')
STATS['wild_tables'] = n

# ---------------------------------------------------------------- heal locations
hl = json.load(open(ours('src/data/heal_locations.json')))
hl['heal_locations'] = [h for h in hl['heal_locations'] if not h['id'].endswith('_SINNOH')]
for h in json.load(open(sin('src/data/heal_locations.json')))['heal_locations']:
    if h['map'] in IDS and h.get('respawn_map') in IDS and 'TWINLEAF' not in h['id']:
        h = dict(h)
        h['id'] = h['id'] + '_SINNOH'
        h['map'] = MAPREN[h['map']]
        h['respawn_map'] = MAPREN[h['respawn_map']]
        hl['heal_locations'].append(h); STATS['heal_locations'] += 1
write(ours('src/data/heal_locations.json'), json.dumps(hl, indent=2) + '\n')

# ---------------------------------------------------------------- report
rep = ['# Sinnoh import report', '', 'stats: %s' % dict(STATS), '', 'missing classes/pics: %s' % sorted(MISSING), '',
       'fallback reasons:']
rep += ['  %5d %s' % (c, r) for r, c in REJECTS.most_common()]
rep += ['', 'fallbacks:'] + ['  %s %s (%s)' % x for x in FALLBACKS]
rep += ['', 'objects with visibility flags (decide post-story state):']
rep += ['  %s %s %s %s' % x for x in hidden_objects]
write(ours('tools/sfr/sinnoh/import_report.txt'), '\n'.join(rep) + '\n')
print(dict(STATS), 'flags', len(sinnoh_flags), 'trainers', len(sinnoh_trainers))
