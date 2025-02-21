;  how can i make it to show the actual signed value not it s complementary code
bits 32

global start

extern exit, printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

segment data use32 class=data
    a dd 0  ; will store first value
    b dd 0  ; will store second value
    
    result db "the result is %i", 0
    A db "a= ", 0
    B db "b= ", 0
    format db "%i", 0
    
segment code use32 class=code
    start:
    
        push dword A    ; we will print 'a= '
        call [printf]
        add esp, 4*1
        
        push dword a    ; we will read a
        push dword format
        call [scanf]
        add esp, 4*2
        
        push dword B    ;we will print 'b= '
        call [printf]
        add esp, 4*1
        
        push dword b    ; we will read 'b= '
        push dword format
        call [scanf]
        add esp, 4*2
        
        mov eax, 0
        mov ax, [a] ;we calculate the value of a/b (signed) and store it in al
        mov bl, [b]
        idiv bl ; al:= a/b
        cbw
        cwde
        
        push eax     ; we print 'the result is ' a/b
        push dword result
        call [printf]
        add esp, 4*2
        
        push dword 0
        call [exit]
        