#include "bubble.h"
#include "queue.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stack.h"

#include <assert.h>
#include <getopt.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// CITATION: The use of a set data type was inspired by the discussion on Piazza. Set functions are based on those posted by Eugene Chou.

// Command line argument options
#define OPTIONS "r:n:p:abrsqQ"

// Global variables that are edited by the sorting functions then reported here
int64_t moves, comparisons;
uint32_t max_stack, max_queue;

// Print helper function called by the output functions above to print the formatted array values
void print_output(uint32_t *A, uint32_t print_out) {
    for (uint32_t i = 0; i < print_out; i += 5) {
        for (uint32_t j = i; j < i + 5 && j < print_out; j++) {
            printf("%13" PRIu32, A[j]);
        }
        printf("\n");
    }
    return;
}

// Functions that run the sorting algorithms and output the results according to format. These all take inputs
// seed and element number as well as how many elements to print.
int bubble_output(uint32_t seed, uint32_t elements, uint32_t print_out) {
    // Reset the global variables:
    moves = 0;
    comparisons = 0;

    // Create an array from the seed:
    uint32_t array[elements];
    srandom(seed);
    for (uint32_t i = 0; i < elements; i++) {
        array[i] = random();
    }

    // Run the sorting algorithm and report results
    bubble_sort(array, elements);

    printf("Bubble Sort \n");
    printf("%u elements, %ld moves, %ld compares \n", elements, moves, comparisons);
    if (print_out != 0) {
        print_output(array, print_out);
    }

    return 0;
}

int shell_output(uint32_t seed, uint32_t elements, uint32_t print_out) {
    // Reset the global variables:
    moves = 0;
    comparisons = 0;

    // Create an array from the seed:
    uint32_t array[elements];
    srandom(seed);
    for (uint32_t i = 0; i < elements; i++) {
        array[i] = random();
    }

    // Run the sorting algorithm and report results
    shell_sort(array, elements);

    printf("Shell Sort\n");
    printf("%u elements, %ld moves, %ld compares \n", elements, moves, comparisons);
    if (print_out != 0) {
        print_output(array, print_out);
    }
    return 0;
}

int qs_output(uint32_t seed, uint32_t elements, uint32_t print_out) {
    // Reset the global variables:
    moves = 0;
    comparisons = 0;

    // Create an array from the seed:
    uint32_t array[elements];
    srandom(seed);
    for (uint32_t i = 0; i < elements; i++) {
        array[i] = random();
    }

    // Run the sorting algorithm and report results
    quick_sort_stack(array, elements);

    printf("Quick Sort (Stack)\n");
    printf("%u elements, %ld moves, %ld compares \n", elements, moves, comparisons);
    printf("Max stack size: %u \n", max_stack);
    if (print_out != 0) {
        print_output(array, print_out);
    }
    return 0;
}

int qq_output(uint32_t seed, uint32_t elements, uint32_t print_out) {
    // Reset the global variables:
    moves = 0;
    comparisons = 0;

    // Create an array from the seed:
    uint32_t array[elements];
    srandom(seed);
    for (uint32_t i = 0; i < elements; i++) {
        array[i] = random();
    }

    // Run the sorting algorithm and report results
    quick_sort_queue(array, elements);

    printf("Quick Sort (Queue)\n");
    printf("%u elements, %ld moves, %ld compares \n", elements, moves, comparisons);
    printf("Max queue size: %u \n", max_queue);
    if (print_out != 0) {
        print_output(array, print_out);
    }
    return 0;
}

int main(int argc, char **argv) {
    // Present user with options
    if (argc == 1) {
        printf("Program usage: \n"
               "  -a            runs all sorts (bubble, shell, quick stack, quick queue)\n"
               "  -b            runs bubblesort\n"
               "  -s            runs shellsort\n"
               "  -q            runs quicksort utilizing a stack\n"
               "  -Q            runs quicksort utilizing a queue\n"
               "  -r seed       sets the random seed to your input\n"
               "  -n size       sets the array size to your input\n"
               "  -p elements   sets the number of elements from the array to print out to your "
               "input\n");
    }
    // Default Settings
    uint32_t elements = 100, seed = 13371453, print_out = 100;

    // Set Initiation
    Set input_set = set_empty();

    // Command line arguments
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            input_set = set_insert(input_set, 81); // ASCII for Q
            input_set = set_insert(input_set, 113); // ASCII for q
            input_set = set_insert(input_set, 115); // ASCII for s
            input_set = set_insert(input_set, 98); // ASCII for b
            break;
        case 'b': input_set = set_insert(input_set, opt); break;
        case 's': input_set = set_insert(input_set, opt); break;
        case 'q': input_set = set_insert(input_set, opt); break;
        case 'Q': input_set = set_insert(input_set, opt); break;
        // CITATION: Use of the atoi function for converting string to uint32_t is inspired by RichieHindle's comments
        // towards the subject on Stack overflow.
        case 'r': seed = atoi(optarg); break;
        case 'n': elements = atoi(optarg); break;
        case 'p': print_out = atoi(optarg); break;
        }
    }
    // Catch the error if print exceeds elements
    if (elements < print_out) {
        print_out = elements;
    }
    //Calls to sort functions based on set containing command line args.
    if (set_member(input_set, 98) == true) {
        bubble_output(seed, elements, print_out);
    }
    if (set_member(input_set, 115) == true) {
        shell_output(seed, elements, print_out);
    }
    if (set_member(input_set, 113) == true) {
        qs_output(seed, elements, print_out);
    }
    if (set_member(input_set, 81) == true) {
        qq_output(seed, elements, print_out);
    }

    return 0;
}
