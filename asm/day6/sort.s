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
	movw (%rdi, %rdx, 2), %bx
	movw 2(%rdi, %rdx, 2), %ax
	cmp %bx, %ax
	jl greater

inner_next:

	inc %rdx
	jmp inner_loop

greater:

	movw %ax, (%rdi, %rdx, 2)
	movw %bx, 2(%rdi, %rdx, 2)
	jmp inner_next

external_next:

	inc %rcx
	dec %r8
	jmp external_loop
end:

        pop %rbx
        ret
