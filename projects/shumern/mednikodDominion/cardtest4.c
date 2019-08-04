/*
 * cardtest4.c
 *

 */

 /*
  * Include the following lines in your makefile:
  *
  * cardtest4: cardtest4.c dominion.o rngs.o
  *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
  */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "getWinners"

// Using this function instead of the standard C assert since we want to collect coverage.
void assert(int test)
{
	if (test > 0)
		printf("PASSED.\n");
	else
		printf("FAILED.\n");
}

int main() {
	int thisPlayer = 0, nextPlayer = 1;
	int players[2] = { 0, 0 };

	int seed = 1000;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
			baron, tribute, smithy, ambassador };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: getWinners for a two player game with first player winning --------------
	printf("TEST 1: getWinners for a two player game with first player winning\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.deckCount[thisPlayer] = 5;
	testG.deck[thisPlayer][0] = province;
	testG.deck[thisPlayer][1] = gold;
	testG.deck[thisPlayer][2] = baron;
	testG.deck[thisPlayer][3] = estate;
	testG.deck[thisPlayer][4] = duchy;

	testG.deckCount[nextPlayer] = 5;
	testG.deck[nextPlayer][0] = minion;
	testG.deck[nextPlayer][1] = province;
	testG.deck[nextPlayer][2] = baron;
	testG.deck[nextPlayer][3] = copper;
	testG.deck[nextPlayer][4] = mine;

	if (getWinners(players, &testG) < 0) {
		printf("Function failed.\n");
	}
	else {
		printf("Player 1 = %d, expected = %d\n", players[0], 1);
		assert(players[0] == 1);

		printf("Player 2 = %d, expected = %d\n", players[1], 0);
		assert(players[1] == 0);
	}


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
