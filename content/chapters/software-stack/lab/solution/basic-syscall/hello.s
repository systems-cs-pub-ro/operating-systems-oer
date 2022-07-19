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
    push %rbp
    mov %rsp, %rbp

    # Call write(1, "Hello, world!\n", 14).
    # rax <- __NR_write (index of write syscall: 1)
    # rdi <- first syscall argument (fd: 1)
    # rsi <- second syscall argument (buffer: hello)
    # rdx <- third syscall argument (length: 14)
    mov $1, %rdi
    lea hello, %rsi
    mov $14, %rdx
    mov $1, %rax
    syscall

    # Call write(1, "Bye, world!\n", 12).
    # rax <- __NR_write (index of write syscall: 1)
    # rdi <- first syscall argument (fd: 1)
    # rsi <- second syscall argument (buffer: hello)
    # rdx <- third syscall argument (length: 12)
    mov $1, %rdi
    lea bye, %rsi
    mov $12, %rdx
    mov $1, %rax
    syscall

    # Call read(0, buffer, 128).
    # rax <- __NR_read (index of read syscall: 0)
    # rdi <- first syscall argument (fd: 0)
    # rsi <- second syscall argument (buffer: buffer)
    # rdx <- third syscall argument (length: len)
    mov $0, %rdi
    lea buffer, %rsi
    lea len, %rdx
    mov $0, %rax
    syscall

    # Call write(1, buffer, size).
    # rax <- __NR_write (index of write syscall: 1)
    # rdi <- first syscall argument (fd: 1)
    # rsi <- second syscall argument (buffer: buffer)
    # rdx <- third syscall argument (length: size - rax)
    mov $1, %rdi
    lea buffer, %rsi
    mov %rax, %rdx
    mov $1, %rax
    syscall

    # Call pause().
    # rax <- __NR_pause (index of pause syscall: 34)
    mov $34, %rax
    syscall

    # Call exit(0).
    # rax <- __NR_exit (index of exit syscall: 60)
    # rdi <- first syscall argument (error_code: 0)
    mov $0, %rdi
    mov $60, %rax
    syscall

    xor %rax, %rax
    leave
    ret
