.globl sinius
.type sinius,@function

.LC_sign:
        .quad 0x8000000000000000

.LC_minus:
        .quad 0x7fffffffffffffff
        .quad 0x7fffffffffffffff

.LC_limit:
        .double 0.000001

sinius:

        movq $1, %rcx
        movsd %xmm0, %xmm3
        movsd %xmm0, %xmm7
        movsd %xmm0, %xmm2
        mulsd %xmm0, %xmm2
        movsd .LC_sign(%rip), %xmm1
        xorps %xmm1, %xmm2
        movsd .LC_limit(%rip), %xmm4
                

cycle:

        # cmp $25, %rcx
        # jge end
        mulsd %xmm2, %xmm7

        inc %rcx
        cvtsi2sd %rcx, %xmm1
        divsd %xmm1, %xmm7
        inc %rcx
        cvtsi2sd %rcx, %xmm1
        divsd %xmm1, %xmm7

        movsd %xmm7, %xmm1
        movsd .LC_minus(%rip), %xmm5
        andpd %xmm5, %xmm1
        ucomisd %xmm4, %xmm1
        jb end
        addsd %xmm7, %xmm3
        jmp cycle


end:

        movsd %xmm3, %xmm0
        ret
