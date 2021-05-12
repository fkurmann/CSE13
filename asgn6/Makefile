CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: tester


tester: pq.o node.o
	$(CC) -o tester pq.o node.o -lm 

pq.o: pq.c
	$(CC) $(CFLAGS) -c pq.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

clean:
	rm -f tester pq.o node.o

scan-build: clean
	scan-build make
