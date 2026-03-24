.globl sinius
.type sinius,@function

.LC_sign:
        .long 0x80000000

sinius:

        movq $1, %rdi
        movsd %xmm0, %xmm3
        movsd %xmm0, %xmm7

cycle:
        
        cmp $200, %rdi
        jge end
        movsd .LC_sign(%rip), %xmm1
        xorps %xmm1, %xmm7
        inc %rdi
        cvtsi2sd %rdi, %xmm1
        divsd %xmm1, %xmm7
        inc %rdi
        cvtsi2sd %rdi, %xmm1
        divsd %xmm1, %xmm7
        mulsd %xmm0, %xmm7
        mulsd %xmm0, %xmm7
        addsd %xmm7, %xmm3
        jmp cycle

end:

        movsd %xmm3, %xmm0
        ret
