CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic

all: sorting

sorting: quick.o stack.o queue.o
	$(CC) -o sorting quick.o stack.o queue.o -lm 

quick.o: quick.c
	$(CC) $(CFLAGS) -c quick.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c

clean:
	rm -f sorting quick.o stack.o queue.o

scan-build: clean
	scan-build make
