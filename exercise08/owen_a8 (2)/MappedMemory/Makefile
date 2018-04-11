all: mmap-read.o mmap-write.o
	gcc -o mmap-read mmap-read.o 
	gcc -o mmap-write mmap-write.o 

mmap-read.o: mmap-read.c
	gcc -c mmap-read.c 

mmap-write.o: mmap-write.c
	gcc -c mmap-write.c 

clean:
	rm -f *.o mmap-read mmap-write *~
