[bits 32]
[section .text]
global enable_A20
enable_A20:
        cli
 
        call    a20wait
        mov     al,0xAD
        out     0x64,al
 
        call    a20wait
        mov     al,0xD0
        out     0x64,al
 
        call    a20wait2
        in      al,0x60
        push    eax
 
        call    a20wait
        mov     al,0xD1
        out     0x64,al
 
        call    a20wait
        pop     eax
        or      al,2
        out     0x60,al
 
        call    a20wait
        mov     al,0xAE
        out     0x64,al
 
        call    a20wait
        sti
        ret

global a20wait
a20wait:
        in      al,0x64
        test    al,2
        jnz     a20wait
        ret
 
global a20wait2
a20wait2:
        in      al,0x64
        test    al,1
        jz      a20wait2
        ret
