Exercise 3
Owen Craston
S#: 101037159
Class: COMP3000

Inside this file are all the documents pertaining to the assignment
The files that I have added to or changed are listed below and included in this folder under /usr/...

usr/src/minix/include/minix/ipc.h
Line 1435: added: pid_t group_id;
with:
typedef struct {
	endpoint_t endpoint;
	endpoint_t parent;
	int maxprio;
	int quantum;
	pid_t group_id;
	uint8_t padding[40];
} mess_lsys_sched_scheduling_start;

usr/src/minix/include/minix/ipc.h
line 1544: changed uint8_t padding[32] to uint8_t padding[36]
with:
typedef struct {
	endpoint_t	destination;
	endpoint_t	source;
	void		*dest_addr;
	void		*src_addr;
	size_t		size;
	void		*ret_addr;
	uint8_t		padding[36];
} mess_lsys_vm_vmremap;

usr/src/minix/lib/libsys/sched_start.c
Line 13: added pid_t group_id,
with:
int sched_inherit(endpoint_t scheduler_e,
	endpoint_t schedulee_e, endpoint_t parent_e, unsigned maxprio,
	endpoint_t *newscheduler_e), pid_t group_id,
{
usr/src/minix/lib/libsys/sched_start.c
line 28: added 	m.m_lsys_sched_scheduling_start.group_id  = group_id;

usr/src/minix/include/minix/sched.h
line 11: added pid_t group_id
with:
int sched_inherit(endpoint_t scheduler_e, endpoint_t schedulee_e,
	endpoint_t parent_e, unsigned maxprio, endpoint_t *newscheduler_e), pid_t group_id;

usr/src/minix/servers/sched/schedproc.h
Line 33: added 	pid_t group_id;
with: 	/* User space scheduling */
	unsigned max_priority;	/* this process' highest allowed priority */
	unsigned priority;		/* the process' current priority */
	unsigned time_slice;		/* this process's time slice */
	unsigned cpu;		/* what CPU is the process running on */
	pid_t group_id;

usr/src/minix/servers/pm/schedule.c
line 84: added 		rmp->mp_procgrp);
with:
/* inherit quantum */
return sched_inherit(ep, 			/* scheduler_e */
	rmp->mp_endpoint, 			/* schedulee_e */
	inherit_from, 				/* parent_e */
	maxprio, 				/* maxprio */
	&rmp->mp_scheduler, /* *newsched_e */
	rmp->mp_procgrp);

usr/src/minix/servers/sched/schedule.c
Line 109: added the size() function
with:
int size(pid_t group_id) {
    int x = 0;

    for(int i = 0; i < NR_PROCS; i++){
      if (group_id == schedproc[i].group_id  && schedproc[i].flags & IN_USE){
          x++;
      }
    }
    if (x == 0){
        return 1;
    } else {
        return x;
    }
}

usr/src/minix/servers/sched/schedule.c
line: 191: replaced rmp->time_slice = DEFAULT_USER_TIME_SLICE  with rmp->time_slice = DEFAULT_USER_TIME_SLICE / size(rmp->group_id);

usr/src/minix/servers/sched/schedule.c
line 225: replaced //rmp->time_slice = schedproc[parent_nr_n].time_slice; with rmp->time_slice = DEFAULT_USER_TIME_SLICE / size(rmp->group_id);
