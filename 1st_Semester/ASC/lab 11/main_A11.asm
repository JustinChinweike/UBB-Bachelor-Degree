bits 32

global start        

extern printf, scanf, exit, reverse_words

import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    input db 100                  ; Buffer for input string
    format_string db "%99[^\n]", 0  ; Read up to 99 characters, stopping at newline
    prompt db "Enter a sentence: ", 0 

segment code use32 class=code
start:
    ; Prompt user for input
    push prompt
    call [printf]
    add esp, 4

    ; Read input from keyboard
    push input
    push format_string
    call [scanf]
    add esp, 8

    ; Call reverse_words function
    push input
    call reverse_words
    add esp, 4

    ; Exit program
    push dword 0
    call [exit]
