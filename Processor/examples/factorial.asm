    in
    pop rax
    push rax

    to:  ;метка
    call func
    push rax
    push 1
    je end
    jmp to

;наша функция
    func:
    push 1
    push rax
    sub
    pop rax
    push rax
    mul
    ret

    end:
    out
    hlt
