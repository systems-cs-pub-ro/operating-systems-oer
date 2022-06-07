.section .bss

    .lcomm buffer, 128

.equ len, 128

.section .rodata

hello:
    .ascii "Hello, world!\n\0"

bye:
    .ascii "Bye, world!\n\0"

.section .text

.global main

main:
    /* Call write(1, "Hello, world!\n", 14). */
    /* rax <- __NR_write (index of write syscall: 1) */
    /* rdi <- first syscall argument (fd: 1) */
    /* rsi <- second syscall argument (buffer: hello) */
    /* rdx <- third syscall argument (length: 14) */
    mov x0, #1
    ldr x1, =hello
    mov x2, #14
    mov x8, #64
    svc #0

    /* Call exit(0). */
    /* rax <- __NR_exit (index of exit syscall: 60) */
    /* rdi <- first syscall argument (error_code: 0) */
    mov x0, #0
    mov x8, #93
    svc #0

    ret
