bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 1010111010101110b
    b db 10101110b
    c dd 0

; our code starts here
segment code use32 class=code
    start:
        mov ebx,0
        ; the bits 0-3 of C are the same as the bits 6-9 of A
        mov ax,[a]
        and ax,0000001111000000b    ;we keep only bits 6-9 of A
        ror ax,6   
        or bx,ax   ; the bits 0-3 are changed 
        
        ;the bits 4-5 of C have the value 1
        or bx,0000000000110000b
        
        ;the bits 6-7 of C are the same as the bits 1-2 of B
        mov al,[b]
        and al,00000110b ; we keep the bits 1-2
        rol al,5
        or bl,al    ; the bits 6-7 are changed
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
