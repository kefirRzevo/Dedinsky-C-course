    push 10
    pop rbx

    label:
    call func1
    push rbx
    push 20
    ja label
    show
    hlt


        func1: 

        push 0
        pop rax 


            loop:
            call func
            push rax
            push 6.29
            ja loop
            jmp end


        func:
            push 60     ;Xc
            push rbx     ;R
            push 2
            mul
            push rax
            cos
            mul
            add
            pop rcx

            push 30     ;Yc
            push rbx     ;R
            push rax
            sin
            mul
            add
            pop rdx

            push rcx
            push rdx
            pix 'x'

            push rax
            push 0.05
            add
            pop rax
            ret
        end:
        push rbx
        push 1
        add
        pop rbx
    ret
