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

int owen_getpids(pid_t top, pid_t dpids[], int len) {
    message m;
    memset(&m, 0, sizeof(m));

    m.m1_i1 = top;
    m.m1_i2 = len;
    for (int i=0; i<len; i++) {
    	m.m_u32.data[i] = dpids[i];
    }
    _syscall(PM_PROC_NR, PM_OWEN_GETDPIDS, &m);
    return NR_PROCS;
}
