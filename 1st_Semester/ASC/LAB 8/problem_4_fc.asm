bits 32

global start

extern exit, printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    a dd 0
    b dd 0
    
    A db 'a= ', 0
    B db 'b= ', 0
    format db '%d', 0
    result db '<%d>*<%d>=<%d>', 0

segment code use32 class=code
    start:
        push dword A
        call [printf]
        add esp, 4
        
        push dword a
        push format
        call [scanf]
        add esp, 8
        
        push dword B
        call [printf]
        add esp, 4
        
        push dword b
        push format
        call [scanf]
        add esp, 8
        
        mov eax, [a]
        mul byte[b]
        
        push eax
        push dword [b]
        push dword [a]
        push result
        call [printf]
        add esp, 16
        
        
        push dword 0
        call [exit]