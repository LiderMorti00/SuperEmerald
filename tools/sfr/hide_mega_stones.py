#!/usr/bin/env python3
"""Super Emerald: tuck the Hoenn Mega Stones out of sight of each map's main path.

The stones were placed by place_mega_stones.py next to the paths, so many show up on
screen as soon as the player walks by. Here, for every map with a FLAG_SFR_ITEM_* ball:
  - the main path is the union of the shortest walks between the map's entrances
    (warps and connection edges);
  - a ball is "in view" if it falls inside the 15x10-tile screen around some tile of
    that path;
  - balls in view move to a free tile reached the same way (on foot, or only by surfing
    if it needed Surf before), at the same height, away from warps, signs and scenes,
    as far out of view as the map allows, preferably tucked next to an obstacle.
A stone is kept at least GAP tiles away from the map's other stones and item balls.
Item, flag and script stay the same. Run from the repo root:
  python3 tools/sfr/hide_mega_stones.py [--apply] [MapName ...]
"""
import json, struct, sys, os, re, collections

VIEW_X, VIEW_UP, VIEW_DOWN = 7, 4, 5
MAX_MOVE = 14          # stay in the same part of the map (same access, same moment)
GAP = 4                # two stones of one map never closer than this (tiles, either axis)

_mb = [l.strip().rstrip(',').split('=')[0].strip() for l in open('include/constants/metatile_behaviors.h')
       if re.match(r'\s*MB_\w+', l)]
MB = {n: i for i, n in enumerate(_mb)}
ONE_WAY = {MB[n] for n in MB if n.startswith(('MB_JUMP_', 'MB_SLIDE_', 'MB_WATERFALL')) or 'CURRENT' in n
           or n in ('MB_ICE', 'MB_THIN_ICE', 'MB_CRACKED_ICE', 'MB_CRACKED_FLOOR', 'MB_CRACKED_FLOOR_HOLE',
                    'MB_MUDDY_SLOPE', 'MB_DEEP_SAND')}
PLAIN = {MB[n] for n in ('MB_NORMAL', 'MB_SAND', 'MB_ASHGRASS', 'MB_CAVE', 'MB_FOOTPRINTS') if n in MB}

