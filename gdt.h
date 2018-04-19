#ifndef GDT_H
#define GDT_H

#include "stdint.h"
/*
  Constants used as flags for each descriptor.
  We only implement two segments in our kernel
  at the moment: one for code and one for data.
*/
#define KERNEL_RX 0xCF9A
#define KERNEL_RW 0xCF92

/*
  The lgdt instruction expects a structure of this exact
  type to load the gdt.
*/

struct gdt_ptr {
        uint16_t limit;
        uint32_t base;
} __attribute__((packed));

/*
  A structure for each entry of the global descriptor table.
  Each entry is 64 consecutive bits interpreted as implied in
  the structure. The only oddity is that the 4 most significant bits of
  the limit must be stored in "flags_high" unless we want to use bit fields.
*/

struct gdt_entry {
        uint16_t limit_low;
        uint16_t base_low;
        uint8_t base_mid;
        uint8_t flags_low;
        uint8_t flags_high;
        uint8_t base_high;
} __attribute__((packed));

void gdt_init();
void descriptor_init(uint32_t n, uint32_t base, uint32_t limit, uint16_t flags);
void gdt_load(uint32_t g);

#endif
