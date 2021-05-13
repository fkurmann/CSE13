#include "defines.h"
#include "header.h"
#include "huffman.h"


#include <assert.h>
//#include <getopt.h> CONSIDER REM
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
//#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

extern uint8_t buffer[BLOCK];
extern uint64_t bytes_read;
extern uint64_t bytes_written;


int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int bytes_read = 1;
    int counter = 0;
    // Read will return 0 if end of file is reached or the length it has read, loop until one of these happen.
    while(bytes_read > 0 && counter  < nbytes) {
        bytes_read = read(infile, buf, nbytes - counter);
	counter += bytes_read;
    }
    return counter;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int bytes_written = 1;
    int counter = 0;
    // Read will return 0 if end of file is reached or the length it has read, loop until one of these happen.
    while(bytes_written > 0 && counter < nbytes) {
        bytes_written = write(outfile, buf, nbytes - counter);
	counter += bytes_written;
    }
    return counter;
}

bool read_bit(int outfile, uint8_t *buf, int nbytes) {

    return false;
}

void write_code(int outile, Code *c) {

    return;
}

void flush_codes(int outfile) {

    return;
}
