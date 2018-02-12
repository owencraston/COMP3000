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
