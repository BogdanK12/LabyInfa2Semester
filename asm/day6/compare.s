.global compare
.type compare,@function

compare:

       push %rbx
       xor %rcx, %rcx
       xor %rbx, %rbx

cycle:

       cmp %rdx, %rcx
       jge end
       movl (%rdi, %rcx, 4), %eax
       cmp $1, %eax
       jne next
       cmp (%rsi, %rcx, 4), %eax
       jne next
       inc %rbx

next:

       inc %rcx
       jmp cycle

end:

       movq %rbx, %rax
       pop %rbx
       ret
