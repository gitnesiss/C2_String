CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11
SRC=$(wildcard s21*.c)
COVFLAGS=-fprofile-arcs -ftest-coverage

ifeq ($(shell uname), Linux)
GFLAGS=-lcheck -lm -lpthread -lrt -lsubunit
else
GFLAGS=-lcheck
LEAKS=CK_FORK=no leaks -atExit -- ./test
endif

all: s21_string.a gcov_report

test: s21_string.a
	checkmk test.check > test.c
	$(CC) $(CFLAGS) $(COVFLAGS) $(SRC) test.c -L. s21_string.a -o test $(GFLAGS)
	./test

others_tests: s21_string.a
	rm *.o
	$(CC) $(CFLAGS) $(COVFLAGS) $(SRC) test_*.c -L. s21_string.a -o test $(GFLAGS)
	./test > report.txt

s21_string.a: s21_string.h $(SRC)
	$(CC) -c $(CFLAGS) $(SRC)
	ar rc s21_string.a *.o
	ranlib s21_string.a

debug:
	$(CC) $(CFLAGS) $(SRC) debug.c -o debug $(GFLAGS) -g

gcov_report: test
	gcovr -r . --html-details -o gcov_report.html

clean: cleancov
	rm -f *.o *.a test.c test

cleancov:
	rm -f *.css *.html *.gcda *.gcno *.gcov

leaks: test
	$(LEAKS)

linter:
	python3 ../materials/linters/cpplint.py --extensions=c ../src/*.c *h
