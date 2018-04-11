all: writelockafile.o testlock.o
	cc -o writelockafile writelockafile.o
	cc -o testlock testlock.o

writelockafile.o: writelockafile.c
	cc -c writelockafile.c 

testlock.o: testlock.c
	cc -c testlock.c

clean:
	rm -f *.o writelockafile testlock
