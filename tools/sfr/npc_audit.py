#!/usr/bin/env python3
"""Super Emerald: find (and optionally remove) object events that can never appear in
Kanto, Johto, Sinnoh and the Sevii Islands.

An object can never appear when, in a normal game:
- its hide flag is set before the player can first see its map (new game, the region's
  world-state scripts run on entering the region, or its map's on-transition script), and
- no reachable script clears that flag, no C code touches it (FlagClear, tables...), and
- no reachable script spawns it with addobject / showobjectat.
Reachable scripts start from C, asm tables, map headers, the events of every object
that can appear, bg events and coord events whose var value can actually happen.
The objects that cannot appear are excluded from the start and the set is refined until
it stops changing.

An object is removed only if, besides, no reachable script names its local ID (or its
number), no clone targets its map, and the map's scripts use no numeric local IDs (the
IDs of the following objects move down by one). The other never-shown objects are listed
as "doubtful" with the reason.

Usage (repo root):
  python3 tools/sfr/npc_audit.py            report (tools/sfr/data/npc_audit.txt)
  python3 tools/sfr/npc_audit.py --apply    also remove the confirmed objects and the map
                                            script labels nothing reaches any more
"""
import collections, glob, json, os, re, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
os.chdir(ROOT)
APPLY = '--apply' in sys.argv

INIT_SCRIPTS = ['EventScript_ResetAllMapFlagsFrlg', 'EventScript_ResetAllMapFlags',
                'SE_EventScript_InitKantoPostgame', 'SE_EventScript_KantoWorldState',
                'SE_EventScript_InitJohto', 'SE_EventScript_JohtoWorldState',
                'SE_EventScript_InitSinnoh', 'SE_EventScript_SinnohWorldState',
                'SE_EventScript_SinnohOnTransition']
SPAWN_CMDS = ('addobject', 'showobjectat', 'addobject_frlg')
LABEL_RE = re.compile(r'^(\w+)::?', re.M)
TOKEN_RE = re.compile(r'\b[A-Za-z_]\w*\b')
TERMINATORS = ('end', 'return', 'goto ', 'step_end', 'releaseall', '.byte 0', 'goto_if_unset', 'goto_if_set')


# ---------------------------------------------------------------- scripts
def load_inc():
    files = sorted(glob.glob('data/maps/*/scripts.inc') + glob.glob('data/maps/*/text.inc')
                   + glob.glob('data/scripts/*.inc') + glob.glob('data/text/*.inc'))
    blocks, order, fileof = {}, [], {}
    for f in files:
        s = open(f, encoding='utf-8', errors='replace').read()
        ms = list(LABEL_RE.finditer(s))
        for i, m in enumerate(ms):
            end = ms[i + 1].start() if i + 1 < len(ms) else len(s)
            name = m.group(1)
            if name in blocks:
                continue
            blocks[name] = (f, m.start(), end, s[m.end():end])
            order.append(name)
            fileof[name] = f
    return blocks, order


def body_lines(body):
    out = []
    for l in body.split('\n'):
        l = l.split('@')[0].strip()
        if l:
            out.append(l)
    return out


def falls_through(body):
    ls = body_lines(body)
    if not ls:
        return True
    last = ls[-1]
    if last.startswith('.'):
        return False
    return not (last == 'end' or last == 'return' or last.startswith('goto ') or last == 'step_end'
                or last.startswith('end') or last.startswith('.byte 0'))


blocks, order = load_inc()
labels = set(blocks)
nxt = {order[i]: order[i + 1] for i in range(len(order) - 1) if blocks[order[i]][0] == blocks[order[i + 1]][0]}
refs = {}
for name, (f, a, b, body) in blocks.items():
    toks = set(TOKEN_RE.findall(re.sub(r'"[^"]*"', '', body.split('@')[0] if False else body)))
    r = {t for t in toks if t in labels and t != name}
    if falls_through(body) and name in nxt:
        r.add(nxt[name])
    refs[name] = r

# labels named outside the .inc files (C, asm, headers): always reachable
outside = set()
for f in glob.glob('src/**/*.c', recursive=True) + glob.glob('src/**/*.h', recursive=True) \
        + glob.glob('include/**/*.h', recursive=True) + glob.glob('data/*.s') + glob.glob('asm/*.s'):
    if 'sfr_obtainable' in f:
        continue
    s = open(f, encoding='utf-8', errors='replace').read()
    for t in set(TOKEN_RE.findall(s)):
        if t in labels:
            outside.add(t)
