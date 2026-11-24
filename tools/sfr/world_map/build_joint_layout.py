# Build the cursor grid of the joint Johto + Kanto PokeNav map from the Johto
# and Kanto grids and the cells LiderMorti00 moved in the joint drawing.
# Writes src/data/region_map/region_map_layout_johto_kanto.h
import os, re, sys
ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', '..')
def lay(n):
    s = open(os.path.join(ROOT, 'src/data/region_map/region_map_layout_%s.h' % n)).read()
    return [[c.strip() for c in r.split(',') if c.strip()] for r in re.findall(r'\{([^{}]*)\}', s)]
W, H = 58, 16              # tiles x 1..58, y 1..16
KANTO_DX, KANTO_DY = 24, -2   # Kanto map tiles -> joint map tiles
grid = {}
J = lay('johto'); K = lay('kanto')
for gy in range(15):
    for gx in range(28):
        m = J[gy][gx]
        if m == 'MAPSEC_NONE': continue
        tx, ty = gx + 1, gy + 2
        if tx >= 26: continue              # east edge of the Johto map is Kanto now
        grid[(tx, ty)] = m
for gy in range(15):
    for gx in range(28):
        m = K[gy][gx]
        if m == 'MAPSEC_NONE': continue
        grid[(gx + 1 + KANTO_DX, gy + 2 + KANTO_DY)] = m
# cells moved or added in the joint drawing
def move(m, frm, to):
    for c in frm:
        if grid.get(c) == m: del grid[c]
    for c in to: grid[c] = m
move('MAPSEC_MT_SILVER', [(21, 7)], [(21, 8)])
move('MAPSEC_ROUTE_28', [(22, 7), (23, 7), (24, 7)], [(22, 8), (23, 8), (24, 8)])
move('MAPSEC_INDIGO_PLATEAU', [(27, 3)], [(25, 3)])
move('MAPSEC_ROUTE_23', [(27, 4), (27, 5), (27, 6), (27, 7)], [(25, 4), (25, 5), (25, 6)])
# Pokemon League Reception Gate (its maps use the Route 26 section)
for c in [(25, 7), (25, 8), (25, 9), (25, 10), (25, 11), (25, 12)]: grid[c] = 'MAPSEC_ROUTE_26'
move('MAPSEC_ROUTE_22', [], [(26, 8), (27, 8), (28, 8)])
# Route 45 / 46 junction one row lower
move('MAPSEC_ROUTE_46', [(18, 8)], [])
move('MAPSEC_ROUTE_45', [], [(19, 9)])
# Route 21 longer, Cinnabar and Route 20 one row lower, Route 19 longer
move('MAPSEC_CINNABAR_ISLAND', [(29, 14)], [(29, 15)])
move('MAPSEC_ROUTE_20', [(x, 14) for x in range(30, 38)], [(x, 15) for x in range(30, 38)])
move('MAPSEC_ROUTE_21', [], [(29, 14)])
move('MAPSEC_ROUTE_19', [], [(37, 14)])
out = ['// Super Emerald: joint Johto + Kanto region map (graphics/pokenav/region_map/map_johto_kanto_source.png)',
       '// Rows are tiles 1..%d, columns tiles 1..%d. Made by tools/sfr/world_map/build_joint_layout.py' % (H, W),
       'static const mapsec_u16_t sRegionMapSections_JohtoKanto[%d][%d] = {' % (H, W)]
rows = []
for ty in range(1, H + 1):
    rows.append('    {' + ', '.join(grid.get((tx, ty), 'MAPSEC_NONE') for tx in range(1, W + 1)) + '}')
out.append(',\n'.join(rows)); out.append('};')
# bounding boxes for every section on the joint map (cursor coordinates: tile - 1, tile - 2)
boxes = {}
for (tx, ty), m in grid.items():
    b = boxes.setdefault(m, [tx, ty, tx, ty])
    b[0] = min(b[0], tx); b[1] = min(b[1], ty); b[2] = max(b[2], tx); b[3] = max(b[3], ty)
out.append('')
out.append('static const struct JointMapSecRect sJointMapSecRects[] = {')
for m in sorted(boxes):
    x0, y0, x1, y1 = boxes[m]
    out.append('    {%s, %d, %d, %d, %d},' % (m, x0 - 1, y0 - 2, x1 - x0 + 1, y1 - y0 + 1))
out.append('};')
open(os.path.join(ROOT, 'src/data/region_map/region_map_layout_johto_kanto.h'), 'w').write('\n'.join(out) + '\n')
if len(sys.argv) > 1:
    sys.path.insert(0, '/tmp')
    from cells import grid as cg
    g = cg(sys.argv[1])
    for ty in range(20):
        for tx in range(60):
            drawn = g[ty][tx] in 'RB=~'
            name = grid.get((tx, ty))
            if drawn and not name: print('drawn, no name', (tx, ty), g[ty][tx])
            if name and not drawn and g[ty][tx] != '-': print('name, not drawn', (tx, ty), name)
