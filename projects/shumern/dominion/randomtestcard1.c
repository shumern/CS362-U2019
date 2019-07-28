/*
 * randomtestcard1.c
 *

 */

 /*
  * Include the following lines in your makefile:
  *
  * randomtestcard1: randomtestcard1.c dominion.o rngs.o
  *      gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
  */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TESTCARD "Baron"

// Random Testing Oracle Variables:
int passed[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int failed[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

// Using this function instead of the standard C assert since we want to collect coverage.
void assert(int test, int index)
{
	if (test > 0)
		passed[index]++;
	else
		failed[index]++;
}


int checkBaron(int p, int c, struct gameState* post) {
// Copy initial game state to pre:
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

// Call function being tested:
	int r;
	r = cardEffect_Baron(p, c, post);

// Check to see if pre hand had any estate cards in it:
	int b = 0;
	int i = 0;
	while ( (b == 0) && (i < pre.handCount) ) {
		if (pre.hand[p][i] == estate) {
			b++;
		}
		i++;			
	}

// Adjust pre for expected values:
	pre.numBuys++;

// Discard an Estate from Hand:
	if ( (c > 0) && (b > 0) ) {
		pre.handCount[p]--;
		memcpy(pre.hand[p], post->hand[p], sizeof(int) * pre.handCount[p]);
		pre.coins += 4;
		pre.discard[p][pre.discardCount[p]] = estate;
		pre.discardCount[p]++;
	}
// Gain an Estate from Supply:
	else {
		if (pre.supplyCount[estate] > 0) {
			pre.supplyCount[estate]--;
			pre.discard[p][pre.discardCount[p]] = estate;
			pre.discardCount[p]++;
		}
	}

// Random Testing Oracles:
	assert(r == 0, 0);
	assert(pre.numBuys == post->numBuys, 1);
	assert(pre.supplyCount[estate] == post->supplyCount[estate], 2);
	assert(pre.coins == post->coins, 3);
	assert(pre.handCount[p] == post->handCount[p], 4);
	assert(pre.discardCount[p] == post->discardCount[p], 5);
	assert(pre.discard[p][pre.discardCount[p] - 1] == post->discard[p][post->discardCount[p] - 1], 6);

	return 0;
}

int main() {

	int i, n, r;			// loop counters and function return value
	int ps, p, c;			// random game state values; players, player, and choice

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
		ps +=2;

	// Initialize game state to valid numbers and verify that function was successuful
		r = initializeGame(ps, k, 1, &G);
		assert(r == 0, 7);

	// Randomize specific game state variables used in cardEffect_Baron:
	// Random number of estate cards - 0 to 9						
		G.supplyCount[estate] = rand() % 10;

	// Choose random player, starting at 0 and ending at number of players less one:
		p = rand() % ps;

	// Randomize player's deck and discard piles, between 0 and 500 cards:
		G.deckCount[p] = rand() % MAX_DECK;
		for (i = 0; i < G.deckCount[p]; i++) {
			G.deck[p][i] = rand() % 27;
		}

		G.discardCount[p] = rand() % MAX_DECK;
		for (i = 0; i < G.discardCount[p]; i++) {
			G.discard[p][i] = rand() % 27;
		}

	// Randomize player's hand, between 0 and 50 cards:
	// (Note that needed a smaller deck than MAX_HAND to increase testing coverage.)
		G.handCount[p] = floor(Random() * 50);				// Could not get rand() to work, not sure why		
		for (i = 0; i < G.handCount[p]; i++) {
			G.hand[p][i] = rand() % 27;
		}

	// Random option in cardeffect_Baron - 0 or 1:
		c = rand() % 2;
		checkBaron(p, c, &G);
	}

// Print Oracle Results:
	printf("Cardeffect_Baron Function Completed:  PASSED = %d, FAILED = %d\n", passed[0], failed[0]);
	printf("Number of Buys:  PASSED = %d, FAILED = %d\n", passed[1], failed[1]);
	printf("Estate Supply Count:  PASSED = %d, FAILED = %d\n", passed[2], failed[2]);
	printf("Number of Coins:  PASSED = %d, FAILED = %d\n", passed[3], failed[3]);
	printf("Hand Card Count:  PASSED = %d, FAILED = %d\n", passed[4], failed[4]);
	printf("Discard Card Count:  PASSED = %d, FAILED = %d\n", passed[5], failed[5]);
	printf("Last Discard Card is Estate:  PASSED = %d, FAILED = %d\n", passed[6], failed[6]);
	printf("InitializeGame Function Completed:  PASSED = %d, FAILED = %d\n", passed[7], failed[7]);
	printf("ALL TESTS COMPLETE\n\n");

	return 0;
}