    ;Квадратка в ассемблере

    in ;a
    pop rax

    in ;b
    pop rbx

    in ;c
    pop rcx

                    ;если линейное ур-е
    push rax
    push 0
    je linear

    push 4          ;Дискриминант
    push rax
    mul
    push rcx
    mul
    push rbx
    push rbx
    mul
    sub
    pop rdx

    push rdx
    push 0          ;D=0
    je case_4       ;one root
    
    push rdx
    push 0
    ja case_3       ;D<0

    jmp case_5      ;D!=0 two roots


    linear:     
    push rbx
    push 0
    jne case_1      ;b!=0

                    ;b=0:
    push rcx
    push 0
    je case_2       ;c=0, all roots

    jmp case_3      ;b=0, c!=0, no roots


case_1:             ;one root linear
    push rbx
    push rcx
    div_
    push 1          ; = one root
    out
    out
    hlt

case_2:             ;all roots
    push -1         ; = all roots
    out
    hlt

case_3:             ;no roots (linear)
    push -2         ; = no roots
    out 
    hlt

case_4:             ;one root quadro
    push rax
    push rbx
    div_
    push -0.5
    mul
    push 1
    out 
    out
    hlt

case_5:             ;two roots
    push 2          ; = two roots
    out

    push 2          ;знаменатель
    push rax
    mul

    push rbx        ;числитель
    push -1
    mul
    push rdx
    sqrt_
    add

    div_
    out             ;first root


    push 2          ;знаменатель
    push rax
    mul

    push rdx        ;числитель
    sqrt_
    push rbx
    push -1
    mul
    sub

    div_
    out             ;second root
    hlt
