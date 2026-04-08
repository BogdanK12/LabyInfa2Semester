.global ln2
.type ln2,@function

.L_delta:
        .double 0.0000001

ln2:

        movq $1, %rcx
        # cvtsi2sd %rcx, %xmm2
        cvtsi2sd %rcx, %xmm5
        cvtsi2sd %rcx, %xmm2

        # movq $3, %rcx
        # cvtsi2sd %rcx, %xmm3
        # divsd %xmm4, %xmm2

        # movq $1, %rcx
        xor %rcx, %rcx
        xorpd %xmm0, %xmm0
        movsd .L_delta(%rip), %xmm1 
        movq $4, %rdx
        cvtsi2sd %rdx, %xmm6
        xor %rcx, %rcx
        # xor %rdx, %rdx

        
cycle:
        # inc %rdx
        # cmp $20, %rdx
        # jg end
        inc %rcx
        movsd %xmm5, %xmm2
        cvtsi2sd %rcx, %xmm3

        divsd %xmm3, %xmm2
        
        movsd %xmm3, %xmm4
        mulsd %xmm4, %xmm4
        mulsd %xmm6, %xmm4
        subsd %xmm5, %xmm4

        divsd %xmm4, %xmm2

        ucomisd %xmm1, %xmm2
        jb end
        addsd %xmm2, %xmm0
        jmp cycle

end:

        addsd %xmm5, %xmm0
        movq $2, %rcx
        cvtsi2sd %rcx, %xmm4
        divsd %xmm4, %xmm0
        ret
