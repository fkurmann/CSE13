## Assignment 5

This assignment contains an encoder and a decoder. The encoder generates a Hamming code given input data read in a bitwise fashion. The decoder will then decode the Hamming code and, if an error is found, attempt to fix the error if it is possible. Given corrupted data from the error function, the decoder function can also print statistics on the amount of corrupted data.

### Files:

**---encode.c:** The function which reads, calls ham encode on, and returns its input using Hamming Codes.

**---decode.c:** The function which reads, calls ham decode on, and returns its input using Hamming Codes, it also can return error statistics.

**---error.c:** Function to add random noise to the encoded files.

**---entropy.c:** Quantifies information from the encoding and decoding processes.

**---bv.h:** Contains the prototype for bv.c.

**---bv.c:** Contains the functions for the bit vector abstract data type.

**---bm.h:** Contains the prototype for bm.c.

**---bm.c:** Contains the functions for the bit matrix abstract data type.

**---hamming.h:** Contains the prototype for hamming.c.

**---hamming.c:** Contains the hamming encode and decode functions which generate the Hamming Codes used by the main methods.

**---Makefile:** The makefile which creates object files for the various ADTs and encode/decode functions, then links the files to create a excecutable binary files encode and decode. Also removes old files and can be called to style all files.

**---README.md:** Markdown file containing instructions to run and build this program.

**---DESIGN.pdf:** Design document showing function requirements, drawings used to visualize the ADTs and the encoding/decoding process, pseudocode for my functions, and general observations during the project.

**---WRITEUP.pdf:** Summary of results from anylizing the entropy of my encoding and decoding error data. Includes graphs and analysis of program functioning.


### Build:

Enter command $ make

There should be no flags or errors during this process

### Running:

Enter command $ ./encode OR $ ./decode to encode, send, and decode files from files.

The program will show options to choose from which print some or all tests with different seed, array size, and printing specifications:

**-h** Print help message describing the program and its command line options

**-v** Enable verbose printing, printing information on the error quantity and probability during decoding.

**-i** Follow with the name of the input file contianing uint8s that contain the bitwise information to encode/decode. If none is specified, command line is input.

**-o** Follow with the name of the output file to print encoded/decoded bits to in the for of uint8s. If none is specified, command line is output.

Enter command $ ./error and $ ./entropy
