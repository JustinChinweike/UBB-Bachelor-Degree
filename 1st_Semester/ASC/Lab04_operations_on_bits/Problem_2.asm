bits 32 

global start        

extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 0111011101010111b
    b dw 1001101110111110b
    c dd 0

; our code starts here
segment code use32 class=code
    start:
        mov  bx, 0
        ;the bits 0-3 of C are the same as the bits 5-8 of B
        mov ax,[b]
        and ax, 0000000111100000b
        ;mov cl,5
        ror ax,5
        or bx,ax    ;bx:= first 4 bites are bites 5-8 from b
        ;the bits 4-8 of C are the same as the bits 0-4 of A
        mov ax,[a]
        and ax, 0000000000001111b
        mov cl,4
        rol ax,cl
        or bx,ax
        ;the bits 9-15 of C are the same as the bits 6-12 of A
        mov ax,[a]
        and ax, 0001111111000000b
        mov cl,3
        rol ax,cl
        or bx,ax
        ;the bits 16-31 of C are the same as the bits of B
        mov dx,[b]
        push dx
        push bx
        pop ebx
        
        mov [c],ebx
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
