#include "bf.h"

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

/*
struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};*/

BloomFilter *bf_create(uint32_t  size) {
    BloomFilter *bf = (BloomFilter *)  malloc(sizeof(BloomFilter));
    if (bf) {
        //  Grimm's Fairy  Tales
        bf->primary[0] = 0x5adf08ae86d36f21;
        bf->primary[1] = 0xa267bbd3116f3957;
        // The  Adventures  of  Sherlock  Holmes
        bf->secondary[0] = 0x419d292ea2ffd49e;
        bf->secondary[1] = 0x09601433057d5786;
        // The  Strange  Case of Dr. Jekyll  and Mr. Hyde
        bf->tertiary[0] = 0x50d8bb08de3818df;
        bf->tertiary[1] = 0x4deaae187c16ae1d;
        bf->filter = bv_create(size);
        if (!bf->filter) {
            free(bf);
	    bf = NULL;
        }
    }
    return  bf;
}

void bf_delete(BloomFilter **bf) {
    if (*bf && (*bf)->filter) {
	bv_delete(&((*bf)->filter));

        free(*bf);
	*bf = NULL;
    }
    return;
}

uint32_t bf_size(BloomFilter *bf) {
    return (bv_length(bf->filter));
}

void bf_insert(BloomFilter *bf, char *oldspeak) {
    return;
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    return false;
}

uint32_t bf_count(BloomFilter *bf) {
    return 0;
}

void bf_print(BloomFilter *bf) {
    return;
}
