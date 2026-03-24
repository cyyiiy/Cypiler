section .data
    msg0 db "Hello, World!", 10
    len0 equ $ - msg0

section .text
    global _start

_start:
    mov rax, 1      ; syscall 'print'
    mov rdi, 1      ; file descriptor 1 (write)
    mov rsi, msg0   ; text address
    mov rdx, len0   ; text length
    syscall

    mov rax, 60     ; syscall 'exit'
    mov rdi, 0      ; exit code 0
    syscall