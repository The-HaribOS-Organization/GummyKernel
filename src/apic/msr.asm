; Ce fichier contient les fonctions permettant
; d'accéder au MSR.

global getMSR
global setMSR

getMSR:
    mov eax, [esp+4]
    mov edx, [esp+8]
    mov ecx, [esp+12]
    rdmsr
    ret

setMSR:
    mov eax, [esp+8]
    mov edx, [esp+12]
    mov ecx, [esp+4]
    wrmsr
    ret
