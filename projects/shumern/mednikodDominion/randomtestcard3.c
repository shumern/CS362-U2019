/*
 * randomtestcard3.c
 *

 */

 /*
  * Include the following lines in your makefile:
  *
  * randomtestcard3: randomtestcard3.c dominion.o rngs.o
  *      gcc -o randomtestcard3 -g  randomtestcard3.c dominion.o rngs.o $(CFLAGS)
  */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TESTCARD "Tribute"

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

int checkTributeRevealCard(int card, int p, struct gameState* pre) {

	if ( ( (card > curse) && (card < copper) ) || (card == gardens) || (card == great_hall) ) {
	// Victory card revealed
		if (pre->deckCount[p] > 0) {
			pre->deckCount[p]--;
			pre->handCount[p]++;
		}
		else if (pre->discardCount[p] > 0) {
			pre->handCount[p]++;
			pre->deckCount[p] += pre->discardCount[p];
			pre->deckCount[p]--;
			pre->discardCount[p] = 0;
		}
	}
	else if ( (card > province) && (card < adventurer) ) {
	// Treasury card revealed
		pre->coins += 2;
	}
	else {
	// Action card revealed
		pre->numActions += 2;
	}

	return 0;
}

int checkTribute(int p, int lp, struct gameState* post) {
	// Copy initial game state to pre:
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	// Call function being tested:
	int r1;
	int revealed[3] = { 0, 0, 0 };
	r1 = tributeAction(p, lp, revealed, post);

	// Adjust pre for expected values:
	int r2 = 0;
	int r3 = 0;
	int b1 = 0;
	int b2 = 0;

	// Player to the left has at least one card in their deck:
	if (pre.deckCount[lp] > 0) {
		r2 = checkTributeRevealCard(pre.deck[lp][pre.deckCount[lp] - 1], p, &pre);
		pre.deckCount[lp]--;
		pre.discardCount[lp]++;
		b1++;
	}
	// Player to the left still has at least one card in their deck:
	if ( (pre.deckCount[lp] > 0) && (b1 > 0) ) {
		r3 = checkTributeRevealCard(pre.deck[lp][pre.deckCount[lp] - 1], p, &pre);
		pre.deckCount[lp]--;
		pre.discardCount[lp]++;
		b2++;
	}

	// Player to the left had zero or one card in their deck and only has one or two discard cards:
	if ( (b1 == 0) && (pre.discardCount[lp] < 3) && (pre.discardCount[lp] > 0) ) {
		r2 = checkTributeRevealCard(pre.discard[lp][pre.discardCount[lp] - 1], p, &pre);
		b1++;

		if ( (pre.discardCount[lp] > 1) && (b1 > 0) ) {
			r3 = checkTributeRevealCard(pre.discard[lp][pre.discardCount[lp] - 2], p, &pre);
			b2++;
		}
	}
	else if ( (b2 == 0) && (pre.discardCount[lp] == 1) ) {
		r3 = checkTributeRevealCard(pre.discard[lp][pre.discardCount[lp] - 1], p, &pre);
	}

	// Can't test situation where player has less than two cards in their deck and had to shuffle.

	// Random Testing Oracles:
	assert(r1 == 0, 0);
	assert(pre.numActions == post->numActions, 1);
	assert(pre.coins == post->coins, 2);
	assert(pre.handCount[p] == post->handCount[p], 3);
	assert(pre.discardCount[p] == post->discardCount[p], 4);
	assert(pre.deckCount[p] == post->deckCount[p], 5);
	assert(pre.handCount[lp] == post->handCount[lp], 6);
	assert(pre.discardCount[lp] == post->discardCount[lp], 7);
	assert(pre.deckCount[lp] == post->deckCount[lp], 8);
	assert(r2 == 0, 9);
	assert(r3 == 0, 10);

	return 0;
}


int main() {

	int i, j, n, r;			// loop counters and function return value
	int ps, p, lp;			// random game state values; players, player, and left player

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

		// Randomize specific game state variables used in cardEffect_Tribute:

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

		// Left player is preceeding player to randomly generated p:
		if (p > 0) {
			lp = p - 1;
		}
		else {
			lp = ps - 1;
		}

		checkTribute(p, lp, &G);
	}

	// Print Oracle Results:
	printf("Cardeffect_Tribute Function Completed:  PASSED = %d, FAILED = %d\n", passed[0], failed[0]);
	printf("Number of Actions:  PASSED = %d, FAILED = %d\n", passed[1], failed[1]);
	printf("Number of Coins:  PASSED = %d, FAILED = %d\n", passed[2], failed[2]);
	printf("Player Hand Card Count:  PASSED = %d, FAILED = %d\n", passed[3], failed[3]);
	printf("Player Discard Card Count:  PASSED = %d, FAILED = %d\n", passed[4], failed[4]);
	printf("Player Deck Card Count:  PASSED = %d, FAILED = %d\n", passed[5], failed[5]);
	printf("Left Player Hand Card Count:  PASSED = %d, FAILED = %d\n", passed[6], failed[6]);
	printf("Left Player Discard Card Count:  PASSED = %d, FAILED = %d\n", passed[7], failed[7]);
	printf("Left Player Deck Card Count:  PASSED = %d, FAILED = %d\n", passed[8], failed[8]);
	printf("First CheckTributeRevealCard Function Completed:  PASSED = %d, FAILED = %d\n", passed[9], failed[9]);
	printf("Second  CheckTributeRevealCard Function Completed:  PASSED = %d, FAILED = %d\n", passed[10], failed[10]);
	printf("InitializeGame Function Completed:  PASSED = %d, FAILED = %d\n", passed[11], failed[11]);
	printf("ALL TESTS COMPLETE\n\n");

	return 0;
}