#!/bin/bash

echo `nasm -f elf32 loader.s`
echo `ld -T link.ld -melf_i386 loader.o -o kernel.elf`

echo `mkdir -p iso/boot/grub`              # create the folder structure
echo `mv stage2_eltorito iso/boot/grub/`   # copy the bootloader
echo `cp kernel.elf iso/boot/`             # copy the kernel
echo `touch iso/boot/grub/menu.lst`
echo `echo "default=0
timeout=0

title os
kernel /boot/kernel.elf" > iso/boot/grub/menu.lst`
