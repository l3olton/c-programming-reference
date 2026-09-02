#!/bin/bash
set -e

mkdir -p build ../../bin/lib ../../bin/include/allocators
gcc -fPIC -c arena.c -o build/arena.o
gcc -shared -o ../../bin/lib/libarena.so build/arena.o
cp arena.h ../../bin/include/allocators
# ln -sf arena.h ../../bin/include/allocators/arena.h
