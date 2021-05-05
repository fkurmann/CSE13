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


int main(int argc, char **argv) {
    bool  outfile_given = false, infile_given = false;

    FILE *output_file = stdout;
    FILE *input_file = stdin;
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
            fclose(input_file);
            free(infile);
            break;
        }
    }

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

    BitMatrix *testa = bm_from_data(92, 5);
    bm_print(testa);
    printf("%u \n", bm_to_data(testa));


    //bm_print(Generator);
    
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
