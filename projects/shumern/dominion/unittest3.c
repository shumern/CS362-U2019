/*
 * unittest3.c
 *

 */

 /*
  * Include the following lines in your makefile:
  *
  * unittest3: unittest3.c dominion.o rngs.o
  *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
  */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "Ambassador"

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
	int thisPlayer = 0, nextPlayer = 1;

	int seed = 1000;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
			baron, tribute, smithy, ambassador };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: choice1 = 1; choice2 = 0 = discard card #1 and return 0 to the supply --------------
	printf("TEST 1: choice1 = 1; choice2 = 0 = discard card #1 and return 0 to the supply\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	choice2 = 0;
	testG.hand[thisPlayer][choice1] = embargo;

	if (cardEffect_Ambassador(thisPlayer, choice1, choice2, &testG, handPos) < 0) {
		printf("Validation tests failed.\n");
	}
	else {
		printf("this player hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - 1);
		assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - 1);

		printf("this player discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + 1);
		assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + 1);

		printf("next player discard count = %d, expected = %d\n", testG.discardCount[nextPlayer], G.discardCount[nextPlayer] + 1);
		assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer] + 1);

		printf("embargo supply = %d, expected = %d\n", testG.supplyCount[embargo], G.supplyCount[embargo] - 1);
		assert(testG.supplyCount[embargo] == G.supplyCount[embargo] - 1);
	}

	// ----------- TEST 2:  choice1 = 1; choice2 = 1 = discard card #1 and return 1 more to the supply --------------
	printf("TEST 2: choice1 = 1; choice2 = 1 = discard card #1 and return 1 more to the supply\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	choice2 = 1;
	testG.hand[thisPlayer][choice1] = embargo;
	testG.hand[thisPlayer][choice1 + 1] = embargo;

	if (cardEffect_Ambassador(thisPlayer, choice1, choice2, &testG, handPos) < 0) {
		printf("Validation tests failed.\n");
	}
	else {
		printf("this player hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - 2);
		assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - 2);

		printf("this player discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + 1);
		assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + 1);

		printf("next player discard count = %d, expected = %d\n", testG.discardCount[nextPlayer], G.discardCount[nextPlayer] + 1);
		assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer] + 1);

		printf("embargo supply = %d, expected = %d\n", testG.supplyCount[embargo], G.supplyCount[embargo]);
		assert(testG.supplyCount[embargo] == G.supplyCount[embargo]);
	}

	// ----------- TEST 3: choice1 = 1; choice2 = 2 = discard card #1 and return 2 more to the supply --------------

	printf("TEST 3: choice1 = 1; choice2 = 2 = discard card #1 and return 2 more to the supply\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	choice2 = 2;
	testG.hand[thisPlayer][choice1] = embargo;
	testG.hand[thisPlayer][choice1 + 1] = embargo;
	testG.hand[thisPlayer][choice1 + 2] = embargo;

	if (cardEffect_Ambassador(thisPlayer, choice1, choice2, &testG, handPos) < 0) {
		printf("Validation tests failed.\n");
	}
	else {
		printf("this player hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] - 3);
		assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - 3);

		printf("this player discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + 1);
		assert(testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + 1);

		printf("next player discard count = %d, expected = %d\n", testG.discardCount[nextPlayer], G.discardCount[nextPlayer] + 1);
		assert(testG.discardCount[nextPlayer] == G.discardCount[nextPlayer] + 1);

		printf("embargo supply = %d, expected = %d\n", testG.supplyCount[embargo], G.supplyCount[embargo]+1);
		assert(testG.supplyCount[embargo] == G.supplyCount[embargo] + 1);
	}

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
