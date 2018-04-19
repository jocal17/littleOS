global gdt_load

section .text

gdt_load:
        mov eax, [esp + 4]      ; expects gdt pointer as argument.
        lgdt [eax]              ; instruction to load gdt.

        jmp 0x08:.reload_segments

.reload_segments:
        ; we only use one segment for data
        mov     ax, 0x10
        mov     ds, ax
        mov     ss, ax
        mov     es, ax
        mov     gs, ax
        mov     fs, ax
        ret
