section .data

section .text
    global _start

_start:
    mov rax, 60     ; syscall 'exit'
    mov rdi, 3      ; exit code 3
    syscall