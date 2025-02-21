bits 32
global start
extern exit
import exit msvcrt.dll


; copies all of them ????????

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
        mov esi, a  ;moves in esi string a
        mov ecx, lenA   ; moves in ecx lenA
        mov edi, r  ;moves in edi string r
        
        repeat1:
            mov al,[esi]   ; moves in al byte from esi
            test al,00000001b   ; performs a fictive and btw. al and 00000001b
            jnz check_sign1     ; jums to check_sign1 if zf = 0 which means the last bit of al is 1
            check_sign1:    ; checks if a number is positive
                test al,10000000b   ; performs a fictive and btw. al and 10000000b
                jz add_number1     ; jums to add_number1 if zf = 1 which means the first bit of al is 0
        
            add_number1:    ; adds a number if it s positive and odd
                mov [edi],al
                inc edi                
            
            inc esi ; moves esi to the next byte in a
            loop repeat1
    
        mov esi, b  ;moves in esi string b
        mov ecx, lenB   ; moves in ecx lenB
        repeat2:
            mov al,[esi]
            test al,00000001b   ; performs a fictive and btw. al and 00000001b
            jnz check_sign2     ; jums to check_sign2 if zf = 0 which means the last bit of al is 1
            check_sign2:    ; checks if a number is positive
                test al,10000000b   ; performs a fictive and btw. al and 10000000b
                jz add_number2     ; jums to add_number2 if zf = 1 which means the first bit of al is 0
        
            add_number2:    ; adds a number if it s positive and odd
                mov [edi],al
                inc edi                  
            
            inc esi ; moves esi to the next byte in b
            loop repeat2

    push dword 0
    call [exit]
    
    
    
    ;adds all numbers???