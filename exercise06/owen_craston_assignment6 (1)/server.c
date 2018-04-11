#include <stdbool.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

// #define N 2 // number of threads
volatile int buffer;
volatile int bufferSize;
volatile int numThreads;
volatile int bufferPosition = 0;
#define bufferArraySize 100
int bufferArray[bufferArraySize];
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER; // for buffer access
sem_t semaphore; // controls the pool of threads

static void * worker(void *arg) {
	// input
	int j;	
   	while (true) {
	   // block until work is available
	   if (sem_wait(&semaphore)) {
	      fprintf(stderr, "sem_wait: %s\n", strerror(errno));
	      exit(EXIT_FAILURE);
	   }
	   // get exclusive access to buffer
	   if (pthread_mutex_lock(&mtx)) {
	      fprintf(stderr, "pthread_mutex_lock: %s\n", strerror(errno));
	      exit(EXIT_FAILURE);
	   }
	   // store input 
	   //code goes here
	   j = bufferArray[bufferPosition];
	   bufferPosition--;

	   // release exclusive access to buffer
	   if (pthread_mutex_unlock(&mtx)) {
	      fprintf(stderr, "pthread_mutex_unlock: %s\n", strerror(errno));
	      exit(EXIT_FAILURE);
	   }
	   // process data
	   fprintf(stdout, "Processing: %d\n", j);
	   sleep(10);
	   fprintf(stdout, "Done with: %d\n", j);	
	}
}

int main(int argc, char *argv[]) {
	// check if the correct number of args were passed
	if (argc > 3) {
		//print error
		fprintf(stderr, "too many arguments, Please input 1 value for the number of threads and another for the number of buffers\n");
		return(0);
	}
	if (argc < 3) {
		//print error
		fprintf(stderr, "too few arguments, Please input 1 value for the number of threads and another for the number of buffers\n");
		return(0);
	}
	// get input commmands for the buffer size and number of threads from user
	numThreads = atoi(argv[1]);
	bufferSize = atoi(argv[2]);

	// check if the bufferSize is too big for the BufferArray
	if (bufferSize > bufferArraySize) {
		fprintf(stderr, "too manny buffers. Please input a buffer number smaller than %d \n", bufferArraySize);
		return(0);
	}

	// print the buffers and threads
	fprintf(stdout, "%d Threads, %d Buffers\n", numThreads, bufferSize);

	int j;
	// initialize semaphore
	if (sem_init(&semaphore, 0, 0)) {
	      fprintf(stderr, "sem_init: %s\n", strerror(errno));
	      exit(EXIT_FAILURE);
	}
	// create pool of N detached threads
   	pthread_t t;
  	for (int i=0; i<numThreads; ++i) { // modify to use dynamic value for number of threads
	   if (pthread_create(&t, NULL, worker, NULL)) {
	      fprintf(stderr, "pthread_create: %s\n", strerror(errno));
	      exit(EXIT_FAILURE);
	   }
	   if (pthread_detach(t)) {
	      fprintf(stderr, "pthread_detach: %s\n", strerror(errno));
	      exit(EXIT_FAILURE);
	   }
   	}
	// main loop
   	while (fscanf(stdin, "%d", &j)!=EOF) {
		if (bufferPosition >= bufferSize) {
			fprintf(stderr, "buffer is full \n");
		} else {
			// get exclusive access to buffer
			if (pthread_mutex_lock(&mtx)) {
				fprintf(stderr, "pthread_mutex_lock: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
			// load input into buffer
			bufferPosition ++;
			bufferArray[bufferPosition] = j;
			// release exclusive access to buffer
			if (pthread_mutex_unlock(&mtx)) {
				fprintf(stderr, "pthread_mutex_unlock: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
			// unlock one thread
			if (sem_post(&semaphore)) {
				fprintf(stderr, "sem_post: %s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
		}
	}
	return(0);
}
