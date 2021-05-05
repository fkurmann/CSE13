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
            printf("Traveling Salesman Problem using Depth First Search \n"
                   "Program usage: \n"
                   "  -h            Show help menu\n"
                   "  -v            Enable verbose printing\n"
                   "  -u            Make the graph undirected\n"
                   "  -i infile     Specify an infile to read from\n"
                   "  -o outfile    Specify an outfile to write to\n");
            break;
        case 'o':
            outfile_given = true;
            char *outfile = strdup(optarg);
            output_file = fopen(outfile, "w");
            if (output_file == NULL) {
                perror("Invalid output file");
                return 1;
            }
            break;
        case 'i':
            // Set the infile string to the argument given by the user
            infile_given = true;
            char *infile = strdup(optarg);
            char file_line[20];

            input_file = fopen(infile, "r");
            if (input_file == NULL) {
                perror("Invalid input file");
                return 1;
            }
            // Set the number of vertices, the first line of the input
            fgets(file_line, 100, input_file);
            vertices = atoi(file_line);
            // Set the names of the cities, the second block of the input
            for (uint32_t i = 0; i < vertices; i++) {
                fgets(file_line, 100, input_file);
                uint32_t len = strlen(file_line);
                // Cut off last character, the newline
                if (len > 0 & file_line[len - 1] == '\n') {
                    file_line[len - 1] = '\0';
                }
                cities[i] = (char *) malloc(sizeof(char) * 100);
                strcpy(cities[i], file_line);
            }
            // Read in the edges, the thrid block of the input
            while (1) {
                fgets(file_line, 100, input_file);
                if (feof(input_file)) {
                    break;
                }
                char *char_coordinate = strtok(file_line, " ");
                while (char_coordinate != NULL) {
                    coordinates[coordinate_index] = atoi(char_coordinate);
                    char_coordinate = strtok(NULL, " ");
                    coordinate_index++;
                }
            }
            // Close the input file, free the dynamically allocated string infile and break without memory leaks.
            fclose(input_file);
            free(infile);
            break;
        }
    }
    return 0;
}
