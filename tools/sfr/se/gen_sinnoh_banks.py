#!/usr/bin/env python3
"""Super Emerald: per-bank voicegroups for the Platinum music.
Platinum has one instrument bank per music type (field, battle, dungeon). Most programs are the
shared General MIDI instruments (voicegroup sinnoh_pt), but some use samples of the bank's own
wave archive, and some are empty (NULL) on purpose. This builds sinnoh_pt_field, _battle and
_dungeon with those programs converted from pokeplatinum, and points each song at its bank.
usage: gen_sinnoh_banks.py /path/to/pokeplatinum   (run after gen_sinnoh_music.py)"""
import sys,os,re,json,struct,subprocess,hashlib
HERE=os.path.dirname(os.path.abspath(__file__)); os.chdir(os.path.join(HERE,'../../..'))
PLAT=sys.argv[1]
exec(open(os.path.join(HERE,'dpp_song_map.py')).read())
def parse(name):
    L=open(os.path.join(PLAT,'res/sound/BANK/%s.txt'%name)).read().split('\n'); P={};cur=None
    for l in L:
        if not l.strip(): continue
        if l.startswith('\t'): P[cur]['regions'].append([x.strip() for x in l.strip().split(',')])
        else:
            f=[x.strip() for x in l.split(',')]; cur=int(f[0]); P[cur]={'type':f[1],'raw':f[2:],'regions':[]}
    return P
sd=json.load(open(os.path.join(PLAT,'res/sound/pl_sound_data.json')))
seq={x['fileName']:x for x in sd['seqInfo'] if x.get('fileName')}
arcs={b['name']:b['waves'] for b in sd['bankInfo'] if 'waves' in b}
def songfile(v): return (v if v.startswith(('BATTLE','VICTORY')) else 'SEQ_'+v)
def adsr(a,d,s,r):
    def rate(v):  # NDS rate (127 = instant) -> m4a multiplier (0 = instant)
        t={127:0,126:150,125:171,124:185,123:195,122:200,121:205,120:210,119:214,118:217,117:220,116:224,115:226,114:228,113:230,112:232,110:235,105:240,100:244}
        if v in t: return t[v]
        k=min(t,key=lambda x:abs(x-v)); return t[k] if v>100 else 248
    return (255 if a>=127 else max(1,a*2)), rate(d), (255 if s>=127 else int(s*1.89)), rate(r)
made={}
def sample(arc,idx,root):
    src=os.path.join(PLAT,'res/sound/WAVARC/%s/%03d.wav'%(arc,idx))
    raw=open(src,'rb').read(); h=hashlib.md5(raw).hexdigest()[:6]
    name='pt_%s_r%d'%(h,root)
    if name in made: return name
    rate=int(float(subprocess.check_output(['ffprobe','-v','error','-show_entries','stream=sample_rate','-of','csv=p=0',src]).decode()))
    orig=rate; rate=min(rate,11025)  # halve the size of 16 kHz samples, still clear on the GBA mixer
    pcm=subprocess.check_output(['ffmpeg','-v','error','-i',src,'-ar',str(rate),'-f','u8','-ac','1','-'])
    loop=None; i=12
    while i<len(raw)-8:
        cid=raw[i:i+4]; sz=struct.unpack('<I',raw[i+4:i+8])[0]
        if cid==b'smpl':
            v=struct.unpack('<9I',raw[i+8:i+44])
            if v[7]: loop=tuple(int(x*rate/orig) for x in struct.unpack('<6I',raw[i+44:i+68])[2:4])
        i+=8+sz+(sz&1)
    if loop: smpl=struct.pack('<9I',0,0,int(1e9/rate),root,0,0,0,1,0)+struct.pack('<6I',0,0,loop[0],min(loop[1],len(pcm)-1),0,0)
    else: smpl=struct.pack('<9I',0,0,int(1e9/rate),root,0,0,0,0,0)
    fmt=struct.pack('<HHIIHH',1,1,rate,rate,1,8)
    body=b'fmt '+struct.pack('<I',16)+fmt+b'smpl'+struct.pack('<I',len(smpl))+smpl+b'data'+struct.pack('<I',len(pcm))+pcm+(b'\0' if len(pcm)&1 else b'')
    open('sound/direct_sound_samples/%s.wav'%name,'wb').write(b'RIFF'+struct.pack('<I',4+len(body))+b'WAVE'+body)
    made[name]=1; return name
