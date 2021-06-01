CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: banhammer

banhammer: banhammer.o speck.o ht.o ll.o bf.o bv.o parser.o node.o llu.o 
	$(CC) -o banhammer banhammer.o speck.o ht.o ll.o bf.o bv.o parser.o node.o llu.o -lm 

banhammer.o: banhammer.c
	$(CC) $(CFLAGS) -c banhammer.c

speck.o: speck.c
	$(CC) $(CFLAGS) -c speck.c

ht.o: ht.c
	$(CC) $(CFLAGS) -c ht.c

ll.o: ll.c
	$(CC) $(CFLAGS) -c ll.c

llu.o: llu.c
	$(CC) $(CFLAGS) -c llu.c

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
	rm -f banhammer test banhammer.o speck.o ht.o ll.o llu.o node.o bf.o bv.o parser.o test.o

format:
	clang-format -i -style=file banhammer.c messages.h speck.h speck.c ht.h ht.c ll.h ll.c llu.h llu.c node.h node.c bf.h bf.c bv.h bv.c parser.h parser.c

scan-build: clean
	scan-build make

test: test.o bv.o bf.o speck.o node.o ll.o ht.o parser.o
	$(CC) -o test test.o bv.o bf.o speck.o node.o ll.o ht.o parser.o -lm 
	./test
