## Assignment 4

This program implements 4 different sorting algorithms, bubblesort, shellsort, iterative quicksort with a stack, and iterative quicksort with a queue. It then allows for sorts to be done on an array built to the user's specification and provides information on the speed and complexity of the different algorithms.

### Files:

**---vertices.h:** Contains the prototype and constant value for VERTICES

**---graph.h:** Contains the protytype for graph.c.

**---graph.c:** Contains the constructor, destructor, and functions for the graph ADT.

**---path.h:** Contains the prototype for path.

**---path.c:** Contains the constructor, destructor, and functions for the path ADT.

**---stack.h:** Contains the prototype for stack.c.

**---stack.c:** The source code for the stack ADT.

**---tsp.c:** The file containing the main method which produces the formatted output summarizing the results and the functions for command line arguments that allow the user to interact with the program.

**---Makefile:** The makefile which creates object files for the various ADTs and main function file, then links them to create a binary file, tsp. Also removes old files.

**---README.md:** Markdown file containing instructions to run and build this program.

**---DESIGN.pdf:** Design document showing function requirements, drawing I used to visualize my ADTs, pseudocode for my functions, and general observations during the project.

### Build:

Enter command $ make

There should be no flags or errors during this process

### Running:

Enter command $ ./tsp

The program will show options to choose from which print some or all tests with different seed, array size, and printing specifications:

**-h** Print help message describing the graph and command line options

**-v** Enable verbose printing, in other words, print all Hamiltonian paths, not just the shortest.

**-u** Specifies the graph to be undirected.

**-i** Follow with the name of the input file contianing cities (vertices) and roads (edges). If none is specified, command line is input.

**-o** Follow with the name of the output file to print path to. If none is specified, command line is output.

