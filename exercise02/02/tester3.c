#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <michel_getdpids.h>
#include <stdlib.h>
#define LEN 14 /* buffer size, in PIDs (can't be > 14) */
#define N 3 /* max number of forked children per parent */
int main(int argc, char** args) {   
	pid_t pid, cpid; /* PIDs */
	pid_t dpids[LEN]; /* buffer for descendant PIDs */
	int i, r; /* control vars */
	/* get the PID */
	pid = getpid();
	/* print the PID */
	printf("My PID is %d\n", pid);
	printf("Test 3 - Tree of children\n");
	/* fork a tree of descendants */
        for (i=0; i<N;i++) {
                if (fork()==-1) 
                        break;
        }
	if (pid==getpid()) { /* in root! */
		/* get and print all descendants */
		r = michel_getdpids(pid, dpids, LEN);
		printf("Tree has %d process(es)\n", r);
		for (i=0;i<r;i++) { printf("%u ", dpids[i]); }
		printf("\n");
		/* corroborate using "ps" */
		system("ps -o pid,ppid,command");
	} else { /* in child! */
		sleep(10); /* sleep 10 seconds */
	}
	return 0;
}
