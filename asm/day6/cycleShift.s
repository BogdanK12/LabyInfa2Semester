.global cycleShift
.type cycleShift,@function

cycleShift:

        push %rbx
        call compare
        movq %rax, %rbx

cycle:
        lea (%rsi),  %rdx
        

end:

        ret        
