CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: pq stack code

pq: pq

stack: stack

code: code

pq: pq.o node.o
	$(CC) -o pq pq.o node.o -lm 

stack: stack.o node.o
	$(CC) -o stack stack.o node.o -lm 

code: pq.o code.o
	$(CC) -o code code.o -lm 

pq.o: pq.c
	$(CC) $(CFLAGS) -c pq.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

code.o: code.c
	$(CC) $(CFLAGS) -c code.c

clean:
	rm -f pq stack code stack.o pq.o node.o code.o

format:
	clang-format -i -style=file stack.c pq.c node.c code.c
scan-build: clean
	scan-build make
