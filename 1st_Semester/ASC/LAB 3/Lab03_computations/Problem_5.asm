;promblem 2_mul&div_unsigned
bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ;a,b,c-byte; d-doubleword; e-qword
    a db 1
    b db 6
    c db 3
    d dd 4
    e dq 5

; our code starts here
segment code use32 class=code
    start:
        ;2/(a+b*c-9)+e-d
        mov al,[b]
        mul byte[c]         ;ax:=b*c
        
        mov bl,[a]
        mov bh,0            ;bx:=a
        
        add al,bl
        adc ah,bh           ;ax:=a+b*c
        
        sub ax,9            ;ax:=a+b*c-9
        mov bx,ax           ;bx:=a+b*c-9
        
        mov ax,2
        mov dx,0
        div bx              ;dx:=dx:ax%bx ax:=dx:ax/bx=2/(a+b*c-9)
        
        mov dx,0
        
        push dx
        push ax
        pop eax             ;eax:=2/(a+b*c-9)
        
        sub eax,[d]         ;eax:=2/(a+b*c-9)-d
        mov edx,0
        
        mov ebx,[e]
        mov ecx,[e+4]       ;ecx:ebx:=e
        
        add eax,ebx
        adc edx,ecx         ;edx:eax:=2/(a+b*c-9)+e-d
        
       
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
