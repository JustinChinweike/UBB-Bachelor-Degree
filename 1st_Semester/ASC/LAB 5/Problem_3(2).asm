bits 32
global start
extern exit
import exit msvcrt.dll

;Two byte strings S1 and S2 are given. Obtain the string D by concatenating the elements of S1 from the left hand side to the right hand side and the elements of S2 from the right hand side to the left hand side.
;Example:
;S1: 1, 2, 3, 4
;S2: 5, 6, 7
;D: 1, 2, 3, 4, 7, 6, 5

;can we use cld, std????
segment data use32 class=data
    S1 db 1, 2, 3, 4
    lenS1 equ $-S1
    S2 db 5, 6, 7
    lenS2 equ $-S2
    D times lenS1+lenS2 db 0
    
segment code use32 class=code
    start:
        mov esi,S1   ;moves S1 in esi
        mov edi,D   ;moves D in edi
        mov ecx,lenS1   ;moves lenS1 in ecx in order to perform the loop lenS1 times
        CLD     ;DF = 0
        repeat1:
            CLD
            mov al, [esi]    ;moves byte from in al
            inc esi          ;moves esi to the next byte in S1
            mov [edi],al     ;moves the byte from al in edi
            inc edi         ;moves edi to the next byte in D
            loop repeat1
            
        mov ecx,lenS2   ;moves lenS2 in ecx in order to perform the loop lenS1 times  
        mov esi,lenS2-1     ;moves lenS2-1 in esi in order to start from the end of the strin
        
        repeat2:
            mov al,[S2+esi]     ;moves in al byte(from the right)  ----> can we use cld, std????
            mov [edi],al    ;moves the byte in edi
            dec esi     ;esi -= 1
            inc edi     ;moves edi to the next byte
            loop repeat2
    
    push dword 0
    call [exit]
        
        
        
        