/*
 * unittest1.c
 *

 */

 /*
  * Include the following lines in your makefile:
  *
  * unittest1: unittest1.c dominion.o rngs.o
  *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
  */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "Baron"

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
	int choice1;
	int thisPlayer = 0;

	int seed = 1000;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
			baron, tribute, smithy, ambassador };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: choice1 = 1 = discard Estate card with one in hand --------------
	printf("TEST 1: choice1 = 1 = discard Estate card with one in hand\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	testG.hand[thisPlayer][1] = estate;

	if (baronAction(thisPlayer, choice1, &testG) < 0) {
		printf("Function failed.\n");
	}
	else {
		printf("number of buys = %d, expected = %d\n", testG.numBuys, G.numBuys + 1);
		assert(testG.numBuys == G.numBuys + 1);

		printf("estate supply count = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
		assert(testG.supplyCount[estate] == G.supplyCount[estate]);

		printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - 1);
		assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - 1);

		printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + 1);
		assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + 1);

		printf("coins = %d, expected = %d\n", testG.coins, G.coins + 4);
		assert(testG.coins == G.coins + 4);
	}

	// ----------- TEST 2:  choice1 = 1 = discard Estate card with none in hand --------------
	printf("TEST 2: choice1 = 1 = discard Estate card with none in hand\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	for (i = 0; i < testG.handCount[thisPlayer]; i++)
	{
		testG.hand[thisPlayer][i] = duchy;
	}

	if (baronAction(thisPlayer, choice1, &testG) < 0) {
		printf("Function failed.\n");
	}
	else {
		printf("number of buys = %d, expected = %d\n", testG.numBuys, G.numBuys + 1);
		assert(testG.numBuys == G.numBuys + 1);

		printf("estate supply count = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate] - 1);
		assert(testG.supplyCount[estate] == G.supplyCount[estate] - 1);

		printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
		assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);

		printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + 1);
		assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + 1);

		printf("coins = %d, expected = %d\n", testG.coins, G.coins);
		assert(testG.coins == G.coins);
	}

	// ----------- TEST 3: choice1 = 0 = don't discard Estate so gain one in discard --------------

	printf("TEST 3: choice1 = 0 = don't discard Estate so gain one in discard\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 0;

	if (baronAction(thisPlayer, choice1, &testG) < 0) {
		printf("Function failed.\n");
	}
	else {
		printf("number of buys = %d, expected = %d\n", testG.numBuys, G.numBuys + 1);
		assert(testG.numBuys == G.numBuys + 1);

		printf("estate supply count = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate] - 1);
		assert(testG.supplyCount[estate] == G.supplyCount[estate] - 1);

		printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
		assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);

		printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + 1);
		assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + 1);

		printf("coins = %d, expected = %d\n", testG.coins, G.coins);
		assert(testG.coins == G.coins);
	}

	// ----------- TEST 4:  choice1 = 1 = discard Estate card using first card in hand --------------
	printf("TEST 4: choice1 = 1 - discard Estate card using first card in hand\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	testG.hand[thisPlayer][0] = estate;
	for (i = 1; i < testG.handCount[thisPlayer]; i++)
	{
		testG.hand[thisPlayer][i] = duchy;
	}

	if (baronAction(thisPlayer, choice1, &testG) < 0) {
		printf("Function failed.\n");
	}
	else {
		printf("number of buys = %d, expected = %d\n", testG.numBuys, G.numBuys + 1);
		assert(testG.numBuys == G.numBuys + 1);

		printf("estate supply count = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
		assert(testG.supplyCount[estate] == G.supplyCount[estate]);

		printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - 1);
		assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - 1);

		printf("discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + 1);
		assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + 1);

		printf("coins = %d, expected = %d\n", testG.coins, G.coins + 4);
		assert(testG.coins == G.coins + 4);
	}

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
