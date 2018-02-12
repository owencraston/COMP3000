Exercise 2
Owen Craston
S#: 101037159
Class: COMP3000 

In this folder is a copy of my usr directory with the code that I added/modified

Created file: usr/include/owen_getdpids.h
with:
int owen_getdpids(pid t top, pid t dpids[], int len);

Added my process call number to /usr/src/minix/include/minix/callnr.h
With:
#define PM_OWEN_GETDPIDS        (PM_BASE + 49)

Added photo to /usr/src/minix/servers/pm/proto.h
with:
int do_owen_getpids(void);

added to /usr/src/minix/servers/pm/table.c
with:
CALL(PM_OWEN_GETDPIDS) = do_owen_getdpids


Created file: src/minix/lib/libc/sys/owen_getpids.c

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

Created /usr/src/minix/servers/pm/owen_getdpids.c

with:
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>i
#include "mproc.h"  // for process table mproc

int do_owen_getdpids(void) {
    int len = m_in.m1_i2;
    pid_t top = m.m1_i1;
    pid_t arr[len] = null;
    int insert_position = 0;
    arr[insert_position] = to_pids;
    insert_position ++;

    //get all the pids for all process (found in table)


    for (int table_idx = 0; table_idx < 14; table_idx++) {
        for (int array_idx = 0; array_idx < 14; array_idx++) {
            int current_pid = mproc[table_idx].mp_id;

            int parent_index = mproc[table_idx].mp_parent;
            int parent_pid = mproc[parent_index].mp_pid;


            if (parent_pid == arr[array_idx]) {
                //add to the array
                arr[insert_position] = current_pid;
                insert_position ++;
            }
        }
    }

}

//
Added to /usr/src/minix/servers/pm/Makefile
with:
owen_getdpids.c to ... 
SRCS=   main.c forkexit.c exec.c time.c alarm.c \
        signal.c utility.c table.c trace.c getset.c misc.c \
        profile.c mcontext.c schedule.c event.c owen_time.c owen_getdpids.c