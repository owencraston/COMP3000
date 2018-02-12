/* Write from "/dev/prime"
 */
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
 
#define BUFFER_LENGTH 256 
static char data[BUFFER_LENGTH];
 
int main(int argc, char* argv[]) {
  int ret, fd, i, n;

  /* parse the argument (number of primes to read) */
  if (argc < 2) {
    // error
    fprintf(stderr, "usage: prime n\n");
    exit(-1);
  }
  /* convert argv[1] to string */
  errno = 0; char *p;
  long conv = strtol(argv[1], &p, 10);
  if (errno != 0 || *p != '\0') {
    // error
    fprintf(stderr, "%s: %s\n", "failed to parse number of primes", strerror(errno));
    exit(-1);
  }
  /* check for errors: e.g., the string does not represent an integer
     or the integer is larger than int */
  if (conv<1 || conv > INT_MAX) {
    // error
    fprintf(stderr, "%s: %s\n", "invalid number of primes", strerror(errno));
    exit(-1);
  } else {
    // no error
    n = conv;
  }

  printf("test started\n");
  fd = open("/dev/owen_prime", O_RDWR);
  if (fd < 0) {
    perror("open failed");
      return errno;
  }
  printf("Reading %d prime number(s)\n", n);
  for (i=0; i<n; i++) {
    ret = read(fd, data, BUFFER_LENGTH);
    if (ret < 0) {
       perror("read failed");
       return errno;
    }
    printf("%s", data);
  }
  return 0;
}
