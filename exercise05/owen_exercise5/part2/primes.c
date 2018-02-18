#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct thread_data {
   int n;
   int result; 
} thread_data;

/* Inefficiently, compute successive prime numbers.  
   Return the nth prime number.  */
void* compute_prime (void * arg) {
   /* dereference the parameter */
   thread_data * tdata = (thread_data *)arg;
   int n = tdata->n;
   int candidate = 2;

   while (true) {
      int factor;
      int is_prime = true;

      /* test primality by successive division.  */
      for (factor = 2; factor < candidate; ++factor)
         if (candidate % factor == 0) {
            is_prime = false;
            break;
         }
      /* is prime number we're looking for?  */
      if (is_prime) {
         if (--n == 0) {
            /* define the result  */
		    tdata->result = candidate;
            pthread_exit(NULL);
         }
      }
      ++candidate;
   }
}

int main ()
{
   pthread_t tid;
   thread_data tdata;
   thread_data tdata2;
   time_t t;

   /* intialize random number generator */
   srand((unsigned) time(&t));
   tdata.n=rand() % 5000;
   tdata2.n=rand() % 5000;
   printf("i is %d, j is %d.\n", tdata.n, tdata2.n);

   /* start the thread, up to "tdata.n" */
   pthread_create (&tid, NULL, compute_prime, (void *)&tdata); 
   // start thread for tdata2
   pthread_create (&tid, NULL, compute_prime, (void *)&tdata2); 
   /* wait for the thread to complete  */
   pthread_join (tid, NULL);

   /* print the computed prime */
   printf("pi is %d, pj is %d.\n", tdata.result, tdata2.result);
   // print the product
   printf("Their product is %d. \n", (tdata.result * tdata2.result));
}
