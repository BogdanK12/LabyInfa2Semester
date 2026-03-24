.globl discriminant
.type discriminant,@function

discriminant:
        fildq (%rsp)
        addq $8, %rsp
        fildq (%rsp)
        addq $8, %rsp
        fildq (%rsp)
        addq $8, %rsp
        fmul %st(2), %st(0)
        fld1

        fmul %st(0), %st(0)
        fmul %st(1), %st(0)
        subq $16, %rsp
        fildq (%rsp)
        addq $16, %rsp
        fmul %st(0), %st(0)
        fsub %st(1), %st(0)
        fistl (%rsp)

        ret
