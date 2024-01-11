#! /bin/bash

clang -pedantic -Wall -Werror -lm -std=c99 main.c -o main 
./main