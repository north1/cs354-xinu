/* Michael North - Lab 3 */
/* cpuintensive() */

#include <xinu.h>

#define LOOP1	10
#define LOOP2	100000000


void cpuintensive() {
	int32 i, j;
	int32 foo = 0;
	pid32 me = getpid();
	struct procent *myEnt = &proctab[me];

	for (i = 0; i < LOOP1; i++) {
		for (j = 0; j < LOOP2; j++) {
			//insert code that performs memory copy (slow) and/or ALU operations (fast)
			//note: this loop consumes significant CPU cycles
			foo = ((10000 * 10000) / 1234) % (i*j)+0.5;
		}

		//using kprintf print the pid followed the outer loop count i,
		//the process's priority and remaining time slice (preempt)
		kprintf("PID: %d -- i: %d -- Prio: %d -- Slice: %d\n", me, i, myEnt->prprio, preempt);
	}
}
