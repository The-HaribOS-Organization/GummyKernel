global load_page_directory
global enable_paging


enable_paging:

    push ebp
    mov ebp, esp
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax
    mov esp, ebp
    pop ebp
    ret

load_page_directory:

    push ebp
    mov ebp, esp
    mov eax, [esp + 8]
    mov cr3, eax

    mov esp, ebp
    pop ebp
    ret
