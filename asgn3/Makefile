CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: sorting

sorting: bubble.o
	$(CC) -o sorting bubble.o

bubble.o: bubble.c
	$(CC) $(CFLAGS) -c bubble.c

clean:
	rm -f sorting bubble.o

scan-build: clean
	scan-build make
