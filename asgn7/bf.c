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


struct BloomFilter {
    uint64_t primary[2];
    uint64_t secondary[2];
    uint64_t tertiary[2];
    BitVector *filter;
};
 BloomFilter *bf_create(uint32_t  size) {2    BloomFilter *bf = (BloomFilter  *)  malloc(sizeof(BloomFilter));3    if (bf) {4      //  Grimm's Fairy  Tales5      bf ->primary [0] = 0x5adf08ae86d36f21;6      bf ->primary [1] = 0xa267bbd3116f3957;7      // The  Adventures  of  Sherlock  Holmes8      bf ->secondary [0] = 0x419d292ea2ffd49e;9      bf ->secondary [1] = 0x09601433057d5786;10      // The  Strange  Case of Dr. Jekyll  and Mr. Hyde11      bf ->tertiary [0] = 0x50d8bb08de3818df;12      bf ->tertiary [1] = 0x4deaae187c16ae1d;13      bf ->filter = bv_create(size);14      if (!bf->filter) {15         free(bf);16         bf = NULL;17      }18    }19    return  bf;20 }
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
