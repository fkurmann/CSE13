## Assignment 6

This assignment contains an encoder and a decoder. The encoder compresses the input file using Huffman coding, it may then return statitics on the file compression and send the compressed file to an output file. The decoder restores the compressed file it is given using the Huffman algorithm in reverse. It may then also return statitics on the decoding and send the decoded file to an output file.

### Files:

**---encode.c:** The function which checks command line args, calls for an input to be read, calls the huffman algorithms, and calls for an output to be written.

**---decode.c:** The function which checks command line args, calls for an input to be read, calls the huffman algorithms, and calls for an output to be written.

**---entropy.c:** Quantifies information from the encoding and decoding processes.

**---defines.h:** Contains macro defenitions used throughout the assignment.

**---header.h:** Contains structure defneition for the file header.

**---node.h:** Contains the prototype for node.c.

**---pq.h:** Contains the prototype for pq.c.

**---code.h:** Contains the prototype for code.c.

**---io.h:** Contains the prototype for io.c.

**---stack.h:** Contains the prototype for stack.c.

**---huffman.h:** Contains the prototype for huffman.c.

**---node.c:** Contains the implementation of the node ADT.

**---pq.h:** Contains the implementation of the priority queue ADT.

**---code.h:** Contains the implementation of the code (a bitwise stack) ADT.

**---io.h:** Contains the implementation of the input/output (via read/write systalls) ADT.

**---stack.h:** Contains the implementation of the stack ADT.

**---huffman.h:** Contains the implementation of the huffman encoding and decoding alorithtms including building a tree, building codes, rebuilding a tree, and deleting a tree.

**---Makefile:** The makefile which creates object files for the various ADTs and encode/decode functions, then links the files to create a excecutable binary files encode and decode. Also removes old files and can be called to style all files.

**---README.md:** Markdown file containing instructions to run and build this program.

**---DESIGN.pdf:** Design document showing function requirements, drawings used to visualize the ADTs and the encoding/decoding process, pseudocode for my functions, and general observations during the project.


### Build:

Enter command $ make {decode, encode, entropy, clean, format} to build/clear/format the desired program(s).

There should be no flags or errors during this process

### Running:

Enter command $ ./encode OR $ ./decode to encode, send, and decode files from files.

**-h** Print help message describing the program and its command line options

**-v** Enable verbose printing, printing information on the error quantity and probability during decoding.

**-i** Follow with the name of the input file contianing uint8s that contain the bitwise information to encode/decode. If none is specified, command line is input.

**-o** Follow with the name of the output file to print encoded/decoded bits to in the for of uint8s. If none is specified, command line is output.

