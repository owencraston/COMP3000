/* File: tester2.c
 *
 * A CPU-bound process with one child.
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
   int i, j;
   fork();
   i = 1;
   while (1) {
      i = j; j = i;
   }
}

