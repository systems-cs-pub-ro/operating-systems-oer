section .bss

    buffer resb 128
    len equ 128

section .rodata

    hello db "Hello, world!", 10, 0
    bye db "Bye, world!", 10, 0

section .text

global main

main:
    push rbp
    mov rsp, rbp

    ; Call write(1, "Hello, world!\n", 14).
    ; rax <- __NR_write (index of write syscall: 1)
    ; rdi <- first syscall argument (fd: 1)
    ; rsi <- second syscall argument (buffer: hello)
    ; rdx <- third syscall argument (length: 14)
    mov rdi, 1
    mov rsi, hello
    mov rdx, 14
    mov rax, 1
    syscall

    ; Call write(1, "Bye, world!\n", 12).
    ; rax <- __NR_write (index of write syscall: 1)
    ; rdi <- first syscall argument (fd: 1)
    ; rsi <- second syscall argument (buffer: hello)
    ; rdx <- third syscall argument (length: 12)
    mov rdi, 1
    mov rsi, bye
    mov rdx, 12
    mov rax, 1
    syscall

    ; Call read(0, buffer, 128).
    ; rax <- __NR_read (index of read syscall: 0)
    ; rdi <- first syscall argument (fd: 0)
    ; rsi <- second syscall argument (buffer: buffer)
    ; rdx <- third syscall argument (length: len)
    mov rdi, 0
    mov rsi, buffer
    mov rdx, len
    mov rax, 0
    syscall

    ; Call write(1, buffer, size).
    ; rax <- __NR_write (index of write syscall: 1)
    ; rdi <- first syscall argument (fd: 1)
    ; rsi <- second syscall argument (buffer: buffer)
    ; rdx <- third syscall argument (length: size - rax)
    mov rdi, 1
    mov rsi, buffer
    mov rdx, rax
    mov rax, 1
    syscall

    ; Call pause().
    ; rax <- __NR_pause (index of pause syscall: 34)
    mov rax, 34
    syscall

    xor rax, rax
    leave
    ret
