.global sort

.type sort,@function

sort:

        push %rbx
        
	xor %rax, %rax
	xor %rbx, %rbx
	xor %rcx, %rcx

	dec %rsi
	movq %rsi, %r8

external_loop:

	xor %rdx, %rdx
	cmp %rsi, %rcx
	jg end

inner_loop:

	cmp %r8, %rdx
	jge external_next
	movl (%rdi, %rdx, 4), %ebx
	movl 4(%rdi, %rdx, 4), %eax
	cmp %ebx, %eax
	jl greater

inner_next:

	inc %rdx
	jmp inner_loop

greater:

	movl %eax, (%rdi, %rdx, 4)
	movl %ebx, 4(%rdi, %rdx, 4)
	jmp inner_next

external_next:

	inc %rcx
	dec %r8
	jmp external_loop



end:

        pop %rbx
        ret
