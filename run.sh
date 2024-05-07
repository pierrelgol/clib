#!/bin/bash

clang -g3 main.c libclib.a -o prog && ./prog
