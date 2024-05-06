#!/bin/bash

clang -g3 -fsanitize=memory main.c libclib.a -o test && ./test
