[org 0x7c00]

mov ah, 0x0e

mov al, 'H'
int 0x10

mov al, "I"
int 0x10

halt:
   jmp halt

times 510 - ($ - $$) db 0
dw 0xaa55
