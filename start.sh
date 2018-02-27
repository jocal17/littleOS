#!/bin/bash

echo `nasm -f elf32 loader.s`
echo `ld -T link.ld -melf_i386 loader.o -o kernel.elf`
echo `cp kernel.elf iso/boot/`             # copy the kernel


echo `find . -name "stage2_eltorito " -exec cp "{}" /littleOS/iso/boot/grub \;`

echo `genisoimage -R                              \
                  -b boot/grub/stage2_eltorito    \
                  -no-emul-boot                   \
                  -boot-load-size 4               \
                  -A os                           \
                  -input-charset utf8             \
                  -quiet                          \
                  -boot-info-table                \
                  -o os.iso                       \
                  iso`


