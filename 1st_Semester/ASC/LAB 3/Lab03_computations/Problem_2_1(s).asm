bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a-byte; b-doubleword; c-qword
    a db 15
    b dd 3344h
    c dq 556677h

; our code starts here
segment code use32 class=code
    start:
        ; c+(a*a-b+7)/(2+a)
        ;(1) (a*a-b+7)
        mov al,[a]
        imul byte[a] ;ax:=a*a
        
        cwde     ;eax:=a*a
        sub eax,[b] ;eax:=a*a-b
        add eax,7
        
        ;(2)(a*a-b+7)/(2+a)
        mov bl,[a]
        mov bh,0
        add bl,2
        adc bh,0    ;bx:=2+a
        
        idiv bx  ;ax:=eax/bx=(a*a-b+7)/(2+a)
        mov bx,ax   ;bx:=eax/bx=(a*a-b+7)/(2+a)   
        
        ;(3) c+(a*a-b+7)/(2+a)
        mov eax,dword[c]
        mov edx,dword[c+4]  ;edx:eax:=cbits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...

; our code starts here
segment code use32 class=code
    start:
        ; ...
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack

        
        sub ax,bx
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
