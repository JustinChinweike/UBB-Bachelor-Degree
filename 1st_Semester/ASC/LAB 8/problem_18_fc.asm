bits 32

global start
extern exit, printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

;Read a decimal number and a hexadecimal number from the keyboard. Display the number of 1's of the sum of the two numbers in decimal format. Example:
;a = 32 = 0010 0000b
;b = 1Ah = 0001 1010b
;32 + 1Ah = 0011 1010b
;The value printed on the screen will be 4



segment data use32 class=data
    a dd 0
    b dd 0
    whilee db 32
    
    A db 'a= ', 0
    B db 'b= ', 0
    format1 db '%d', 0
    format2 db '%x', 0
    
    result db 'the result is %d', 0

segment code use32 class=code
    start:
        push dword A
        call [printf]
        add esp, 4
        
        push dword a
        push format1
        call [scanf]
        add esp, 8
        
        push dword B
        call [printf]
        add esp, 4
        
        push dword b
        push format2
        call [scanf]
        add esp, 8
        
        mov eax, [a]
        add eax, [b]    ;eax:= a+b
        
        mov bl, 32  ; bl counts how many times we repeat the cycle
        mov bh, 0   ; in bh we keep the no 1s        
        repeat1:
            dec bl
            clc ; cf:=0
            rcr eax,1
            adc bh,0
            cmp bl,0
            jne repeat1
        
        mov eax, 0
        mov al,bh
        
        push eax
        push result
        call [printf]
        add esp, 8
        
        
        push dword 0
        call [exit]