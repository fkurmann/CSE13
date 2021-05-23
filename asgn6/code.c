#include "code.h"

#include "defines.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Code code_init(void) {
    Code c;
    c.top = 0;
    return c;
}

bool code_empty(Code *c) {
    return c->top == 0;
}

bool code_full(Code *c) {
    return c->top == ALPHABET;
}

uint32_t code_size(Code *c) {
    return c->top;
}

// If the code is full, return false, else push a bit
bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c) == true) {
        return false;
    }
    // Locate byte which top is pointing to, the byte to be adjusted
    uint8_t byte = c->top / 8;
    uint8_t bit_in_byte = c->top % 8;
    // If pushing a byte with value one, the array byte must be modified
    if (bit == 1) {
        c->bits[byte] += pow(2, bit_in_byte);
    }
    // Index shift regardless
    c->top++;
    return true;
}

// If the code is empty, return false, else pop a bit
bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c) == true) {
        return false;
    }
    // Begin by shifting top back to sit on the top value
    c->top--;
    // Locate top bit inside it's byte, then extract it from there as with Asgn5's get bit
    uint8_t byte = c->top / 8;
    uint8_t bit_in_byte = c->top % 8;
    uint8_t byte_value = c->bits[byte];
    byte_value = byte_value >> bit_in_byte;
    byte_value = byte_value % 2;
    *bit = byte_value;
    // If popping a byte with value one, the array byte must be modified
    if (byte_value == 1) {
        c->bits[byte] -= pow(2, bit_in_byte);
    }
    // Index shift regardless
    return true;
}

void code_print(Code *c) {
    for (uint8_t i = 0; i < code_size(c); i++) {
        for (uint8_t j = 0; j < 8 && (j + 8 * i) < (uint8_t) code_size(c); j++) {
            // Extract bit values as with Asgn5's get bit
            uint8_t byte_value = c->bits[i];
            byte_value = byte_value >> j;
            byte_value = byte_value % 2;
            printf("%u  ", byte_value);
        }
        printf("   ");
    }
    printf("\n");
    return;
}
