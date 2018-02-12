#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <michel_getdpids.h>
#include <stdlib.h>
#define LEN 14 /* buffer size, in PIDs (can't be > 14) */
#define N 5 /* number of forked children */
int main(int argc, char** args) {   
	pid_t pid, cpid; /* PIDs */
	pid_t dpids[LEN]; /* buffer for descendant PIDs */
	int i, j, r; /* control vars */
	printf("Test 2 - Fan of children\n");
	/* get the PID */
	pid = getpid();
	/* print the PID */
	printf("My PID is %d\n", pid);
	/* fork N children */
	for (j=0; j<N;j++) {
		if (fork()<=0) /* in child! */
			break;
	}
	if (pid==getpid()) { /* in root! */
		/* get and print all descendants */
		r = michel_getdpids(pid, dpids, LEN);
		printf("Tree has %d process(es)\n", r);
		for (i=0;i<r;i++) { printf("%d ", (int) dpids[i]); };
		printf("\n");
		/* corroborate using "ps" */
		system("ps -o pid,ppid,command");
	} else { /* in child! */
		sleep(10); /* sleep 10 seconds */
	}
	return 0;
}
