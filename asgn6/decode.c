#include "defines.h"
#include "header.h"
#include "huffan.h"
#include "helper.h"

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

// CITATION: The file permissions code was provided by Professor Long in the Asgn5 handout.

// Command line argument options
#define OPTIONS "i:o:hv"

uint32_t bytes_processed = 0, uncorrected_errors = 0, corrected_errors = 0;

int main(int argc, char **argv) {
    // Initilize all variables necessary for the main method.
    struct stat statbuf;
    bool verbose_printing = false, outfile_given = false, infile_given = false;
    uint8_t input_byte_lower, input_byte_upper, output_byte_lower = 0, output_byte_upper = 0;
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
            // An outfile is given, set it to the program output if it exists.
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

            // Check the file permissions and store them
            fstat(fileno(input_file), &statbuf);
            free(infile);
            break;
        }
    }

    // Set the file permissions of output to match input.
    if (outfile_given == true) {
        fchmod(fileno(output_file), statbuf.st_mode);
    }

    // Close the input output files if they are opened, delete ADT, end program.
    if (outfile_given == true) {
        fclose(output_file);
    }
    if (infile_given == true) {
        fclose(input_file);
    }
    return 0;
}
