
#include "defines.h"
#include "header.h"
#include "huffman.h"
#include "io.h"
#include "code.h"
#include "pq.h"
#include "node.h"

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
#include <fcntl.h>

// Global variables
uint8_t buffer[BLOCK];
uint32_t bytes_processed, uncorrected_errors, corrected_errors;
// Command line argument options
#define OPTIONS "i:o:hv"

// Helper functions:
// A helper file to print the histogram
void print_histogram(uint64_t *histogram) {
    for (int i = 0; i < 256; i += 8) {
	printf("Indexes from %3u \t", i);
	for (int j = 0; j < 8; j++) {
            printf("%lu \t", histogram[i + j]);
	}
	printf("\n");
    }
    return;
}

int main(int argc, char **argv) {
    // Initilize variables used by main method
    struct stat statbuf;
    bool outfile_given = false, infile_given = false, verbose_printing;
    
    // Create and initilize the histogram    
    uint64_t histogram[ALPHABET];
    for (int i = 0; i < 256; i++) {
        histogram[i] = 0;
    }
    histogram[0]++;
    histogram[255]++;

    // Set input and output files to 0, which represents stdin/stdout
    int output_file = 0;
    int input_file = 0;

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
            // If an outfile is given, set it as output
            outfile_given = true;
            char *outfile = strdup(optarg);
	    output_file = open(outfile, O_WRONLY | O_CREAT);
	    free(outfile);
            break;
        case 'i':
            // Set the infile string to the argument given by the user
            infile_given = true;
            char *infile = strdup(optarg);
            input_file = open(infile, O_RDONLY);
            // Check the file permissions and store them
            //fstat(fileno(input_file), &statbuf);

            free(infile);
            break;
	case 'v':
	    verbose_printing = true;
	    break;
        }
    }

    int input_length = read_bytes(input_file, buffer, BLOCK);
    //write_bytes(output_file, buffer, 10);
    //printf("\n");
    //printf("\n");

    // Create the histogram given the contents of the buffer
    for (int i = 0; i < input_length; i++) {
        printf("%u \n", buffer[i]);
        histogram[buffer[i]]++;
    }

    // TEMPORARY: Print the histogram to check it
    // print_histogram(histogram);


    // Call Huffman functions to build a tree
    Node *root = build_tree(histogram); 
    node_print(root);

    // Call Huffman functions to make the codes
    //Code code_table = code_init();
    //build_codes(root, &code_table);
    







    // Set outfile permissions to equal infile permissions
    if (outfile_given == true) {
        //fchmod(fileno(output_file), statbuf.st_mode);
    }

    // Close the input output files if they were opened.
    if (outfile_given == true) {
        close(output_file);
    }
    if (infile_given == true) {
        close(input_file);
    }
    return 0;
}
