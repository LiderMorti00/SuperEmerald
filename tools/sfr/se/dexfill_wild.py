#!/usr/bin/env python3
"""Super Emerald: wild tables that make the National Dex completable.
Kanto Safari = Unova, Hoenn Safari = Kalos, Johto Safari = Paldea,
Great Marsh = Galar (+ missing Sinnoh), Sevii Islands = Alola."""
import json,sys
P='src/data/wild_encounters.json'
d=json.load(open(P))
G=d['wild_encounter_groups'][0]['encounters']
def find(label):
    for e in G:
        if e['base_label']==label: return e
    raise SystemExit('no '+label)
def mons(L,lo,hi):
    out=[]
    for s in L:
        if isinstance(s,tuple): s,a,b=s
        else: a,b=lo,hi
        out.append({'min_level':a,'max_level':b,'species':'SPECIES_'+s})
    return out
def land(label,L,lo,hi,rate=None):
    e=find(label); assert len(L)==12,(label,len(L))
    if 'land_mons' not in e: e['land_mons']={'encounter_rate':rate or 20}
    e['land_mons']['mons']=mons(L,lo,hi)
def water(label,L,lo,hi):
    e=find(label); assert len(L)==5
    if 'water_mons' not in e: e['water_mons']={'encounter_rate':4}
    e['water_mons']['mons']=mons(L,lo,hi)
def fish(label,L,lo,hi):
    e=find(label); assert len(L)==10
    e['fishing_mons']['mons']=mons(L,lo,hi)
def add_time(label,suffix,kind,L,lo,hi,rate=20):
    base=find(label); nl=label+'_'+suffix
    e=next((x for x in G if x['base_label']==nl),None)
    if e is None:
        e={'map':base['map'],'base_label':nl}; G.insert(G.index(base)+1,e)
    e[kind]={'encounter_rate':rate,'mons':mons(L,lo,hi)}

# ---- Kanto Safari Zone (FRLG): Unova ----
for v in ('FireRed','LeafGreen'):
    land('sSafariZoneCenter_'+v,['PATRAT','PURRLOIN','PANSEAR','BLITZLE','MINCCINO','PETILIL','RHYHORN','EXEGGCUTE','WATCHOG','LIEPARD','AUDINO','CHANSEY'],56,60)
    land('sSafariZoneEast_'+v,['DARUMAKA','WOOBAT','YAMASK','SIGILYPH','NIDORAN_M','NIDORAN_F','KANGASKHAN','SCYTHER','SWOOBAT','COFAGRIGUS','DARMANITAN','AUDINO'],56,60)
    land('sSafariZoneNorth_'+v,['KLINK','VANILLITE','LITWICK','PAWNIARD','DURANT','HEATMOR','TAUROS','CHANSEY','KLANG','LAMPENT','BISHARP','CRYOGONAL'],56,60)
    land('sSafariZoneWest_'+v,['KARRABLAST','SHELMET','TYNAMO','CRYOGONAL','VENONAT','PARAS','TAUROS','KANGASKHAN','EELEKTRIK','ZEBSTRIKA','ESCAVALIER','ACCELGOR'],56,60)
    for a in ('Center','East','North','West'):
        water('sSafariZone%s_%s'%(a,v),['PSYDUCK','TYNAMO','PSYDUCK','EELEKTRIK','GOLDUCK'],52,60)

# ---- Hoenn Safari Zone: Kalos ----
land('gSafariZone_South',['SCATTERBUG','FLABEBE','PIKACHU','DODUO','GLOOM','PSYDUCK','SCATTERBUG','FLABEBE','SPEWPA','FLOETTE','VIVILLON','FLORGES'],26,30)
land('gSafariZone_Southwest',['HONEDGE','SWIRLIX','DODUO','XATU','GLOOM','PSYDUCK','HONEDGE','SWIRLIX','DOUBLADE','SLURPUFF','XATU','AEGISLASH'],26,30)
land('gSafariZone_North',['GOOMY','BERGMITE','DONPHAN','DODUO','GLOOM','PSYDUCK','GOOMY','BERGMITE','SLIGGOO','DONPHAN','AVALUGG','GOODRA'],26,30)
land('gSafariZone_Northwest',['SKIDDO','FLABEBE','RHYHORN','DODUO','GLOOM','PSYDUCK','SKIDDO','RHYHORN','GOGOAT','FLOETTE','GOGOAT','FLORGES'],26,30)
water('gSafariZone_North',['PSYDUCK','GOOMY','PSYDUCK','GOOMY','GOLDUCK'],20,30)

