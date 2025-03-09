#!/bin/bash

rm -f 'libfake.so (deleted)' libfoo.so libfake.so main
rm -rf ./unpacked/home/ctf/*

gcc -s -shared -o libfoo.so lib.c
gcc -s -shared -o libfake.so dummy.c

gcc -L. -o main main.c -lfoo -lfake -lpthread -s
patchelf --replace-needed libfoo.so ./libfoo.so main
patchelf --replace-needed libfake.so ./libfake.so main

cp ./libfoo.so libfake.so ./main ./unpacked/home/ctf

./pack.sh >/dev/null 2>&1
