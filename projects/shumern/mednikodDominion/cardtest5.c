/*
 * cardtest5.c
 *

 */

 /*
  * Include the following lines in your makefile:
  *
  * cardtest5: cardtest5.c dominion.o rngs.o
  *      gcc -o cardtest5 -g  cardtest5.c dominion.o rngs.o $(CFLAGS)
  */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "drawCard"

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

	// ----------- TEST 1: draw a card from the deck - top card is remodel --------------
	printf("TEST 1: draw a card from the deck - top card is remodel\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.deckCount[thisPlayer] = 2;
	testG.deck[thisPlayer][0] = council_room;
	testG.deck[thisPlayer][1] = remodel;

	if (drawCard(thisPlayer, &testG) < 0) {
		printf("Function failed.\n");
	}
	else {
		printf("this player's hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 1);
		assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 1);

		printf("this player's deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], 1);
		assert(testG.deckCount[thisPlayer] == 1);

		printf("this player's card in hand = %d, expected = %d\n", testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1], remodel);
		assert(testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] == remodel);

		printf("this player's card in hand = %d, prior = %d\n", testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1], G.hand[thisPlayer][G.handCount[thisPlayer] - 1]);
		assert(testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] != G.hand[thisPlayer][G.handCount[thisPlayer] - 1]);
	}

	// ----------- TEST 2: draw a card where there is no cards in the deck --------------
	printf("TEST 2: draw a card where there is no cards in the deck\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.deckCount[thisPlayer] = 0;
	testG.discardCount[thisPlayer] = 2;
	testG.discard[thisPlayer][0] = council_room;
	testG.discard[thisPlayer][1] = remodel;

	if (drawCard(thisPlayer, &testG) < 0) {
		printf("Function failed.\n");
	}
	else {
		printf("this player's hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + 1);
		assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + 1);

		printf("this player's deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], 1);
		assert(testG.deckCount[thisPlayer] == 1);

		printf("this player's discard count = %d, expected = %d\n", testG.discardCount[thisPlayer], 0);
		assert(testG.discardCount[thisPlayer] == 0);

		printf("this player's card in hand = %d, prior = %d\n", testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1], G.hand[thisPlayer][G.handCount[thisPlayer] - 1]);
		assert(testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] != G.hand[thisPlayer][G.handCount[thisPlayer] - 1]);
	}

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
