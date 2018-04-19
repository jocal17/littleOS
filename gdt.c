#include "gdt.h"

struct gdt_entry entries[3];
struct gdt_ptr gdt;

void gdt_init()
{
        gdt.base = (uint32_t)&entries;
        gdt.limit = sizeof(struct gdt_entry) * 3 - 1;

        descriptor_init(0, 0, 0, 0);
        descriptor_init(1, 0, 0xFFFFFFFF, KERNEL_RX);
        descriptor_init(2, 0, 0xFFFFFFFF, KERNEL_RW);

        gdt_load((uint32_t)&gdt);

}

void descriptor_init(uint32_t n, uint32_t base, uint32_t limit, uint16_t flags)
{
        entries[n].base_low = base & 0xFFFF;
        entries[n].base_mid = (base >> 16) & 0xFF;
        entries[n].base_high = (base >> 24) & 0xFF;

        entries[n].limit_low = limit & 0xFFFF;
        entries[n].flags_high = (limit >> 16) & 0x0F;

        entries[n].flags_low = flags & 0xFF;
        entries[n].flags_high |= (flags >> 8) & 0xF0;

}
