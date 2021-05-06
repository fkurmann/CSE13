#include "bm.h"
#include "hamming.h"

#include <assert.h>
#include <getopt.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Command line argument options
#define OPTIONS "i:o:h"

// CITATION: These three helper functions were provided by Professor Long in the asignment 5 handout.

uint8_t lower_nibble(uint8_t val) {
    return val & 0xF;
}
uint8_t upper_nibble(uint8_t val) {
    return val >> 4;
}

uint8_t pack_byte(uint8_t upper, uint8_t lower) {
    return (upper<< 4) | (lower & 0xF);
}


int main(int argc, char **argv) {
    bool  outfile_given = false, infile_given = false;
    uint8_t input_byte, lower_input_nibble, upper_input_nibble;
    
    FILE *output_file = stdout;
    FILE *input_file = stdin;

    // Create the Generator matrix and initialize its values.
    BitMatrix *Generator = bm_create(4, 8);
    // Set the left half of the generator
    for (uint32_t i = 0; i < 4; i++) {
        bm_set_bit(Generator, i, i);
    }
    // Set the right half of the generator
    for (uint32_t i = 4; i < 8; i++) {
        for (uint32_t j = 0; j < 4; j++) {
	    if (i != j + 4) {
		bm_set_bit(Generator, j , i);
	    }
	}
    }

    // Command line arguments get processed, booleans for verbose and undirected are set, in and outfiles are stored.
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf(" A Hamming (8, 4) systematic code generator.\n"
                   "Program usage: \n"
                   "  -h            Show help menu\n"
                   "  -i infile     Specify an infile to read from\n"
                   "  -o outfile    Specify an outfile to write to\n");
            break;
        case 'o':
            outfile_given = true;
            char *outfile = strdup(optarg);
            output_file = fopen(outfile, "wb");
            if (output_file == NULL) {
                perror("Invalid output file");
                return 1;
            }
            free(outfile);
            break;
        case 'i':
            // Set the infile string to the argument given by the user
            infile_given = true;
            char *infile = strdup(optarg);
            
            input_file = fopen(infile, "r");
            if (input_file == NULL) {
                perror("Invalid input file");
                return 1;
            }
            free(infile);
            break;
        }
    }
    
    // Read the input file byte by byte, breaking if the end of the file is reached.
    while(1) {
        input_byte = fgetc(input_file);
        // Don't encode spaces, stop when end of file is reached.
	if (input_byte == 32) {
	    continue;
	}
        if (feof(input_file)) {
	    break;
	}
	// Split, encode, and print the current byte
	lower_input_nibble = lower_nibble(input_byte);
	upper_input_nibble = upper_nibble(input_byte);

	lower_input_nibble = ham_encode(Generator, lower_input_nibble);
	upper_input_nibble = ham_encode(Generator, upper_input_nibble);

	printf("%c", lower_input_nibble);
	printf("%c", upper_input_nibble);
    }
    
    // Delete the generator, end the program.
    printf("\n");
    bm_delete(&Generator);
    // Close the input output files if they were opened.
    if (outfile_given == true) {
        fclose(output_file);
    }
    if (infile_given == true) {
        fclose(input_file);
    }
    return 0;
}
