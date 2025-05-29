global irq_0
global irq_1
global irq_12
extern pit_handler
extern kboard_handler
extern mouse_handler


irq_0:
    push byte 0
    push byte 0x20
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
    push byte 0x21
    pushad
    push esp
    call kboard_handler
    
    pop esp
    popad
    add esp, 8

    mov al, 0x20
    out 0x20, al
    iret

irq_12:
    push byte 0
    push byte 0x2C
    pushad
    push esp
    call mouse_handler
    
    pop esp
    popad
    add esp, 8

    mov al, 0x20
    out 0xA0, al
    out 0x20, al
    iret
