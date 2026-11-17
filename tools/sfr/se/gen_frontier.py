import re,glob,os,json,collections,hashlib
os.chdir('/home/claude/superfirered')
# ---- species info
SP={}
for f in sorted(glob.glob('src/data/pokemon/species_info/gen_*_families.h')):
    s=open(f).read()
    for m in re.finditer(r'\n    \[(SPECIES_\w+)\]\s*=\s*\{(.*?)\n    \},',s,re.S):
        name,b=m.group(1),m.group(2)
        g=lambda k: (re.search(r'\.'+k+r'\s*=\s*([^,\n]+)',b) or [None,None])[1]
        try:
            st=[int(g(k)) for k in ('baseHP','baseAttack','baseDefense','baseSpeed','baseSpAttack','baseSpDefense')]
        except Exception: continue
        types=re.findall(r'TYPE_\w+',(re.search(r'\.types\s*=\s*MON_TYPES\(([^)]*)\)',b) or [None,''])[1] or '')
        SP[name]=dict(stats=st,types=types,lvl=g('levelUpLearnset'),tm=g('teachableLearnset'),
            evo='.evolutions' in b and 'EVOLUTION(' in b,
            leg=bool(re.search(r'\.(isLegendary|isMythical|isUltraBeast|isParadox|isRestrictedLegendary|isSubLegendary)\s*=\s*TRUE',b)),
            restricted=bool(re.search(r'\.isRestrictedLegendary\s*=\s*TRUE|\.isMythical\s*=\s*TRUE',b)),
            banned=bool(re.search(r'\.isFrontierBanned\s*=\s*TRUE',b)),
            dex=g('natDexNum'), name=(re.search(r'\.speciesName\s*=\s*_\("([^"]*)"\)',b) or [None,''])[1],
            form=bool(re.search(r'\.(isMegaEvolution|isPrimalReversion|isGigantamax|isTeraForm|isUltraBurst|isTotem)\s*=\s*TRUE',b)))
# ---- learnsets
LS={}
for f in glob.glob('src/data/pokemon/level_up_learnsets/*.h'):
    for m in re.finditer(r'static const struct LevelUpMove (\w+)\[\]\s*=\s*\{(.*?)\};',open(f).read(),re.S):
        LS[m.group(1)]=[(int(a),b) for a,b in re.findall(r'LEVEL_UP_MOVE\(\s*(\d+),\s*(MOVE_\w+)\)',m.group(2))]
TM={}
for m in re.finditer(r'static const u16 (\w+)\[\]\s*=\s*\{(.*?)\};',open('src/data/pokemon/teachable_learnsets.h').read(),re.S):
    TM[m.group(1)]=re.findall(r'MOVE_\w+',m.group(2))
