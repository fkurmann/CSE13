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

int allOutput(void) { 

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

int sinOutput(void) { 
    // Sin comparison:
    printf("  x            arcSin           Library        Difference\n");
    printf(LINES);
    for (double i = -1.0; i <= 1.0; i += 0.1) {
	double my_fxn = arcSin(i), lib_fxn = asin(i);	
        printf(FORMAT, i, my_fxn, lib_fxn, (my_fxn - lib_fxn));
    }
    return 0;
}

int cosOutput(void) { 
    // Cos comparison:
    printf("\n");
    printf("  x            arcCos           Library       Difference\n");
    printf(LINES);
    for (double i = -1.0; i <= 1.0; i += 0.1) {
	double my_fxn = arcCos(i), lib_fxn = acos(i);	
        printf(FORMAT, i, my_fxn, lib_fxn, (my_fxn - lib_fxn));
    }
    return 0;
}

int tanOutput(void) { 
    // Tan comparison:
    printf("\n");
    printf("  x            arcTan           Library       Difference\n");
    printf(LINES);
    for (double i = 1.0; i <= 10.0; i += 0.1) {
	double my_fxn = arcTan(i), lib_fxn = atan(i);
        printf(FORMAT, i, my_fxn, lib_fxn, (my_fxn - lib_fxn));
    }    
    return 0;
}

int logOutput(void) { 
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

int main(int argc, char **argv) {
    int opt = 0, a_added = 0, s_added = 0, c_added = 0, t_added = 0, l_added = 0;
    
    if (argc == 1) {
        printf("Program usage: \n"
	       "  -a            runs all tests (acrsin, arccos, arctan, log)\n"
	       "  -s            runs arcsin tests\n"
	       "  -c            runs arccos tests\n"
	       "  -t            runs arctan tests\n"
	       "  -l            runs log tests\n");
    }
    	
    while ((opt = getopt(argc, argv, OPTIONS)) != -1)  {
        switch (opt) {
	    case'a': 
    	        a_added = 1;
                break;
            case's':
    	        s_added = 1;
                break;
            case'c': 
    	        c_added = 1;
                break;
            case't':
    	        t_added = 1;
                break;
	    case'l':
    	        l_added = 1;
	        break;
	    default:
	        break;
        }
    }

    if (a_added == 1) {
           allOutput();
    }

    else { 
        if (s_added == 1) {
            sinOutput();
        }
        if (c_added == 1) {
            cosOutput();
        }
        if (t_added == 1) {
            tanOutput();
	}
	if (l_added == 1) {
	    logOutput();
	}
    }
    return 0;
}




