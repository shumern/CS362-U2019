/*
 * cardtest2.c
 *

 */

 /*
  * Include the following lines in your makefile:
  *
  * cardtest2: cardtest2.c dominion.o rngs.o
  *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
  */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "shuffle"

// Using this function instead of the standard C assert since we want to collect coverage.
void assert(int test)
{
	if (test > 0)
		printf("PASSED.\n");
	else
		printf("FAILED.\n");
}

int main() {
	int thisPlayer = 0;

	int seed = 1000;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
			baron, tribute, smithy, ambassador };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: shuffle cards and look at differences --------------
	printf("TEST 1: shuffle - copper, estate, baron, mine, silver\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.deckCount[thisPlayer] = 5;
	testG.deck[thisPlayer][0] = copper;
	testG.deck[thisPlayer][1] = estate;
	testG.deck[thisPlayer][2] = baron;
	testG.deck[thisPlayer][3] = mine;
	testG.deck[thisPlayer][4] = silver;

	if (shuffle(thisPlayer, &testG) < 0) {
		printf("Function failed.\n");
	}
	else {
		printf("shuffled card = %d, pre-shuffle = %d\n", testG.deck[thisPlayer][0], copper);
		assert(testG.deck[thisPlayer][0] != copper);

		printf("shuffled card = %d, pre-shuffle = %d\n", testG.deck[thisPlayer][1], estate);
		assert(testG.deck[thisPlayer][1] != estate);

		printf("shuffled card = %d, pre-shuffle = %d\n", testG.deck[thisPlayer][2], baron);
		assert(testG.deck[thisPlayer][2] != baron);

		printf("shuffled card = %d, pre-shuffle = %d\n", testG.deck[thisPlayer][3], mine);
		assert(testG.deck[thisPlayer][3] != mine);

		printf("shuffled card = %d, pre-shuffle = %d\n", testG.deck[thisPlayer][4], silver);
		assert(testG.deck[thisPlayer][4] != silver);
	}

	// ----------- TEST 2: shuffle cards and look at differences --------------
	printf("TEST 2: shuffle - minion, gold, duchy\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.deckCount[thisPlayer] = 3;
	testG.deck[thisPlayer][0] = minion;
	testG.deck[thisPlayer][1] = gold;
	testG.deck[thisPlayer][2] = duchy;

	if (shuffle(thisPlayer, &testG) < 0) {
		printf("Function failed.\n");
	}
	else {
		printf("shuffled card = %d, pre-shuffle = %d\n", testG.deck[thisPlayer][0], minion);
		assert(testG.deck[thisPlayer][0] != minion);

		printf("shuffled card = %d, pre-shuffle = %d\n", testG.deck[thisPlayer][1], gold);
		assert(testG.deck[thisPlayer][1] != gold);

		printf("shuffled card = %d, pre-shuffle = %d\n", testG.deck[thisPlayer][2], duchy);
		assert(testG.deck[thisPlayer][2] != duchy);
	}

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
