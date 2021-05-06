CC = clang
CFLAGS = -Wall -Wextra -Wpedantic

encode: encode

decode: decode

error: error

entropy: entropy

encode: encode.o hamming.o bv.o bm.o helper.o
	$(CC) -o encode encode.o hamming.o bv.o bm.o helper.o -lm 

decode: decode.o hamming.o bv.o bm.o helper.o
	$(CC) -o decode decode.o hamming.o bv.o bm.o helper.o -lm 

error: error.o
	$(CC) -o error decode.o hamming.o bv.o bm.o helper.o -lm 

entropy: entropy.o
	$(CC) -o entropy decode.o hamming.o bv.o bm.o helper.o -lm 

helper.o: helper.c
	$(CC) $(CFLAGS) -c helper.c

hamming.o: hamming.c
	$(CC) $(CFLAGS) -c hamming.c

encode.o: encode.c
	$(CC) $(CFLAGS) -c encode.c

decode.o: decode.c
	$(CC) $(CFLAGS) -c decode.c

bv.o: bv.c
	$(CC) $(CFLAGS) -c bv.c

bm.o: bm.c
	$(CC) $(CFLAGS) -c bm.c

entropy.o: entropy.c
	$(CC) $(CFLAGS) -c entropy.c

error.o: error.c
	$(CC) $(CFLAGS) -c error.c

clean:
	rm -f encode decode error entropy hamming.o encode.o decode.o bv.o bm.o helper.o entropy.o error.o

format:
	clang-format -i -style=file hamming.c encode.c decode.c bv.c bm.c helper.c entropy.c error.c

scan-build: clean
	scan-build make
