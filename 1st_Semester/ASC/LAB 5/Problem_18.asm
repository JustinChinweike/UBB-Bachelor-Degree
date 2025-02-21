bits 32
global start
extern exit
import exit msvcrt.dll

segment data use32 class=data
    ;A: 2, 1, 3, -3
    ;B: 4, 5, -5, 7
    ;R: 1, 3, 5, 7
    a db 2,1,3,-3
    lenA equ $-a
    b db 4,5,-5,7
    lenB equ $-b
    r times lenA+lenB db 0
    
segment code use32 class=code
    start:
        mov esi, 0
        mov ecx, lenA
        mov edi,0
        repeat:
            mov bl,[a+esi]   ; bl=[esi], esi+=1
            mov al,bl        ; al:=bl
            and al,00000001b ; al:=00000000+last bit of a1  
            cmp al,0
            ja check_sign1
            check_sign1:    ; checks if a number is positive
                cmp bl,0
                jge add_number1
        
            add_number1:    ; adds a number if it s positive and odd
                mov [r+edi],bl
                inc edi                
            
            inc esi
            loop repeat
    
        mov esi, 0
        mov ecx, lenA
        repeat2:
            mov bl,[b+esi]
            mov al,bl
            and al,00000001b ; al:=00000000+last bit of a1  
            cmp al,0
            ja check_sign2
            check_sign2:    ; checks if a number is positive
                cmp bl,0
                jge add_number2
        
            add_number2:    ; adds a number if it s positive and odd
                mov [r+edi],bl
                inc edi                
            
            inc esi
            loop repeat2

    push dword 0
    call [exit]
    
    
    
    ;adds all numbers???