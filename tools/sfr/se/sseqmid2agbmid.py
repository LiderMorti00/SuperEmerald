#!/usr/bin/env python3
"""Super Emerald: turn a pret pokeplatinum sequence MIDI (SSEQ written as MIDI, with
LABELnn / CALLnn / JUMPnn text events and 0xFD 'return' markers) into a plain MIDI
for mid2agb: subroutines are expanded, every track is run to a common loop and the
loop is marked with '[' and ']'. DS-only controllers are dropped and CC11
(expression) is folded into CC7 (volume).
usage: sseqmid2agbmid.py in.mid out.mid [program_map.json]"""
import sys,json,mido

KEEP_CC={1,7,10,20,21,22,26}

def load(path):
    m=mido.MidiFile(path,clip=True)
    tracks=[]
    for tr in m.tracks:
        t=0;evs=[]
        for msg in tr:
            t+=msg.time; evs.append((t,msg))
        tracks.append(evs)
    return m,tracks

def prep(evs):
    labels={}
    dur={}
    for i,(t,msg) in enumerate(evs):
        if msg.type=='text' and msg.text.startswith('LABEL'):
            labels[int(msg.text[5:7])]=i
    # pair notes with their note-offs (in source order)
    open_={}
    for i,(t,msg) in enumerate(evs):
        if msg.type=='note_on' and msg.velocity>0:
            open_.setdefault((msg.channel,msg.note),[]).append(i)
        elif msg.type=='note_off' or (msg.type=='note_on' and msg.velocity==0):
            q=open_.get((msg.channel,msg.note))
            if q: j=q.pop(0); dur[j]=t-evs[j][0]
    return labels,dur

def run(evs,labels,dur,limit=None):
    """Plays a track. Returns (events, loopStart, loopLen); stops at the first backward jump
    when limit is None, otherwise keeps looping until out time reaches limit."""
    out=[];pc=0;src=evs[0][0] if evs else 0;now=0;stack=[];seen={};loop=(None,None)
    steps=0
    while pc<len(evs):
        steps+=1
        if steps>2000000: break
        t,msg=evs[pc]
        now+=t-src; src=t
        if limit is not None and now>=limit: break
        if msg.type=='text':
            tx=msg.text
            if tx.startswith('LABEL'):
                seen.setdefault(int(tx[5:7]),now)
            elif tx.startswith('CALL'):
                n=int(tx[4:6]); stack.append((pc+1,src)); pc=labels[n]; src=evs[pc][0]; continue
            elif tx.startswith('JUMP'):
                n=int(tx[4:6]); tgt=labels[n]
                if n in seen and loop[0] is None:
                    loop=(seen[n],now-seen[n])
                    if limit is None: break
                pc=tgt; src=evs[pc][0]; continue
        elif msg.type=='marker' and len(msg.text)==1 and ord(msg.text)==0xFD:
            if stack:
                pc,src=stack.pop(); continue
        elif msg.type=='end_of_track':
            break
        elif msg.type=='note_on' and msg.velocity>0:
            d=dur.get(pc,1)
            out.append((now,0,msg.copy(time=0)))
            out.append((now+max(d,1),-1,mido.Message('note_off',channel=msg.channel,note=msg.note,velocity=0)))
        elif msg.type in('control_change','program_change','pitchwheel','set_tempo'):
            out.append((now,1,msg.copy(time=0)))
        pc+=1
    return out,loop

def convert(inp,outp,pmap=None):
    m,tracks=load(inp)
    info=[]
    for evs in tracks:
        lab,dur=prep(evs)
        _,loop=run(evs,lab,dur)
        info.append((lab,dur,loop))
    loops=[i[2] for i in info if i[2][0] is not None]
    if loops:
        S=max(l[0] for l in loops); L=max(l[1] for l in loops); end=S+L
    else:
        S=None; end=None
    om=mido.MidiFile(type=1,ticks_per_beat=m.ticks_per_beat)
    for ti,(evs,(lab,dur,loop)) in enumerate(zip(tracks,info)):
        if end is not None and loop[0] is not None:
            out,_=run(evs,lab,dur,limit=end)
        else:
            out,_=run(evs,lab,dur)
            if end is not None: out=[e for e in out if e[0]<end] + [(min(e[0],end),-1,e[2]) for e in out if e[0]>=end and e[2].type=='note_off']
        if end is not None:
            fixed=[]
            for t,pri,msg in out:
                if t>end and msg.type=='note_off': t=end
                if t>end: continue
                fixed.append((t,pri,msg))
            out=fixed
        # fold expression into volume, drop DS-only controllers, remap programs
        vol={};exp={};res=[]
        for t,pri,msg in sorted(out,key=lambda e:(e[0],e[1])):
            if msg.type=='control_change':
                c=msg.channel
                if msg.control==7: vol[c]=msg.value
                elif msg.control==11: exp[c]=msg.value
                elif msg.control in KEEP_CC: res.append((t,msg)); continue
                else: continue
                v=vol.get(c,127)*exp.get(c,127)//127
                res.append((t,mido.Message('control_change',channel=c,control=7,value=v))); continue
            if msg.type=='program_change' and pmap is not None:
                msg=msg.copy(program=pmap.get(str(msg.program),msg.program))
            res.append((t,msg))
        if ti==0 and S is not None:
            res.append((S,mido.MetaMessage('marker',text='[')))
            res.append((end,mido.MetaMessage('marker',text=']')))
            res.sort(key=lambda e:(e[0],0 if e[1].type=='marker' and e[1].text=='[' else 1))
        tr=mido.MidiTrack(); last=0
        for t,msg in res:
            tr.append(msg.copy(time=t-last)); last=t
        tr.append(mido.MetaMessage('end_of_track',time=0))
        om.tracks.append(tr)
    om.save(outp)
    return S,end

if __name__=='__main__':
    pm=json.load(open(sys.argv[3])) if len(sys.argv)>3 else None
    print(convert(sys.argv[1],sys.argv[2],pm))
