#include "philos.h"    //Check to make sure that even though this file is in a different repo, it is found

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void) {
	//typedef enum faciem { PASS, LEFT, RIGHT, CENTER } faces;
	//faces die[] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS};
	
	uint32_t seed, num_players, center_value = 0;

	//Scanner to enter random seed
	printf("Random seed: ");
	if (scanf("%u", &seed) < 1) {//check constraints to this if statement
		fprintf(stderr, "Invalid random seed.\n");
		return 1;
	}
        
	//Scanner to enter number of players
	printf("Number of players: ");
	if (scanf("%u", &num_players) < 1 || num_players > 14) {
		fprintf(stderr, "Invalid number of players\n");
		return 1;
	}
	
	srandom(seed);
	//int roll = random();
	printf("%u\n", num_players);
	
	//create an array corresponding to length of num_players, give them all 3$
	int32_t current_player = 0;

	while (num_players > 1) {
		int num_rolls = 0;

		if () {
			run_rolls > 0;
		
			if () {
				run_rolls = 1;
			}
			if () {
				run_rolls = 2;
			}
			if () {
				rum_rolls = 3;
			}
		}












	}
	printf("End of Program\n");
	

	return 0;
}