# ---- moves
MV={}
s=open('src/data/moves_info.h').read()
for m in re.finditer(r'\n    \[(MOVE_\w+)\]\s*=\s*\{(.*?)\n    \},',s,re.S):
    b=m.group(2)
    def gi(k,d=0):
        x=re.search(r'\.'+k+r'\s*=\s*([^,\n]+)',b)
        if not x: return d
        v=x.group(1).strip()
        mm=re.search(r'(\d+)\s*:\s*(\d+)\s*$',v)  # B_UPDATED ? a : b
        if mm: v=mm.group(1)
        try: return int(v)
        except: return d
    t=re.search(r'\.type\s*=\s*(TYPE_\w+)',b); c=re.search(r'\.category\s*=\s*(DAMAGE_CATEGORY_\w+)',b)
    MV[m.group(1)]=dict(power=gi('power'),acc=gi('accuracy',100) or 100,type=t.group(1) if t else 'TYPE_NORMAL',cat=c.group(1) if c else 'DAMAGE_CATEGORY_STATUS',
        z=bool(re.search(r'isZMove|isMaxMove|\.effect = EFFECT_MAX',b)), charge=bool(re.search(r'EFFECT_TWO_TURNS_ATTACK|EFFECT_SEMI_INVULNERABLE|MOVE_EFFECT_RECHARGE|EFFECT_EXPLOSION|EFFECT_SOLAR_BEAM|EFFECT_FUTURE_SIGHT|EFFECT_FOCUS_PUNCH|EFFECT_DREAM_EATER|EFFECT_SNORE|EFFECT_LAST_RESORT|EFFECT_BELCH|EFFECT_SPIT_UP|EFFECT_FINAL_GAMBIT|EFFECT_SYNCHRONOISE|EFFECT_MIND_BLOWN|EFFECT_STEEL_BEAM|EFFECT_FAKE_OUT|EFFECT_SKY_DROP|EFFECT_GEOMANCY|EFFECT_METEOR_BEAM|EFFECT_DOUBLE_SHOCK|EFFECT_SUCKER_PUNCH|EFFECT_UPPER_HAND|EFFECT_FIRST_TURN_ONLY|EFFECT_HIT_ESCAPE|EFFECT_COUNTER|EFFECT_MIRROR_COAT|EFFECT_METAL_BURST|EFFECT_ENDEAVOR|EFFECT_OHKO|EFFECT_SHELL_TRAP|EFFECT_BIDE|EFFECT_HIDDEN_POWER|EFFECT_NATURAL_GIFT|EFFECT_FLING|EFFECT_POLTERGEIST|EFFECT_DYNAMAX',b)))
BAD={'MOVE_STRUGGLE','MOVE_HYPER_BEAM','MOVE_GIGA_IMPACT','MOVE_THRASH','MOVE_OUTRAGE','MOVE_PETAL_DANCE','MOVE_RAGING_FURY','MOVE_SELF_DESTRUCT','MOVE_EXPLOSION','MOVE_MISTY_EXPLOSION','MOVE_HEAD_SMASH','MOVE_LIGHT_OF_RUIN','MOVE_TERA_BLAST','MOVE_STEEL_ROLLER','MOVE_RISING_VOLTAGE','MOVE_EXPANDING_FORCE','MOVE_GRASSY_GLIDE','MOVE_SPLISHY_SPLASH','MOVE_FLOATY_FALL','MOVE_ZIPPY_ZAP','MOVE_DOUBLE_IRON_BASH','MOVE_ROLLOUT','MOVE_ICE_BALL','MOVE_UPROAR','MOVE_DIG','MOVE_FLY','MOVE_DIVE','MOVE_BOUNCE','MOVE_PHANTOM_FORCE','MOVE_SHADOW_FORCE','MOVE_SOLAR_BEAM','MOVE_SOLAR_BLADE','MOVE_SKY_ATTACK','MOVE_RAZOR_WIND','MOVE_SKULL_BASH','MOVE_FUTURE_SIGHT','MOVE_DOOM_DESIRE','MOVE_FOCUS_PUNCH','MOVE_HYDRO_CANNON','MOVE_BLAST_BURN','MOVE_FRENZY_PLANT','MOVE_ROCK_WRECKER','MOVE_ROAR_OF_TIME','MOVE_PRISMATIC_LASER','MOVE_ETERNABEAM','MOVE_METEOR_ASSAULT','MOVE_BURN_UP','MOVE_DOUBLE_SHOCK','MOVE_SUPERPOWER'}
STATUS=['MOVE_SWORDS_DANCE','MOVE_NASTY_PLOT','MOVE_DRAGON_DANCE','MOVE_QUIVER_DANCE','MOVE_CALM_MIND','MOVE_BULK_UP','MOVE_SHIFT_GEAR','MOVE_COIL','MOVE_ROOST','MOVE_RECOVER','MOVE_SLACK_OFF','MOVE_SOFT_BOILED','MOVE_SYNTHESIS','MOVE_MOONLIGHT','MOVE_WILL_O_WISP','MOVE_THUNDER_WAVE','MOVE_TOXIC','MOVE_SPORE','MOVE_SLEEP_POWDER','MOVE_STEALTH_ROCK','MOVE_PROTECT','MOVE_SUBSTITUTE','MOVE_LIGHT_SCREEN','MOVE_REFLECT']
def moveset(sp):
    d=SP[sp]; pool=set(m for _,m in LS.get(d['lvl'],[]))|set(TM.get(d['tm'],[]))
    hp,atk,de,spe,spa,spd=d['stats']
    phys=atk>=spa
    cat='DAMAGE_CATEGORY_PHYSICAL' if phys else 'DAMAGE_CATEGORY_SPECIAL'
    cands=[]
    for m in pool:
        i=MV.get(m)
        if not i or m in BAD or i['z'] or i['charge'] or i['power']<=1: continue
        if i['power']>150: continue
        sc=i['power']*i['acc']/100*(1.5 if i['type'] in d['types'] else 1)*(1 if i['cat']==cat else 0.55)
        cands.append((sc,m,i['type']))
    cands.sort(reverse=True)
    chosen=[];types=set()
    for sc,m,t in cands:
        if t in types: continue
        chosen.append(m); types.add(t)
        if len(chosen)==3: break
    st=[m for m in STATUS if m in pool]
    if st and len(chosen)>=2:
        # prefer setup matching category
        pref=[m for m in st if m in (('MOVE_SWORDS_DANCE','MOVE_DRAGON_DANCE','MOVE_BULK_UP','MOVE_SHIFT_GEAR','MOVE_COIL') if phys else ('MOVE_NASTY_PLOT','MOVE_QUIVER_DANCE','MOVE_CALM_MIND'))]
        chosen.append((pref or st)[0])
    else:
        for sc,m,t in cands:
            if m not in chosen: chosen.append(m)
            if len(chosen)==4: break
    if not chosen:
        lv=[m for _,m in LS.get(d['lvl'],[])][-4:]
        chosen=lv
    while len(chosen)<4: chosen.append('MOVE_NONE')
    return chosen[:4],phys
