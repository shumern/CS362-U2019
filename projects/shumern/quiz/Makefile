CFLAGS= -Wall -fpic -coverage -lm -std=c99

quiz: testme.c
	gcc -o quiz testme.c $(CFLAGS)

randomtestresults: quiz
	-./quiz >> results.out
	gcov testme.c -b >> randomtestresults.out


all: quiz 

clean:
	rm -f *.o quiz  *.gcov *.gcda *.gcno *.so *.out
