#!/usr/bin/env python3
"""Super Emerald: Sevii Islands trainers use Alola Pokémon (levels and team sizes kept)."""
import re,json,os,zlib
os.chdir(os.path.join(os.path.dirname(__file__),'../../..'))
TRAINERS=json.load(open('tools/sfr/se/dexfill_sevii_trainers.json'))
W=['Wishiwashi','Toxapex','Araquanid','Pyukumuku','Bruxish','Golisopod','Dhelmise','Mareanie','Dewpider']
POOL={
 'Swimmer':W,'Fisherman':W,'Tuber':['Wishiwashi','Mareanie','Dewpider','Pyukumuku','Popplio','Sandygast'],
 'Bird Keeper':['Toucannon','Trumbeak','Oricorio','Oricorio-Pom-Pom','Oricorio-Pau','Oricorio-Sensu'],
 'Ruin Maniac':['Palossand','Lycanroc','Mudsdale','Golem-Alola','Graveler-Alola','Minior','Dugtrio-Alola'],
 'Hiker':['Golem-Alola','Graveler-Alola','Lycanroc','Mudsdale','Palossand','Minior'],
 'Aroma Lady':['Tsareena','Lurantis','Shiinotic','Comfey','Ribombee','Steenee'],
 'Painter':['Ribombee','Comfey','Oricorio-Pau','Smeargle','Shiinotic','Togedemaru'],
 'Lady':['Ninetales-Alola','Tsareena','Comfey','Ribombee','Persian-Alola'],
 'Pkmn Ranger':['Lycanroc','Bewear','Toucannon','Lurantis','Mudsdale','Vikavolt','Salazzle','Kommo-o'],
 'Crush Girl':['Crabominable','Bewear','Hakamo-o','Passimian','Kommo-o'],
 'Black Belt':['Crabominable','Bewear','Hakamo-o','Passimian','Kommo-o'],
 'Crush Kin':['Crabrawler','Crabominable','Stufful','Bewear','Hakamo-o'],
 'Psychic':['Oranguru','Bruxish','Exeggutor-Alola','Raichu-Alola','Mimikyu','Minior'],
 'Gentleman':['Persian-Alola','Oranguru','Ninetales-Alola','Turtonator'],
 'Cooltrainer':['Kommo-o','Lycanroc','Golisopod','Vikavolt','Salazzle','Turtonator','Drampa','Tsareena','Toucannon','Mimikyu'],
 'Cool Couple':['Kommo-o','Salazzle','Lycanroc','Tsareena'],
 'Young Couple':['Ribombee','Comfey','Togedemaru','Raichu-Alola'],
 'Juggler':['Mimikyu','Togedemaru','Marowak-Alola','Sandslash-Alola','Minior'],
 'Twins':['Togedemaru','Komala','Comfey','Ribombee'],
 'Sis And Bro':['Raichu-Alola','Primarina','Togedemaru','Ribombee'],
 'Tamer':['Salazzle','Turtonator','Mudsdale','Bewear','Kommo-o'],
 'Pkmn Breeder':['Steenee','Hakamo-o','Charjabug','Trumbeak','Mudbray','Salandit'],
 'Pokemaniac':['Turtonator','Drampa','Komala','Mimikyu','Kommo-o'],
 'Picnicker':['Tsareena','Ribombee','Comfey','Lurantis','Shiinotic'],
 'Camper':['Gumshoos','Lycanroc','Vikavolt','Raticate-Alola','Toucannon'],
 'Youngster':['Gumshoos','Raticate-Alola','Lycanroc','Vikavolt','Toucannon'],
}
p='src/data/trainers_frlg.party'; t=open(p).read()
names=sorted(set(sum(TRAINERS.values(),[])))
def key(n): return n if n in POOL else None
n_done=0
for n in names:
    for var in [n]+['%s_%d'%(n,i) for i in range(2,7)]:
        m=re.search(r'(=== %s ===\n.*?\n\n)(.*?)(?=\n=== |\Z)'%re.escape(var),t,re.S)
        if not m: continue
        head,body=m.group(1),m.group(2)
        c=re.search(r'Class: (.*?)(?: Frlg)?\n',head).group(1)
        c={'Swimmer F':'Swimmer','Swimmer M':'Swimmer'}.get(c,c)
        if c not in POOL: print('no pool',c); continue
        pool=POOL[c]; mons=re.split(r'\n\n+',body.strip())
        h=zlib.crc32(var.encode()); out=[]
        for i,mon in enumerate(mons):
            lines=mon.split('\n')
            lv=next(l for l in lines if l.startswith('Level:'))
            sp=pool[(h+i*7)%len(pool)]
            if sp in [o.split('\n')[0].split(' @ ')[0] for o in out]: sp=pool[(h+i*7+1)%len(pool)]
            item=(' @ '+lines[0].split(' @ ',1)[1]) if ' @ ' in lines[0] else ''
            out.append(sp+item+'\n'+lv)
        t=t[:m.start(2)]+'\n\n'.join(out)+'\n'+t[m.end(2):]
        n_done+=1
open(p,'w').write(t); print('trainers',n_done)
