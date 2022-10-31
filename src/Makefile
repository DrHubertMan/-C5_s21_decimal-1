CC = gcc
CFLAGS = -Wall -Werror -Wextra -c 
OFLAGS = -Wall -Werror -Wextra -o

all: test

test:
	$(CC) $(OFLAGS) test.out *.c
	./test.out

clean:
	rm -rf *.out *.o

rebuild: clean test
