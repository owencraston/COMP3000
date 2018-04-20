#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main (int argc, char* argv[])
{

  char* file = argv[1];
  int fd;
  struct flock lock;

  if (argc != 2) {
    printf("Invalid number of arguments.\n");
    return(0);
  } else if (!fopen (argv[1],"r")) {
    printf("Invalid file.\n");
    return(0);
  }

  fd = open(file, O_RDWR);
  lock.l_type    = F_WRLCK;
  lock.l_start   = 0;
  lock.l_whence  = SEEK_SET;
  lock.l_len     = 0;
  fcntl(fd, F_GETLK, &lock);
  if (lock.l_type == F_WRLCK) {
     printf("File is locked. PID %d.\n", lock.l_pid);
  }
  else if (lock.l_type == F_RDLCK) {
     printf("File is locked. PID %d.\n", lock.l_pid);
  } else {
    printf("File is not locked\n");
  }

  close (fd);
  return 0;
}