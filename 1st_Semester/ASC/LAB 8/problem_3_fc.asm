; how do i show the signed value
bits 32

global start

extern exit, printf, scanf
import exit     msvcrt.dll
import printf   msvcrt.dll
import scanf    msvcrt.dll

segment data use32 class=data
    a dd 0
    b dd 0
    
    result db "<%d>+<%d>=<%d>", 0
    result2 db "<%d>", 0
    A db "a= ", 0
    B db "b= ", 0
    format db "%d", 0
    
segment code use32 class=code
    start:
        ; we print 'a= '
        push dword  A
        call [printf]
        add esp, 4
        
        ; we read a value for a
        push dword a
        push dword format
        call [scanf]
        add esp, 8
        
        ; we print 'b= '
        push dword B
        call [printf]
        add esp, 4
        
        ; we read a value for b
        push dword b
        push dword format
        call [scanf]
        add esp, 8
        
        mov eax, 0
        mov al, [a]
        add al, [b]
        push eax
        
        mov eax, [b]
        push eax
        
        mov eax, [a]
        push eax        
        
        push dword result
        call [printf]
        add esp, 16
        
        push dword 0
        call [exit]