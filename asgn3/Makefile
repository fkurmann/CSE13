CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: sorting

sorting: sorting.o set.o bubble.o shell.o quick.o stack.o queue.o
	$(CC) -o sorting sorting.o set.o bubble.o shell.o quick.o stack.o queue.o -lm 

sorting.o: sorting.c
	$(CC) $(CFLAGS) -c sorting.c

set.o: set.c
	$(CC) $(CFLAGS) -c set.c

bubble.o: bubble.c
	$(CC) $(CFLAGS) -c bubble.c

shell.o: shell.c
	$(CC) $(CFLAGS) -c shell.c

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c

clean:
	rm -f sorting sorting.o set.o bubble.o shell.o quick.o stack.o queue.o

format:
	clang-format -i -style=file sorting.c set.c bubble.c shell.c quick.c stack.c queue.c
scan-build: clean
	scan-build make
