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
HashTable *ht_create(uint32_t  size , bool  mtf) {2    HashTable *ht = (HashTable  *)  malloc(sizeof(HashTable));3    if (ht) {4      //  Leviathan5      ht ->salt [0] = 0x9846e4f157fe8840;6      ht ->salt [1] = 0xc5f318d7e055afb8;7      ht ->size = size;8      ht ->mtf = mtf;9      ht ->lists = (LinkedList  **)  calloc(size , sizeof(LinkedList  *));10      if (!ht->lists) {11         free(ht);12         ht = NULL;13      }14    }15    return  ht;16 }
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
