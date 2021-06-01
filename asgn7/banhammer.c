#include "bf.h"
#include "ht.h"
#include "llu.h"
#include "messages.h"
#include "parser.h"

#include <assert.h>
#include <ctype.h>
#include <fcntl.h>
#include <getopt.h>
#include <inttypes.h>
#include <math.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// Defenitions
#define MAXWORD 100
#define OPTIONS "t:f:hsm"
#define WORD    "([A-Za-z_0-9]+)|(([A-Za-z_0-9]+)'([A-Za-z_0-9]+))+|(([A-Za-z_0-9]+)-([A-Za-z_0-9]+))+"

// Static and gloabal variables
static bool oldspeak = false, thoughtcrime = false;
extern uint64_t seeks, links;

// Helper functions

// Read in the badspeak words and set the bloomfilter and hashtable with these
int read_badspeak(BloomFilter *bf, HashTable *ht) {
    FILE *badspeak;
    badspeak = fopen("badspeak.txt", "r");
    char bad_word[MAXWORD];

    while (fscanf(badspeak, "%s", bad_word) == 1) {
        bf_insert(bf, bad_word);
        ht_insert(ht, bad_word, NULL);
    }

    fclose(badspeak);
    return 0;
}

// Read in the oldspeak words and their newspeak replacements and set the bloomfilter and hashtable with these
int read_oldspeak(BloomFilter *bf, HashTable *ht) {
    FILE *newspeak;
    newspeak = fopen("newspeak.txt", "r");
    char old_word[MAXWORD], new_word[MAXWORD];

    while (fscanf(newspeak, "%s %s", old_word, new_word) == 2) {
        bf_insert(bf, old_word);
        ht_insert(ht, old_word, new_word);
    }

    fclose(newspeak);
    return 0;
}

// Call parser functions to scan input text, check all words for oldspeak, badspeak status
int parse_text(BloomFilter *bf, HashTable *ht, LinkedListUntracked *bad, LinkedListUntracked *old) {
    // Initialze and complie the regex
    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to comple regex. \n");
        return 1;
    }

    // Read from stdin, every word matching the regex is checked for bloom filter membership, after it is converted to all lower case
    char *word = NULL;
    Node *ht_node;
    while ((word = next_word(stdin, &re)) != NULL) {
        // All characters to lower case
        for (uint64_t i = 0; i < strlen(word); i++) {
            word[i] = tolower(word[i]);
        }

        // Check the bf first
        if (bf_probe(bf, word) == true) {
            ht_node = ht_lookup(ht, word);

            if (ht_node != NULL) {
                // Either badspeak or oldspeak occured
                if (ht_node->newspeak == NULL) {
                    // Badspeak specifically occured, add node to the badspeak list
                    llu_insert(bad, ht_node->oldspeak, NULL);
                    seeks++;
                    links++;
                    thoughtcrime = true;
                } else {
                    // Oldspeak specifically occured add node to the oldspeak list
                    llu_insert(old, ht_node->oldspeak, ht_node->newspeak);
                    seeks++;
                    links++;
                    oldspeak = true;
                }
            }
            // No if means bf issued a false positive, do nothing
        }
        // False from bf means definetly not badspeak, continue
    }
    ht_node = NULL;
    node_delete(&ht_node);

    clear_words();
    regfree(&re);
    return 0;
}

// Prints the message in case of oldspeak AND badspeak
int print_mixspeak_message(LinkedListUntracked *bad, LinkedListUntracked *old) {
    printf("%s", mixspeak_message);
    llu_print(bad);
    llu_print(old);
    return 0;
}

// Prints the message in case of badspeak
int print_badspeak_message(LinkedListUntracked *bad) {
    printf("%s", badspeak_message);
    llu_print(bad);
    return 0;
}

// Prints the message in case of oldspeak
int print_goodspeak_message(LinkedListUntracked *old) {
    printf("%s", goodspeak_message);
    llu_print(old);
    return 0;
}

// Print the statistics if user wishes to
int print_statistics(BloomFilter *bf, HashTable *ht) {
    //printf("Printing statistics\n");
    float avg_seek_length, htl, bfl;
    avg_seek_length = links / (float) seeks;
    htl = 100 * (ht_count(ht) / (float) ht_size(ht));
    bfl = 100 * (bf_count(bf) / (float) bf_size(bf));

    //Print statements for output of banhammer to turn in
    printf("Seeks %lu \n", seeks);
    printf("Average seek length: %.6f \n", avg_seek_length);
    printf("Hash table load: %.6f%% \n", htl);
    printf("Bloom filter load: %.6f%% \n", bfl);

    // Print statements optimized for putting into data files for graphing
    //printf("%u \t %u \t %lu \n", bf_size(bf), bf_count(bf), seeks);
    //printf("%u \t %u \t %.6f \t %.6f \n", ht_size(ht), ht_count(ht), avg_seek_length, htl);
    //printf("%u \t %.6f \n", ht_size(ht), avg_seek_length);
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
                   "  -f size       Spacify Bloom filter size (default: 2^20)\n");
            return 0;
        case 't': tsize = atoi(optarg); break;
        case 'f': fsize = atoi(optarg); break;
        case 'm': mtf = true; break;
        case 's': statistics = true; break;
        }
    }

    // Create a bloom filter and hash table
    BloomFilter *bf = bf_create(fsize); // Check if this is the size you want
    HashTable *ht = ht_create(tsize, mtf); // Size check

    // Because I already made a linked list, I'm gonna use it to store transgressions as well
    // However, to prevent altering global variables, I created an untracked linked list, same
    // except that it does not alter seeks and links
    LinkedListUntracked *llold = llu_create(false);
    LinkedListUntracked *llbad = llu_create(false);

    // Call to read in badspeak and oldspeak
    read_badspeak(bf, ht);
    read_oldspeak(bf, ht);

    // Not yet fully implemented:
    parse_text(bf, ht, llbad, llold);

    // Check for flags
    if (statistics == false) {
        if (thoughtcrime == true && oldspeak == true) {
            // Return mixspeak message
            print_mixspeak_message(llbad, llold);
        } else if (thoughtcrime == true) {
            // Return badspeak message
            print_badspeak_message(llbad);
        } else if (oldspeak == true) {
            // Return goodspeak message
            print_goodspeak_message(llold);
        } else {
            // Model citizen, no message
        }
    }

    // If statistical printing is specified, print statistics
    if (statistics == true) {
        print_statistics(bf, ht);
    }

    llu_delete(&llold);
    llu_delete(&llbad);
    bf_delete(&bf);
    ht_delete(&ht);
    return 0;
}
