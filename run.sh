#!/bin/bash

clang -Wall -Wextra -glldb -march=native -mtune=native -fsanitize=address -fsanitize=undefined -fsanitize=integer -fstrict-overflow main.c libplib.a  -o test

./test
