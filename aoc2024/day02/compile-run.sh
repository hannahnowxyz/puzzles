#!/bin/bash
gcc -std=c99 -O3 -Wall -Wpedantic $1 -o test.bin && ./test.bin
