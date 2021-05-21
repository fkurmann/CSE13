#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"

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

// Global variables for read and write functions
extern uint8_t buffer[BLOCK];
uint64_t bytes_read;
uint64_t bytes_written;

// Static variables for bitwise read and write functions
static uint8_t bit_buffer[BLOCK];
static uint32_t buffer_index = 0;

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
    // Write will return 0 if end of file is reached or the length it has written, loop until one of these happen.
    while(bytes_written > 0 && counter < nbytes) {
        bytes_written = write(outfile, buf, nbytes - counter);
	counter += bytes_written;
    }
    return counter;
}

bool read_bit(int infile, uint8_t *bit) {
    int last_bit = 8 * BLOCK;
    // Read from input to bit buffer if the buffer is empty
    if (buffer_index == 0) {
        int bytes_read = read_bytes(infile, bit_buffer, BLOCK);
	// If unable to read a full block, the end of the input has been reached
	if (bytes_read < BLOCK) {
	    last_bit = 8 * bytes_read + 1;
	}
    }
    // Pass back bits from the bit_buffer through the bit pointer using bit_vector's get operation
    uint32_t buffer_byte = buffer_index / 8;
    uint32_t buffer_bit_in_byte = buffer_index % 8;
    uint8_t buffer_byte_value = bit_buffer[buffer_byte];
    buffer_byte_value = buffer_byte_value >> buffer_bit_in_byte;
    if (buffer_byte_value % 2 != 0) {
        *bit = 1;
    }
    else {
        *bit = 0;
    }
    buffer_index++;

    // If you hit the end of a complete buffer, fill the buffer again with another block from the infile.
    if (buffer_index == 8 * BLOCK) {
        buffer_index = 0; 
    }

    // If you hit the last bit in an incomplete buffer, you have read all bits from infile, return false, else return true
    if (buffer_index == (uint32_t) last_bit) {
        return false;
    }
    else {
        return true;
    }
}

void write_code(int outfile, Code *c) {
    // Fill the buffer using bit_vector operations get, set, and clr.
    for (uint32_t i = 0; i < c->top; i++) {
        // Buffer indexing variables
	uint32_t buffer_byte = buffer_index / 8;
	uint32_t buffer_bit_in_byte = buffer_index % 8;
        uint8_t buffer_byte_value = bit_buffer[buffer_byte];
	buffer_byte_value = buffer_byte_value >> buffer_bit_in_byte;
	
	// Code indexing variables
	uint32_t byte = (i / 8);
	uint32_t bit_in_byte = i % 8;
	uint8_t byte_value = c->bits[byte];
	byte_value = byte_value >> bit_in_byte;
	if (byte_value % 2 != 0) {
	   // Bit I has value 1, set buffer index to 1
	   bit_buffer[buffer_byte] += pow(2, buffer_bit_in_byte);
	}
	else {
            // Bit I has value 0, clear buffer index to equal 0
	    if (buffer_byte_value % 2 != 0) {
	        bit_buffer[buffer_byte] -= pow(2, buffer_bit_in_byte);
	    }
	}
	
	// Move to next bit in the buffer
        buffer_index++;
        
	// Write the buffer to the outfile if it is full, reset buffer index
        if (buffer_index == 8 * BLOCK) {
            bytes_written += (uint64_t) write_bytes(outfile, bit_buffer, BLOCK);
	    buffer_index = 0;
        }
    }

    return;
}

void flush_codes(int outfile) {
    if (buffer_index != 0) {
        bytes_written += (uint64_t) write_bytes(outfile, bit_buffer, buffer_index / 8);
	buffer_index = 0;
	//printf("Flushing \n");
    }
    return;
}
