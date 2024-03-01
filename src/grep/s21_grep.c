#include "s21_grep.h"

int main(int argc, char **argv) {
  if (argc >= 3) {
    Arguments arguments = parser(argc, argv);
    output(arguments, argc, argv);
    free(arguments.pattern);
  } else {
    perror("ERROR");
    exit(1);
  }
  return 0;
}

Arguments parser(int argc, char **argv) {
  Arguments arg = {0};
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        arg.e = 1;
        pattern_add(&arg, optarg);
        break;
      case 'i':
        arg.i = REG_ICASE;
        break;
      case 'v':
        arg.v = 1;
        break;
      case 'c':
        arg.c = 1;
        break;
      case 'l':
        arg.c = 1;
        arg.l = 1;
        break;
      case 'n':
        arg.n = 1;
        break;
      case 'h':
        arg.h = 1;
        break;
      case 's':
        arg.s = 1;
        break;
      case 'f':
        arg.f = 1;
        add_reg_from_file(&arg, optarg);
        break;
      case 'o':
        arg.o = 1;
        break;
      default:
        perror("ERROR");
        exit(1);
    }
  }
  if (arg.len_pattern == 0) {
    pattern_add(&arg, argv[optind]);
    optind++;
  }
  if (argc - optind == 1) {
    arg.h = 1;
  }
  return arg;
}

void pattern_add(Arguments *arg, char *pattern) {
  if (pattern == NULL) {
    printf("error");
    return;
  }
  int n = strlen(pattern);
  if (arg->len_pattern == 0) {
    arg->pattern = malloc(1024 * sizeof(char));
    arg->mem_pattern = 1024;
  }
  if (arg->mem_pattern < arg->len_pattern + n) {
    arg->pattern = realloc(arg->pattern, arg->mem_pattern * 2 * sizeof(char));
  }
  if (arg->len_pattern != 0) {
    strcat(arg->pattern + arg->len_pattern, "|");
    arg->len_pattern++;
  }
  arg->len_pattern += sprintf(arg->pattern + arg->len_pattern, "(%s)", pattern);
}

void add_reg_from_file(Arguments *arg, char *filepath) {
  FILE *fp = fopen(filepath, "r");
  if (fp == NULL) {
    if (!arg->s) perror(filepath);
    exit(1);
  }
  char line[ALLOC_SIZE];
  while (fgets(line, sizeof(line), fp) != NULL) {
    size_t read = strlen(line);
    if (line[read - 1] == '\n') {
      line[read - 1] = '\0';
      read--;
    }
    pattern_add(arg, line);
  }
  fclose(fp);
}

void output_line(char *line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') putchar('\n');
}

void print_match(regex_t *reg, char *line) {
  regmatch_t match;
  int offset = 0;
  while (1) {
    int result = regexec(reg, line + offset, 1, &match, 0);
    if (result != 0) break;
    for (int i = match.rm_so; i < match.rm_eo; i++) {
      putchar(line[offset + i]);
    }
    putchar('\n');
    offset += match.rm_eo;
  }
}

void process_file(Arguments arg, char *path, regex_t *reg) {
  FILE *fp = fopen(path, "r");
  if (fp == NULL) {
    if (!arg.s) perror(path);
    exit(1);
  }
  char line[ALLOC_SIZE];
  int line_count = 1;
  int c = 0;
  while (fgets(line, sizeof(line), fp) != NULL) {
    size_t read = strlen(line);
    if (line[read - 1] == '\n') {
      line[read - 1] = '\0';
      read--;
    }
    int result = regexec(reg, line, 0, NULL, 0);
    if ((result == 0 && !arg.v) || (arg.v && result != 0)) {
      if (!arg.c && !arg.l) {
        if (!arg.h) printf("%s:", path);
        if (arg.n) printf("%d:", line_count);
        if (arg.o)
          print_match(reg, line);
        else
          output_line(line, read);
      }
      c++;
    }
    line_count++;
  }
  if (arg.c && !arg.l) {
    if (!arg.h) printf("%s:", path);
    printf("%d\n", c);
  }
  if (arg.l && c > 0) printf("%s\n", path);
  fclose(fp);
}

void output(Arguments arg, int argc, char **argv) {
  regex_t reg;
  if (arg.pattern == NULL) {
    printf("error");
    return;
  }
  int error = regcomp(&reg, arg.pattern, REG_EXTENDED | arg.i);
  if (error) {
    perror("Error");
  }
  for (int i = optind; i < argc; i++) {
    process_file(arg, argv[i], &reg);
  }
  regfree(&reg);
}