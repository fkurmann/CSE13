#include "philos.h"    //Check to make sure that even though this file is in a different repo, it is found

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Helper functions for left and right players
static inline uint32_t left(uint32_t current_player, uint32_t num_players) {
	return ((current_player + num_players -1) % num_players);
}
static inline uint32_t right(uint32_t current_player, uint32_t num_players) {
	return ((current_player + 1) % num_players);
}

int main(void) {
	//typedef enum faciem { PASS, LEFT, RIGHT, CENTER } faces;
	//faces die[] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS};
	
	uint32_t seed, num_rolls, center_value = 0, num_players, current_player = 0, player_left, player_right, roll;

	//Scanner to enter random seed
	printf("Random seed: ");
	if (scanf("%u", &seed) < 1) {//check constraints to this if statement*********************************************************
		fprintf(stderr, "Invalid random seed.\n");
		return 1;
	} 
	srandom(seed);

	//Scanner to enter number of players
	printf("Number of players: ");
	if (scanf("%u", &num_players) < 1 || num_players > 14) {
		fprintf(stderr, "Invalid number of players\n");
		return 1;
	}
		
	
	//****************************NO CHANGES ABOVE THIS LINE********************

	//declare and initialize player balance array
	int player_balance [num_players];
	for (uint8_t i = 0; i < num_players; i++) {
		player_balance[i] = 3;
	}

	while (num_players > 1) {      //Will eventually become while(num_players > 1)
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

		//Roll the dice and conduct the resulting transfers depending on how many rolls a player gets
		for (uint32_t i = 0; i < num_rolls; i++) {
			
			//check that current player balance does not fall below zero during turn
			if (player_balance[current_player] == 0) {
				num_players--;
				break;
			}

			roll = random() % 6;

			if (roll == 0) {
				player_balance[current_player]--;
				player_left = left(current_player, num_players);
				if (player_balance[player_left] == 0) { // Player resurrection means add to num_players
					num_players++;
				}
				player_balance[player_left]++;
			}
			if (roll == 1) {
				player_balance[current_player]--;
				player_right = right(current_player, num_players);
				if (player_balance[player_right] == 0) { // Player resurrection means add to num_players
					num_players++;
				}
				player_balance[player_right]++;
			}
			if (roll == 2) {
				player_balance[current_player]--;
				center_value++;
			}

		}
		// check that current player balance didn't hit zero during turn
		if (player_balance[current_player] == 0) {
				num_players--;
		}


		current_player = player_right;
		printf("Number of players remaining: %u\n", num_players);
	}
	//printf("Number of last player: %u\n", current_player);
	//printf("Rolls for last player: %u\n", num_rolls);
	printf("End of Program\n");
	return 0;
}


