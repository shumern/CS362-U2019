/*
 * unittest4.c
 *

 */

 /*
  * Include the following lines in your makefile:
  *
  * unittest4: unittest4.c dominion.o rngs.o
  *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
  */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "Tribute"

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

	// ----------- TEST 1: card1 = baron; card2 = copper = gain 2 actions and 2 coins --------------
	printf("TEST 1: card1 = baron; card2 = copper = gain 2 actions and 2 coins\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 1] = baron;
	testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 2] = copper;

	if (cardEffect_Tribute(thisPlayer, nextPlayer, &testG) < 0) {
		printf("Function failed.\n");
	}
	else {
		printf("this player hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
		assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);

		printf("this player deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
		assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);

		printf("next player deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer] - 2);
		assert(testG.deckCount[nextPlayer] == G.deckCount[nextPlayer] - 2);

		printf("next player discard count = %d, expected = %d\n", testG.discardCount[nextPlayer], G.discardCount[nextPlayer] + 2);
		assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer] + 2);

		printf("number of actions = %d, expected = %d\n", testG.numActions, G.numActions + 2);
		assert(testG.numActions == G.numActions + 2);

		printf("coins = %d, expected = %d\n", testG.coins, G.coins + 2);
		assert(testG.coins == G.coins + 2);
	}

	// ----------- TEST 2:  card1 = silver; card2 = estate = gain 2 coins and draw 2 cards from deck --------------
	printf("TEST 2: card1 = silver; card2 = estate = gain 2 coins and draw 2 cards from deck\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 1] = silver;
	testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 2] = estate;

	if (cardEffect_Tribute(thisPlayer, nextPlayer, &testG) < 0) {
		printf("Function failed.\n");
	}
	else {
		printf("this player hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 2);
		assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2);

		printf("this player deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 2);
		assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 2);

		printf("next player deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer] - 2);
		assert(testG.deckCount[nextPlayer] == G.deckCount[nextPlayer] - 2);

		printf("next player discard count = %d, expected = %d\n", testG.discardCount[nextPlayer], G.discardCount[nextPlayer] + 2);
		assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer] + 2);

		printf("number of actions = %d, expected = %d\n", testG.numActions, G.numActions);
		assert(testG.numActions == G.numActions);

		printf("coins = %d, expected = %d\n", testG.coins, G.coins + 2);
		assert(testG.coins == G.coins + 2);
	}

	// ----------- TEST 3: nextPlayer only has 2 cards; card1 = duchy; card2 = mine = draw 2 cards from deck and gain 2 actions --------------
	printf("TEST 3: nextPlayer only has 2 cards; card1 = duchy; card2 = mine = draw 2 cards from deck and gain 2 actions\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.deckCount[nextPlayer] = 2;
	testG.discardCount[nextPlayer] = 0;
	testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 1] = duchy;
	testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 2] = mine;

	if (cardEffect_Tribute(thisPlayer, nextPlayer, &testG) < 0) {
		printf("Function failed.\n");
	}
	else {
		printf("this player hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 2);
		assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 2);

		printf("this player deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - 2);
		assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - 2);

		printf("next player deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer] - 2);
		assert(testG.deckCount[nextPlayer] == G.deckCount[nextPlayer] - 2);

		printf("next player discard count = %d, expected = %d\n", testG.discardCount[nextPlayer], G.discardCount[nextPlayer] + 2);
		assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer] + 2);

		printf("number of actions = %d, expected = %d\n", testG.numActions, G.numActions + 2);
		assert(testG.numActions == G.numActions + 2);

		printf("coins = %d, expected = %d\n", testG.coins, G.coins);
		assert(testG.coins == G.coins);
	}

	// ----------- TEST 4: card1 = copper; card2 = copper = gain 4 coins --------------
	printf("TEST 4: card1 = copper; card2 = copper = gain 4 coins\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 1] = copper;
	testG.deck[nextPlayer][testG.deckCount[nextPlayer] - 2] = copper;

	if (cardEffect_Tribute(thisPlayer, nextPlayer, &testG) < 0) {
		printf("Function failed.\n");
	}
	else {
		printf("this player hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
		assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);

		printf("this player deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
		assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);

		printf("next player deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], G.deckCount[nextPlayer] - 2);
		assert(testG.deckCount[nextPlayer] == G.deckCount[nextPlayer] - 2);

		printf("next player discard count = %d, expected = %d\n", testG.discardCount[nextPlayer], G.discardCount[nextPlayer] + 2);
		assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer] + 2);

		printf("number of actions = %d, expected = %d\n", testG.numActions, G.numActions);
		assert(testG.numActions == G.numActions);

		printf("coins = %d, expected = %d\n", testG.coins, G.coins + 4);
		assert(testG.coins == G.coins + 4);
	}

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
