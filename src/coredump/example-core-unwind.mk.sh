#!/bin/sh
gcc -Os -Wall \
    -Wl,--start-group \
        -lunwind -lunwind-x86 -lunwind-coredump \
        example-core-unwind.c \
    -Wl,--end-group \
    -oexample-core-unwind