_hdr = open('src/data/tilesets/headers.h').read()
_mt = open('src/data/tilesets/metatiles.h').read()
def attrs(ts):
    body = _hdr[_hdr.index('const struct Tileset %s =' % ts):]
    sym = re.search(r'\.metatileAttributes = (\w+)', body).group(1)
    path = re.search(r'%s\[\] = INCBIN_U16\("([^"]+)"\)' % sym, _mt).group(1)
    b = open(path, 'rb').read()
    return [struct.unpack_from('<H', b, 2 * i)[0] & 0xFF for i in range(len(b) // 2)]

def load(map_dir):
    d = json.load(open(f'data/maps/{map_dir}/map.json'))
    lay = [l for l in json.load(open('data/layouts/layouts.json'))['layouts'] if l.get('id') == d['layout']][0]
    return d, lay, open(lay['blockdata_filepath'], 'rb').read()

def analyse(map_dir):
    d, lay, blocks = load(map_dir)
    w, h = lay['width'], lay['height']
    blk = lambda x, y: struct.unpack_from('<H', blocks, (y * w + x) * 2)[0]
    inside = lambda x, y: 0 <= x < w and 0 <= y < h
    coll = lambda x, y: (blk(x, y) >> 10) & 3
    elev = lambda x, y: blk(x, y) >> 12
    pa, sa = attrs(lay['primary_tileset']), attrs(lay['secondary_tileset'])
    def beh(x, y):
        m = blk(x, y) & 0x3FF
        return pa[m] if m < 512 else (sa[m - 512] if m - 512 < len(sa) else 0)
    objs = d.get('object_events') or []
    stones = [(i, o) for i, o in enumerate(objs) if str(o.get('flag', '')).startswith('FLAG_SFR_ITEM_')]
    solid = {(o['x'], o['y']) for o in objs if not str(o.get('flag', '')).startswith('FLAG_SFR_ITEM_')}
    signs = {(b['x'], b['y']) for b in d.get('bg_events') or []}
    warps = [(e['x'], e['y']) for e in d.get('warp_events') or []]
    coords = {(c['x'], c['y']) for c in d.get('coord_events') or []}
    def walk(x, y, water):
        if not inside(x, y) or coll(x, y) or (x, y) in solid or (x, y) in signs or beh(x, y) in ONE_WAY:
            return False
        return water or elev(x, y) != 1
    def step_ok(a, b):
        e1, e2 = elev(*a), elev(*b)
        return e1 == e2 or 0 in (e1, e2) or 15 in (e1, e2) or 1 in (e1, e2)
    entrances = [p for p in warps if inside(*p)]
    for c in d.get('connections') or []:
        dirn = c['direction']
        edge = {'up': [(x, 0) for x in range(w)], 'down': [(x, h - 1) for x in range(w)],
                'left': [(0, y) for y in range(h)], 'right': [(w - 1, y) for y in range(h)]}.get(dirn, [])
        edge = [p for p in edge if walk(*p, False)]
        if edge:   # one entrance per connection: the middle of its open edge
            entrances.append(edge[len(edge) // 2])
    def bfs(srcs, water):
        dist, par, q = {}, {}, collections.deque()
        for s in srcs:
            dist[s] = 0; par[s] = None; q.append(s)
        while q:
            p = q.popleft()
            for n in ((p[0]+1, p[1]), (p[0]-1, p[1]), (p[0], p[1]+1), (p[0], p[1]-1)):
                if n in dist or not (walk(*n, water) or n in warps) or not step_ok(p, n):
                    continue
                dist[n] = dist[p] + 1; par[n] = p; q.append(n)
        return dist, par
    land, _ = bfs(entrances, False)
    full, _ = bfs(entrances, True)
    main = set()
    for i, a in enumerate(entrances):
        _, par = bfs([a], False)
        for b in entrances[i + 1:]:
            p = b
            while p is not None and p in par:
                main.add(p); p = par[p]
    if not main:
        main = set(entrances)
    def view_score(p):   # > 0: off screen from every main-path tile
        best = None
        for m in main:
            dx = abs(p[0] - m[0]) - VIEW_X
            dy = (m[1] - p[1] - VIEW_UP) if p[1] < m[1] else (p[1] - m[1] - VIEW_DOWN)
            s = max(dx, dy)
            best = s if best is None else min(best, s)
        return best
    taken = solid | signs | coords | set(warps) | {(o['x'], o['y']) for _, o in stones}
    near = {(x + dx, y + dy) for x, y in warps + list(coords) + list(signs) for dx in (-1, 0, 1) for dy in (-1, 0, 1)}
    analyse.view, analyse.land, analyse.elev = view_score, land, elev   # for hand checks
    res = []
    used = set()
    final = {i: (o['x'], o['y']) for i, o in stones}
    balls = [(o['x'], o['y']) for o in objs if o.get('graphics_id') == 'OBJ_EVENT_GFX_ITEM_BALL'
             and not str(o.get('flag', '')).startswith('FLAG_SFR_ITEM_')]
    def spaced(q, i):   # apart from the other stones and from the map's own item balls
        others = [r for j, r in final.items() if j != i] + balls
        return all(max(abs(q[0] - r[0]), abs(q[1] - r[1])) >= GAP for r in others)
    for i, o in stones:
        p = (o['x'], o['y'])
        if p not in full:      # the ball itself sits past a one-way tile (ledge, slide...): leave it
            res.append(dict(map=map_dir, idx=i + 1, item=o['trainer_sight_or_berry_tree_id'], old=p,
                            score=view_score(p), surf=False, moved=None)); continue
        water = p not in land
        reach = full if water else land
        score = view_score(p)
        entry = dict(map=map_dir, idx=i + 1, item=o['trainer_sight_or_berry_tree_id'], old=p, score=score,
                     surf=water, moved=None)
        if score is not None and score > 0 and spaced(p, i):
            res.append(entry); continue
        cands = []
        for q in reach:
            if q in taken or q in near or q in used or not spaced(q, i) or elev(*q) in (0, 1, 15) or elev(*q) != elev(*p):
                continue
            if not (1 <= q[0] < w - 1 and 1 <= q[1] < h - 1):
                continue
            if abs(q[0] - p[0]) + abs(q[1] - p[1]) > MAX_MOVE:
                continue
            if beh(*q) not in PLAIN and beh(*q) != beh(*p):
                continue
            if water and q in land:      # keep it behind Surf if it was
                pass
            s = view_score(q)
            tucked = sum(1 for n in ((q[0]+1, q[1]), (q[0]-1, q[1]), (q[0], q[1]+1), (q[0], q[1]-1)) if not walk(*n, water))
            cands.append((min(s, 6), tucked, reach[q], q))
        if cands:
            cands.sort(reverse=True)
            best = cands[0]
            if score is not None and score > 0:
                ok = best[0] > 0                      # hidden already: only to space it out, staying hidden
            else:
                ok = best[0] > 0 or best[0] - score >= 3 or not spaced(p, i)
            if ok:
                entry['moved'] = best[3]; entry['new_score'] = best[0]; used.add(best[3]); final[i] = best[3]
        res.append(entry)
    return d, res

def main():
    apply = '--apply' in sys.argv
    names = [a for a in sys.argv[1:] if not a.startswith('--')]
    if not names:
        import glob
        names = sorted({os.path.basename(os.path.dirname(p)) for p in glob.glob('data/maps/*/map.json')
                        if 'FLAG_SFR_ITEM_' in open(p).read()})
    for n in names:
        d, res = analyse(n)
        changed = False
        for r in res:
            tag = 'keep (out of view)' if r['moved'] is None and r['score'] > 0 else \
                  ('MOVE %s -> %s (view %d -> %d)' % (r['old'], r['moved'], r['score'], r['new_score']) if r['moved'] else 'keep (no better spot, view %d)' % r['score'])
            print('%-36s %-20s %s%s' % (n, r['item'], tag, ' [surf]' if r['surf'] else ''))
            if r['moved'] and apply:
                o = d['object_events'][r['idx'] - 1]; o['x'], o['y'] = r['moved']; changed = True
        if changed:
            with open(f'data/maps/{n}/map.json', 'w') as f:
                f.write(json.dumps(d, indent=2, ensure_ascii=False) + '\n')

if __name__ == '__main__':
    main()
