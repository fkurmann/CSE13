#include "philos.h"  

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//
// Helper functions for left and right players
//
// @param: current_player, number of the current (rolling player)
//         num_players, the original total number of players, equal to length of player_balance
// @return: player number (numerical id for player_balance and philosophers) of left or right player
//
static inline uint32_t left(uint32_t current_player, uint32_t num_players) {
    return ((current_player + num_players -1) % num_players);
}
static inline uint32_t right(uint32_t current_player, uint32_t num_players) {
    return ((current_player + 1) % num_players);
}

int main(void) {
    int32_t iseed = 0, inum_players = 0;	
    uint32_t seed, num_rolls, center_value = 0, num_players, original_num_players, current_player = 0;
    uint32_t winner = 0, player_left, player_right, roll;
	
    // Scanner to enter random seed
    printf("Random seed: ");
    if (scanf("%d", &iseed) == 1) {
	    if (iseed < 0) {   
                fprintf(stderr, "Invalid random seed.\n");
                return 1;
	   } 
    } else {
        fprintf(stderr, "Invalid num inputs.\n");
	return 1;
    }
    seed = iseed;
    srandom(seed);

    // Scanner to enter number of players
    printf("How many players? ");
    if (scanf("%d", &inum_players) == 1) {
	   if (inum_players < 1 || inum_players > 14) {
               fprintf(stderr, "Invalid number of players\n");
               return 1;
	   }
    } else {
        fprintf(stderr, "Invalid num inputs.\n");
        return 1;
    }
    num_players = inum_players;
    // Declare and initialize player balance array to equal the original number of players	
    int player_balance [num_players];
    for (uint32_t i = 0; i < num_players; i++) {
        player_balance[i] = 3;
    }
    
    // Variable original_num_players needed as num_players will be modified
    original_num_players = num_players;

    while (num_players > 1) {
        num_rolls = 0;
	player_right = right(current_player, original_num_players);
	player_left = left(current_player, original_num_players);
        
	if (player_balance[current_player] > 0) {
	    if (player_balance[current_player] == 1) {
	        num_rolls = 1;
	    } else if(player_balance[current_player] == 2) {
	        num_rolls = 2;
	    } else {
		num_rolls = 3;
	    }
	    printf("%s rolls... ", philosophers[current_player]);
	}

        //Roll the dice and conduct the resulting transfers depending on how many rolls a player gets
	for (uint32_t i = 0; i < num_rolls; i++) {	
	    // Check that current player balance does not fall below zero during turn
	    if (player_balance[current_player] == 0) {
	        num_players--;
		break;
	    }
	    roll = random() % 6;
	    if (roll == 0) {
	        player_balance[current_player]--;
		if (player_balance[player_left] == 0) { // Player resurrection means add to num_players
		        num_players++;
		}
		player_balance[player_left]++;
		printf("gives $1 to %s ", philosophers[player_left]);
	    } else if (roll == 1) {
                player_balance[current_player]--;
		if (player_balance[player_right] == 0) { // Player resurrection means add to num_players
		    num_players++;
		}
		player_balance[player_right]++;
		printf("gives $1 to %s ", philosophers[player_right]);
	    } else if (roll == 2) {
	        player_balance[current_player]--;
		center_value++;
		printf("puts $1 in the pot ");
	    } else {
		printf("gets a pass ");
	    }
	}
	// Check that current player didn't hit zero during their last roll
	if (num_rolls != 0) {
	    printf("\n");
	    if (player_balance[current_player] == 0) {
	        num_players--;
	    }
	}

	current_player = player_right; // Move to next player
    }
	
    // 
    // Once while loop has finished (one player remains) find the player by scanning player_balance
    //
    uint32_t index = 0;
    while (1) {
        if (player_balance[index] != 0) {
	    winner = index;
	    break;
	}
	index++;
    }

    printf("%s wins the $%u pot with $%u left in the bank!\n", philosophers[winner], center_value, player_balance[winner]);
    return 0;
}


