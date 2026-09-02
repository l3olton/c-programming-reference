#!/bin/bash
set -e

gcc main.c -I../../../bin/include -L../../../bin/lib -larena -o example.out
LD_LIBRARY_PATH=../../../bin/lib ./example.out
