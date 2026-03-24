.globl factorial
.type factorial,@function

factorial:

        movq $1, %rax
        
cycle:

        cmp $0, %rdi
        jle end
        mul %rdi
        dec %rdi
        jmp cycle

end:

        ret        
