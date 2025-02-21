;promblem 2_add&subb_signed
bits 32 
global start        

extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ;a - byte, b - word, c - double word, d - qword
    a db 4
    b dw 2
    c dd -5
    d dq 1

; our code starts here
segment code use32 class=code
    start:
        ;(c+b)-a-(d+d)
        mov bx,[b]
        cwd         ;dx:bx:=b
        
        push dx
        push bx
        pop ebx ;ebx:=b
        
        add ebx,[c] ;ebx:=(c+b)
        sub bl,[a]  ;ebx:=(c+b)-a
        mov eax,ebx ;eax:=(c+b)-a
        cdq         ;edx:eax:=(c+b)-a
        
        mov ebx,dword[d]
        mov ecx,dword[d+4]  ;ecx:ebx:=d
        add ebx,dword[d]    
        add ecx,dword[d+4]  ;ecx:ebx:=(d+d)
                
        sub eax,ebx
        sbb edx,ecx     ;eax:edx:=;(c+b)-a-(d+d)
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
