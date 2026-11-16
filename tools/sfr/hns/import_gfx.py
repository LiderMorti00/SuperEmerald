#!/usr/bin/env python3
"""Super Emerald: import the HnS overworld sprites used by the Johto maps (plus the
gym leaders, Elite Four and rivals needed by our scripts).

Usage (repo root): python3 -I tools/sfr/hns/import_gfx.py [--hns /path/to/pokehns-expansion]

Writes src/data/object_events/hns/*.h, copies the pngs/palettes, and adds the
OBJ_EVENT_GFX_*_HNS ids and OBJ_EVENT_PAL_TAG_*_HNS tags between "Super Emerald: HnS"
markers. Safe to run again.
"""
import json, os, re, shutil, sys
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from common import HNS, hns, ours, read, write, johto_maps

EXTRA = '''GOLD_NORMAL JASMINE WHITNEY FALKNER BUGSY MORTY CHUCK PRYCE CLAIR WILL KAREN KOGA
BRUNO LANCE SILVER ELM KURT EUSINE MOM PROF_OAK RED_NORMAL'''.split()
PAL_TAG_BASE = 0x11A1
BEGIN = '// Super Emerald: HnS begin'
END = '// Super Emerald: HnS end'

# ---- what we need
need = set('OBJ_EVENT_GFX_%s_HNS' % x for x in EXTRA)
for grp, m in johto_maps():
    for o in json.load(open(hns('data/maps', m, 'map.json'))).get('object_events', []):
        g = o.get('graphics_id', '')
        if g.endswith('_HNS'):
            need.add(g)

H_PTR = read(hns('src/data/object_events/object_event_graphics_info_pointers.h'))
H_INFO = read(hns('src/data/object_events/object_event_graphics_info.h'))
H_PICS = read(hns('src/data/object_events/object_event_pic_tables.h'))
H_GFX = read(hns('src/data/object_events/object_event_graphics.h'))
H_ANIM = read(hns('src/data/object_events/object_event_anims.h'))
H_MOVE = read(hns('src/event_object_movement.c'))
H_EVOBJ = read(hns('include/constants/event_objects.h'))
O_ANIM = read(ours('src/data/object_events/object_event_anims.h'))

def block(text, name):
    """Return 'static const ... name[] = { ... };' block."""
    m = re.search(r'(?:static )?const [^\n=]*\b%s\[\][^=]*=\s*\{' % re.escape(name), text)
    if not m:
        raise SystemExit('missing ' + name)
    i = m.end(); depth = 1
    while depth:
        c = text[i]
        depth += c == '{'
        depth -= c == '}'
        i += 1
    j = text.index(';', i) + 1
    return text[m.start():j]

infos, pics, gfxsyms, paltags, anims = [], [], [], set(), []
# lamp objects use HnS field-effect pics; our DNS window lights replace them
SKIP = {'OBJ_EVENT_GFX_SMALL_LIGHT_HNS', 'OBJ_EVENT_GFX_POKE_CENTER_LIGHT_HNS', 'OBJ_EVENT_GFX_MART_LIGHT_HNS', 'OBJ_EVENT_GFX_LIGHT_HNS'}
O_GFX = read(ours('src/data/object_events/object_event_graphics.h'))
H_RULES = read(hns('spritesheet_rules.mk'))
ids = sorted(need - SKIP)
for gid in ids:
    sym = re.search(r'\[%s\]\s*=\s*&(\w+)' % gid, H_PTR).group(1)
    m = re.search(r'const struct ObjectEventGraphicsInfo %s = \{(.*?)\};' % sym, H_INFO, re.S)
    body = m.group(1)
    if '.tileTag' in body:
        kv = dict((k, v.strip()) for k, v in re.findall(r'\.(\w+)\s*=\s*([^,\n]+)', body))
        tile, pal, refl, size = kv['tileTag'], kv['paletteTag'], kv['reflectionPaletteTag'], kv['size']
        w, h, slot, shadow = kv['width'], kv['height'], kv['paletteSlot'], kv['shadowSize']
        inanim, tracks, oam, subs = kv['inanimate'], kv['tracks'], kv['oam'], kv['subspriteTables']
        anim, images, affine = kv['anims'], kv['images'], kv.get('affineAnims', 'NULL')
    else:
        f = [x.strip() for x in body.split(',')]
        (tile, pal, refl, size, w, h, slot, shadow, inanim, comp, tracks, oam, subs, anim, images, affine) = f[:16]
    infos.append((gid, sym, dict(tile=tile, pal=pal, refl=refl, size=size, w=w, h=h, slot=slot,
                                 shadow=shadow, inanim=inanim, tracks=tracks, oam=oam, subs=subs,
                                 anim=anim, images=images, affine=affine)))
    paltags.update(t for t in (pal, refl) if t.endswith('_HNS'))
    pt = block(H_PICS, images)
    pics.append(pt)
    gfxsyms += re.findall(r'gObjectEventPic_\w+', pt)
    if anim.endswith('_hns') and anim not in [a for a, _ in anims]:
        anims.append((anim, None))

