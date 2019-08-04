/*
 * cardtest3.c
 *

 */

 /*
  * Include the following lines in your makefile:
  *
  * cardtest3: cardtest3.c dominion.o rngs.o
  *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
  */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "endTurn"

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

	int seed = 1000;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
			baron, tribute, smithy, ambassador };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: endTurn and look at game state --------------
	printf("TEST 1: endTurn - game state set correctly for 2 players\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));

	if (endTurn(&testG) < 0) {
		printf("Function failed.\n");
	}
	else {
		printf("this player's handCount = %d, expected = %d\n", testG.handCount[thisPlayer], 0);
		assert(testG.handCount[thisPlayer] == 0);

		printf("this player's discardCount = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + G.handCount[thisPlayer]);
		assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + G.handCount[thisPlayer]);

		printf("next player's handCount = %d, expected = %d\n", testG.handCount[nextPlayer], 5);
		assert(testG.handCount[nextPlayer] == 5);

		printf("next player's discardCount = %d, expected = %d\n", testG.discardCount[nextPlayer], 0);
		assert(testG.discardCount[nextPlayer] == 0);

		printf("next player's deckCount = %d, expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer] - 5);
		assert(testG.deckCount[nextPlayer] == G.deckCount[nextPlayer] - 5);

		printf("outpost played = %d, expected = %d\n", testG.outpostPlayed, 0);
		assert(testG.outpostPlayed == 0);

		printf("whose Turn = %d, expected = %d\n", testG.whoseTurn, nextPlayer);
		assert(testG.whoseTurn == nextPlayer);

		printf("phase = %d, expected = %d\n", testG.phase, 0);
		assert(testG.phase == 0);

		printf("number of actions = %d, expected = %d\n", testG.numActions, 1);
		assert(testG.numActions == 1);

		printf("number of buys = %d, expected = %d\n", testG.numBuys, 1);
		assert(testG.numBuys == 1);

		printf("coins = %d, expected = %d\n", testG.coins, 0);
		assert(testG.coins == 0);

		printf("number of played cards = %d, expected = %d\n", testG.playedCardCount, 0);
		assert(testG.playedCardCount == 0);
	}

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
