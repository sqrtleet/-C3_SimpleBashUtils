//
// Created by nikse on 23.02.2024.
//

#ifndef C3_SIMPLEBASHUTILS_1_S21_CAT_H

// #define _GNU_SOURCE
#include "getopt.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define ALLOC_SIZE 1024

typedef struct Arguments {
  int b, n, s, E, T, v;
} Arguments;

Arguments parser(int, char **);

void output(Arguments *, char **);

void router(Arguments *, char *, size_t);

char option_v(char);

#define C3_SIMPLEBASHUTILS_1_S21_CAT_H

#endif  // C3_SIMPLEBASHUTILS_1_S21_CAT_H