# ---- anim tables (and the sAnim_* arrays they use) that only HnS has
anim_text = []
for a, _ in anims:
    b = block(H_ANIM, a)
    for sub in re.findall(r'\bsAnim_\w+', b):
        if not re.search(r'\b%s\[\]' % sub, O_ANIM) and sub not in ''.join(anim_text):
            anim_text.append(block(H_ANIM, sub))
    anim_text.append(b)

# frame size of each pic, from the graphics info that uses it
PIC_DIMS = {}
for gid, sym, d in infos:
    pt = block(H_PICS, d['images'])
    for pic in re.findall(r'gObjectEventPic_\w+', pt):
        try:
            PIC_DIMS.setdefault(pic, '-mwidth %d -mheight %d' % (int(d['w']) // 8, int(d['h']) // 8))
        except ValueError:
            pass

# ---- palettes
tag_to_pal = dict((t, p) for p, t in re.findall(r'\{(gObjectEventPal_\w+),\s*(OBJ_EVENT_PAL_TAG_\w+_HNS)\}', H_MOVE))
tags = sorted(paltags)
pal_syms = [tag_to_pal[t] for t in tags]

# ---- graphics INCBINs + copy files
gfx_lines = []
for s in sorted(set(gfxsyms)) + pal_syms:
    if re.search(r'\b%s\[\]' % s, O_GFX):
        continue  # already in our build
    m = re.search(r'const u(?:16|32) %s\[\] = INCBIN_U(?:16|32)\(([^)]+)\);' % s, H_GFX)
    if not m:
        raise SystemExit('no INCBIN for ' + s)
    files = re.findall(r'"([^"]+)"', m.group(1))
    for path in files:
        src = path.replace('.4bpp', '.png').replace('.gbapal', '.pal')
        if not os.path.exists(hns(src)):
            raise SystemExit('missing file ' + src)
        os.makedirs(os.path.dirname(ours(src)), exist_ok=True)
        shutil.copyfile(hns(src), ours(src))
    first = files[0]
    if first.endswith('.gbapal'):
        gfx_lines.append('const u16 %s[] = INCGFX_U16("%s", ".gbapal");' % (s, first.replace('.gbapal', '.pal')))
    else:
        # 1.17 converts sheets on the fly: frame size in 8x8 tiles from HnS rules or the sprite size
        rule = re.search(r'%s: %%.4bpp: %%.png\n\t\$\(GFX\) \$< \$@ (-mwidth \d+ -mheight \d+)' % re.escape(first.replace('graphics/object_events/pics', '$(OBJEVENTGFXDIR)')), H_RULES)
        opts = rule.group(1) if rule else PIC_DIMS.get(s, '')
        args = ', "%s"' % opts if opts else ''
        gfx_lines.append('const u32 %s[] = INCGFX_U32("%s", ".4bpp"%s);' % (s, first.replace('.4bpp', '.png'), args))

# ---- write C data
hdr = '// Super Emerald: generated by tools/sfr/hns/import_gfx.py from Pokemon Heart & Soul.\n\n'
write(ours('src/data/object_events/hns/graphics.h'), hdr + '\n'.join(gfx_lines) + '\n')
write(ours('src/data/object_events/hns/pic_tables.h'), hdr + '\n\n'.join(pics) + '\n')
write(ours('src/data/object_events/hns/anims.h'), hdr + '\n\n'.join(anim_text) + '\n')
out = [hdr]
for gid, sym, d in infos:
    out.append('''const struct ObjectEventGraphicsInfo %s = {
    .tileTag = %s,
    .paletteTag = %s,
    .reflectionPaletteTag = %s,
    .size = %s,
    .width = %s,
    .height = %s,
    .paletteSlot = %s,
    .shadowSize = %s,
    .inanimate = %s,
    .tracks = %s,
    .compressionMode = OBJECT_EVENT_COMPRESSION_NONE,
    .oam = %s,
    .subspriteTables = %s,
    .anims = %s,
    .images = %s,
    .affineAnims = %s,
};
''' % (sym, d['tile'], d['pal'], d['refl'], d['size'], d['w'], d['h'], d['slot'], d['shadow'],
       d['inanim'], d['tracks'], d['oam'], d['subs'], d['anim'], d['images'], d['affine']))
write(ours('src/data/object_events/hns/graphics_info.h'), '\n'.join(out))

# ---- constants
p = ours('include/constants/event_objects.h'); s = read(p)
s = re.sub(r'\n    ' + re.escape(BEGIN) + r'.*?' + re.escape(END) + r'\n', '\n', s, flags=re.S)
s = s.replace('    NUM_OBJ_EVENT_GFX,\n', '    %s\n%s    %s\n    NUM_OBJ_EVENT_GFX,\n'
              % (BEGIN, ''.join('    %s,\n' % g for g in ids), END), 1)
s = re.sub(re.escape(BEGIN) + r' \(tags\).*?' + re.escape(END) + r' \(tags\)\n', '', s, flags=re.S)
tagdefs = ''.join('#define %-40s 0x%04X\n' % (t, PAL_TAG_BASE + i) for i, t in enumerate(tags))
assert PAL_TAG_BASE + len(tags) < 0x11FF
anchor = '#define OBJ_EVENT_PAL_TAG_NONE'
s = s.replace(anchor, '%s (tags)\n%s#define OBJ_EVENT_GFX_MON_BASE OBJ_EVENT_MON // HnS map data\n%s (tags)\n%s'
              % (BEGIN, tagdefs, END, anchor), 1)
write(p, s)

# ---- pointers
p = ours('src/data/object_events/object_event_graphics_info_pointers.h'); s = read(p)
s = re.sub(re.escape(BEGIN) + r'.*?' + re.escape(END) + r'\n', '', s, flags=re.S)
ext = ''.join('extern const struct ObjectEventGraphicsInfo %s;\n' % sym for _, sym, _ in infos)
i = s.index('const struct ObjectEventGraphicsInfo *const gObjectEventGraphicsInfoPointers')
s = s[:i] + BEGIN + '\n' + ext + END + '\n\n' + s[i:]
ent = ''.join('    [%s] = &%s,\n' % (g, sym) for g, sym, _ in infos)
j = s.index('{', s.index('gObjectEventGraphicsInfoPointers')) + 2
s = s[:j] + '    ' + BEGIN + '\n' + ent + '    ' + END + '\n' + s[j:]
write(p, s)

# ---- event_object_movement.c: includes + palettes
p = ours('src/event_object_movement.c'); s = read(p)
s = re.sub(r'\n?' + re.escape(BEGIN) + r'.*?' + re.escape(END) + r'\n', '\n', s, flags=re.S)
s = s.replace('#include "data/object_events/object_event_graphics.h"\n',
              '#include "data/object_events/object_event_graphics.h"\n%s\n#include "data/object_events/hns/graphics.h"\n%s\n' % (BEGIN, END), 1)
s = s.replace('#include "data/object_events/object_event_anims.h"\n',
              '#include "data/object_events/object_event_anims.h"\n%s\n#include "data/object_events/hns/anims.h"\n#include "data/object_events/hns/pic_tables.h"\n%s\n' % (BEGIN, END), 1)
s = s.replace('#include "data/object_events/object_event_graphics_info.h"\n',
              '#include "data/object_events/object_event_graphics_info.h"\n%s\n#include "data/object_events/hns/graphics_info.h"\n%s\n' % (BEGIN, END), 1)
k = s.index('{', s.index('static const struct SpritePalette sObjectEventSpritePalettes[]')) + 2
s = s[:k] + BEGIN + '\n' + ''.join('    {%s, %s},\n' % (ps, t) for ps, t in zip(pal_syms, tags)) + END + '\n' + s[k:]
write(p, s)
print('gfx', len(ids), 'palettes', len(tags), 'pics', len(set(gfxsyms)), 'anims', len(anims))
