#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <michel_getdpids.h>
#define LEN 14 /* buffer size, in PIDs (can't be > 14) */
int main(int argc, char** args) {   
	pid_t pid, cpid; /* PIDs */
	pid_t dpids[LEN]; /* buffer for descendant PIDs */
	int i, r; /* control vars */
	printf("Test 1 - Single child\n");
	/* get the PID */
	pid = getpid();
	/* print the PID */
	printf("My PID is %d\n", pid);
	cpid = fork();
	if (cpid!=0) { /* in parent! */
		printf("Child PID is %d\n", cpid);
		/* get and print all descendants */
		r = michel_getdpids(pid, dpids, LEN);
		printf("Tree has %d process(es)\n", r);
		for (i=0;i<r;i++) { printf("%d ", dpids[i]); };
		printf("\n");
	} else { /* in child! */
		sleep(10); /* sleep 10 seconds */
	}
	return 0;
}
