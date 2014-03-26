/* ready.c - ready */

#include <xinu.h>


/* LAB 3 -- had to make note of the change to readylist */
qid16	readylist[TSTAB_SIZE];		/* index of ready list		*/
/* LAB 3 -- */

/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status	ready(
	  pid32		pid,		/* ID of process to make ready	*/
	  bool8		resch		/* reschedule afterward?	*/
	)
{
	register struct procent *prptr;

	if (isbadpid(pid)) {
		return(SYSERR);
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];
	prptr->prstate = PR_READY;
	/* LAB 3 -- Changed insert to enqueue for mlfq */
	//insert(pid, readylist, prptr->prprio); //pre-Lab 3 version
	enqueue(pid, readylist[prptr->prprio]);
	/* LAB 3 -- */

	if (resch == RESCHED_YES) {
		resched();
	}
	return OK;
}
