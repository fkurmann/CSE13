#include "bf.h"
#include "speck.h"

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
    // Hash using all three salts
    uint32_t hash_one = hash(bf->primary, oldspeak);
    uint32_t hash_two = hash(bf->secondary, oldspeak);
    uint32_t hash_three = hash(bf->tertiary, oldspeak);

    // Check if your hash values exceed vector length to prevent segmentation faults
    if (hash_one > bv_length(bf->filter) || hash_two > bv_length(bf->filter) || hash_three > bv_length(bf->filter)) {
        printf ("Error, hash values exceed length of bit vector. \n");
	return;
    } 
    // Set the bits of your bit vector assiciated with the hashed values for oldspeak
    bv_set_bit(bf->filter, hash_one);
    bv_set_bit(bf->filter, hash_two);
    bv_set_bit(bf->filter, hash_three);
    return;
}

bool bf_probe(BloomFilter *bf, char *oldspeak) {
    // Hash using all three salts
    uint32_t hash_one = hash(bf->primary, oldspeak);
    uint32_t hash_two = hash(bf->secondary, oldspeak);
    uint32_t hash_three = hash(bf->tertiary, oldspeak);
    
    // Check if your hash values exceed vector length to prevent segmentation faults
    if (hash_one > bv_length(bf->filter) || hash_two > bv_length(bf->filter) || hash_three > bv_length(bf->filter)) {
        printf ("Error, hash values exceed length of bit vector. \n");
	return false;
    } 
    // Get the bits of your bit vector assiciated with the hashed values for oldspeak
    uint8_t index_one = bv_get_bit(bf->filter, hash_one);
    uint8_t index_two = bv_get_bit(bf->filter, hash_two);
    uint8_t index_three = bv_get_bit(bf->filter, hash_three);
    if (index_one == 1 && index_two == 1 && index_three == 1) {
        return true;
    } else{
        return false;
    }
}

uint32_t bf_count(BloomFilter *bf) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < bf_size(bf); i++) {
        if (bv_get_bit(bf->filter, i) == 1) {
	    count++;
	}
    }
    return count;
}

void bf_print(BloomFilter *bf) {
    return;
}
