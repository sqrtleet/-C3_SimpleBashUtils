SHELL := /bin/bash

CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
CHECK=valgrind --tool=memcheck --leak-check=yes
FILE=test.txt
REG_FILE=test2.txt

all: clean s21_grep tests

s21_grep: s21_grep.c s21_grep.h
	$(CC) $(CFlags) s21_grep.c -o s21_grep

tests:
	cp ../../materials/linters/.clang-format ../../src/grep/
	clang-format -n s21_grep.*
	diff <(./s21_grep qwe $(FILE)) <(grep qwe $(FILE))
	diff <(./s21_grep -v qwe $(FILE)) <(grep -v qwe $(FILE))
	diff <(./s21_grep -i c $(FILE)) <(grep -i c $(FILE))
	diff <(./s21_grep -iv c $(FILE)) <(grep -iv c $(FILE))
	diff <(./s21_grep -in c $(FILE)) <(grep -in c $(FILE))
	diff <(./s21_grep -ie "^qw" $(FILE)) <(grep -ie "^qw" $(FILE))
	diff <(./s21_grep -ince "^qw" $(FILE)) <(grep -ince "^qw" $(FILE))
	diff <(./s21_grep -lh as $(FILE)) <(grep -lh as $(FILE))
	diff <(./s21_grep -hc as $(FILE)) <(grep -hc as $(FILE))
	diff <(./s21_grep -e qwe $(FILE)) <(grep -e qwe $(FILE))
	diff <(./s21_grep -s unfind $(FILE)) <(grep -s unfind $(FILE))
	diff <(./s21_grep -f $(REG_FILE) $(FILE)) <(grep -f $(REG_FILE) $(FILE))
	diff <(./s21_grep -oi he $(FILE)) <(grep -oi he $(FILE))
	diff <(./s21_grep -ohf $(REG_FILE) $(FILE)) <(grep -ohf $(REG_FILE) $(FILE))
	diff <(./s21_grep -oinc he $(FILE)) <(grep -oinc he $(FILE))
	diff <(./s21_grep -oihlnc -e XC -e ZX -f $(REG_FILE) $(FILE)) <(grep -oihlnc -e XC -e ZX -f $(REG_FILE) $(FILE))

	$(CHECK) ./s21_grep qwe $(FILE)
	$(CHECK) ./s21_grep -v qwe $(FILE)
	$(CHECK) ./s21_grep -i c $(FILE)
	$(CHECK) ./s21_grep -iv c $(FILE)
	$(CHECK) ./s21_grep -in c $(FILE)
	$(CHECK) ./s21_grep -ie "^qw" $(FILE)
	$(CHECK) ./s21_grep -ince "^qw" $(FILE)
	$(CHECK) ./s21_grep -lh as $(FILE)
	$(CHECK) ./s21_grep -hc as $(FILE)
	$(CHECK) ./s21_grep -e qwe $(FILE)
	$(CHECK) ./s21_grep -s unfind $(FILE)
	$(CHECK) ./s21_grep -f $(REG_FILE) $(FILE)
	$(CHECK) ./s21_grep -oi as $(FILE)
	$(CHECK) ./s21_grep -ohf $(REG_FILE) $(FILE)
	$(CHECK) ./s21_grep -oinc as $(FILE)
	$(CHECK) ./s21_grep -oihlnc -e XC -e ZX -f $(REG_FILE) $(FILE)
clean:
	rm -rf *.o s21_grep .clang-format

rebuild: clean s21_grep
