CC = clang
CFLAGS = -Wall -Werror -Wextra -Wpedantic

all: encode decode

pq: pq.o node.o
	$(CC) -o pq pq.o node.o -lm 

stack: stack.o node.o
	$(CC) -o stack stack.o node.o -lm 

code: pq.o code.o
	$(CC) -o code code.o -lm 

encode: encode.o io.o code.o huffman.o pq.o node.o stack.o
	$(CC) -o encode encode.o io.o code.o huffman.o pq.o node.o stack.o -lm 

decode: decode.o io.o code.o huffman.o pq.o node.o stack.o
	$(CC) -o decode decode.o io.o code.o huffman.o pq.o node.o stack.o -lm 

pq.o: pq.c
	$(CC) $(CFLAGS) -c pq.c

node.o: node.c
	$(CC) $(CFLAGS) -c node.c

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c

code.o: code.c
	$(CC) $(CFLAGS) -c code.c

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c

io.o: io.c
	$(CC) $(CFLAGS) -c io.c

huffman.o: huffman.c
	$(CC) $(CFLAGS) -c huffman.c


clean:
	rm -f pq stack code encode decode stack.o pq.o node.o code.o encode.o decode.o io.o huffman.o

format:
	clang-format -i -style=file stack.c pq.c node.c code.c encode.c decode.c io.c huffman.c

scan-build: clean
	scan-build make

test: encode decode
	./encode -i DESIGN.pdf -o encoded.txt -v
	./decode -i encoded.txt -v
