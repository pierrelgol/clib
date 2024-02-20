#!/bin/bash

clang -Wall -Wextra -glldb -march=native -mtune=native -fsanitize=address -fsanitize=undefined -fsanitize=integer -fstrict-overflow test.c libplib.a  -o test

lldb ./test include/clib.h
