CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: banhammer

encode: encode.o io.o code.o huffman.o pq.o node.o stack.o
	$(CC) -o encode encode.o io.o code.o huffman.o pq.o node.o stack.o -lm 

decode: decode.o io.o code.o huffman.o pq.o node.o stack.o
	$(CC) -o decode decode.o io.o code.o huffman.o pq.o node.o stack.o -lm 

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

io.o: io.c
	$(CC) $(CFLAGS) -c io.c

clean:
	rm -f banhammer banhammer.o  speck.o ht.o ll.o node.o bf.o bv.o parser.o

format:
	clang-format -i -style=file banhammer.c messages.h speck.h speck.c ht.h ht.c ll.h ll.c node.h node.c bf.h bf.c bv.h bv.c parser.h parser.c

scan-build: clean
	scan-build make

test: encode decode
	./encode -i DESIGN.pdf -o encoded.txt -v
	./decode -i encoded.txt -v
