
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

// Constructor for header
Header *header_create(uint16_t permissions, uint16_t tree_size, uint64_t file_size) {
    Header *h = (Header *) malloc(sizeof(Header));
    if (h) {
        h->magic = MAGIC;
	h->permissions = permissions;
	h->tree_size = tree_size;
	h->file_size = file_size;
    }
    return h;
}
// Destructor for header
void header_delete(Header **h) {
    if (*h) {
        free(*h);
	*h = NULL;
    }
    return;
}

// Function that does post order traversal of tree to write it to the outfile
void tree_to_outfile(Node *root, int output_file) {
    // If a node is NOT a root or interior node, write L followed by the node to the outfile
    if (root->symbol != '$') {
        buffer[buffer_index] = 'L';
	buffer_index++;
	buffer[buffer_index] = root->symbol;
	//printf("%u \n", buffer[buffer_index]);
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
	//printf("%u \n", input_buffer[i]);
	//code_print(&table[input_buffer[i]]);
	write_code(output_file, &table[input_buffer[i]]);
    }
    flush_codes(output_file);
    return;
}

int main(int argc, char **argv) {
    // Initilize variables used by main method
    struct stat statbuf;
    bool outfile_given = false, infile_given = false, verbose_printing;
    uint16_t tree_size = 0;    
    // Create and initilize the histogram    
    uint64_t histogram[ALPHABET];
    for (int i = 0; i < 256; i++) {
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
    int input_length = read_bytes(input_file, input_buffer, BLOCK);
    //write_bytes(output_file, input_buffer, 10);

    // Create the histogram given the contents of the buffer
    for (int i = 0; i < input_length; i++) {
	if (histogram[input_buffer[i]] == 0) {
	    tree_size++;
	}
        //printf("%u \n", input_buffer[i]);
        histogram[input_buffer[i]]++;
    }

    // Call Huffman functions to build a tree
    Node *tree_root = build_tree(histogram); 
    node_print(tree_root);
    // Call Huffman functions to make the codes
    c = code_init();
    build_codes(tree_root, code_table);
    
    
    // Call constructor for the header, then write the header to the outfile and call header destructor 
    uint64_t file_size = (uint64_t) input_length; //ASGN DOC says you can get this number using fstat() - this seems to work?
    uint16_t permissions = (uint16_t) statbuf.st_mode;
    tree_size = (3 * tree_size) - 1;
    Header *header = header_create(permissions, tree_size, file_size);
    
    // Cast the header to an integer and print it to the outfile
    uint8_t integer_header = (uint8_t) (&header);
    write_bytes(output_file, &integer_header, sizeof(Header)); 
    header_delete(&header);
    
    // Call function to write tree to a buffer, then the outfile
    tree_to_outfile(tree_root, output_file); 
    printf("%u \n", write_bytes(output_file, buffer, buffer_index));

    // Call function to write codes to outfile
    write_codes(code_table, input_buffer, input_length, output_file);

    
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
