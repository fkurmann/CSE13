#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"
//#include "code.h" CHECK IF YOU NEED

#include <assert.h>
#include <getopt.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// Global variables
uint8_t buffer[BLOCK];
uint32_t bytes_processed, uncorrected_errors, corrected_errors;
// Command line argument options
#define OPTIONS "i:o:hv"

int main(int argc, char **argv) {
    // Initilize variables used by main method
    struct stat statbuf;
    bool outfile_given = false, infile_given = false, verbose_printing;
    uint8_t input_byte, lower_input_nibble, upper_input_nibble;

    FILE *output_file = stdout;
    FILE *input_file = stdin;

    // Command line arguments get processed, booleans for verbose and undirected are set, in and outfiles are stored.
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf(" A Huffman encoder: Compresses a file using Huffman coding.\n"
                   "Program usage: \n"
                   "  -h            Show help menu\n"
                   "  -i infile     Specify an infile to read from\n"
                   "  -o outfile    Specify an outfile to write to\n"
		   "  -v            Print statistics on compression\n");
            break;
        case 'o':
            // If an outfile is given, set it as output if it exists
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

            // Check the file permissions and store them
            fstat(fileno(input_file), &statbuf);

            free(infile);
            break;
	case 'v':
	    verbose_printing = true;
	    break;
        }
    }

    // Set outfile permissions to equal infile permissions
    if (outfile_given == true) {
        fchmod(fileno(output_file), statbuf.st_mode);
    }

    // Close the input output files if they were opened.
    if (outfile_given == true) {
        fclose(output_file);
    }
    if (infile_given == true) {
        fclose(input_file);
    }
    return 0;
}
