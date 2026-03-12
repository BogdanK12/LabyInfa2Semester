	.global findClosestToAverage
.type findClosestToAverage,@function

findClosestToAverage:

        push %rbx
        xor %rax, %rax
        xor %rcx,%rcx
        movq %rdx, %r9
        test %rsi, %rsi
        jz nullptr

cycle:
        cmp %rsi, %rcx
        jge prefind
        movslq (%rdi, %rcx, 4), %rbx
        addq %rbx, %rax
        inc %rcx
        jmp cycle

prefind:

        xor %rcx, %rcx
        cqo
        idiv %rsi
        leaq (%rdi), %rdx
        movslq (%rdi), %r8
        subq %rax, %r8
        cmp $0, %r8
        jge find
        negq %r8

find:

        cmp %rsi, %rcx
        jge end
        movslq (%rdi, %rcx, 4), %rbx
        subq %rax, %rbx        
        cmp $0, %rbx
        jg skip_module

module:

        negq %rbx

skip_module:

        cmp %r8, %rbx        
        jl swap

next_find:

        inc %rcx
        jmp find

swap:

        movq %rbx, %r8
        leaq (%rdi, %rcx, 4), %rdx
        jmp next_find

end:
        movq %rdx, (%r9)
        pop %rbx
        ret

nullptr:
        movq $0, (%r9)
        pop %rbx
        ret
