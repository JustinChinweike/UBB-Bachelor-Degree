extern printf
import printf msvcrt.dll

bits 32

segment data use32 class=data
    format_string db "%s ", 0       ; Format string for printf
    reverse_buffer times 100 db 0   ; Buffer for reversed word

segment code use32 class=code
global reverse_words

reverse_words:
    push ebp
    mov ebp, esp
    sub esp, 100                    ; Allocate space on the stack

    mov esi, [ebp + 8]             ; Pointer to the input string
    lea edi, [reverse_buffer]      ; Pointer to the buffer for reversed word

next_word:
    ; Skip leading spaces
    cmp byte [esi], 0
    je end_process                 ; End of string
    cmp byte [esi], ' '
    jne word_found
    inc esi
    jmp next_word

word_found:
    mov edx, esi                   ; Store starting position of the word
    mov ecx, 0                     ; Counter for word length

find_word_end:
    cmp byte [esi], 0
    je reverse                     ; End of string
    cmp byte [esi], ' '
    je reverse                     ; End of word
    inc esi
    inc ecx
    jmp find_word_end

reverse:
    dec esi                        ; Point to the last character of the word
    mov ebx, ecx                   ; Save word length for iteration

reverse_loop:
    cmp ebx, 0
    je print_word
    mov al, [esi]                  ; Read character
    mov [edi], al                  ; Write to buffer
    inc edi
    dec esi
    dec ebx
    jmp reverse_loop

print_word:
    mov byte [edi], 0              ; Null-terminate the reversed word
    push reverse_buffer            ; Push reversed word address
    push format_string             ; Push format string
    call [printf]                  ; Print the reversed word
    add esp, 8                     ; Clean up stack

    lea edi, [reverse_buffer]      ; Reset buffer pointer
    inc esi                        ; Move past the space
    jmp next_word

end_process:
    leave
    ret
