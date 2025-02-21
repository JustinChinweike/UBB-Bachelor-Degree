bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 1100101011001010b
    b dw 0101110001011100b
    c dd 0

; our code starts here
segment code use32 class=code
    start:
        ;compute the result in ebx
        mov ebx,0
        ;(1) bitii 0-6 ai lui C au valoarea 0
        and ebx,00000000000000000000000000000000b
        
        ;(2)bitii 7-9 ai lui C coincid cu bitii 0-2 ai lui A
        mov ax,[a]
        and ax,0000000000000111b    ; ax has 0 everywhere but 0-2
        rol ax,7
        or bx,ax    ; bits 7-9 of ebx are bits 0-2 of a
        
        ;(3)bitii 10-15 ai lui C coincid cu bitii 8-13 ai lui B
        mov ax,[b]
        and ax,0011111100000000b
        rol ax,2
        or bx,ax    ;bits 10-15 of ebx are bits 8-13 of B
        
        ;(4)
        rol ebx,16
        or bx,1111111111111111b
        rol ebx,16
        ;11111111111111110111000100000000b
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
