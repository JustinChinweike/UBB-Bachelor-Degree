bits 32
global start

extern exit, printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    a dd 0
    
    number db "the number in base 10 is ", 0
    format db "%d", 0
    result db "the number in base 16 is %x", 0
    
segment code use32 class=code
    start:
        push dword number
        call [printf]
        add esp, 4
        
        push a
        push dword format
        call [scanf]
        add esp, 8
        
        mov eax,[a]
        
        push eax
        push result
        call [printf]
        add esp, 8
        
        push dword 0
        call [exit]