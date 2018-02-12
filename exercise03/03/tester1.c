/* File: tester1.c
 *
 * A CPU-bound process (no children).
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
   int i, j;
   i = 1;
   while (1) {
      i = j; j = i;
   }
}