csrc = ''.join(open(f, encoding='utf-8', errors='replace').read()
               for f in glob.glob('src/**/*.c', recursive=True) + glob.glob('src/**/*.h', recursive=True))
ctokens = set(TOKEN_RE.findall(csrc))


# ---------------------------------------------------------------- maps
def zone_of(mapname, mapsec):
    if mapname.endswith('_hns'):
        return 'Johto'
    if mapname.endswith('_sinnoh'):
        return 'Sinnoh'
    if mapname.endswith('_Frlg'):
        return 'Sevii' if mapsec in SEVII else 'Kanto'
    return None


regions_c = open('src/regions.c').read()
SEVII = set()
for sub, body in re.findall(r'\[KANTO_SUBREGION_(SEVII\w+)\]\s*=\s*\{(.*?)\}', regions_c, re.S):
    SEVII |= set(re.findall(r'MAPSEC_\w+', body)) - {'MAPSEC_NONE'}

maps = {}
for p in sorted(glob.glob('data/maps/*/map.json')):
    d = json.load(open(p))
    name = p.split('/')[2]
    z = zone_of(name, d.get('region_map_section'))
    maps[name] = (p, d, z)

clone_targets = set()
for name, (p, d, z) in maps.items():
    for o in d.get('object_events') or []:
        if o.get('type') == 'clone':
            clone_targets.add(o.get('target_map'))

# objects of the four zones
objs = []   # (map, index(1-based), obj)
for name, (p, d, z) in maps.items():
    if not z:
        continue
    for i, o in enumerate(d.get('object_events') or [], 1):
        objs.append((name, i, o))


# ---------------------------------------------------------------- flags and vars
def cmd_args(line):
    parts = line.split(None, 1)
    return parts[0], [a.strip() for a in parts[1].split(',')] if len(parts) > 1 else []


init_set, init_var = set(), {}
def run_init(label, seen):
    if label in seen or label not in blocks:
        return
    seen.add(label)
    for l in body_lines(blocks[label][3]):
        c, a = cmd_args(l)
        if c == 'setflag' and a:
            init_set.add(a[0])
        elif c == 'setvar' and len(a) > 1:
            init_var[a[0]] = a[1]
        elif c == 'call' and a:
            run_init(a[0], seen)
        elif c.startswith(('goto_if', 'call_if', 'goto')):
            break       # anything after a branch is not guaranteed
for s in INIT_SCRIPTS:
    run_init(s, set())

# on-transition setflags of each map (before any branch)
trans_set = collections.defaultdict(set)
for name, (p, d, z) in maps.items():
    if not z:
        continue
    ms = blocks.get(name + '_MapScripts')
    if not ms:
        continue
    for l in body_lines(ms[3]):
        c, a = cmd_args(l)
        if c == 'map_script' and len(a) > 1 and a[0] in ('MAP_SCRIPT_ON_TRANSITION', 'MAP_SCRIPT_ON_LOAD'):
            for ll in body_lines(blocks.get(a[1], ('', 0, 0, ''))[3]):
                cc, aa = cmd_args(ll)
                if cc.startswith(('goto', 'call')) or cc == 'end':
                    break
                if cc == 'setflag' and aa:
                    trans_set[name].add(aa[0])


def obj_script(o):
    s = o.get('script', '0')
    return s if s in labels else None


# ---------------------------------------------------------------- fixpoint
def reachable(excluded_scripts, dead_coords):
    entries = set(outside)
    for name, (p, d, z) in maps.items():
        entries.add(name + '_MapScripts')
        for i, o in enumerate(d.get('object_events') or [], 1):
            s = obj_script(o)
            if s and (name, i) not in excluded_scripts:
                entries.add(s)
        for e in (d.get('bg_events') or []):
            if e.get('script') in labels:
                entries.add(e['script'])
        for j, e in enumerate(d.get('coord_events') or []):
            if e.get('script') in labels and (name, j) not in dead_coords:
                entries.add(e['script'])
    entries &= labels
    seen = set(entries); st = list(entries)
    while st:
        x = st.pop()
        for y in refs.get(x, ()):
            if y not in seen:
                seen.add(y); st.append(y)
    return seen


