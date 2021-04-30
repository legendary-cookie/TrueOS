#!/bin/bash
nasm testloader.asm -fbin -o boot.bin
qemu-system-x86_64 boot.bin
