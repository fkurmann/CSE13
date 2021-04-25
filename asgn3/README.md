## Assignment 3

This program implements 4 different sorting algorithms, bubblesort, shellsort, iterative quicksort with a stack, and iterative quicksort with a queue. It then allows for sorts to be done on an array built to the user's specification and provides information on the speed and complexity of the different algorithms.

### Files:

**---bubble.h:** Contains the prototype for bubble.c.
**---bubble.c:** The source code for the bubblesort function.
**---gaps.h:** Contains the gaps array that is used by shellsort.
**---shell.h:** Contains the prototype for shell.c.
**---shell.c:** The source code for the shellsort function.
**---quick.h:** Contains the prototype for quick.c.
**---quick.c:** The source code for both quicksort functions and the partition helper function.

**---stack.h:** Contains the prototype for stack.c.
**---stack.c:** The source code for the stack ADT.
**---queue.h:** Contains the prototype for queue.c.
**---queue.c:** The source code for the queue ADT.
**---set.h:** Contains the protytype for set.c.
**---set.c:** Contains the functions for set creation and manipulation.

**---sorting.c:** The file containing the main method which produces the formatted output summarizing the results and the functions for command line arguments that allow the user to interact with the program.
**---Makefile:** The makefile which creates object files for the various sorts and the stack, then links them to create a binary file, sorting. Also removes old files.

**---README.md:** Markdown file containing instructions to run and build this program.
**---DESIGN.pdf:** Design document showing mathematical drawings and examples I used to arrive at my Taylor series and Newton's methods, pseudocode for my library functions, and general observations during the project.
**---WRITEUP.pdf:** File discussing results of comparison between the math library's and my functions.

### Build:

Enter command $ make

There should be no flags or errors during this process

### Running:

Enter command $ ./sorting 

The program will show options to choose from which print some or all tests with different seed, array size, and printing specifications:
**-a** Run ALL tests
**-s** Run bubblesort tests
**-s** Run shellsort tests
**-q** Run quicksort with stack tests
**-Q** Run quicksort with queue tests
**-r** Follow with random seed for array.
**-n** Follow with number of array items to sort.
**-p** Follow with number of sorted array items to print.

Run again with the desired suffix to see test output.