def scan(reach):
    """flag clears, spawns, var values and local ID uses in the reachable scripts."""
    cleared, spawned, varvals, named = set(), set(), collections.defaultdict(set), collections.defaultdict(set)
    for lab in reach:
        f = blocks[lab][0]
        for l in body_lines(blocks[lab][3]):
            c, a = cmd_args(l)
            if c == 'clearflag' and a:
                cleared.add(a[0])
            if c in SPAWN_CMDS and a:
                spawned.add((f, a[0]))
            if c == 'setvar' and len(a) > 1:
                varvals[a[0]].add(a[1])
            if c in ('addvar', 'subvar', 'copyvar', 'specialvar') and a:
                varvals[a[0]].add('*')
            for t in TOKEN_RE.findall(l):
                if t.startswith('LOCALID_'):
                    named[t].add(lab)
    return cleared, spawned, varvals, named


flagged = [(n, i, o) for n, i, o in objs if str(o.get('flag', '0')) not in ('0', '', 'None')]
hidden0 = {}
for n, i, o in flagged:
    fl = o['flag']
    if fl.startswith(('FLAG_TEMP', 'FLAG_DAILY')):
        continue
    if fl in init_set or fl in trans_set[n]:
        hidden0[(n, i)] = o

# coord events that can never fire: their var never takes the value (setvar anywhere)
_, _, allvals, _ = None, None, None, None
allvals = collections.defaultdict(set)
for lab in blocks:
    for l in body_lines(blocks[lab][3]):
        c, a = cmd_args(l)
        if c == 'setvar' and len(a) > 1:
            allvals[a[0]].add(a[1])
        if c in ('addvar', 'subvar', 'copyvar', 'specialvar', 'getpartysize', 'random') and a:
            allvals[a[0]].add('*')
dead_coords = set()
for name, (p, d, z) in maps.items():
    for j, e in enumerate(d.get('coord_events') or []):
        v, val = e.get('var'), str(e.get('var_value'))
        if not v or v in ctokens or v.startswith('VAR_TEMP') or v == 'VAR_RESULT':
            continue
        possible = {init_var[v]} if v in init_var else {'0'}
        possible |= allvals.get(v, set())
        if '*' not in possible and val not in possible:
            dead_coords.add((name, j))

cand = dict(hidden0)
for _ in range(30):
    reach = reachable(set(cand), dead_coords)
    cleared, spawned, varvals, named = scan(reach)
    keep = {}
    for (n, i), o in cand.items():
        fl = o['flag']
        if fl in cleared or fl in ctokens:
            continue
        lid = o.get('local_id')
        f = maps[n][0].replace('map.json', 'scripts.inc')
        if lid and (f, lid) in spawned:
            continue
        keep[(n, i)] = o
    if keep.keys() == cand.keys():
        break
    cand = keep

reach = reachable(set(cand), dead_coords)
cleared, spawned, varvals, named = scan(reach)


# ---------------------------------------------------------------- removal check
def map_files(n):
    return [f for f in (f'data/maps/{n}/scripts.inc', f'data/maps/{n}/text.inc') if os.path.exists(f)]


NUMERIC_CMDS = ('applymovement', 'removeobject', 'addobject', 'showobjectat', 'hideobjectat',
                'turnobject', 'setobjectxy', 'setobjectxyperm', 'setobjectmovementtype',
                'setobjectsubpriority', 'resetobjectsubpriority', 'faceplayer_obj', 'copyobjectxytoperm',
                'waitmovement', 'getobjectxy', 'createvobject')
numeric_maps = set()
for n in maps:
    for f in map_files(n):
        for l in open(f, encoding='utf-8', errors='replace'):
            l = l.split('@')[0].strip()
            c, a = cmd_args(l) if l else ('', [])
            if c in NUMERIC_CMDS and a and re.fullmatch(r'\d+', a[0]) and a[0] not in ('0', '255'):
                numeric_maps.add(n)
            if 'VAR_LAST_TALKED' in l and re.search(r'VAR_LAST_TALKED\s*,\s*\d+', l):
                numeric_maps.add(n)

