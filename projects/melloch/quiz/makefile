CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c 
	gcc -o testme testme.c -g $(CFLAGS)

test: testme
	./testme &> testresults.out
	gcov -b -f testme.c >> testresults.out
	cat testme.c.gcov >> testresults.out

all: testme test

clean:
	rm -f *.o testme.exe testme test *.gcov *.gcda *.gcno *.so *.out 