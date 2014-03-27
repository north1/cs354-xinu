/* Michael North - Lab 3 */
/* cpuintensive() */

#include <xinu.h>

#define LOOP1	10
#define LOOP2	1

/* LAB 3 -- This process is intended to be iointensive and give up control frequently via sleepms() */

void iointensive() {
	int32 i, j;
	pid32 me = getpid();
	struct procent *myEnt = &proctab[me];

	for (i = 0; i < LOOP1; i++) {
		for (j = 0; j < LOOP2; j++) {
			sleepms(500);
		}

		//using kprintf print the pid followed the outer loop count i,
		//the process's priority and remaining time slice (preempt)
		kprintf("IO PID: %d -- i: %d -- Prio: %d -- totCPU: %d\n", me, i, myEnt->prprio, myEnt->prtotalcpu);
	}
}
