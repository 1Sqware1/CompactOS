MULTIBOOT_MAGIC equ 0x1BADB002
MULTIBOOT_FLAGS equ 0x00
MULTIBOOT_CHECKSUM equ -(MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)

section .multiboot
align 4
   dd MULTIBOOT_MAGIC
   dd MULTIBOOT_FLAGS
   dd MULTIBOOT_CHECKSUM

section .text
global _start
extern kernel_main

_start:
     cli
     mov esp, stack_space
     call kernel_main

.halt:
     hlt
     jmp .halt

section .bss
resb 8192
stack_space:

; yes, AI help me withn this. I dont want learn NASM T_T
