/* resched.c - resched */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  resched  -  Reschedule processor to highest priority eligible process
 *------------------------------------------------------------------------
 */
void	resched(void)		/* assumes interrupts are disabled	*/
{
	struct procent *ptold;	/* ptr to table entry for old process	*/
	struct procent *ptnew;	/* ptr to table entry for new process	*/

	/* If rescheduling is deferred, record attempt and return */

	if (Defer.ndefers > 0) {
		Defer.attempt = TRUE;
		return;
	}

	/* Point to process table entry for the current (old) process */

	ptold = &proctab[currpid];

	if (ptold->prstate == PR_CURR) {  /* process remains running */
		/* LAB 3 -- Reprioritize process based on time-share table */
		int32 newprio = tstab[ptold->prprio].ts_tqexp + 1;
		if (newprio > 59) {newprio = 59;}
		ptold->prprio = newprio;
		
		if (ptold->prprio > firstready(readylist)) {
			return;
		}

		/* Old process will no longer remain current */

		ptold->prstate = PR_READY;
		/* LAB 3 - Changed insert to enqueue for mlfq */
		enqueue(currpid, readylist[ptold->prprio]);
	}
	else if (ptold->prstate == PR_SLEEP) { /* process voluntarily gave up CPU */
		/* LAB 3 -- Reprioritize process based on time-share table */
		int32 newprio = tstab[ptold->prprio].ts_slpret + 1;
		if (newprio > 59) {newprio = 59;}
		ptold->prprio = newprio;
	}

	/* Force context switch to highest priority ready process */

	/* LAB 3 -- Changed dequeue to demlfq to handle readylist */
	currpid = demlfq(readylist);
	
	ptnew = &proctab[currpid];
	ptnew->prstate = PR_CURR;
	
	/* LAB 3 -- reset time slice for process -- previously set to QUANTUM */
	preempt = tstab[ptnew->prprio].ts_quantum;
	
	/* LAB 3 -- reset clktimeold for the new process; update prtotalcpu for the old process */
	ptnew->clktimeold = clktimeaccru;
	ptold->prtotalcpu += clktimeaccru - ptold->clktimeold;
	ctxsw(&ptold->prstkptr, &ptnew->prstkptr); 	//this appears to be the only place in the source where
							//ctxsw is ever called. very convenient for lab 3.4

	/* Old process returns here when resumed */

	return;
}
