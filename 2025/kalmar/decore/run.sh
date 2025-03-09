#!/bin/sh

qemu-system-x86_64 \
    -kernel ./bzImage \
    -initrd ./initramfs.cpio.gz \
    -append "console=ttyS0 loglevel=0 oops=panic" \
    -cpu kvm64,+smep,+smap \
    -smp 2 \
    -no-reboot -nographic -monitor none

