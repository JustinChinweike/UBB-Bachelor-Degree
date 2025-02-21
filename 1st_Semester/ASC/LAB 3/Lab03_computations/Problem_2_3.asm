bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a,b,d-byte; c-doubleword; x-qword
    a db 22h
    b db 33h
    d db 44h
    c dd 22334455h
    x dq 1122334455667788h
    k dd 0
; our code starts here
segment code use32 class=code
    start:
        ; (8-a*b*100+c)/d+x
        ;(1) a*b*100
        mov al,[a]
        mul byte[b]     ;ax:=a*b
        mov bx,100
        mul bx      ;dx:ax:=a*b*100
        
        ;(2) 8-a*b*100+c
        mov [k],ax
        mov [k+2],dx
        mov ebx,[k]     ;ebx:=a*b*100
        mov eax,8
        sub eax,ebx     ;eax:=(8-a*b*100)
        mov ebx,[c]     ;ebx:=c
        mov edx,0 
        add eax,ebx
        adc edx,0       ;edx:eax:=8-a*b*100+c
        
        ;(3) (8-a*b*100+c)/d
        mov ebx,[d]
        div ebx         ;eax:=(8-a*b*100+c)/d
        
        ;(4)  (8-a*b*100+c)/d+x
        mov edx,0       ;edx:eax:=(8-a*b*100+c)/d
        mov ebx,dword[x]
        mov ecx,dword[x+4]  ;ecx:ebx:=x
        
        add eax,ebx
        adc edx,ecx     ;edx:eax:=(8-a*b*100+c)/d+x
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
