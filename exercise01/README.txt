Exercise 1
Owen Craston
S#: 101037159
Class: COMP3000 
Note: I was not sure exactly how to submit the source code so I included the code I added in this folder under usr
There is a screenshot of the results of this program

// Changes

Created file: usr/include/owen_time.h
with
void owen_time(int * sec, int * nsec);

Added owen_time.h to src/include/Makefilell
 INCS=	a.out.h aio.h ar.h assert.h atomic.h \
	 ...owen_time.h
//
Created file: src/minix/lib/libc/sys/owen_time.c
with 
#include <sys/cdefs.h>
#include "namespace.h"
#include <sys/types.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <lib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>


void owen_time (int * sec, int * nsec) {
  message m;
  memset(&m, 0, sizeof(m));
  _syscall(PM_PROC_NR, PM_OWEN_TIME, &m);
  *sec = m.m_pm_lc_time.sec;
  *nsec = m.m_pm_lc_time.nsec;
}

Added owen_time.c usr/src/minix/lib/libc/sys/Makefile.inc
SRCS+= 	accept.c access.c adjtime.c bind.c brk.c sbrk.c m_closefrom.c getsid.c \
	...owen_time.c
//
Added my process call ID to the src/minix/include/minix/callnr.h file by appending it the the list with the name of the ID we choose to give. This give us...
#define PM_OWEN_TIME		(PM_BASE + 48)
 and updated #define NR_PM_CALLS		49	 to be 49 since we were adding a call
//
Added to file usr/src/minix/servers/pm/proto.hi

added the following prototype declaration to the end of the file
/* custom system call owen_time */
int do_owen_time(void);
//
Added to the file: usr/src/minix/servers/pm/table.c
at the bottom of this file I added the following...
CALL(PM_OWEN_TIME) = do_owen_time			/* owen_time(2) */
//

Created file: usr/src/minix/servers/pm/owen_time.c
with 
#include "pm.h"
#include <minix/callnr.h>
#include <minix/com.h>
#include <signal.h>
#include <sys/time.h>
#include "mproc.h"


int do_owen_time(void){
  /* Perform the owen_time system call. */
    struct timespec tv;

    (void)clock_time(&tv);

    mp->mp_reply.m_pm_lc_time.sec = tv.tv_sec;
    mp->mp_reply.m_pm_lc_time.nsec = tv.tv_nsec;
    return(OK);
}
//
Declared my system call in usr/src/minix/servers/pm/Makefile
added my system call to the mskefile using the following code
SRCS=	main.c forkexit.c exec.c time.c alarm.c \
	signal.c utility.c table.c trace.c getset.c misc.c \
	profile.c mcontext.c schedule.c event.c owen_time.c
//

Test code:
Created file: usr/src/tester.c

and add the following code to the file
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <owen_time.h>

int main(int argc, char** args) {
   int sec, nsec;
/* get the current time */
   owen_time(&sec, &nsec);
   /* print local time */
   printf("System time is %d sec and %d nsec\n", sec, nsec);
   return 0;
}

To compile: cc -o tester tester.c
To run: clear;uname -a;date; more tester.c;./tester.
