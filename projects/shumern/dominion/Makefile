CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

unittestresults: unittest1.c unittest2.c unittest3.c unittest4.c unittest5.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c cardtest5.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	./unittest1 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	
	gcc -o unittest5 -g unittest5.c dominion.o rngs.o $(CFLAGS)
	./unittest5 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	./cardtest1 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	./cardtest2 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	./cardtest3 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardtest4 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out
	
	gcc -o cardtest5 -g cardtest5.c dominion.o rngs.o $(CFLAGS)
	./cardtest5 >> unittestresults.out
	gcov dominion.c -b -f >> unittestresults.out

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out
