bits 32
global start
extern exit
import exit msvcrt.dll

segment data use32 class=data
    S db 1,2,3,4    ; declare the string of bytes
    len equ $-S     ; compute the length of the string in len
    D times len-1 db 0      ; reserve len-1 bytes for the destination string and initialize it
    
segment code use32 class=code
    start:
        mov ecx,len-1   ; we put the length len - 1 in ECX in order to make a loop of len-1 steps
        mov esi,S   ;we put string S in esi
        mov edi,D   ;we put string D in edi
        
        repeat:
            mov al,[esi]  ;al takes bytes form s
            mul byte[esi+1]     ;we multiply al with the next byte from S
            
            mov [edi],al    ; we move al in the byte of edi 
            inc esi ; esi moves to the next byte
            inc edi ; edi moves to the next byte
            
        loop repeat
    
        push dword 0
        call [exit]
        
