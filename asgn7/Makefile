CC = clang
CFLAGS = -Wall -Wextra -Wpedantic

all: banhammer

banhammer: banhammer.o speck.o ht.o ll.o bf.o bv.o parser.o node.o 
	$(CC) -o banhammer banhammer.o speck.o ht.o ll.o bf.o bv.o parser.o node.o -lm 

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c

ht.o: ht.c
	$(CC) $(CFLAGS) -c ht.c

ll.o: ll.c
	$(CC) $(CFLAGS) -c ll.c

bf.o: bf.c
	$(CC) $(CFLAGS) -c bf.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

parser.o: parser.c
	$(CC) $(CFLAGS) -c parser.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

test.o: test.c
	$(CC) $(CFLAGS) -c test.c

clean:
	rm -f banhammer test banhammer.o speck.o ht.o ll.o node.o bf.o bv.o parser.o test.o

format:
	clang-format -i -style=file banhammer.c messages.h speck.h speck.c ht.h ht.c ll.h ll.c node.h node.c bf.h bf.c bv.h bv.c parser.h parser.c

scan-build: clean
	scan-build make

test: test.o bv.o bf.o speck.o node.o ll.o ht.o
	$(CC) -o test test.o bv.o bf.o speck.o node.o ll.o ht.o -lm 
	./test
