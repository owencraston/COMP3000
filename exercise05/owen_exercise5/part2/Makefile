all: primes.o
	gcc -o primes primes.o -lpthread 

primes.o: primes.c
	gcc -c primes.c 

clean:
	rm -f *.o primes
