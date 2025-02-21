bits 32
global start
extern exit
import exit msvcrt.dll

;Two byte strings S1 and S2 are given. Obtain the string D by concatenating the elements of S1 from the left hand side to the right hand side and the elements of S2 from the right hand side to the left hand side.
;Example:
;S1: 1, 2, 3, 4
;S2: 5, 6, 7
;D: 1, 2, 3, 4, 7, 6, 5


segment data use32 class=data
    S1 db 1, 2, 3, 4
    lenS1 equ $-S1
    S2 db 5, 6, 7
    lenS2 equ $-S2
    D times lenS1+lenS2 db 0
    
segment code use32 class=code
    start:
        mov esi,S1
        mov edi,D
        mov ecx,lenS1
        repeat1:
            CLD
            mov al, [esi]    ;moves byte in al
            inc esi          ;increases esi
            mov [edi],al     ;moves the byte from al in edi
            inc edi
            
            loop repeat1
            
        mov ecx,lenS2    
        mov esi,S2
        
        repeat2:
            std     ;df:=1
            lodsb   ;moves in al a byte from [esi] and increases esi
            cld     ;df:=0
            stosb
            loop repeat2
    
    push dword 0
    call [exit]
        
        
        
        