## Assignment 7

This assignment contains an encoder and a decoder. The encoder compresses the input file using Huffman coding, it may then return statitics on the file compression and send the compressed file to an output file. The decoder restores the compressed file it is given using the Huffman algorithm in reverse. It may then also return statitics on the decoding and send the decoded file to an output file.

### Files:

**--banhammer.c:** Contains the main method which calls on abstract data types and other files' function to run the bloom filtering on input text.

**--messages.h:** Defines mixspeak, badspeak, goodspeak messages used in banhammer.c.

**---speck.h:** Contains the prototype for the speck cipher.

**---speck.c:** Contains the implementation of the hash functions using the speck cipher.

**---ht.h:** Contains the prototype for the ht.c

**---ll.h:** Contains the prototype for ll.c.

**---node.h:** Contains the prototype for node.c.

**---bf.h:** Contains the prototype for bf.c.

**---bv.h:** Contains the prototype for bv.c.

**---parser.h:** Contains the prototype for parser.c.

**---ht.c:** Contains the implementation of the hash table ADT.

**---ll.c:** Contains the implementation of the linked list ADT.

**---node.c:** Contains the implementation of the node ADT.

**---bf.c:** Contains the implementation of the bloom filter ADT.

**---bv.c:** Contains the implementation of the bit vector.

**---parser.c:** Contains the implementation of the regex parser for input strings.

**---Makefile:** The makefile which creates object files for the various ADTs and encode/decode functions, then links the files to create a excecutable binary files encode and decode. Also removes old files and can be called to style all files.

**---README.md:** Markdown file containing instructions to run and build this program.

**---DESIGN.pdf:** Design document showing function requirements, drawings used to visualize the ADTs and the filtering process, pseudocode for my functions, and general observations during the project.

**---WRITEUP.pdf:** Design document showing function requirements, drawings used to visualize the ADTs and the encoding/decoding process, pseudocode for my functions, and general observations during the project.

### Build:

Enter command $ make {<>, all, clean, format} to build/clear/format the desired program(s).

There should be no flags or errors during the scan-build process.

### Running:

Enter command $ ./banhammer (-h -t -f -m -s).

**-h** Print help message describing the program and its command line options.

**-t** Follow with the desired size of the hash table. Default is 10000

**-f** Follow with the desired size of the Bloom filter. Default is 2^20

**-m** Enable the move to front rule.

**-s** Enable printing of statistics to stdout.

