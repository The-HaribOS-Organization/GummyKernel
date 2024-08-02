global setIDT


setIDT:

    mov eax, [esp+4]
    lidt [eax]
    ret
