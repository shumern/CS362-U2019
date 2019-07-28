/*
 * randomtestcard2.c
 *

 */

 /*
  * Include the following lines in your makefile:
  *
  * randomtestcard2: randomtestcard2.c dominion.o rngs.o
  *      gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
  */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TESTCARD "Minion"

  // Random Testing Oracle Variables:
int passed[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int failed[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

// Using this function instead of the standard C assert since we want to collect coverage.
void assert(int test, int index)
{
	if (test > 0)
		passed[index]++;
	else
		failed[index]++;
}

int checkMinionSetPlayerCards(int p, struct gameState* pre) {
// Have at least 4 cards in the deck:
	if (pre->deckCount[p] > 3) {
		pre->deckCount[p] -= 4;
		pre->discardCount[p] += pre->handCount[p];
		pre->handCount[p] = 4;
	}
	else {
	// Have less than 4 cards in the deck, will need to shuffle:
		pre->deckCount[p] += pre->discardCount[p] + pre->handCount[p];
		pre->discardCount[p] = 0;
		// Have at least 4 cards in the deck after shuffling:
		if (pre->deckCount[p] > 3) {
			pre->deckCount[p] -= 4;
			pre->handCount[p] = 4;
		}
		else {
		// Have less than 4 cards in the deck after shuffling:
			pre->handCount[p] = pre->deckCount[p];
			pre->deckCount[p] = 0;
		}
	}

	return 0;
}

int checkMinion(int p, int c1, int c2, struct gameState* post, int h) {
	// Copy initial game state to pre:
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	// Call function being tested:
	int r1;
	r1 = cardEffect_Minion(p, c1, c2, post, h);

	// Test the next player, they may or may not have five cards in their hand:
	int np, r2, r3;
	if (p > pre.numPlayers - 1) {
		np = 0;
	}
	else {
		np = p + 1;
	}

	// Adjust pre for expected values:
	pre.numActions++;

	// Gain two gold:
	if (c1 > 0) {
		r2 = 0;				// Not calling checkMinionSetPlayerCards
		r3 = 0;

		pre.coins += 2;
		pre.discard[p][pre.discardCount[p]] = pre.hand[p][h];
		pre.discardCount[p]++;
		pre.handCount[p]--;
		memcpy(pre.hand[p], post->hand[p], sizeof(int) * pre.handCount[p]);
	}
	// Discard hand, draw 4 cards:
	else {
		r2 = checkMinionSetPlayerCards(p, &pre);
		if (pre.handCount[np] > 4) {
		// Next player had at least five cards in their hand:
			r3 = checkMinionSetPlayerCards(np, &pre);
		}
		else {
			r3 = 0;
		}
	}

	// Random Testing Oracles:
	assert(r1 == 0, 0);
	assert(pre.numActions == post->numActions, 1);
	assert(pre.coins == post->coins, 2);
	assert(r2 == 0, 3);
	assert(pre.handCount[p] == post->handCount[p], 4);
	assert(pre.discardCount[p] == post->discardCount[p], 5);
	assert(pre.deckCount[p] == post->deckCount[p], 6);
	assert(r3 == 0, 7);
	assert(pre.handCount[np] == post->handCount[np], 8);
	assert(pre.discardCount[np] == post->discardCount[np], 9);
	assert(pre.deckCount[np] == post->deckCount[np], 10);

	return 0;
}

int main() {

	int i, j, n, r;			// loop counters and function return value
	int ps, p, c1, c2, h;	// random game state values; players, player, choice1, choice1, and handpos

	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
			baron, tribute, smithy, ambassador };

	struct gameState G;

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	printf("RANDOM TESTS.\n");

	SelectStream(2);
	PutSeed(3);
	srand(time(0));

	// Random tests:
	for (n = 0; n < 2000; n++) {
		// Random number of players - 2, 3 or 4:
		ps = rand() % 3;
		ps += 2;

		// Initialize game state to valid numbers and verify that function was successuful
		r = initializeGame(ps, k, 1, &G);
		assert(r == 0, 11);

		// Randomize specific game state variables used in cardEffect_Minion:

		// Randomize every player's deck and discard piles, between 0 and 500 cards:
		for (j = 0; j < ps; j++) {
			G.deckCount[j] = rand() % MAX_DECK;
			for (i = 0; i < G.deckCount[j]; i++) {
				G.deck[j][i] = rand() % 27;
			}

			G.discardCount[j] = rand() % MAX_DECK;
			for (i = 0; i < G.discardCount[j]; i++) {
				G.discard[j][i] = rand() % 27;
			}

			// Randomize player's hand between 0 and 50 cards:
			// (Note that needed a smaller deck than MAX_HAND to increase testing coverage.)
			G.handCount[j] = floor(Random() * 50);				// Could not get rand() to work, not sure why		
			for (i = 0; i < G.handCount[j]; i++) {
				G.hand[j][i] = rand() % 27;
			}
		}

		// Choose random player, starting at 0 and ending at number of players less one:
		p = rand() % ps;

		// Random options in cardeffect_Minion - 0 or 1:
		c1 = rand() % 2;
		c2 = rand() % 2;

		// Hand postion of card:
		h = rand() % G.handCount[p];

		checkMinion(p, c1, c2, &G, h);
	}

	// Print Oracle Results:
	printf("Cardeffect_Minion Function Completed:  PASSED = %d, FAILED = %d\n", passed[0], failed[0]);
	printf("Number of Actions:  PASSED = %d, FAILED = %d\n", passed[1], failed[1]);
	printf("Number of Coins:  PASSED = %d, FAILED = %d\n", passed[2], failed[2]);
	printf("Player CheckMinionSetPlayer Function Completed:  PASSED = %d, FAILED = %d\n", passed[3], failed[3]);
	printf("Player Hand Card Count:  PASSED = %d, FAILED = %d\n", passed[4], failed[4]);
	printf("Player Discard Card Count:  PASSED = %d, FAILED = %d\n", passed[5], failed[5]);
	printf("Player Deck Card Count:  PASSED = %d, FAILED = %d\n", passed[6], failed[6]);
	printf("Next Player CheckMinionSetPlayer Function Completed:  PASSED = %d, FAILED = %d\n", passed[7], failed[7]);
	printf("Next Player Hand Card Count:  PASSED = %d, FAILED = %d\n", passed[8], failed[8]);
	printf("Next Player Discard Card Count:  PASSED = %d, FAILED = %d\n", passed[9], failed[9]);
	printf("Next Player Deck Card Count:  PASSED = %d, FAILED = %d\n", passed[10], failed[10]);
	printf("InitializeGame Function Completed:  PASSED = %d, FAILED = %d\n", passed[11], failed[11]);
	printf("ALL TESTS COMPLETE\n\n");

	return 0;
}
