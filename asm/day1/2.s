.globl _start

.data
message: .asciz "Hello, world!"

.text
_start:

        movq $message, %rsi
        movq $1, %rdi
        movq $13, %rdx
        movq $1, %rax
        syscall

        movq $60, %rax
        syscall
