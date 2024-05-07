#!/bin/bash

make; clang -g3 ./test/main.c libclib.a -o test_runner; ./test_runner