ITEMS_P=['ITEM_LIFE_ORB','ITEM_CHOICE_BAND','ITEM_LEFTOVERS','ITEM_SITRUS_BERRY','ITEM_FOCUS_SASH','ITEM_EXPERT_BELT','ITEM_LUM_BERRY','ITEM_SHELL_BELL','ITEM_SCOPE_LENS','ITEM_MUSCLE_BAND','ITEM_QUICK_CLAW','ITEM_KINGS_ROCK','ITEM_WHITE_HERB','ITEM_BRIGHT_POWDER']
ITEMS_S=['ITEM_LIFE_ORB','ITEM_CHOICE_SPECS','ITEM_LEFTOVERS','ITEM_SITRUS_BERRY','ITEM_FOCUS_SASH','ITEM_EXPERT_BELT','ITEM_LUM_BERRY','ITEM_SHELL_BELL','ITEM_SCOPE_LENS','ITEM_WISE_GLASSES','ITEM_QUICK_CLAW','ITEM_CHESTO_BERRY','ITEM_WHITE_HERB','ITEM_BRIGHT_POWDER']
def h(s): return int(hashlib.md5(s.encode()).hexdigest(),16)
# ---- choose species: national dex 387..1025 base forms (+ every gen 1-9 species not already in frontier)
existing=set(re.findall(r'\.species = (SPECIES_\w+)',open('src/data/battle_frontier/battle_frontier_mons.h').read()))
dex=re.findall(r'^\s*NATIONAL_DEX_(\w+),',open('include/constants/pokedex.h').read(),re.M)
base=[]
for n in dex:
    k='SPECIES_'+n
    if k not in SP:
        # default form alias
        al=re.search(r'^\s*'+k+r'\s*=\s*(SPECIES_\w+)',open('include/constants/species.h').read(),re.M)
        if al and al.group(1) in SP: k=al.group(1)
        else: continue
    if k in existing or SP[k]['banned'] or SP[k]['form']: continue
    if k in ('SPECIES_SHEDINJA',): continue
    base.append(k)
