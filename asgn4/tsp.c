#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <assert.h>
#include <getopt.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Command line argument options
#define OPTIONS "i:o:hvu"

// Recursive depth first search algorithm takes in the curren and shortest paths, the graph, and a vertex to go deeper on.
void dfs(Graph *G, uint32_t vertex, Path *current_path, Path *shortest_path) {


    return;
}


// Global variables that are edited by the sorting functions then reported here
// uint32_t recursive_calles;



int main(int argc, char **argv) {
    bool verbose_printing = false, undirected = false, outfile_given = false, infile_given = false;
    //char infile [] = "Empty";
    //char outfile [] = "Empty";
    uint32_t vertices;
    char cities [VERTICES][100];
    uint32_t coordinates [1000];
    
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
        case 'u': undirected = true; break;
        case 'v': verbose_printing = true; break;
        case 'o': 
		  printf("%s \n", optarg);
		  //char outfile[] = optarg; 
		  break;
        case 'i': 
		  // Set the infile string to the argument given by the user
		  infile_given = true;
		  char* infile = strdup(optarg);
		  char file_line[20];
		  
		  // Open the file specified by input, returning an error if no such file is found.
		  // CITATION: This file opening, reading, and checking is inspired by code found on the website tutorials
		  // point.com.
		  FILE *input_file = fopen(infile, "r");
		  if (input_file == NULL) {
	              perror("Invalid file");
		      return 1;
		  }
                  
		  // Set the number of vertices, the first line of the input
		  fgets(file_line, 100, input_file);
		  vertices = atoi(file_line);
		  if (vertices > VERTICES) {
	              fprintf(stderr, "Error: Input file contains too many vertices \n");
		      return 1;
		  }
                   
		  // Set the names of the cities, the second block of the input
		  for (uint32_t i = 0; i < vertices; i++) {
		      fgets(file_line, 100, input_file);
	              strcpy(cities[i], (file_line));
		  }

		  // Set the coordinates of the cities, the thrid block of the input
		  for (uint32_t i = 0; i < (3 * vertices); i += 3) {
		      fgets(file_line, 100, input_file);

		      char *char_coordinate = strtok(file_line, " ");
		      uint32_t index = 0;
		      while (char_coordinate != NULL) {
			  coordinates[i + index] = atoi(char_coordinate);
			  char_coordinate = strtok(NULL, " ");
                          index++;
		      }
		  }
                  // Close the input file, free the dynamically allocated string infile and break without memory leaks.
		  fclose(input_file);
		  free(infile); 
		  break;
	}
    }

    /*
    if (infile_given == true ||  outfile_given == true) {
        
	for (uint32_t i = 0; i < vertices; i++) {
	    printf("%s", cities[i]);
        }
    }
    */

    // Read the input from a file or the command line and create ititial adt's
    Path *shortest_path = path_create();
    Path *current_path = path_create();
    Graph *map = graph_create(vertices, undirected);
    for (uint32_t i = 0; i < (3* vertices); i += 3) {
        graph_add_edge(map, coordinates[i], coordinates[i+1], coordinates[i+2]);
    }
    //graph_print(map);
    printf("%u \n", graph_vertices(map));

    // Delete the ADT's to prevent memory leaks.
    path_delete(&shortest_path);
    path_delete(&current_path);
    graph_delete(&map);

    return 0;
}
