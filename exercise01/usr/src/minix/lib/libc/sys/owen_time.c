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
