#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

/* termination variable,
"volatile" tells compiler that value
may change at any time,
i.e., due to the arrival of a signal
*/
volatile sig_atomic_t term = false;

// sigusr1 handler
void sigusr1_handler(int signal_number){
    printf("SIGUSR1 was raised!\n");
     _exit(0);
}

// handler of sigterm
void sigterm_handler(int signal_number){
    // set term to true
    term = true;
}

// child process logic
void child_process(){
    int parent_pid = getppid();
    if(kill(parent_pid, SIGUSR1)  == -1){
        printf("Failure %d\n", errno);
    }
    _exit(0);
}

void main(){
    // fork child process
    if(fork() == 0){
        printf("Child process created.\n");
        child_process();
    }

    struct sigaction sa;
    
    // set handlers
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &sigusr1_handler;
    sigaction(SIGUSR1, &sa, NULL);

    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = &sigterm_handler;
    sigaction(SIGTERM, &sa, NULL);

    /* pause and handle SIGUSR1 until SIGTERM */
    while(!term) pause();
}
