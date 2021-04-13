#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <inttypes.h>
#include <unistd.h>

#define OPTIONS "pi:"

int main(int argc, char **argv) {
    int opt = 0;
    while ((opt = getopt(argc, argc, OPTIONS)) != -1)  {
        switch (opt) {
        case'p' 
	    printf("-p option. \n");
            break;
        case'p':
            printf("-p option. \n");
            break;
        }
    }
    return 0
}
