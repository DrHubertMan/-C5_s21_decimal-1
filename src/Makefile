CC = gcc
CFLAGS = -Wall -Werror -Wextra -c 
OFLAGS = -Wall -Werror -Wextra -o

all: test

test: s21_decimal.o
	$(CC) $(OFLAGS) test.out *.o
	rm -rf *.o
	./test.out

s21_decimal.o:
	$(CC) $(CFLAGS) *.c

clean:
	rm -rf *.out *.o

rebuild: clean test
