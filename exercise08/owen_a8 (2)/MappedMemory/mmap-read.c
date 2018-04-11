/* Mapped-memory example - Reader program
 * Version: March 11, 2018
 */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include "mmap.h"

int main (int argc, char* const argv[]) {
  int fd;
  void* file_memory;
  int integer;

// erorr checking
  //check if the correct number of args were passed
  if (argc > 3) {
    printf("too many arguments passed, Please pass a file to read and a positive integer \n");
    return(1);
  } else if (argc < 3) {
    printf("too few arguments passed, PLease pass a file to read and a positive integer \n");
    return(1);
  } else if (atoi(argv[2]) < 1) { // check if the number passed is a positive number
    printf("the number passed is not a positive integer, PLease pass a positive integer as the second argument \n");
    return(1);
  } else if (!fopen(argv[1], "r")) { // check if the file is readable
    printf("can not read file, PLease pass a valid file path \n");
    return(1);
  }
  //now that we have done our error checking, we may proceed...

  // set n as the command line arg
  int n = atoi(argv[2]);

  /* open the file  */
  fd = open (argv[1], O_RDWR, S_IRUSR | S_IWUSR);

  /* create the memory-mapping */
  file_memory = mmap (NULL, FILESIZE, PROT_READ | PROT_WRITE,
		      MAP_SHARED, fd, 0);
  close (fd);

  /* read and print the integerS */
  for(int i=0; i < n; i++) {
    sscanf (file_memory, "%d", &integer);
    printf ("file contains: %d\n", integer);

    //increment the memory
    file_memory += sizeof(int); // increment by the size of an integer since we are storing ints
  }

  /* release the memory */
  munmap (file_memory, FILESIZE);

  return 0;
}
