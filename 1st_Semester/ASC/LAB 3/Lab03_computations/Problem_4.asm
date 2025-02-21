;promblem 17_add&subb_signed
bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ;a - byte, b - word, c - double word, d - qword
    a db 4
    b dw 2
    c dd -5
    d dq 1

; our code starts here
segment code use32 class=code
    start:
        ;(c+d-a)-(d-c)-b
        mov eax,[c]
        cdq                 ;edx:eax:=c
        add eax,dword[d]
        adc edx,dword[d+4]  ;edx:eax:=c+d
        sub al,[a]          ;edx:eax:=c+d-a
        
        mov ebx,eax
        mov ecx,edx         ;ecx:ebx:=c+d-a
        
        mov eax,dword[d]
        mov edx,dword[d+4]  ;edx:eax:=d  
        sub eax,[c]         ;edx:eax:=d-c
        
        sub ebx,eax
        sbb ecx,edx         ;ecx:ebx:=(c+d-a)-(d-c)
        
        sub bx,[b]          ;ecx:ebx:=(c+d-a)-(d-c)-b
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