SILENT='voice_square_1 60, 0, 0, 2, 0, 0, 0, 0'
base=[l.strip().split('  @')[0] for l in open('sound/voicegroups/sinnoh_pt.inc') if l.strip().startswith('voice_') and not l.strip().startswith('voice_group')]
GROUP={'BANK_BGM_FIELD':'sinnoh_pt_field','BANK_BGM_BATTLE':'sinnoh_pt_battle','BANK_BGM_DUNGEON':'sinnoh_pt_dungeon','BANK_BASIC':'sinnoh_pt_field'}
import mido
used={}
for k,v in MAP.items():
    b=seq[songfile(v)+'.sseq']['bank']
    for t in mido.MidiFile('sound/songs/midi/mus_dpp_%s.mid'%k).tracks:
        for x in t:
            if x.type=='program_change': used.setdefault(b,set()).add(x.program)
vgs=[];ks=[]
for bank,grp in sorted(set(GROUP.items()),key=lambda x:x[1]):
    if bank=='BANK_BASIC': continue
    P=parse(bank); arc=arcs[bank][1]; lines=list(base)
    for p in sorted(used.get(bank,set())|used.get('BANK_BASIC',set()) if bank=='BANK_BGM_FIELD' else used.get(bank,set())):
        d=P.get(p)
        if d is None or d['type']=='NULL': lines[p]=SILENT; continue
        if d['type']=='Single' and d['raw'][1]=='1':
            s,_,root,a,dd,su,r,pan=map(int,d['raw'][:8]); A=adsr(a,dd,su,r)
            lines[p]='voice_directsound 60, 0, DirectSoundWaveData_%s, %d, %d, %d, %d'%(sample(arc,s,root),*A)
        elif d['type']=='Keysplit' and any(rg[2]=='1' for rg in d['regions']):
            ends=[int(x) for x in d['raw'] if x!='0']
            sub='%s_%d'%(grp,p); sv=[]
            for rg in d['regions']:
                s,w,root,a,dd,su,r,pan=int(rg[1]),rg[2],int(rg[3]),*map(int,rg[4:9])
                A=adsr(a,dd,su,r)
                smp=sample(arc if w=='1' else 'WAVE_ARC_BASIC',s,root)
                sv.append('\tvoice_directsound 60, 0, DirectSoundWaveData_%s, %d, %d, %d, %d'%(smp,*A))
            vgs.append('voice_group %s\n'%sub+'\n'.join(sv))
            kl=['keysplit %s, 0'%sub]+['\tsplit %d, %d'%(i,min(e,127)+1 if i==len(ends)-1 else e+1) for i,e in enumerate(ends)]
            ks.append('\n'.join(kl))
            lines[p]='voice_keysplit voicegroup_%s, keysplit_%s'%(sub,sub)
    vgs.append('voice_group %s @ Generated by tools/sfr/se/gen_sinnoh_banks.py from %s\n'%(grp,bank)+'\n'.join('\t'+l+'  @ %d'%i for i,l in enumerate(lines)))
open('sound/voicegroups/sinnoh_pt_banks.inc','w').write('\n\n'.join(ks)+'\n\n'+'\n\n'.join(vgs)+'\n')
vg=open('sound/voice_groups.inc').read()
if 'sinnoh_pt_banks.inc' not in vg:
    vg=vg.replace('.include "sound/voicegroups/sinnoh_pt_drums.inc"\n','.include "sound/voicegroups/sinnoh_pt_drums.inc"\n.include "sound/voicegroups/sinnoh_pt_banks.inc"\n'); open('sound/voice_groups.inc','w').write(vg)
ds=open('sound/direct_sound_data.inc').read()
for n in sorted(made):
    if 'DirectSoundWaveData_%s::'%n not in ds:
        ds+='\n\t.align 2\nDirectSoundWaveData_%s::\n\t.incbin "sound/direct_sound_samples/%s.bin"\n'%(n,n)
open('sound/direct_sound_data.inc','w').write(ds)
cfg=open('sound/songs/midi/midi.cfg').read()
for k,v in MAP.items():
    g=GROUP[seq[songfile(v)+'.sseq']['bank']]
    cfg=re.sub(r'^(mus_dpp_%s\.mid:.*)-G_sinnoh_pt\w*'%k, r'\1-G_'+g, cfg, flags=re.M)
open('sound/songs/midi/midi.cfg','w').write(cfg)
print('samples',sorted(made))
