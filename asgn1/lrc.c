#include "philos.h"    //Check to make sure that even though this file is in a different repo, it is found

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int main(void) {
	//typedef enum faciem { PASS, LEFT, RIGHT, CENTER } faces;
	//faces die[] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS};
	
	uint32_t seed, num_rolls, center_value = 0;
	uint8_t num_players, current_player = 0;

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
	printf("%u\n", num_players);
	
	
	//****************************NO CHANGES ABOVE THIS LINE********************

	//declare and initialize player balance array
	int player_balance [num_players];
	for (uint8_t i = 0; i < num_players; i++) {
		player_balance[i] = 3;
	}

	while (current_player < num_players) {      //Will eventually become while(num_players > 1)
		num_rolls = 0;

		if (player_balance[current_player] > 0) {
		
			if (player_balance[current_player] == 1) {
				num_rolls = 1;
			}
			if (player_balance[current_player] == 2) {
				num_rolls = 2;
			}
			else {
				num_rolls = 3;
			}
		}
	
		uint32_t roll;

		//Roll the dice and conduct the resulting transfers depending on how many rolls a player gets
		for (uint32_t i = 0; i < num_rolls; i++) {
			roll = random() % 6
			printf("%u\n", roll);

			if roll == 0 {
				//give to left
			}
			if roll == 1 {
				//give to right
			}
			if roll == 2 {
				//give to center
			center_value++;
			}
		}
		current_player++;
	}
	printf("Number of last player: %u\n", current_player);
	printf("Rolls for last player: %u\n", num_rolls);
	printf("End of Program\n");
	center_value++; //to shut up the pedantic error for now	

	return 0;
}



static inline uint8_t left(uint8_t current_player, uint8_t, num_players) {
	return ((current_player + num_players -1) % num_players);
}
static inline uint8_t right(uint8_t current_player, uint8_t, num_players) {
	return ((current_player + 1) % num_players);
}
