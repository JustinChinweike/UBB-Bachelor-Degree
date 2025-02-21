bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 1
    b db 2
    c db 3
    d dw 4
; our code starts here
segment code use32 class=code
    start:
        ;d*(d+2*a)/(b*c)
        mov al,[a]      ;AL:=a
        mov ah,2        ;AH:=2
        mul ah          ;AX:AL*AH=a*2
        add al,[d]      ;AX:=AX+d=(d+2*a)
        mul word [d]    ;DX:AX:=AX*d
        mov bx,ax       ;BX:=AX=d*(d+2*a)
        mov ax,[b]      ;AX:=b
        mul byte [c]    ;AX:=AX*c=(b*c)
        mov cx,ax       ;CX:=AX=(b*c)       
        mov ax,bx       ;AX:=BX=d*(d+2*a)
        div cx
        
        
        
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
