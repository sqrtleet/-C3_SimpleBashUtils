#include "s21_cat.h"

int main(int argc, char **argv) {
  if (argc >= 2) {
    Arguments arguments = parser(argc, argv);
    output(&arguments, argv);
  } else {
    perror("ERROR");
    exit(1);
  }
  return 0;
}
// Разбор аргументов с помощью getopt()
Arguments parser(int argc, char **argv) {
  Arguments args = {0};
  struct option long_options[] = {{"number", no_argument, NULL, 'n'},
                                  {"number-nonblank", no_argument, NULL, 'b'},
                                  {"squeeze-blank", no_argument, NULL, 's'},
                                  {0, 0, 0, 0}};
  int opt;
  while ((opt = getopt_long(argc, argv, "bnEeTtsv", long_options, 0)) != -1) {
    switch (opt) {
      case 'b':
        args.b = 1;
        break;
      case 'n':
        args.n = 1;
        break;
      case 'e':
        args.E = 1;
        args.v = 1;
        break;
      case 'E':
        args.E = 1;
        break;
      case 't':
        args.T = 1;
        args.v = 1;
        break;
      case 'T':
        args.T = 1;
        break;
      case 's':
        args.s = 1;
        break;
      default:
        perror("ERROR");
        exit(1);
    }
  }
  return args;
}

void output(Arguments *args, char **argv) {
  FILE *fp = fopen(argv[optind], "r");
  if (fp == NULL) {
    perror("ERROR");
    exit(1);
  }

  char line[ALLOC_SIZE];
  int line_count = 1;
  int empty_count = 0;

  while (fgets(line, sizeof(line), fp) != NULL) {
    size_t read = strlen(line);
    if (line[0] == '\n') {
      empty_count++;
    } else {
      empty_count = 0;
    }
    if (args->s && empty_count > 1) {
      continue;
    }
    if (args->b || args->n) {
      if (args->b && line[0] != '\n') {
        printf("%6d\t", line_count);
        line_count++;
      } else if (args->n && !args->b) {
        printf("%6d\t", line_count);
        line_count++;
      }
    }
    router(args, line, read);
  }
  fclose(fp);
}

void router(Arguments *args, char *s, size_t n) {
  for (size_t i = 0; i < n; i++) {
    if (args->T && s[i] == '\t')
      printf("^I");
    else {
      if (args->E && s[i] == '\n') {
        putchar('$');
      } else if (args->v) {
        s[i] = option_v(s[i]);
      }
      putchar(s[i]);
    }
  }
}

char option_v(char ch) {
  if (ch == '\n' || ch == '\t') return ch;
  if (ch > 0 && ch <= 31) {
    putchar('^');
    ch += 64;
  } else if (ch == 127) {
    putchar('^');
    ch = '?';
  }
  return ch;
}