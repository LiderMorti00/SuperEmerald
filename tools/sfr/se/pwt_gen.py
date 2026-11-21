import sys,re; sys.path.insert(0,'/tmp/pwt'); from roster import R,EV
ROOT='/home/claude/superfirered/'
# 1) facility classes enum
p=ROOT+'include/constants/trainers.h'; s=open(p).read()
enum=''.join('    FACILITY_CLASS_SE_%s,\n'%r[0] for r in R)
s=s.replace('    FACILITY_CLASS_LASS_FRLG,\n    FACILITY_CLASSES_COUNT,','    FACILITY_CLASS_LASS_FRLG,\n    // Super Emerald: Pokemon World Tournament (Johto) stars\n'+enum+'    FACILITY_CLASSES_COUNT,',1)
s=s.replace('    FACILITY_CLASSES_COUNT,\n','    FACILITY_CLASSES_COUNT,\n',1)
if 'FACILITY_CLASS_SE_FIRST' not in s:
    s=s.replace('#define TRAINER_RECORD_MIXING_FRIEND','#define FACILITY_CLASS_SE_FIRST FACILITY_CLASS_SE_%s\n#define TRAINER_RECORD_MIXING_FRIEND'%R[0][0],1)
open(p,'w').write(s)
# 2) lookups
p=ROOT+'src/data/pokemon/trainer_class_lookups.h'; s=open(p).read()
a='    [FACILITY_CLASS_LASS_FRLG]          = TRAINER_PIC_LASS_FRLG,\n'
s=s.replace(a,a+''.join('    [FACILITY_CLASS_SE_%s] = TRAINER_PIC_%s,\n'%(r[0],r[2]) for r in R),1)
a='    [FACILITY_CLASS_LASS_FRLG]          = TRAINER_CLASS_LASS_FRLG,\n'
s=s.replace(a,a+''.join('    [FACILITY_CLASS_SE_%s] = TRAINER_CLASS_%s,\n'%(r[0],r[4]) for r in R),1)
open(p,'w').write(s)
# 3) data header
SPEECH=[('EC_WORD_I_AM, EC_WORD_NEVER, EC_WORD_GOING, EC_WORD_TO, EC_WORD_LOSE, EC_WORD_EXCL','EC_WORD_A, EC_WORD_WIN, EC_WORD_IS, EC_WORD_JUST, EC_WORD_AWESOME, EC_EMPTY_WORD','EC_WORD_YOU, EC_WORD_WON, EC_WORD_EXCL, EC_WORD_MOVE, EC_WORD_ON, EC_WORD_EXCL')]
REG={'K':'SE_PWT_KANTO','J':'SE_PWT_JOHTO','H':'SE_PWT_HOENN','S':'SE_PWT_SINNOH','X':'SE_PWT_KALOS','U':'SE_PWT_UNOVA'}
RANK={'L':'SE_PWT_RANK_LEADER','E':'SE_PWT_RANK_ELITE','C':'SE_PWT_RANK_CHAMPION','B':'SE_PWT_RANK_BRAIN'}
o='// Super Emerald: Pokemon World Tournament (Johto) roster. Generated from tools/sfr/se/pwt_roster.py\n\n'
mons=[];sets=[]
for r in R:
    ids=[]
    for m in r[7]:
        sp,it,na,e,ms=m.split('|')
        ids.append(len(mons)); mons.append((sp,it,na,e,ms))
    sets.append(ids)
o+='const struct TrainerMon gSEPwtMons[] =\n{\n'
for i,(sp,it,na,e,ms) in enumerate(mons):
    mv=', '.join('MOVE_'+x for x in ms.split(','))
    o+='    [%d] = {\n        .species = SPECIES_%s,\n        .moves = {%s},\n        .heldItem = ITEM_%s,\n        .ev = TRAINER_PARTY_EVS(%s),\n        .nature = NATURE_%s,\n        .ball = BALL_POKE\n    },\n'%(i,sp,mv,it,EV[e],na)
o+='};\n\n'
o+='const struct BattleFrontierTrainer gSEPwtTrainers[] =\n{\n'
for r,ids in zip(R,sets):
    sb,sw,sl=SPECIH=SPEECH[0]
    o+='    [SE_PWT_TRAINER_%s] = {\n        .facilityClass = FACILITY_CLASS_SE_%s,\n        .trainerName = _("%s"),\n        .speechBefore = {%s},\n        .speechWin = {%s},\n        .speechLose = {%s},\n        .monSet = (const u16[]){%s, 0xFFFF}\n    },\n'%(r[0],r[0],r[1][:7],sb,sw,sl,', '.join(map(str,ids)))
o+='};\n\n'
o+='const u8 *const gSEPwtNames[] =\n{\n'+''.join('    [SE_PWT_TRAINER_%s] = COMPOUND_STRING("%s"),\n'%(r[0],r[1]) for r in R)+'};\n\n'
o+='const u16 gSEPwtGfx[] =\n{\n'+''.join('    [SE_PWT_TRAINER_%s] = OBJ_EVENT_GFX_%s,\n'%(r[0],r[3]) for r in R)+'};\n\n'
o+='const u8 gSEPwtRegions[] =\n{\n'+''.join('    [SE_PWT_TRAINER_%s] = %s,\n'%(r[0],' | '.join('(1 << %s)'%REG[c] for c in r[5])) for r in R)+'};\n\n'
o+='const u8 gSEPwtRanks[] =\n{\n'+''.join('    [SE_PWT_TRAINER_%s] = %s,\n'%(r[0],RANK[r[6]]) for r in R)+'};\n'
open(ROOT+'src/data/battle_frontier/se_pwt.h','w').write(o)
# 4) constants header
c='#ifndef GUARD_CONSTANTS_SE_PWT_H\n#define GUARD_CONSTANTS_SE_PWT_H\n\n// Super Emerald: Pokemon World Tournament (Johto)\n'
c+='enum\n{\n'+''.join('    SE_PWT_TRAINER_%s,\n'%r[0] for r in R)+'    SE_PWT_TRAINERS_COUNT\n};\n\n'
c+='''// Regions (bits of gSEPwtRegions)
#define SE_PWT_KANTO   0
#define SE_PWT_JOHTO   1
#define SE_PWT_HOENN   2
#define SE_PWT_SINNOH  3
#define SE_PWT_KALOS   4
#define SE_PWT_UNOVA   5

#define SE_PWT_RANK_LEADER    0
#define SE_PWT_RANK_ELITE     1
#define SE_PWT_RANK_CHAMPION  2
#define SE_PWT_RANK_BRAIN     3

// Cups (VAR_SE_PWT_CUP)
#define SE_PWT_CUP_KANTO      0
#define SE_PWT_CUP_JOHTO      1
#define SE_PWT_CUP_HOENN      2
#define SE_PWT_CUP_SINNOH     3
#define SE_PWT_CUP_KALOS      4
#define SE_PWT_CUP_CHAMPIONS  5
#define SE_PWT_CUP_WORLD      6
#define SE_PWT_CUPS_COUNT     7

#endif // GUARD_CONSTANTS_SE_PWT_H
'''
open(ROOT+'include/constants/se_pwt.h','w').write(c)
print(len(mons),'mons',len(R),'trainers')
