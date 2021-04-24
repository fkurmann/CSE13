#include "set.h"

#include <assert.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// CITATION: These set functions are those provided by Eugene Chou on the CSE 13S Piazza.

Set set_empty(void) {
    return 0x00000000;
}

bool set_member(Set s, int x) {
    return s & (1 << (x % SET_CAPACITY));
}

Set set_insert(Set s, int x) {
    return s | (1 << (x % SET_CAPACITY));
}

Set set_remove(Set s, int x) {
    return s & ~(1 << (x % SET_CAPACITY));
}

Set set_union(Set s, Set t) {
    return s | t;
}

Set set_intersect(Set s, Set t) {
    return s & t;
}

Set set_difference(Set s, Set t) {
    return s & ~t;
}

Set set_complement(Set s) {
    return ~s;
}