confirmed, doubtful = [], []
for (n, i), o in sorted(cand.items()):
    why = []
    lid = o.get('local_id')
    if lid and named.get(lid):
        why.append('local ID named by reachable ' + ', '.join(sorted(named[lid])[:3]))
    if maps[n][1]['id'] in clone_targets:
        why.append('cloned by a connected map')
    if n in numeric_maps:
        why.append('map scripts use numeric local IDs')
    (doubtful if why else confirmed).append((n, i, o, why))

# ---------------------------------------------------------------- report
zones = collections.Counter(z for n, (p, d, z) in maps.items() if z)
lines = ['Super Emerald NPC audit (tools/sfr/npc_audit.py)', '']
lines.append('Maps checked: ' + ', '.join(f'{z} {c}' for z, c in sorted(zones.items())))
lines.append(f'Objects checked: {len(objs)}; hidden at start: {len(hidden0)}; never shown: {len(cand)}')
lines.append(f'Confirmed for removal: {len(confirmed)}; doubtful: {len(doubtful)}')
lines.append('')
lines.append('== Confirmed')
for n, i, o, why in confirmed:
    lines.append(f"{n} #{i} {o.get('local_id') or ''} {o['graphics_id']} ({o['x']},{o['y']}) {o['flag']} {o.get('script')}")
lines.append('')
lines.append('== Doubtful (kept)')
for n, i, o, why in doubtful:
    lines.append(f"{n} #{i} {o.get('local_id') or ''} {o['graphics_id']} ({o['x']},{o['y']}) {o['flag']} {o.get('script')}: {'; '.join(why)}")
os.makedirs('tools/sfr/data', exist_ok=True)
open('tools/sfr/data/npc_audit.txt', 'w').write('\n'.join(lines) + '\n')
print('\n'.join(lines[:6]))

if not APPLY:
    sys.exit(0)

# ---------------------------------------------------------------- apply
by_map = collections.defaultdict(list)
for n, i, o, why in confirmed:
    by_map[n].append(i)
for n, idx in by_map.items():
    p, d, z = maps[n]
    d['object_events'] = [o for i, o in enumerate(d['object_events'], 1) if i not in idx]
    open(p, 'w').write(json.dumps(d, indent=2, ensure_ascii=False) + '\n')
    maps[n] = (p, d, z)

# coord events of the edited maps that can never fire go too (their scripts may name the
# removed objects)
dropped_coords = 0
for n in by_map:
    p, d, z = maps[n]
    ce = d.get('coord_events') or []
    keep = [e for j, e in enumerate(ce) if (n, j) not in dead_coords]
    if len(keep) != len(ce):
        dropped_coords += len(ce) - len(keep)
        d['coord_events'] = keep
        open(p, 'w').write(json.dumps(d, indent=2, ensure_ascii=False) + '\n')

# drop the labels of the edited maps' files that nothing reaches any more, unless something
# that stays (any script, map.json, C or asm) still names them
cand_labels = set()
for n in by_map:
    for f in map_files(n):
        for lab, b in blocks.items():
            if b[0] == f and not lab.endswith('_MapScripts'):
                cand_labels.add(lab)
reach = reachable(set(), set(dead_coords))
cand_labels -= reach
json_tokens = set()
for name, (p, d, z) in maps.items():
    json_tokens |= set(TOKEN_RE.findall(json.dumps(d)))
while True:
    used = set(outside) | (json_tokens & labels)
    for lab, b in blocks.items():
        if lab in cand_labels:
            continue
        used |= refs.get(lab, set())
    stay = cand_labels & used
    if not stay:
        break
    cand_labels -= stay
removed_labels = 0
for n in by_map:
    for f in map_files(n):
        s = open(f, encoding='utf-8').read()
        ms = list(LABEL_RE.finditer(s))
        cut = []
        for k, mm in enumerate(ms):
            if mm.group(1) not in cand_labels:
                continue
            end = ms[k + 1].start() if k + 1 < len(ms) else len(s)
            body = s[mm.end():end]
            if '.macro' in body:            # keep a macro defined at the end of the block
                end = mm.end() + body.index('.macro')
            cut.append((mm.start(), end))
        for a2, b2 in reversed(cut):
            s = s[:a2] + s[b2:]
        removed_labels += len(cut)
        s = re.sub(r'\n{3,}', '\n\n', s)
        open(f, 'w', encoding='utf-8').write(s)
print(f'removed {len(confirmed)} objects from {len(by_map)} maps, {dropped_coords} dead coord events '
      f'and {removed_labels} unreachable labels')
