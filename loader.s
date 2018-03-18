        global loader
        extern sum_of_three

        MAGIC_NUMBER equ 0x1BADB002
        FLAGS        equ 0x0
        CHECKSUM     equ -MAGIC_NUMBER


        section .text
        align 4
        dd MAGIC_NUMBER
        dd FLAGS
        dd CHECKSUM

loader:
        KERNEL_STACK_SIZE equ 4096
        mov esp, kernel_stack + KERNEL_STACK_SIZE
        push dword 3
        push dword 2
        push dword 1
        call sum_of_three

.loop:
        jmp .loop


        section .bss
        align 4

kernel_stack:
        resb KERNEL_STACK_SIZE


