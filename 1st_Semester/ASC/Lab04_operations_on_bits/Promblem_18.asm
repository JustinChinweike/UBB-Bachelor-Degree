bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 0111011101010111b
    b dd 0

; our code starts here
segment code use32 class=code
    start:
        
        mov ebx,0 ; we compute the result in ebx
        
        ;the bits 0-3 of B have the value 0;
        and ebx,11111111111111111111111111110000b
        
        ;the bits 4-7 of B are the same as the bits 8-11 of A
        mov ax,[a]
        and ax,0000111100000000b
        mov cl,4
        ror ax,cl   ;
        mov dx,0
        push dx
        push ax
        pop eax
        or ebx,eax
        
        ;the bits 8-9 and 10-11 of B are the invert of the bits 0-1 of A (so 2 times) ;???????????
        mov ax,[a]  ;ax:=a
        not ax
        and ax,0000000000000011b ; ax has the first two bits of A
        mov dx,[a]
        not dx
        and dx,0000000000000011b   ;dx has the first two bits of A
        rol dx,2
        or ax,dx    ;ax has the the firt 4 bits the invert of the bits 0-1 of A (so 2 times)
        rol ax,8
        mov dx,0    ;ax:dx:= ax
        push dx
        push ax
        pop eax
        or ebx,eax
        
        ;bitii 12-15 ai lui B sunt biti de 1
        or ebx,00000000000000001111000000000000b 
        
        ;bitii 16-31 ai lui B sunt identici cu bitii 0-15 ai lui B.
        ;mov cl,16
        mov ax,bx
        rol ebx,16 ; the bits 16-31 of B are the previous 16 bits of B
        mov bx,ax
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
