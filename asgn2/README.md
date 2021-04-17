## Assignment 2

This program compares the math.h library functions asin, acos, atan, and log with the corresponding functions arcSin, arcCos, arcTan, and Log built by myself in the source code file mathlib.c.

### Files:

**---mathlib.h:** The function prototype file for my versions of the libary files
**---mathlib.c:** The source code for my math functions as well as a few helper math functions such as Exp(), Abs(), and Sqrt()
**---mathlib-test.c:** The file containing the main method which tests the math functions based on the command line input given by the user.
**---Makefile:** The makefile which creates object files of mathlib.c and mathlib-test.c, a binary file of mathlib-test and also removes old files.
**---README.md:** Markdown file containing instructions to run and build this program
**---DESIGN.pdf:** Design document showing mathematical drawings and examples I used to arrive at my Taylor series and Newton's methods, pseudocode for my library functions, and general observations during the project.
**---WRITEUP.pdf:** File discussing results of comparison between the math library's and my functions.

### Build:

Enter command $ make

There should be no flags or errors during this process

### Running:

Enter command $ ./mathlib-test

The program will show options to choose from which print some or all tests:
**-a** Run ALL tests
**-s** Run arcsin tests
**-c** Run arccos tests
**-t** Run arctan tests
**-l** Run log tests

Run again with the desired suffix to see test output.
