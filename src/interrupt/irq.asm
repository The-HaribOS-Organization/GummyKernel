global irq_0
global irq_1
extern pit_handler
extern kboard_handler


irq_0:
    push byte 0
    push byte 32
    pushad
    push esp
    call pit_handler
    
    pop esp
    popad
    add esp, 8

    mov al, 0x20
    out 0x20, al
    iret

irq_1:
    push byte 0
    push byte 33
    pushad
    push esp
    call kboard_handler
    
    pop esp
    popad
    add esp, 8

    mov al, 0x20
    out 0x20, al
    iret
