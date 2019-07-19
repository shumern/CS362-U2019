/*
 * cardtest1.c
 *

 */

 /*
  * Include the following lines in your makefile:
  *
  * cardtest1: cardtest1.c dominion.o rngs.o
  *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
  */


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TESTCARD "initializeGame"

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
	struct gameState G;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
			baron, tribute, smithy, ambassador };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: initializeGame and look at supply and game state --------------
	printf("TEST 1: initializeGame - look at supply and game state for 2 players\n");

	printf("curse supply count = %d, expected = %d\n", G.supplyCount[curse], 10);
	assert(G.supplyCount[curse] == 10);

	printf("estate supply count = %d, expected = %d\n", G.supplyCount[estate], 8);
	assert(G.supplyCount[estate] == 8);

	printf("duchy supply count = %d, expected = %d\n", G.supplyCount[duchy], 8);
	assert(G.supplyCount[duchy] == 8);

	printf("province supply count = %d, expected = %d\n", G.supplyCount[province], 8);
	assert(G.supplyCount[province] == 8);

	printf("copper supply count = %d, expected = %d\n", G.supplyCount[copper], 46);
	assert(G.supplyCount[copper] == 46);

	printf("silver supply count = %d, expected = %d\n", G.supplyCount[silver], 40);
	assert(G.supplyCount[silver] == 40);

	printf("gold supply count = %d, expected = %d\n", G.supplyCount[gold], 30);
	assert(G.supplyCount[gold] == 30);

	printf("adventurer supply count = %d, expected = %d\n", G.supplyCount[adventurer], 10);
	assert(G.supplyCount[adventurer] == 10);

	printf("council_room supply count = %d, expected = %d\n", G.supplyCount[council_room], -1);
	assert(G.supplyCount[council_room] == -1);

	printf("feast supply count = %d, expected = %d\n", G.supplyCount[feast], -1);
	assert(G.supplyCount[feast] == -1);

	printf("gardens supply count = %d, expected = %d\n", G.supplyCount[gardens], -1);
	assert(G.supplyCount[gardens] == -1);

	printf("mine supply count = %d, expected = %d\n", G.supplyCount[mine], 10);
	assert(G.supplyCount[mine] == 10);

	printf("remodel supply count = %d, expected = %d\n", G.supplyCount[remodel], -1);
	assert(G.supplyCount[remodel] == -1);

	printf("smithy supply count = %d, expected = %d\n", G.supplyCount[smithy], 10);
	assert(G.supplyCount[smithy] == 10);

	printf("village supply count = %d, expected = %d\n", G.supplyCount[village], 10);
	assert(G.supplyCount[village] == 10);

	printf("baron supply count = %d, expected = %d\n", G.supplyCount[baron], 10);
	assert(G.supplyCount[baron] == 10);

	printf("great_hall supply count = %d, expected = %d\n", G.supplyCount[great_hall], -1);
	assert(G.supplyCount[great_hall] == -1);

	printf("minion supply count = %d, expected = %d\n", G.supplyCount[minion], 10);
	assert(G.supplyCount[minion] == 10);

	printf("steward supply count = %d, expected = %d\n", G.supplyCount[steward], -1);
	assert(G.supplyCount[steward] == -1);

	printf("tribute supply count = %d, expected = %d\n", G.supplyCount[tribute], 10);
	assert(G.supplyCount[tribute] == 10);

	printf("ambassador supply count = %d, expected = %d\n", G.supplyCount[ambassador], 10);
	assert(G.supplyCount[ambassador] == 10);

	printf("cutpurse supply count = %d, expected = %d\n", G.supplyCount[cutpurse], 10);
	assert(G.supplyCount[cutpurse] == 10);

	printf("embargo supply count = %d, expected = %d\n", G.supplyCount[embargo], 10);
	assert(G.supplyCount[embargo] == 10);

	printf("outpost supply count = %d, expected = %d\n", G.supplyCount[outpost], -1);
	assert(G.supplyCount[outpost] == -1);

	printf("salvager supply count = %d, expected = %d\n", G.supplyCount[salvager], -1);
	assert(G.supplyCount[salvager] == -1);

	printf("sea_hag supply count = %d, expected = %d\n", G.supplyCount[sea_hag], -1);
	assert(G.supplyCount[sea_hag] == -1);

	printf("treasure_map supply count = %d, expected = %d\n", G.supplyCount[treasure_map], -1);
	assert(G.supplyCount[treasure_map] == -1);

	printf("this player's handCount = %d, expected = %d\n", G.handCount[thisPlayer], 5);
	assert(G.handCount[thisPlayer] == 5);

	printf("this player's discardCount = %d, expected = %d\n", G.discardCount[thisPlayer], 0);
	assert(G.discardCount[thisPlayer] == 0);

	printf("this player's deckCount = %d, expected = %d\n", G.deckCount[thisPlayer], 5);
	assert(G.deckCount[thisPlayer] == 5);

	printf("next player's handCount = %d, expected = %d\n", G.handCount[nextPlayer], 5);
	assert(G.handCount[nextPlayer] == 5);

	printf("next player's discardCount = %d, expected = %d\n", G.discardCount[nextPlayer], 0);
	assert(G.discardCount[nextPlayer] == 0);

	printf("next player's deckCount = %d, expected = %d\n", G.deckCount[nextPlayer], 5);
	assert(G.deckCount[nextPlayer] == 5);

	printf("outpost played = %d, expected = %d\n", G.outpostPlayed, 0);
	assert(G.outpostPlayed == 0);

	printf("whose Turn = %d, expected = %d\n", G.whoseTurn, thisPlayer);
	assert(G.whoseTurn == thisPlayer);

	printf("phase = %d, expected = %d\n", G.phase, 0);
	assert(G.phase == 0);

	printf("number of actions = %d, expected = %d\n", G.numActions, 1);
	assert(G.numActions == 1);

	printf("number of buys = %d, expected = %d\n", G.numBuys, 1);
	assert(G.numBuys == 1);

	printf("coins = %d, expected = %d\n", G.coins, 0);
	assert(G.coins == 0);

	printf("number of played cards = %d, expected = %d\n", G.playedCardCount, 0);
	assert(G.playedCardCount == 0);

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}
