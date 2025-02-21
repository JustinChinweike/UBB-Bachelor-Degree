bits 32
global start
extern exit
import exit msvcrt.dll

segment data use32 class=data
    sir DD 12345678h, 1256ABCDh, 12AB4344h
    len equ ($-sir)/4
    ord times len DW 0
    rez times len DD 0
    
segment code use32 class=code
    start:
    mov ecx,len
    mov esi,sir
    mov edi,ord
    
    repeat1:
    ; will put in ord low words from sir
        lodsw   ; will put in ax the low part of the dword
        stosw   ; will put in edi:= AX
        inc esi
        inc esi ; we move esi to the high word of the next dword
    loop repeat1

    mov dx, 1 ;dx will tell if the string ord  is sorted or not
    
    order:
        cmp dx,0
        je part2;;;
        
        mov esi, ord    ;prepare the parsing of string “ord”; set the starting offset in Esi
        mov dx,0    
        mov ecx, len-1
        
        repeat2:
            mov ax, word[esi]   ;ax = ord[i]
            mov bx, word[esi+2]
            cmp ax, bx     ;fictional substraction affecting flags of the word from ord and the next word
            jae next
            
            mov dx, word[esi+2] ;aux = ord[i+1];
            mov word[esi], dx   ; ord[i] = aux
            mov word[esi+2], ax ; ord[i+1] = ord[i];
            mov dx, 1   ;set dx in order to signalize that an interchange happened
            
            next:
                inc esi
                inc esi ; esi moves to the next word
                loop repeat2 ; resume repeat2 if we did not reach the end of string “ord”
                jmp order   ; otherwise resume the order cycle.
            
    ; ord is orderd descending

    part2:
        mov ecx,len
        mov esi,ord
        mov edi,rez
        repeat3:
            lodsw   
            stosw
            inc edi
            inc edi ; will put esi in rez on the second word of each dword (low word in forming dword)
        loop repeat3
        
        mov ecx,len
        mov esi,sir
        mov edi,rez
        
        repeat4:
            lodsw
            lodsw   ; copy in ax the high word
            inc edi
            inc edi ; will put esi in rez on the second word of each dword (low word in forming dword)
            stosw   ; store the high word
        loop repeat4
    
    
    push dword 0
    call [exit]
        
; question ---- example why 2xlodsd loads first low and than high part