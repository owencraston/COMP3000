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
