; The following program reads text from "input.txt" and writes it to "output.txt".

bits 32

global start


;A file name is given in the data segment. Read from the console numbers in base 10,
 ;until 0 is met. Write to the file each number followed by the number of bits of 1 
 ;from its binary representation.

;Example:
;2 14 5 9

;out.txt
;2 - 1
;14 - 3
;5 - 2
;9 - 2



; Declare external functions needed by our program
extern exit, fopen, fread, fwrite, fclose, scanf 
import exit msvcrt.dll
import fopen msvcrt.dll
import fread msvcrt.dll
import fwrite msvcrt.dll
import fclose msvcrt.dll
import scanf msvcrt.dll

; Data segment
segment data use32 class=data
   
    output_file db "output.txt", 0    ; Output file name
    write_mode db "w", 0               ; Read mode
    
    output_fd dd -1                   ; File descriptor for output file
    len equ 100                  
    buffer times len db 0        

    text db  "we read %d from output.txt"
    format dd "%d",  0     

; Code segment
segment code use32 class=code
    start:
   
   
   read_write_loop: 
    ; read from the console 
      push dword text 
      push dword format 
      call [scanf] 
      add esp, 4*2

      

       ; Open output file for writing
       push dword write_mode
       push dword output_file
       call [fopen]
       add esp, 4*2
       mov [output_fd], eax

       ; Check if output file opened successfully
       cmp eax, 0
       je close_input

    

        ; Write data to output file: fwrite(buffer, 1, bytes_read, output_fd)
        push dword [output_fd]
        push eax            ; Number of bytes read
        push dword 1
        push dword buffer
        call [fwrite]
        add esp, 4*4

        jmp read_write_loop         ; Repeat until EOF

    close_input: 
        ; Close output file: fclose(output_fd)
        push dword [output_fd]
        call [fclose]
        add esp, 4

    

    final:
        ; Exit the program
        push dword 0
        call [exit]
