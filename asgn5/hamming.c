#include "hamming.h"
#include "bm.h"
#include "helper.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

extern uint32_t bytes_processed, uncorrected_errors, corrected_errors;
uint32_t lookup_table[] = {10, 4, 5, 9, 6, 9, 9, 3, 7, 9, 9, 2, 9, 1, 0, 9};

uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    return(bm_to_data(bm_multiply(bm_from_data(msg, 4), G)));
}

HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg){
    BitMatrix *Encoded = bm_from_data(code, 8); // Turn the byte into a bit matrix to multiply with the transpose.
    bytes_processed++;
    uint8_t error = bm_to_data(bm_multiply(Encoded, Ht));  //the decoder spits out 4 bits, these are the error message, bm to data turns it into a uint.
    
    bm_delete(&Encoded);
    
    // Case 1: Ham error
    if (lookup_table[error] == 9) {
        uncorrected_errors++;
	*msg = lower_nibble(code); 
	return HAM_ERR;
    }

    // Case 2: Ham ok
    else if (lookup_table[error] == 10) {
        *msg = lower_nibble(code); 
	return HAM_OK;
    }

    // Case 3: Ham corrected
    else {
	corrected_errors++;
	// Turn the output bit into a bitmatrix so that it can be adjusted according to the error found by the decoder.
	BitMatrix *Decoded = bm_from_data(lower_nibble(code), 8);
	if (bm_get_bit(Decoded, 0, lookup_table[error]) == 1) {
	    bm_clr_bit(Decoded, 0, lookup_table[error]);
	}
	else {
	    bm_set_bit(Decoded, 0, lookup_table[error]);
	}

	*msg = bm_to_data(Decoded);

	bm_delete(&Decoded);
	return HAM_CORRECT;
    }
}
