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
uint64_t bytes_written, bytes_read;
Code c;

// Command line argument options
#define OPTIONS "i:o:hv"

// Helper functions:

int main(int argc, char **argv) {
    // Initilize variables used by main method
    struct stat statbuf;
    bool outfile_given = false, infile_given = false, verbose_printing = false;
    uint64_t output_size = 0;   
  
    // Set input and output files to 0, which represents stdin/stdout
    int output_file = 0;
    int input_file = 0;

    // Command line arguments get processed, booleans for verbose and undirected are set, in and outfiles are stored.
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf(" A Huffman decoder: Decompress a huffman encode file.\n"
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
    // Read the header from the infile into the input buffer
    struct Header header;
    read_bytes(input_file, (uint8_t *) (&header), sizeof(Header));
    if (header.magic != MAGIC) {
	printf("Your magic number %u \n", header.magic);
        printf("Error, the magic number of the input file is incompatibe with this decoder. \n");
	return 1;
    }

    // Read the tree section of the input into the tree_dump array, then rebuild the tree based on this array
    uint8_t tree_dump[header.tree_size];
    bytes_read += (uint64_t) read_bytes(input_file, tree_dump, header.tree_size);
   
    Node *tree_root = rebuild_tree(header.tree_size, tree_dump);
    
    // Traverse the tree using the code section of input, add outputs to the output buffer/file
    uint8_t code_bit = 0;
    Node *current_node = tree_root;
    
    while (output_size < header.file_size) {
        read_bit(input_file, &code_bit);

	// If a leaf node is reached, copy it to the output buffer and return to the root node
	if (current_node->symbol != '$' || current_node->left == NULL || current_node->right == NULL) {
	    buffer[buffer_index] = current_node->symbol;
	    current_node = tree_root;
	    buffer_index++;
	    output_size++;
	}
       
	// Traverse left if the code contains 0, right if it contains 1
	if (code_bit == 0) {
            current_node = current_node->left;
	}
	if (code_bit == 1) {
	    current_node = current_node->right;
	}
	
	// Write the output buffer to the outfile if it's full
	if (buffer_index == BLOCK) {
            bytes_written += (uint64_t) write_bytes(output_file, buffer, BLOCK);
	    buffer_index = 0;
	}
    }
    // Write the remainder of the output buffer to the output file
    bytes_written += (uint64_t) write_bytes(output_file, buffer, buffer_index);
            
    // Delete the reconstructed tree
    delete_tree(&tree_root);

    if (output_file == 0) {
        printf("\n");
    }

    if (verbose_printing == true) {
	if (output_file == 0) {
		printf("\n");
	}
        uint32_t compressed_size = (uint32_t) statbuf.st_size;
        uint32_t decompressed_size = (uint32_t) bytes_written;
        double space_saving = 100 * ( 1 - (double) compressed_size / decompressed_size);
        fprintf(stderr, "Compressed file size: %u bytes\n"
                        "Decompressed file size: %u bytes\n"
                        "Space saving %f%% \n", compressed_size, decompressed_size, space_saving);
    }
    
    // Set outfile permissions to equal infile permissions
    if (outfile_given == true) {
        fchmod((output_file), statbuf.st_mode);
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
