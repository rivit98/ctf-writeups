#!/bin/sh

set -e

DIR=$(mktemp -d)
trap "rm -rf $DIR" EXIT

cd $DIR
cp /app/rootfs.img .
cp /app/bootloader.bin .

timeout 10m qemu-system-i386 \
    -nographic \
    -serial none \
    -serial mon:stdio \
    -m 1096M \
    -rtc base=localtime \
    -nodefaults \
    -no-reboot \
    -drive file=./rootfs.img,format=raw,if=ide,index=0,media=disk \
    -kernel ./bootloader.bin