# ---- Johto Safari Zone (HnS): Paldea ----
P9=(62,65)
land('gSafariZone_Top_Mid0_hns',['LECHONK','FIDOUGH','PAWMI','SQUAWKABILLY','EEVEE','MR_MIME','GIRAFARIG','TANGELA','DACHSBUN','PAWMO',('SCREAM_TAIL',)+P9,('IRON_BUNDLE',)+P9],55,58)
land('gSafariZone_Low_Mid0_hns',['TADBULB','CAPSAKID','CHARCADET','MAGNEMITE','TAUROS',('IRON_JUGULIS',)+P9,'TEDDIURSA','AIPOM','ARMAROUGE','CERULEDGE',('IRON_HANDS',)+P9,('SANDY_SHOCKS',)+P9],55,58)
land('gSafariZone_Low_Left0_hns',['CYCLIZAR','RELLOR','BOMBIRDIER','LARVITAR','PHANPY','GLIGAR','CUBONE',('IRON_THORNS',)+P9,'RABSCA','KINGAMBIT',('GREAT_TUSK',)+P9,('IRON_TREADS',)+P9],55,58)
land('gSafariZone_Top_Left0_hns',['TAROUNTULA','NYMBLE','SCYTHER','PINSIR','KANGASKHAN','CHANSEY','HERACROSS','DITTO','SPIDOPS','LOKIX',('BRUTE_BONNET',)+P9,('SLITHER_WING',)+P9],55,58)
land('gSafariZone_Low_Right0_hns',['FRIGIBAX','CETODDLE','DRATINI','SNEASEL','PILOSWINE','DUNSPARCE','PUPITAR','DRAGONAIR','ARCTIBAX','CETITAN',('ROARING_MOON',)+P9,('IRON_VALIANT',)+P9],60,64)
land('gSafariZone_Top_Right0_hns',['GIMMIGHOUL_ROAMING','POLTCHAGEIST','KRABBY','PSYDUCK','EXEGGCUTE','SHUCKLE','SKIPLOOM','WOOPER','GHOLDENGO','SINISTCHA',('FLUTTER_MANE',)+P9,('IRON_MOTH',)+P9],55,58)
water('gSafariZone_Low_Right0_hns',['WOOPER','CETODDLE','GOLDUCK','QUAGSIRE','CETITAN'],60,64)
water('gSafariZone_Top_Right0_hns',['HORSEA','STARYU','CORSOLA','DRATINI','WIGLETT'],55,58)
fish('gSafariZone_Top_Right0_hns',['MAGIKARP','MAGIKARP','FINIZEN','CHINCHOU','SHELLDER','FINIZEN','QWILFISH','TATSUGIRI','DONDOZO','VELUZA'],55,58)

# ---- Great Marsh: Galar (+ Carnivine, Burmy, Cherubi, Phione) ----
for lab in ('gGreatMarsh_Sinnoh','gGreatMarsh_PostGame_Sinnoh'):
    land(lab,['NICKIT','GOSSIFLEUR','YAMPER','CLOBBOPUS','MEOWTH_GALAR','FARFETCHD_GALAR','MILCERY','CUFANT','CARNIVINE','TROPIUS','SIRFETCHD','ALCREMIE'],58,62)
    water(lab,['WOOPER','QUAGSIRE','PINCURCHIN','PINCURCHIN','PHIONE'],56,60)
add_time('gGreatMarsh_Sinnoh','Night','land_mons',['YAMASK_GALAR','SNOM','MORPEKO','STONJOURNER','BURMY','CHERUBI','WOOPER','YANMA','DRACOZOLT','ARCTOZOLT','RUNERIGUS','GRAPPLOCT'],58,62)

