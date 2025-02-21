bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; a - byte, b - word, c - double word, d - qword
    a db 11h
    b dw 1122h
    c dd 998877h
    d dq 99887766h
    
; our code starts here
segment code use32 class=code
    start:
        ; (d+c) - (c+b) - (b+a)
        ; 1. d+c
        mov eax,[d]     ; eax:= the least important doublew of d
        mov edx,[d+4]   ; edx:= the most important doublew of d
        
        add eax,[c]
        adc edx,0       ; eax:edx:= d+c
        
        ; 2. d+c - (c+b)
        mov ebx,[c]     ;ebx:= c
        add bx, [b]     ;ebx:= b+c
        
        sub eax,ebx     ;eax:edx:= d+c - (c+b)
        ;...
      
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
