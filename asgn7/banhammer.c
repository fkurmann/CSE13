#include "parser.h"
#include "ht.h"
#include "bf.h"

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

// Constants
#define SIZE 10000
#define MAXWORD 100
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

int read_oldspeak(BloomFilter *bf, HashTable *ht) {
    FILE * newspeak;
    newspeak = fopen("newspeak.txt", "r");
    char old_word [MAXWORD], new_word[MAXWORD];
    
    while (fscanf(newspeak, "%s %s", old_word, new_word) == 1) {
        bf_insert(bf, old_word);
        ht_insert(ht, old_word, new_word);
    }
    
    fclose(newspeak);
    return 0;
}

int main(void) {
    BloomFilter *bf = bf_create(SIZE); // Check if this is the size you want
    HashTable *ht = ht_create(SIZE, false); // Size check

    read_badspeak(bf, ht);
    printf("%u \n", bf_count(bf));

    read_oldspeak(bf, ht);
    printf("%u \n", ht_count(ht));


















    bf_delete(&bf);
    ht_delete(&ht);
    return 0;
}