def grp(s):
    d=SP[s]
    if d['restricted'] or sum(d['stats'])>=670: return 2
    return 1 if d['evo'] else 0
base.sort(key=lambda s:grp(s))
LASTFE=[s for s in base if grp(s)==0][-1]
print('new species',len(base))
json.dump(base,open('/tmp/se/frontier_new.json','w'))
# ---- pools
tmf='src/data/battle_frontier/battle_frontier_trainer_mons.h'
T=open(tmf).read()
fm=open('src/data/battle_frontier/battle_frontier_mons.h').read()
id2sp=dict(re.findall(r'\[(FRONTIER_MON_\w+)\]\s*=\s*\{\s*\.species = (SPECIES_\w+)',fm))
pools={}
for m in re.finditer(r'#define (FRONTIER_MONS_\w+)(\([^)]*\))?\s*\\\n(.*?)(?=\n#define |\Z)',T,re.S):
    body=m.group(3)
    if not re.search(r'^\s*-1\s*$',body,re.M): continue
    ids=re.findall(r'FRONTIER_MON_\w+',body)
    sps=[id2sp[i] for i in ids if i in id2sp and id2sp[i] in SP]
    if not sps: continue
    bst=[sum(SP[s]['stats']) for s in sps]
    tc=collections.Counter(t for s in sps for t in set(SP[s]['types']))
    top,cnt=tc.most_common(1)[0]
    theme=top if cnt>=0.6*len(sps) else None
    pools[m.group(1)]=dict(lo=sorted(bst)[len(bst)//10],hi=sorted(bst)[-1-len(bst)//10],theme=theme,n=len(sps),leg=any(SP[s]['leg'] for s in sps))
for k,v in pools.items(): print(k,v)
NAMETHEME=[('BUG','TYPE_BUG'),('FISHERMAN','TYPE_WATER'),('SWIMM','TYPE_WATER'),('TUBER','TYPE_WATER'),('SAILOR','TYPE_WATER'),('BIRD_KEEPER','TYPE_FLYING'),('KINDLER','TYPE_FIRE'),('HIKER',('TYPE_ROCK','TYPE_GROUND')),('PSYCHIC','TYPE_PSYCHIC'),('HEX_MANIAC',('TYPE_GHOST','TYPE_DARK')),('BLACK_BELT','TYPE_FIGHTING'),('BATTLE_GIRL','TYPE_FIGHTING'),('DRAGON_TAMER','TYPE_DRAGON'),('AROMA_LADY','TYPE_GRASS'),('RUIN_MANIAC',('TYPE_ROCK','TYPE_GROUND','TYPE_PSYCHIC','TYPE_STEEL')),('GUITARIST',('TYPE_ELECTRIC','TYPE_DARK')),('NINJA_BOY',('TYPE_POISON','TYPE_DARK','TYPE_BUG'))]
SKIP={'FRONTIER_MONS_EEVEELUTIONS','FRONTIER_MONS_BUG_CATCHER_1_EXTRA'}
for k,v in pools.items():
    th=None
    for key,t in NAMETHEME:
        if key in k: th=t if isinstance(t,tuple) else (t,)
    if th is None and v['theme']: th=(v['theme'],)
    v['th']=th
added=collections.Counter(); assign=collections.defaultdict(list)
order=sorted(base,key=lambda s:h(s))
for s in order:
    d=SP[s]; b=sum(d['stats']); restricted=d['restricted'] or b>=670
    cands=[]
    for k,v in pools.items():
        if k in SKIP: continue
        if restricted:
            if not v['leg']: continue
        else:
            if not (v['lo']-20<=b<=v['hi']+20): continue
            if d['leg'] and not v['leg'] and b>=560: continue
        themed = v['th'] is not None
        if themed and not (set(v['th'])&set(d['types'])): continue
        cap=max(25,int(v['n']*1.2))
        if added[k]>=cap: continue
        cands.append((0 if themed else 1, added[k], h(s+k)%97, k))
    cands.sort()
    pick=[c[3] for c in cands if c[0]==0][:2]+[c[3] for c in cands if c[0]==1][:2]
    if not pick and cands: pick=[cands[0][3]]
    for k in pick: added[k]+=1; assign[k].append(s)
orphans=[s for s in base if not any(s in v for v in assign.values())]
for s in orphans:
    b=sum(SP[s]['stats'])
    best=min((k for k,v in pools.items() if k not in SKIP and v['th'] is None),key=lambda k:abs((pools[k]['lo']+pools[k]['hi'])/2-b))
    assign[best].append(s); added[best]+=1
orphans=[s for s in base if not any(s in v for v in assign.values())]
print('orphans',len(orphans),orphans[:20])
print('total adds',sum(added.values()))
import pickle; pickle.dump((dict(assign),orphans),open('/tmp/se/assign.pkl','wb'))
import sys
if 'write' in sys.argv:
    consts=[];sets=[]
    cpath='include/constants/battle_frontier_mons.h'; C=open(cpath).read()
    n0=int(re.search(r'#define NUM_FRONTIER_MONS\s+(\d+)',C).group(1))
    idx=n0; cid={}
    for s in base:
        name='FRONTIER_MON_'+s[8:]
        if name in C: name+='_SE'
        cid[s]=name; consts.append('#define %-40s %d'%(name,idx)); idx+=1
        mv,phys=moveset(s); d=SP[s]
        items=ITEMS_P if phys else ITEMS_S
        it=items[h(s)%len(items)]
        fast=d['stats'][3]>=80
        nat=('NATURE_JOLLY' if fast else 'NATURE_ADAMANT') if phys else ('NATURE_TIMID' if fast else 'NATURE_MODEST')
        ev='TRAINER_PARTY_EVS(6, 252, 0, 252, 0, 0)' if phys else 'TRAINER_PARTY_EVS(6, 0, 0, 252, 252, 0)'
        sets.append('    [%s] = {\n        .species = %s,\n        .moves = {%s},\n        .heldItem = %s,\n        .ev = %s,\n        .nature = %s,\n        .ball = BALL_POKE\n    },\n'%(name,s,', '.join(mv),it,ev,nat))
    consts.append('#define FRONTIER_MON_SE_LAST_EVOLVED %s // last fully evolved one (Battle Factory rentals)'%cid[LASTFE])
    C=re.sub(r'#define NUM_FRONTIER_MONS\s+\d+','// Super Emerald: Pokemon from every generation (tools: se_tools/gen_frontier.py)\n'+'\n'.join(consts)+'\n\n#define NUM_FRONTIER_MONS           %d'%idx,C)
    open(cpath,'w').write(C)
    fp='src/data/battle_frontier/battle_frontier_mons.h'; F=open(fp).read().rstrip()
    assert F.endswith('};')
    F=F[:-2].rstrip()+(',' if not F[:-2].rstrip().endswith(',') else '')+'\n    // Super Emerald: Pokemon from every generation\n'+''.join(sets)+'};\n'
    open(fp,'w').write(F)
    # pools
    T=open(tmf).read()
    for k,lst in assign.items():
        m=re.search(r'#define '+k+r'(\([^)]*\))?\s*\\\n(.*?)(?=\n#define |\Z)',T,re.S)
        body=m.group(2)
        mm=list(re.finditer(r'^(\s*)-1\s*$',body,re.M))[-1]
        ind=mm.group(1)
        ins=''.join('%s%s, \\\n'%(ind,cid[s]) for s in lst)
        nb=body[:mm.start()]+ins+body[mm.start():]
        T=T[:m.start(2)]+nb+T[m.end(2):]
    open(tmf,'w').write(T)
    print('written',idx)
