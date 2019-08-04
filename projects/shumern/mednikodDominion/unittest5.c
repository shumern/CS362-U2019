/*
 * unittest5.c
 *

 */

 /*
  * Include the following lines in your makefile:
  *
  * unittest5: unittest5.c dominion.o rngs.o
  *      gcc -o unittest5 -g  unittest5.c dominion.o rngs.o $(CFLAGS)
  */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "Mine"

// Using this function instead of the standard C assert since we want to collect coverage.
void assert(int test)
{
	if (test > 0)
		printf("PASSED.\n");
	else
		printf("FAILED.\n");
}

int main() {
	int choice1 = 0, choice2 = 0, handPos = 0;
	int thisPlayer = 0;

	int seed = 1000;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
			baron, tribute, smithy, ambassador };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: choice1 = 1; choice2 = silver = trash copper and add silver from the supply --------------
	printf("TEST 1: choice1 = copper; choice2 = silver = trash copper and add silver from the supply\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = copper;
	choice2 = silver;
//	testG.hand[thisPlayer][choice1] = copper;

	if (mineAction(thisPlayer, choice1, choice2, &testG, handPos) < 0) {
		printf("Validation tests failed.\n");
	}
	else {
		printf("this player hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - 1);
		assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - 1);

		printf("this player discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + 1);
		assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + 1);

		printf("played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount);
		assert(testG.playedCardCount == G.playedCardCount);

		printf("silver supply = %d, expected = %d\n", testG.supplyCount[silver], G.supplyCount[silver] - 1);
		assert(testG.supplyCount[silver] == G.supplyCount[silver] - 1);
	}

	// ----------- TEST 2:  choice1 = 1; choice2 = gold = trash silver and add gold from the supply --------------
	printf("TEST 2: choice1 = silver; choice2 = gold = trash silver and add gold from the supply\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = silver;
	choice2 = gold;
//	testG.hand[thisPlayer][choice1] = silver;

	if (mineAction(thisPlayer, choice1, choice2, &testG, handPos) < 0) {
		printf("Validation tests failed.\n");
	}
	else {
		printf("this player hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - 1);
		assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - 1);

		printf("this player discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + 1);
		assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + 1);

		printf("played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount);
		assert(testG.playedCardCount == G.playedCardCount);

		printf("gold supply = %d, expected = %d\n", testG.supplyCount[gold], G.supplyCount[gold] - 1);
		assert(testG.supplyCount[gold] == G.supplyCount[gold] - 1);
	}

	// ----------- TEST 3: choice1 = 1; choice2 = gold = trash copper and try to add gold from the supply --------------
	printf("TEST 3: choice1 = copper; choice2 = gold = trash copper and try to add gold from the supply\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = copper;
	choice2 = gold;
//	testG.hand[thisPlayer][choice1] = copper;

	if (mineAction(thisPlayer, choice1, choice2, &testG, handPos) < 0) {
		printf("Validation tests failed.\n");
	}
	else {
		printf("this player hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer]);
		assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer]);

		printf("this player discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer]);
		assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer]);

		printf("played card count = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount);
		assert(testG.playedCardCount == G.playedCardCount);

		printf("gold supply = %d, expected = %d\n", testG.supplyCount[gold], G.supplyCount[gold]);
		assert(testG.supplyCount[gold] == G.supplyCount[gold]);
	}

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
