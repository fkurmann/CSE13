#include "mathlib.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <inttypes.h>
#include <unistd.h>

#define OPTIONS "asctl"
#define FORMAT " %7.4lf % 16.8lf % 16.8lf % 16.10lf\n"
#define LINES "  -            ------           -------       ----------\n"
/*
int main(int argc, char **argv) {
    int opt = 0;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1)  {
        switch (opt) {
	case'a': 
    	    printf("  x            all              Library        Difference\n");
            break;
        case's':
    	    printf("  x            arcSin           Library        Difference\n");
            break;
        case'c': 
    	    printf("  x            arccos           Library        Difference\n");
            break;
        case't':
    	    printf("  x            arctan           Library        Difference\n");
            break;
	case'l':
    	    printf("  x            arclog           Library        Difference\n");
	    break;
        }
    }
    return 0;
}

*/

int main(void) { 

    // Sin comparison:
    printf("  x            arcSin           Library        Difference\n");
    printf(LINES);
    for (double i = -1.0; i <= 1.0; i += 0.1) {
	double my_fxn = arcSin(i), lib_fxn = asin(i);	
        printf(FORMAT, i, my_fxn, lib_fxn, (my_fxn - lib_fxn));
    }

    // Cos comparison:
    printf("\n");
    printf("  x            arcCos           Library       Difference\n");
    printf(LINES);
    for (double i = -1.0; i <= 1.0; i += 0.1) {
	double my_fxn = arcCos(i), lib_fxn = acos(i);	
        printf(FORMAT, i, my_fxn, lib_fxn, (my_fxn - lib_fxn));
    }

    // Tan comparison:
    printf("\n");
    printf("  x            arcTan           Library       Difference\n");
    printf(LINES);
    for (double i = 1.0; i <= 10.0; i += 0.1) {
	double my_fxn = arcTan(i), lib_fxn = atan(i);
        printf(FORMAT, i, my_fxn, lib_fxn, (my_fxn - lib_fxn));
    }

    // Log comparison:
    printf("\n");
    printf("  x            Log              Library       Difference\n");
    printf(LINES);
    for (double i = 1.0; i <= 10.0; i += 0.1) {
	double my_fxn = Log(i), lib_fxn = log(i);
	
        printf(FORMAT, i, my_fxn, lib_fxn, (my_fxn - lib_fxn));
    }
    
    return 0;
}
