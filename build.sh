#! /usr/bin/env bash

clang -Ofast -march=native -Wall -pedantic -Ideps deps/cJson/cJSON.c src/main.c -o get-in
