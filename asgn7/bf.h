#ifndef __BF_H__
#define __BF_H__

#include "bv.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct BloomFilter BloomFilter;

struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size);

void bf_delete(BloomFilter **bf);

uint32_t bf_size(BloomFilter *bf);

void bf_insert(BloomFilter *bf, char *oldspeak);

bool bf_probe(BloomFilter *bf, char *oldspeak);

uint32_t bf_count(BloomFilter *bf);

void bf_print(BloomFilter *bf);

#endif
