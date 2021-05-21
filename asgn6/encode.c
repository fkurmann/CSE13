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
uint8_t input_buffer[BLOCK];
uint8_t buffer[BLOCK];
static uint32_t buffer_index = 0;
uint32_t bytes_processed, uncorrected_errors, corrected_errors;
uint64_t bytes_read = 0, bytes_written;
Code c;

// Command line argument options
#define OPTIONS "i:o:hv"

// Helper functions:
// A helper function to print the histogram
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

// Function that does post order traversal of tree to write it to the outfile
void tree_to_outfile(Node *root, int output_file) {
    // If a buffer is full, write it to the outfile and start at it's beginning again.
    if (buffer_index == BLOCK) {
        bytes_written += (uint64_t) write_bytes(output_file, (uint8_t *) buffer, BLOCK);
        buffer_index = 0;	
    }

    // If a node is NOT a root or interior node, write L followed by the node to the outfile
    if (root->symbol != '$' || root->left == NULL || root->right == NULL) {
        buffer[buffer_index] = 'L';
	buffer_index++;
	buffer[buffer_index] = root->symbol;
	buffer_index++;
    }

    // If the node is a root or interior node, post order traversal
    else {
        tree_to_outfile(root->left, output_file);
        tree_to_outfile(root->right, output_file);
	buffer[buffer_index] = 'I';
	buffer_index++;
    }
    return;
}

// Function for writing code for each symbol to the outfile
void write_codes(Code table[ALPHABET], uint8_t *input_buffer, int input_length, int output_file) {
    for (int i = 0; i < input_length; i++) {
	write_code(output_file, &table[input_buffer[i]]);
    }

    flush_codes(output_file);
    return;
}

int main(int argc, char **argv) {
    // Initilize variables used by main method
    struct stat statbuf;
    bool outfile_given = false, infile_given = false, verbose_printing = false;
    int tree_size = 2; // There will always be at least 2 unique symbols in the tree    

    // Create and initilize the histogram    
    uint64_t histogram[ALPHABET];
    for (int i = 0; i < ALPHABET; i++) {
        histogram[i] = 0;
    }
    histogram[0]++;
    histogram[255]++;

    // Create and initilize the code array
    Code code_table[ALPHABET];
    Code zero = code_init();
    for (int i = 0; i < ALPHABET; i++) {
        code_table[i] = zero;
    }
  
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
            fstat((input_file), &statbuf);

            free(infile);
            break;
	case 'v':
	    verbose_printing = true;
	    break;
        }
    }
    
    
    // Read from the input into the buffer
    uint32_t decompressed_size = (uint32_t) statbuf.st_size;
    int bytes_in = 0;
    while (bytes_read < (uint64_t) decompressed_size) {
        // Add bytes_in to bytes_read since bytes_in must be used for histogram making, bytes read may exceed buffer size.
	bytes_in = read_bytes(input_file, input_buffer, BLOCK);
        bytes_read += (uint64_t) bytes_in;

	// Create the histogram given the contents of the buffer
        for (int i = 0; i < bytes_in; i++) {
	    if (histogram[input_buffer[i]] == 0) {
	        tree_size++;
	    }
            histogram[input_buffer[i]]++;
        }
    }

    // Call Huffman functions to build a tree
    Node *tree_root = build_tree(histogram); 

    // Call Huffman functions to make the codes
    c = code_init();
    build_codes(tree_root, code_table);
   
    // Construct the header 
    struct Header header;
    header.magic = MAGIC;
    header.permissions = statbuf.st_mode;
    header.file_size = statbuf.st_size;
    header.tree_size = 3 * tree_size - 1;
    
    // Cast the header to an integer and print it to the outfile
    bytes_written += (uint64_t) write_bytes(output_file, (uint8_t *) (&header), sizeof(Header)); 
    
    // Call function to write tree to a buffer, then to the outfile
    tree_to_outfile(tree_root, output_file); 
    bytes_written += (uint64_t) write_bytes(output_file, buffer, buffer_index);

    // Call function to write codes to outfile
    // Reread the input buffer by buffer to print the codes for each byte
    bytes_read = 0;
    lseek(input_file, 0, SEEK_SET);
    while (bytes_read < (uint64_t) decompressed_size) {
        // Add bytes_in to bytes_read since bytes_in must be used for histogram making, bytes read may exceed buffer size.
	bytes_in = read_bytes(input_file, input_buffer, BLOCK);
        bytes_read += (uint64_t) bytes_in;
        
	// Write the codes for the buffer just filled from infile
        write_codes(code_table, input_buffer, bytes_in, output_file);
    }

    // Set outfile permissions to equal infile permissions
    if (outfile_given == true) {
        fchmod((output_file), statbuf.st_mode);
    }
    
    // If verbose printing is specified, print info
    if (verbose_printing == true) {
	if (output_file == 0) {
	    printf("\n");
	}	    
        //struct stat output_statbuf;
        //fstat(output_file, &output_statbuf);
	uint32_t decompressed_size = (uint32_t) statbuf.st_size;
        uint32_t compressed_size = (uint32_t) bytes_written; 
        double space_saving = 100 * ( 1 - (double) compressed_size / decompressed_size);
	fprintf(stderr, "Uncompressed file size: %u bytes \n"
	    	        "Compressed file size: %u bytes \n"
		        "Space saving %f%% \n", decompressed_size, compressed_size, space_saving);
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
