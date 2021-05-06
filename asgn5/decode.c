#include "bm.h"
#include "hamming.h"
#include "helper.h"

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
#define OPTIONS "i:o:hv"

uint32_t bytes_processed = 0, uncorrected_errors = 0, corrected_errors = 0;

int main(int argc, char **argv) {
    bool verbose_printing = false, outfile_given = false, infile_given = false;
    uint8_t input_byte_lower, input_byte_upper, output_byte_lower = 22, output_byte_upper = 22;
    BitMatrix *Transpose = bm_create(8, 4);
    // Set lower half of bit matrix
    for(uint32_t i = 0; i < 4; i++) {
        bm_set_bit(Transpose, i + 4, i);
    }
    // Set upper half of bit matrix
    for (uint32_t i = 0; i < 4; i++) {
        for (uint32_t j = 0; j < 4; j++) {
            if (i != j) {
	        bm_set_bit(Transpose, i, j);
	    }
	}
    }

    FILE *output_file = stdout;
    FILE *input_file = stdin;
    
    // Command line arguments get processed, booleans for verbose and undirected are set, in and outfiles are stored.
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("A Hamming (8, 4) systematic decoder. \n"
                   "Program usage: \n"
                   "  -h            Show help menu\n"
                   "  -v            Enable verbose printing\n"
                   "  -i infile     Specify an infile to read from\n"
                   "  -o outfile    Specify an outfile to write to\n");
            break;
        case 'v': verbose_printing = true; break;
        case 'o':
            outfile_given = true;
            char *outfile = strdup(optarg);
            output_file = fopen(outfile, "w");
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

    while(1) {
        input_byte_lower = fgetc(input_file);
        input_byte_upper = fgetc(input_file);
	if (feof(input_file)) {
	    break;
	}
	ham_decode(Transpose, input_byte_lower, &output_byte_lower);
	ham_decode(Transpose, input_byte_upper, &output_byte_upper);

	output_byte_lower = pack_byte(output_byte_upper, output_byte_lower);
	
	fprintf(output_file, "%c", output_byte_lower);
    }
    
    
    //If verbose printing was selected, print the statistics:
    if (verbose_printing == true) {
	float error_rate = (uncorrected_errors + corrected_errors) / (float) bytes_processed;
        fprintf(output_file, "Total bytes processed: %u \n", bytes_processed);
        fprintf(output_file, "Uncorrected errors: %u \n", uncorrected_errors);
        fprintf(output_file, "Corrected errors: %u \n", corrected_errors);
        fprintf(output_file, "Error rate: %.6f \n", error_rate);
    }

    // Close the input output files if they are opened, delete ADT, end program.
    fprintf(output_file, "\n");
    bm_delete(&Transpose);
    if (outfile_given == true) {
        fclose(output_file);
    }
    if (infile_given == true) {
        fclose(input_file);
    }
    return 0;
}
