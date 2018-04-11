/* Mapped-memory example - Writer program
 * Version: March 11, 2018
 */
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include "mmap.h"

/* return a uniformly generated random number in the range [low,high]  
 */
int random_range (unsigned const low, unsigned const high) {
  unsigned const range = high - low + 1;
  return low + (int) (((double) range) * rand () / (RAND_MAX + 1.0));
}

/* Create and write to a shared file for communication with another process.
 *
 * argv[1] = file name
 *
 * Note: Error processing is omitted
 */
int main (int argc, char* const argv[]) {
  int fd;
  void* file_memory;
// error checking
  // check if the correct number of args were passed
  if (argc > 3) {
    printf("too many arguments passed, Please pass a file to write to and a positive integer \n");
    return(1);
  } else if (argc < 3) {
    printf("too few arguments passed, PLease pass a file to write to and a positive integer \n");
    return(1);
  } else if (atoi(argv[2]) < 1) { // check if the number passed is a positive number
    printf("the number passed is not a positive integer, PLease pass a positive integer as the second argument \n");
    return(1);
  } else if (!fopen(argv[1], "w")) { // check if the file is readable
    printf("can not write to file, PLease pass a valid file path \n");
    return(1);
  }
  //set n as the valid command line arg
  int n = atoi(argv[2]);

  /* seed the random number generator */
  srand (time (NULL));

  /* open or create a file to hold an unsigned integer  */
  fd = open (argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

  /* write FILESIZE spaces */
  for (int i=0; i<FILESIZE; i++) write (fd, " ", 1);
  write (fd, "", 1); /* write a NULL at EOF */

  /* create the memory-mapping  
     1st param=start addr of mapping into memory, NULL means chosen by OS
     2nd param=length of map (bytes)
     3rd param=protection
     4th param=options, MAP_SHARED used for interprocess communications
     5th param=file descriptor of mapped file
     6th param=offset from start of file where mapping starts
   */
  file_memory = mmap (NULL, FILESIZE, PROT_WRITE, MAP_SHARED, fd, 0);
  close (fd);

  // write n random integers 
  for (int i=0; i<n; i++) {
    /* write a random integer to memory-mapped area  */
    sprintf((char*) file_memory, "%d\n", random_range (-100, 100));
    file_memory += sizeof(int); // iincrement the file memory by the size of an int since we are writing ints
  }

  /* release the memory  */
  munmap (file_memory, FILESIZE);
}
