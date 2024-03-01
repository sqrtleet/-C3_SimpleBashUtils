//
// Created by nikse on 25.02.2024.
//

#ifndef C3_SIMPLEBASHUTILS_1_S21_GREP_H

#include "getopt.h"
#include "regex.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define ALLOC_SIZE 1024

typedef struct Arguments {
  int e, i, v, c, l, n, h, s, f, o;
  char* pattern;
  int len_pattern;
  int mem_pattern;
} Arguments;

Arguments parser(int, char**);

void pattern_add(Arguments*, char*);

void add_reg_from_file(Arguments*, char*);

void output_line(char*, int);

void print_match(regex_t*, char*);

void process_file(Arguments, char*, regex_t*);

void output(Arguments, int, char**);
#define C3_SIMPLEBASHUTILS_1_S21_GREP_H

#endif  // C3_SIMPLEBASHUTILS_1_S21_GREP_H
