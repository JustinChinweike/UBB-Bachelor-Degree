;promblem 2_add&subb

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
    a db 9
    b dw 2
    c dd 3
    d dq 4

; our code starts here
segment code use32 class=code
    start:
        ;(b+b)+(c-a)+d
        mov bx,[b]
        add bx,[b]  ;BX:=(b+b)
        mov ah, 8
        mov eax,[c] ;EAX:=c
        sub al, byte[a] ;EAX:=(c-a)
        add ax,bx ;EAX:=(b+b)+(c-a)
        mov ebx, dword[d]
        mov ecx, dword[d+4] ;ebx:ecx:=d
        add ebx,eax ;ebx:ecx:=(b+b)+(c-a)+d
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
