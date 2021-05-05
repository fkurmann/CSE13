CC = clang
CFLAGS = -Wall -Wextra -Wpedantic

all: test

test: encode.o decode.o bv.o bm.o
	$(CC) -o test encode.o decode.o bv.o bm.o -lm 

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

bm.o: bm.c
	$(CC) $(CFLAGS) -c bm.c

clean:
	rm -f test encode.o decode.o bv.o bm.o

format:
	clang-format -i -style=file encode.c decode.c bv.c bm.c

scan-build: clean
	scan-build make
