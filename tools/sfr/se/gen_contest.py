import re,sys,hashlib
exec(open('/home/claude/se_tools/gen_frontier.py').read().split('# ---- pools')[0].replace("existing=set(re.findall(r'\\.species = (SPECIES_\\w+)',open('src/data/battle_frontier/battle_frontier_mons.h').read()))","existing=set()"))
base=[k for k in base if int(re.findall(r'^\s*NATIONAL_DEX_(\w+),',open('include/constants/pokedex.h').read(),re.M).index(SP[k]['dex'][13:]))>=386]
p='src/data/contest_opponents.h'; s=open(p).read()
start=s.index('gContestOpponents[]')
blocks=list(re.finditer(r'    \[(CONTEST_OPPONENT_\w+)\] = \{\n(.*?)\n    \},',s[start:],re.S))
CAT={'Cool':['TYPE_FIRE','TYPE_FIGHTING','TYPE_DRAGON','TYPE_ELECTRIC','TYPE_STEEL'],
     'Beauty':['TYPE_WATER','TYPE_ICE','TYPE_FAIRY','TYPE_FLYING','TYPE_PSYCHIC'],
     'Cute':['TYPE_NORMAL','TYPE_FAIRY','TYPE_GRASS','TYPE_BUG'],
     'Smart':['TYPE_PSYCHIC','TYPE_GRASS','TYPE_STEEL','TYPE_GHOST','TYPE_DARK'],
     'Tough':['TYPE_ROCK','TYPE_GROUND','TYPE_FIGHTING','TYPE_POISON','TYPE_STEEL']}
newsp=[k for k in base if not SP[k]['leg'] and SP[k]['dex'] and k not in ('SPECIES_SHEDINJA',)]
used=set(); out=s; n=0
h=lambda x:int(hashlib.md5(x.encode()).hexdigest(),16)
for i,m in enumerate(blocks):
    if i%2==0: continue
    b=m.group(2)
    cats=[c for c in CAT if re.search(r'\.aiPool_'+c+r' = TRUE',b)]
    types=set(t for c in cats for t in CAT[c])
    cands=[k for k in newsp if k not in used and set(SP[k]['types'])&types]
    if not cands: continue
    k=sorted(cands,key=lambda x:h(x+m.group(1)))[0]; used.add(k)
    name=SP[k]['name'].upper().replace('É','é')[:10]
    lv=[mv for _,mv in LS.get(SP[k]['lvl'],[]) if mv in MV]
    mv=list(dict.fromkeys(lv))[-4:]
    while len(mv)<4: mv.append('MOVE_NONE')
    nb=re.sub(r'\.species = SPECIES_\w+','.species = '+k,b)
    nb=re.sub(r'\.nickname = _\("[^"]*"\)','.nickname = _("%s")'%name,nb)
    nb=re.sub(r'\.moves =\s*\{[^}]*\}','.moves =\n        {\n            %s\n        }'%(',\n            '.join(mv)),nb)
    out=out.replace(b,nb,1); n+=1
open(p,'w').write(out); print('changed',n)
