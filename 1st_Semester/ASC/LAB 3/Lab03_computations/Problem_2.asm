;promblem 17_add&subb

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
    c dd 5
    d dq 1

; our code starts here
segment code use32 class=code
    start:
        ; (c+c-a)-(d+d)-b
        mov eax,[c]
        add eax,[c] ;EAX:=(c+c)
        sub al,[a]  ;EDX:EAX:=(c+c-a)
        mov ebx,dword[d]
        mov ecx,dword[d+4]  ;ecx:ebx:=d
        add ebx,dword[d]    
        add ebx,dword[d+4]  ;ecx:ebx:=(d+d) 
        sub eax,ebx
        sub edx,ecx     ;EDX:EAX:=(c+c-a)-(d+d)
        sub ax,[b]
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