# ---- Sevii Islands: Alola ----
V=('FireRed','LeafGreen')
for v in V:
    land('sOneIslandKindleRoad_'+v,['SALANDIT','GEODUDE_ALOLA','PONYTA','SPEAROW','YUNGOOS','MEOWTH_ALOLA','SALANDIT','GRAVELER_ALOLA','SALAZZLE','GUMSHOOS','RAPIDASH','PERSIAN_ALOLA'],60,64)
    land('sOneIslandTreasureBeach_'+v,['YUNGOOS','SANDSHREW_ALOLA','SPEAROW','TANGELA','MEOWTH_ALOLA','EXEGGCUTE','GUMSHOOS','DRAMPA','FEAROW','PERSIAN_ALOLA','EXEGGUTOR_ALOLA','DRAMPA'],60,64)
    land('sTwoIslandCapeBrink_'+v,['FOMANTIS','COMFEY','ODDISH','BOUNSWEET','GLOOM','MEOWTH_ALOLA','STEENEE','PSYDUCK','LURANTIS','PERSIAN_ALOLA','TSAREENA','COMFEY'],60,64)
    land('sThreeIslandBondBridge_'+v,['PASSIMIAN','RATTATA_ALOLA','PIDGEY','ODDISH','PIDGEOTTO','MEOWTH_ALOLA','RATICATE_ALOLA','PSYDUCK','PIKACHU','PERSIAN_ALOLA','RAICHU_ALOLA','PASSIMIAN'],60,64)
    land('sThreeIslandBerryForest_'+v,['BOUNSWEET','MORELULL','COMFEY','FOMANTIS','EXEGGCUTE','DROWZEE','STEENEE','SHIINOTIC','LURANTIS','HYPNO','TSAREENA','EXEGGUTOR_ALOLA'],60,64)
    land('sSixIslandPatternBush_'+v,['STUFFUL','FOMANTIS','SPINARAK','HERACROSS','MORELULL','LEDYBA','BEWEAR','HERACROSS','LURANTIS','SHIINOTIC','HERACROSS','STUFFUL'],58,62)
    land('sFiveIslandMeadow_'+v,['STUFFUL','BOUNSWEET','YUNGOOS','PIDGEOTTO','SENTRET','HOPPIP','GUMSHOOS','STEENEE','BEWEAR','PERSIAN_ALOLA','TSAREENA','COMFEY'],62,66)
    land('sSixIslandWaterPath_'+v,['GRIMER_ALOLA','SALANDIT','ODDISH','FEAROW','SENTRET','MEOWTH_ALOLA','GLOOM','MUK_ALOLA','SALAZZLE','PERSIAN_ALOLA','FEAROW','MUK_ALOLA'],62,66)
    land('sSixIslandRuinValley_'+v,['DIGLETT_ALOLA','PASSIMIAN','NATU','YANMA','WOOPER','MEOWTH_ALOLA','WOBBUFFET','DUGTRIO_ALOLA','NATU','PERSIAN_ALOLA','DRAMPA','DUGTRIO_ALOLA'],60,64)
    land('sSevenIslandSevaultCanyonEntrance_'+v,['JANGMO_O','PHANPY','SENTRET','FEAROW','CUBONE','MEOWTH_ALOLA','HAKAMO_O','PSYDUCK','PHANPY','PERSIAN_ALOLA','MAROWAK_ALOLA','KOMMO_O'],62,66)
    land('sSevenIslandSevaultCanyon_'+v,['JANGMO_O','GEODUDE_ALOLA','CUBONE','PHANPY','HAKAMO_O','MAROWAK_ALOLA','ONIX','SKARMORY','LARVITAR','GOLEM_ALOLA','LARVITAR','KOMMO_O'],64,68)
    land('sFourIslandIcefallCave1F_'+v,['SWINUB','SANDSHREW_ALOLA','SEEL','VULPIX_ALOLA','ZUBAT','SWINUB','DELIBIRD','SANDSLASH_ALOLA','GOLBAT','NINETALES_ALOLA','GOLBAT','SANDSHREW_ALOLA'],60,64)
    land('sFourIslandIcefallCaveB1F_'+v,['SWINUB','VULPIX_ALOLA','SEEL','SANDSHREW_ALOLA','ZUBAT','SWINUB','DELIBIRD','NINETALES_ALOLA','GOLBAT','SANDSLASH_ALOLA','GOLBAT','VULPIX_ALOLA'],60,64)
    # sea: Wishiwashi, Dhelmise, Mareanie, Pyukumuku, Bruxish
    for lab in ('sOneIslandTreasureBeach_','sOneIslandKindleRoad_','sThreeIslandBondBridge_','sSixIslandOutcastIsland_','sSixIslandWaterPath_','sSevenIslandTanobyRuins_','sFiveIslandResortGorgeous_','sFiveIslandWaterLabyrinth_','sFiveIslandMeadow_','sFiveIslandMemorialPillar_','sOneIsland_','sFiveIsland_'):
        try:
            fish(lab+v,['MAGIKARP','WISHIWASHI','HORSEA','WISHIWASHI','MAREANIE','HORSEA','BRUXISH','GYARADOS','SEADRA','DHELMISE'],50,62)
            water(lab+v,['TENTACOOL','PYUKUMUKU','MAREANIE','TENTACRUEL','TOXAPEX'],50,62)
        except SystemExit as ex: print(ex)
json.dump(d,open(P,'w'),indent=2,ensure_ascii=False); open(P,'a').write('\n')
