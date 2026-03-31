.globl integral
.type integral,@function

.L_parts:
        .double 10000.0 
.L_two:
        .double 2.0

integral:
        subq $8, %rsp
        movsd %xmm0, %xmm1
        movsd %xmm0, %xmm4

        movsd .L_parts(%rip), %xmm2
        divsd %xmm2, %xmm1

        movsd %xmm1, %xmm2 

        movsd .L_two(%rip), %xmm5
        divsd %xmm5, %xmm1

        xorpd %xmm3, %xmm3
        
cycle:

        ucomisd %xmm4, %xmm1
        jae end
        movsd %xmm1, %xmm0
        subq $16, %rsp
        movdqu %xmm1, (%rsp)
        subq $16, %rsp
        movdqu %xmm2, (%rsp)
        subq $16, %rsp
        movdqu %xmm3, (%rsp)
        subq $16, %rsp
        movdqu %xmm4, (%rsp)
        subq $16, %rsp
        movdqu %xmm7, (%rsp)

        call sin

        movdqu (%rsp), %xmm7
        addq $16, %rsp
        movdqu (%rsp), %xmm4
        addq $16, %rsp
        movdqu (%rsp), %xmm3
        addq $16, %rsp
        movdqu (%rsp), %xmm2
        addq $16, %rsp
        movdqu (%rsp), %xmm1
        addq $16, %rsp

        xorpd %xmm5, %xmm5

        addsd %xmm0, %xmm5
        
        movsd %xmm1, %xmm0
        mulsd %xmm0, %xmm0
        addsd %xmm0, %xmm5

        mulsd %xmm2, %xmm5

        addsd %xmm5, %xmm3


cycle_next:

        addsd %xmm2, %xmm1
        jmp cycle

end:
        movsd %xmm3, %xmm0
        addq $8, %rsp
        ret
