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

// Variables if needed


struct HashTable{
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
};

BloomFilter *bf_create(uint32_t size) {
    return bf;
}

bf_delete(BloomFilter **bf) {
    return;
}

uint32_t bf_size(BloomFilter *bf) {
    return;
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    return;
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    return;
}

uint32_t bf_count(BloomFilter *bf) {
    return;
}

void bf_print(BloomFilter *bf) {
    return;
}
