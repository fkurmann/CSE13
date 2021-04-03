#include "philos.h"    //Check to make sure that even though this file is in a different repo, it is found

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void) {
	//typedef enum faciem { PASS, LEFT, RIGHT, CENTER } faces;
	//faces die[] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS};
	
	uint32_t seed, players;

	//Scanner to enter random seed
	printf("Random seed: ");
	if (scanf("%u", &seed) <1) {//check constraints to this if statement
		fprintf(stderr, "Invalid random seed.\n");
		return 1;
	}
        
	//Scanner to enter number of players
	printf("Number of players: ");
	if (scanf("%u", &players) < 1 || players > 14) {
		fprintf(stderr, "Invalid number of players.n");
		return 1;
	}
	
	srandom(seed); //Random number generator starting point


	printf("End of Program");
	

	return 0;
}

