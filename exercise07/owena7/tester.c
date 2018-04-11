/* Memory allocation tester program
 * COMP3000, Michel Barbeau
 * Version: March 1, 2018
 */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "mymalloc.h"

void main(int argc, char *argv[]) {
   int sizes[] = { 1024, 2048, 4096 };
   int N = 3;
   int i;
   void * p[N];

   fprintf(stdout, "\n");
   fprintf(stdout, "Initial program break: %10p\n", sbrk(0));
  
   fprintf(stdout, "*** First test ***\n");
   for (i = 0; i < N; i++) {
      fprintf(stderr, "Allocating %d bytes\n", sizes[i]);
      p[i] = mymalloc(sizes[i]);
      if (p[i]==NULL) {
         fprintf(stderr, "mymalloc failed!\n");
         exit(EXIT_FAILURE);
      }
      fprintf(stdout, "After allocation, program break is:  %10p\n", sbrk(0));
   }
   for (i = N-1; i >=0; i--) {
      fprintf(stderr, "Address being freed: %10p\n", p[i]);
      myfree(p[i]);
      fprintf(stdout, "After freeing, program break is: %10p\n", sbrk(0));
   }

   fprintf(stdout, "*** 2nd test ***\n");
   fprintf(stdout, "Testing freeing invalid address\n");
   myfree(NULL);
   fprintf(stdout, "Program break is:  %10p\n", sbrk(0));

   fprintf(stdout, "*** 3rdt test ***\n");
   for (i = 0; i < N; i++) {
      fprintf(stderr, "Allocating %d bytes\n", sizes[i]);
      p[i] = mymalloc(sizes[i]);
      if (p[i]==NULL) {
         fprintf(stderr, "mymalloc failed!\n");
         exit(EXIT_FAILURE);
      }
      fprintf(stdout, "After allocation, program break is:  %10p\n", sbrk(0));
   }
   for (i = 0; i < N; i++) {
      fprintf(stderr, "Address being freed: %10p\n", p[i]);
      myfree(p[i]);
      fprintf(stdout, "After freeing, program break is: %10p\n", sbrk(0));
   }

   fprintf(stdout, "*** 4th test ***\n");
   fprintf(stdout, "Final program break is:  %10p\n", sbrk(0));

   return;
}
