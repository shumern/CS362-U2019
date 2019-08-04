/*
 * unittest2.c
 *

 */

 /*
  * Include the following lines in your makefile:
  *
  * unittest2: unittest2.c dominion.o rngs.o
  *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
  */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "Minion"

// Using this function instead of the standard C assert since we want to collect coverage.
void assert(int test)
{
	if (test > 0)
		printf("PASSED.\n");
	else
		printf("FAILED.\n");
}

int main() {
	int i;
	int choice1 = 0, choice2 = 0, handPos = 0;
	int thisPlayer = 0, nextPlayer = 1;

	int seed = 1000;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
			baron, tribute, smithy, ambassador };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: choice1 = 1 = gain 2 coins --------------
	printf("TEST 1: choice1 = 1 = gain 2 coins\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	choice2 = 0;

	if (minionAction(thisPlayer, choice1, choice2, &testG, handPos) < 0) {
		printf("Function failed.\n");
	}
	else {
		printf("number of actions = %d, expected = %d\n", testG.numActions, G.numActions + 1);
		assert(testG.numActions == G.numActions + 1);

		printf("this player hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
		assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);

		printf("this player deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
		assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);

		printf("this player discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
		assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]);

		printf("coins = %d, expected = %d\n", testG.coins, G.coins + 2);
		assert(testG.coins == G.coins + 2);

		printf("next player hand count = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);
		assert(testG.handCount[nextPlayer] == G.handCount[nextPlayer]);

		printf("next player deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);
		assert(testG.deckCount[nextPlayer] == G.deckCount[nextPlayer]);

		printf("next player discard count = %d, expected = %d\n", testG.discardCount[nextPlayer], G.discardCount[nextPlayer]);
		assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer]);
	}

	// ----------- TEST 2:  choice2 = 1 = redraw hand, other player has 5 cards in hand --------------
	printf("TEST 2: choice2 = 1 = redraw hand, other player has 5 cards in hand\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 0;
	choice2 = 1;
	testG.handCount[nextPlayer] = 5;
	for (i = 0; i < testG.handCount[nextPlayer]; i++)
	{
		testG.hand[nextPlayer][i] = duchy;
	}

	if (minionAction(thisPlayer, choice1, choice2, &testG, handPos) < 0) {
		printf("Function failed.\n");
	}
	else {
		printf("number of actions = %d, expected = %d\n", testG.numActions, G.numActions + 1);
		assert(testG.numActions == G.numActions + 1);

		printf("this player hand count = %d, expected = %d\n", testG.handCount[thisPlayer], 4);
		assert(testG.handCount[thisPlayer] == 4);

		printf("this player deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 4);
		assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 4);

		printf("this player discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + G.handCount[thisPlayer]);
		assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + G.handCount[thisPlayer]);

		printf("coins = %d, expected = %d\n", testG.coins, G.coins);
		assert(testG.coins == G.coins);

		printf("next player hand count = %d, expected = %d\n", testG.handCount[nextPlayer], 4);
		assert(testG.handCount[nextPlayer] == 4);

		printf("next player deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer] - 4);
		assert(testG.deckCount[nextPlayer] == G.deckCount[nextPlayer] - 4);

		printf("next player discard count = %d, expected = %d\n", testG.discardCount[nextPlayer], G.discardCount[nextPlayer] + 5);
		assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer] + 5);
	}

	// ----------- TEST 3: choice2 = 1 = redraw hand, other player does not have 5 cards in hand --------------

	printf("TEST 3: choice2 = 1 = redraw hand, other player does not have 5 cards in hand\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 0;
	choice2 = 1;
	testG.handCount[nextPlayer] = 4;
	for (i = 0; i < testG.handCount[nextPlayer]; i++)
	{
		testG.hand[nextPlayer][i] = duchy;
	}

	if (minionAction(thisPlayer, choice1, choice2, &testG, handPos) < 0) {
		printf("Function failed.\n");
	}
	else {
		printf("number of actions = %d, expected = %d\n", testG.numActions, G.numActions + 1);
		assert(testG.numActions == G.numActions + 1);

		printf("this player hand count = %d, expected = %d\n", testG.handCount[thisPlayer], 4);
		assert(testG.handCount[thisPlayer] == 4);

		printf("this player deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 4);
		assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 4);

		printf("this player discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + G.handCount[thisPlayer]);
		assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + G.handCount[thisPlayer]);

		printf("coins = %d, expected = %d\n", testG.coins, G.coins);
		assert(testG.coins == G.coins);

		printf("next player hand count = %d, expected = %d\n", testG.handCount[nextPlayer], G.handCount[nextPlayer]);
		assert(testG.handCount[nextPlayer] == G.handCount[nextPlayer]);

		printf("next player deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer]);
		assert(testG.deckCount[nextPlayer] == G.deckCount[nextPlayer]);

		printf("next player discard count = %d, expected = %d\n", testG.discardCount[nextPlayer], G.discardCount[nextPlayer]);
		assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer]);
	}

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
