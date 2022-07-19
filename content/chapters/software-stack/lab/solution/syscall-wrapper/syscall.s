section .text

global read
global write
global getpid
global exit

read:
    ; rax <- __NR_read (index of read syscall: 0)
    ; rdi, rsi, rdx are the 3 arguments.
    ; As rdi, rsi, rdx are also the first 3 arguments in the x86_64 calling
    ; convention, they don't need to be changed.
    mov rax, 0
    syscall

    ret

write:
    ; rax <- __NR_write (index of write syscall: 1)
    ; rdi, rsi, rdx are the 3 arguments.
    ; As rdi, rsi, rdx are also the first 3 arguments in the x86_64 calling
    ; convention, they don't need to be changed.
    mov rax, 1
    syscall

    ret

getpid:
    ; rax <- __NR_getpid (index of getpid syscall: 1)
    ; There are no arguments.
    mov rax, 39
    syscall

    ret

exit:
    ; rax <- __NR_exit (index of exit syscall: 60)
    ; rdi is the argument.
    ; As rdi is also the first argument in the x86_64 calling convention,
    ; it doesn't need to be changed.
    mov rax, 60
    syscall

    ret
