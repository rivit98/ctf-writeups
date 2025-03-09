#!/bin/sh

mkdir unpacked
cd unpacked
cpio -idv < ../initramfs.cpio
