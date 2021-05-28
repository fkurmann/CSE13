#include "parser.h"
#include "ht.h"
#include "bf.h"
#include "messages.h"
#include "llu.h"

#include <regex.h>
#include <assert.h>
#include <fcntl.h>
#include <getopt.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// Defenitions
#define MAXWORD 100
#define OPTIONS "t:f:hsm"
#define WORD "([A-Za-z_0-9]+)|(([A-Za-z_0-9]+)'([A-Za-z_0-9]+))+|(([A-Za-z_0-9]+)-([A-Za-z_0-9]+))+"

// Static and gloabal variables
static bool oldspeak = false, thoughtcrime = false;
uint64_t seeks;

// Helper functions

// Read in the badspeak words and set the bloomfilter and hashtable with these
int read_badspeak(BloomFilter *bf, HashTable *ht) {
    FILE * badspeak;
    badspeak = fopen("badspeak.txt", "r");
    char bad_word [MAXWORD];
    
    while (fscanf(badspeak, "%s", bad_word) == 1) {
        bf_insert(bf, bad_word);
        ht_insert(ht, bad_word, NULL);
    }

    fclose(badspeak);
    return 0;
}

// Read in the oldspeak words and their newspeak replacements and set the bloomfilter and hashtable with these
int read_oldspeak(BloomFilter *bf, HashTable *ht) {
    FILE * newspeak;
    newspeak = fopen("newspeak.txt", "r");
    char old_word [MAXWORD], new_word[MAXWORD];
    
    while (fscanf(newspeak, "%s %s", old_word, new_word) == 2) {
        bf_insert(bf, old_word);
        ht_insert(ht, old_word, new_word);
    }
    
    fclose(newspeak);
    return 0;
}

// Call parser functions to scan input text, check all words for oldspeak, badspeak status
int parse_text(BloomFilter *bf, HashTable *ht) {
    // Initialze and complie the regex 
    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to comple regex. \n");
	return 1;
    }
 
    // Read from stdin, every word matching the regex is checked for bloom filter membership, after it is converted to all lower case
    char *word = NULL;
    while ((word = next_word(stdin, &re)) != NULL) {
        printf("Word: %s\n", word);

	if (bf_probe(bf, word) == true) {
	    Node *ht_node = ht_lookup(ht, word);

	    if (ht_node != NULL) {
	    node_print(ht_node);
	        // Either badspeak or oldspeak occured
		if (ht_node->newspeak == NULL) {
                    printf("Identified as badspeak\n");
		    // Badspeak specifically occured
		    thoughtcrime = true;
		}
		else {
		    // Oldspeak specifically occured
                    printf("Identified as oldspeak\n");
		    oldspeak = true;
		}
	    }
	    // No if means bf issued a false positive, do nothing
	}
	// False from bf means definetly not badspeak, continue
    }

    clear_words();
    regfree(&re);

    return 0;
}

int print_mixspeak_message(void) {
    printf("%s \n", mixspeak_message);
    return 0;
}

int print_badspeak_message(void) {
    printf("%s \n", badspeak_message);
    return 0;
}

int print_goodspeak_message(void) {
    printf("%s \n", goodspeak_message);
    return 0;
}




int main(int argc, char **argv) {
    // Variables for main function, many of which are set by user via command line
    uint32_t tsize = 10000, fsize = 1048576;
    bool mtf = false, statistics = false;
    // Command line arguments get processed, size, mtf, and statistics printing are set

    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h':
            printf("A word filtering program for the GPRSC\n"
	           "Filters out and reports bad words parsed from stdin.\n\n" 
		   "Program usage: \n"
                   "  -h            Show help menu\n"
                   "  -s            Print program statistics\n"
                   "  -m            Enable move-to-front rule (optimizes search)\n"
                   "  -t size       Specify hash table size (default: 10000)\n"
                   "  -f size       Spacify Bloom filter size (default: 2^20)");
            return 0;
            //break;
        case 't':
            tsize = atoi(optarg);
	    break;
        case 'f':
            fsize = atoi(optarg);
            break;
	case 'm':
	    mtf = true;
	    break;
	case 's':
	    statistics = true;
	    break;
        }
    }

    // Create a bloom filter and hash table
    BloomFilter *bf = bf_create(fsize); // Check if this is the size you want
    HashTable *ht = ht_create(tsize, mtf); // Size check

    // Because I already made a linked list, I'm gonna use it to store transgressions as well
    // However, to prevent altering global variables, I created an untracked linked list, same 
    // except that it does not alter seeks and links

    LinkedListUntracked *llold = llu_create();
    LinkedListUntracked *llbad = llu_create();

    // Call to read in badspeak
    read_badspeak(bf, ht);
    //printf("%u \n", bf_count(bf));
    //printf("%u \n", ht_count(ht));

    // Call to read in oldspeak
    read_oldspeak(bf, ht);
    //printf("%u \n", bf_count(bf));
    //printf("%u \n", ht_count(ht));

    
    // Not yet fully implemented:
    parse_text(bf, ht);

    
    // Check for flags
    if (thoughtcrime == true && oldspeak == true) {
        printf("Badspeak and oldspeak\n");
	print_mixspeak_message();
        // Return mixspeak message
    } else if (thoughtcrime == true) {
        printf("Just badspeak\n");
	print_badspeak_message();
        // Return badspeak message
    } else if (oldspeak == true) {
        printf("Just oldspeak\n");
	print_goodspeak_message();
        // Return goodspeak message
    } else {
        printf("You're good\n");
        // Model citizen, no message
    }

    // If statistical printing is specified, print statistics
    if (statistics == true) {
	printf("Printing statistics\n");
        float avg_seek_length, htl, bfl;
	//avg_seek_length = 100 * (seeks / (float) links);
	htl = 100 * (ht_count(ht) / (float) ht_size(ht));
	bfl = 100 * (bf_count(bf) / (float) bf_size(bf));

	printf("Seeks %lu \n", seeks);
	//printf("Average seek length: %.6f \n", avg_seek_length);
	printf("Hash table load: %.6f%% \n", htl);
	printf("Bloom filter load: %.6f%% \n", bfl);

    }



    bf_delete(&bf);
    ht_delete(&ht);
    return 0;
}
