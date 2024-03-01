SHELL := /bin/bash

CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
CHECK=valgrind --tool=memcheck --leak-check=yes
FILE=test.txt

all: clean s21_cat tests

s21_cat: s21_cat.c s21_cat.h
	$(CC) $(CFlags) s21_cat.c -o s21_cat

tests:
	cp ../../materials/linters/.clang-format ../../src/cat/
	clang-format -n s21_cat.*
	diff <(./s21_cat $(FILE)) <(cat $(FILE))
	diff <(./s21_cat -e $(FILE)) <(cat -e $(FILE))
	diff <(./s21_cat -s $(FILE)) <(cat -s $(FILE))
	diff <(./s21_cat -n $(FILE)) <(cat -n $(FILE))
	diff <(./s21_cat -b $(FILE)) <(cat -b $(FILE))
	diff <(./s21_cat --squeeze-blank $(FILE)) <(cat --squeeze-blank $(FILE))
	diff <(./s21_cat --number $(FILE)) <(cat --number $(FILE))
	diff <(./s21_cat --number-nonblank $(FILE)) <(cat --number-nonblank $(FILE))
	diff <(./s21_cat -etsnb $(FILE)) <(cat -etsnb $(FILE))

	$(CHECK) ./s21_cat $(FILE)
	$(CHECK) ./s21_cat -e $(FILE)
	$(CHECK) ./s21_cat -s $(FILE)
	$(CHECK) ./s21_cat -n $(FILE)
	$(CHECK) ./s21_cat -b $(FILE)
	$(CHECK) ./s21_cat -t $(FILE)
	$(CHECK) ./s21_cat --squeeze-blank $(FILE)
	$(CHECK) ./s21_cat --number $(FILE)
	$(CHECK) ./s21_cat --number-nonblank $(FILE)
	$(CHECK) ./s21_cat -etsnb $(FILE)
clean:
	rm -rf *.o s21_cat .clang-format

rebuild: clean s21_cat
