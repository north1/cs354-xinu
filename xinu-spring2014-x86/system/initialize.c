/* initialize.c - nulluser, sysinit, sizmem */

/* Handle system initialization and become the null process */

#include <xinu.h>
#include <string.h>

extern	void	start(void);	/* start of Xinu code */
extern	void	*_end;		/* end of Xinu code */

/* Function prototypes */

extern	void main(void);	/* main is the first process created	*/
extern	void xdone(void);	/* system "shutdown" procedure		*/
static	void sysinit(void);	/* initializes system structures	*/

/* Declarations of major kernel variables */

struct	procent	proctab[NPROC];	/* Process table			*/
struct	sentry	semtab[NSEM];	/* Semaphore table			*/
struct	memblk	memlist;	/* List of free memory blocks		*/

/* Active system status */

int	prcount;		/* Total number of live processes	*/
pid32	currpid;		/* ID of currently executing process	*/

/* Memory bounds set by start.S */

void	*minheap;		/* start of heap			*/
void	*maxheap;		/* highest valid memory address		*/

/* Table for proccess scheduling in lab 3 */
struct ts_ent tstab[TSTAB_SIZE];

/* Array of prioritized ready queues for lab 3 */
qid16 readylist[TSTAB_SIZE];

/*------------------------------------------------------------------------
 * nulluser - initialize the system and become the null process
 *
 * Note: execution begins here after the C run-time environment has been
 * established.  Interrupts are initially DISABLED, and must eventually
 * be enabled explicitly.  The code turns itself into the null process
 * after initialization.  Because it must always remain ready to execute,
 * the null process cannot execute code that might cause it to be
 * suspended, wait for a semaphore, put to sleep, or exit.  In
 * particular, the code must not perform I/O except for polled versions
 * such as kprintf.
 *------------------------------------------------------------------------
 */

void	nulluser(void)
{
	sysinit();

	kprintf("\n\r%s\n\n\r", VERSION);

	/* Output Xinu memory layout */

	kprintf("%10d bytes physical memory.\n",
		(uint32)maxheap - (uint32)0);
	kprintf("           [0x%08X to 0x%08X]\r\n",
		(uint32)0, (uint32)maxheap - 1);
	kprintf("%10d bytes of Xinu code.\n",
		(uint32)&etext - (uint32)0);
	kprintf("           [0x%08X to 0x%08X]\n",
		(uint32)0, (uint32)&etext - 1);
	kprintf("%10d bytes of data.\n",
		(uint32)&end - (uint32)&etext);
	kprintf("           [0x%08X to 0x%08X]\n",
		(uint32)&etext, (uint32)&end - 1);
	if ( (char *)minheap < HOLESTART) {
	    kprintf("%10d bytes of heap space below 640K.\n",
		(uint32)HOLESTART - (uint32)roundmb(minheap));
	}
	if ( (char *)maxheap > HOLEEND ) {
	    kprintf("%10d bytes of heap space above 1M.\n",
		(uint32)maxheap - (uint32)HOLEEND);
	    kprintf("           [0x%08X to 0x%08X]\n",
		(uint32)HOLEEND, (uint32)truncmb(maxheap) - 1);
	}

	/* Enable interrupts */
	
	enable();

	/* Start the network */
	
	/* resume(create((void *)netin, NETSTK, NETPRIO, "netin", 0)); */

	/* Create a process to execute function main() */

	resume (
	   create((void *)main, INITSTK, INITPRIO, "Main process", 20, 0,
           NULL));

	/* Become the Null process (i.e., guarantee that the CPU has	*/
	/*  something to run when no other process is ready to execute)	*/

	while (TRUE) {
	/* do nothing */
	}
}

/*------------------------------------------------------------------------
 *
 * sysinit - intialize all Xinu data structures and devices
 *
 *------------------------------------------------------------------------
 */

static	void	sysinit(void)
{
	int32	i;
	struct	procent	*prptr;		/* ptr to process table entry	*/
	struct	dentry	*devptr;	/* ptr to device table entry	*/
	struct	sentry	*semptr;	/* prr to semaphore table entry	*/
	struct	memblk	*memptr;	/* ptr to memory block		*/


	/* Initialize the time-share process table for lab 3 */
	tstab[0].ts_quantum = 200;
	tstab[0].ts_tqexp = 0;
	tstab[0].ts_slpret = 50;
	tstab[1].ts_quantum = 200;
	tstab[1].ts_tqexp = 0;
	tstab[1].ts_slpret = 50;
	tstab[2].ts_quantum = 200;
	tstab[2].ts_tqexp = 0;
	tstab[2].ts_slpret = 50;
	tstab[3].ts_quantum = 200;
	tstab[3].ts_tqexp = 0;
	tstab[3].ts_slpret = 50;
	tstab[4].ts_quantum = 200;
	tstab[4].ts_tqexp = 0;
	tstab[4].ts_slpret = 50;
	tstab[5].ts_quantum = 200;
	tstab[5].ts_tqexp = 0;
	tstab[5].ts_slpret = 50;
	tstab[6].ts_quantum = 200;
	tstab[6].ts_tqexp = 0;
	tstab[6].ts_slpret = 50;
	tstab[7].ts_quantum = 200;
	tstab[7].ts_tqexp = 0;
	tstab[7].ts_slpret = 50;
	tstab[8].ts_quantum = 200;
	tstab[8].ts_tqexp = 0;
	tstab[8].ts_slpret = 50;
	tstab[9].ts_quantum = 200;
	tstab[9].ts_tqexp = 0;
	tstab[9].ts_slpret = 50;
	tstab[10].ts_quantum = 160;
	tstab[10].ts_tqexp = 0;
	tstab[10].ts_slpret = 51;
	tstab[11].ts_quantum = 160;
	tstab[11].ts_tqexp = 1;
	tstab[11].ts_slpret = 51;
	tstab[12].ts_quantum = 160;
	tstab[12].ts_tqexp = 2;
	tstab[12].ts_slpret = 51;
	tstab[13].ts_quantum = 160;
	tstab[13].ts_tqexp = 3;
	tstab[13].ts_slpret = 51;
	tstab[14].ts_quantum = 160;
	tstab[14].ts_tqexp = 4;
	tstab[14].ts_slpret = 51;
	tstab[15].ts_quantum = 160;
	tstab[15].ts_tqexp = 5;
	tstab[15].ts_slpret = 51;
	tstab[16].ts_quantum = 160;
	tstab[16].ts_tqexp = 6;
	tstab[16].ts_slpret = 51;
	tstab[17].ts_quantum = 160;
	tstab[17].ts_tqexp = 7;
	tstab[17].ts_slpret = 51;
	tstab[18].ts_quantum = 160;
	tstab[18].ts_tqexp = 8;
	tstab[18].ts_slpret = 51;
	tstab[19].ts_quantum = 160;
	tstab[19].ts_tqexp = 9;
	tstab[19].ts_slpret = 51;
	tstab[20].ts_quantum = 120;
	tstab[20].ts_tqexp = 10;
	tstab[20].ts_slpret = 52;
	tstab[21].ts_quantum = 120;
	tstab[21].ts_tqexp = 11;
	tstab[21].ts_slpret = 52;
	tstab[22].ts_quantum = 120;
	tstab[22].ts_tqexp = 12;
	tstab[22].ts_slpret = 52;
	tstab[23].ts_quantum = 120;
	tstab[23].ts_tqexp = 13;
	tstab[23].ts_slpret = 52;
	tstab[24].ts_quantum = 120;
	tstab[24].ts_tqexp = 14;
	tstab[24].ts_slpret = 52;
	tstab[25].ts_quantum = 120;
	tstab[25].ts_tqexp = 15;
	tstab[25].ts_slpret = 52;
	tstab[26].ts_quantum = 120;
	tstab[26].ts_tqexp = 16;
	tstab[26].ts_slpret = 52;
	tstab[27].ts_quantum = 120;
	tstab[27].ts_tqexp = 17;
	tstab[27].ts_slpret = 52;
	tstab[28].ts_quantum = 120;
	tstab[28].ts_tqexp = 18;
	tstab[28].ts_slpret = 52;
	tstab[29].ts_quantum = 120;
	tstab[29].ts_tqexp = 19;
	tstab[29].ts_slpret = 52;
	tstab[30].ts_quantum = 80;
	tstab[30].ts_tqexp = 20;
	tstab[30].ts_slpret = 53;
	tstab[31].ts_quantum = 80;
	tstab[31].ts_tqexp = 21;
	tstab[31].ts_slpret = 53;
	tstab[32].ts_quantum = 80;
	tstab[32].ts_tqexp = 22;
	tstab[32].ts_slpret = 53;
	tstab[33].ts_quantum = 80;
	tstab[33].ts_tqexp = 23;
	tstab[33].ts_slpret = 53;
	tstab[34].ts_quantum = 80;
	tstab[34].ts_tqexp = 24;
	tstab[34].ts_slpret = 53;
	tstab[35].ts_quantum = 80;
	tstab[35].ts_tqexp = 25;
	tstab[35].ts_slpret = 54;
	tstab[36].ts_quantum = 80;
	tstab[36].ts_tqexp = 26;
	tstab[36].ts_slpret = 54;
	tstab[37].ts_quantum = 80;
	tstab[37].ts_tqexp = 27;
	tstab[37].ts_slpret = 54;
	tstab[38].ts_quantum = 80;
	tstab[38].ts_tqexp = 28;
	tstab[38].ts_slpret = 54;
	tstab[39].ts_quantum = 80;
	tstab[39].ts_tqexp = 29;
	tstab[39].ts_slpret = 54;
	tstab[40].ts_quantum = 40;
	tstab[40].ts_tqexp = 30;
	tstab[40].ts_slpret = 55;
	tstab[41].ts_quantum = 40;
	tstab[41].ts_tqexp = 31;
	tstab[41].ts_slpret = 55;
	tstab[42].ts_quantum = 40;
	tstab[42].ts_tqexp = 32;
	tstab[42].ts_slpret = 55;
	tstab[43].ts_quantum = 40;
	tstab[43].ts_tqexp = 33;
	tstab[43].ts_slpret = 55;
	tstab[44].ts_quantum = 40;
	tstab[44].ts_tqexp = 34;
	tstab[44].ts_slpret = 55;
	tstab[45].ts_quantum = 40;
	tstab[45].ts_tqexp = 35;
	tstab[45].ts_slpret = 56;
	tstab[46].ts_quantum = 40;
	tstab[46].ts_tqexp = 36;
	tstab[46].ts_slpret = 57;
	tstab[47].ts_quantum = 40;
	tstab[47].ts_tqexp = 37;
	tstab[47].ts_slpret = 58;
	tstab[48].ts_quantum = 40;
	tstab[48].ts_tqexp = 38;
	tstab[48].ts_slpret = 58;
	tstab[49].ts_quantum = 40;
	tstab[49].ts_tqexp = 39;
	tstab[49].ts_slpret = 58;
	tstab[50].ts_quantum = 40;
	tstab[50].ts_tqexp = 40;
	tstab[50].ts_slpret = 58;
	tstab[51].ts_quantum = 40;
	tstab[51].ts_tqexp = 41;
	tstab[51].ts_slpret = 58;
	tstab[52].ts_quantum = 40;
	tstab[52].ts_tqexp = 42;
	tstab[52].ts_slpret = 58;
	tstab[53].ts_quantum = 40;
	tstab[53].ts_tqexp = 43;
	tstab[53].ts_slpret = 58;
	tstab[54].ts_quantum = 40;
	tstab[54].ts_tqexp = 44;
	tstab[54].ts_slpret = 58;
	tstab[55].ts_quantum = 40;
	tstab[55].ts_tqexp = 45;
	tstab[55].ts_slpret = 58;
	tstab[56].ts_quantum = 40;
	tstab[56].ts_tqexp = 46;
	tstab[56].ts_slpret = 58;
	tstab[57].ts_quantum = 40;
	tstab[57].ts_tqexp = 47;
	tstab[57].ts_slpret = 58;
	tstab[58].ts_quantum = 40;
	tstab[58].ts_tqexp = 48;
	tstab[58].ts_slpret = 58;
	tstab[59].ts_quantum = 20;
	tstab[59].ts_tqexp = 49;
	tstab[59].ts_slpret = 59;
	


	/* Initialize the interrupt vectors */

	initevec();

	/* Initialize system variables */

	/* Count the Null process as the first process in the system */

	prcount = 1;

	/* Scheduling is not currently blocked */

	Defer.ndefers = 0;

	/* Initialize the free memory list */

	/* Note: PC version has to pre-allocate 640K-1024K "hole" */

	maxheap = (void *)MAXADDR;
	minheap = &end;

	memptr = memlist.mnext = (struct memblk *)roundmb(minheap);
	if ((char *)(maxheap+1) > HOLESTART) {
		/* create two blocks that straddle the hole */
		memptr->mnext = (struct memblk *)HOLEEND;
		memptr->mlength = (int) truncmb((unsigned) HOLESTART -
	     		 (unsigned)&end - 4);
		memptr = (struct memblk *) HOLEEND;
		memptr->mnext = (struct memblk *) NULL;
		memptr->mlength = (int) truncmb( (uint32)maxheap - 
				(uint32)HOLEEND - NULLSTK);
	} else {
		/* initialize free memory list to one block */
		memlist.mnext = memptr = (struct memblk *) roundmb(&end);
		memptr->mnext = (struct memblk *) NULL;
		memptr->mlength = (uint32) truncmb((uint32)maxheap -
				(uint32)&end - NULLSTK);
	}

	/* Initialize process table entries free */

	for (i = 0; i < NPROC; i++) {
		prptr = &proctab[i];
		prptr->prstate = PR_FREE;
		prptr->prname[0] = NULLCH;
		prptr->prstkbase = NULL;
		prptr->prprio = 0;
	}

	/* Initialize the Null process entry */

	prptr = &proctab[NULLPROC];
	prptr->prstate = PR_CURR;
	prptr->prprio = 0;
	strncpy(prptr->prname, "prnull", 7);
	prptr->prstkbase = getstk(NULLSTK);
	prptr->prstklen = NULLSTK;
	prptr->prstkptr = 0;
	currpid = NULLPROC;

	/* Initialize semaphores */

	for (i = 0; i < NSEM; i++) {
		semptr = &semtab[i];
		semptr->sstate = S_FREE;
		semptr->scount = 0;
		semptr->squeue = newqueue();
	}

	/* Initialize buffer pools */

	bufinit();
	/* Create a ready list for processes */

	//readylist = newqueue(); old - prelab3
	for (i = 0; i < TSTAB_SIZE; i++) {
		readylist[i] = newqueue();
	}

	/* Initialize the PCI bus */

	pci_init();

	/* Initialize the real time clock */

	clkinit();

	for (i = 0; i < NDEVS; i++) {
		if (! isbaddev(i)) {
			devptr = (struct dentry *) &devtab[i];
			(devptr->dvinit) (devptr);
		}
	}
	return;
}

#define	NBPG		4096		/* number of bytes per page	*/

/*------------------------------------------------------------------------
 * sizmem - return memory size (in pages)
 *------------------------------------------------------------------------
 */
int32	sizmem(void) {

	unsigned char	*ptr, *start, stmp, tmp;
	int32		npages;

        return 4096;	/* 16M for now */
	start = ptr = 0;
	npages = 0;
	stmp = *start;
	while (1) {
		tmp = *ptr;
		*ptr = 0xA5;
		if (*ptr != 0xA5)
			break;
		*ptr = tmp;
		++npages;
		ptr += NBPG;
		if ((uint32)ptr == (uint32)HOLESTART) {	/* skip I/O pages */
			npages += (1024-640)/4;
			ptr = (unsigned char *)HOLEEND;
		}
	}
	return npages;
}

int32	stop(char *s)
{
	kprintf("%s\n", s);
	kprintf("looping... press reset\n");
	while(1)
		/* empty */;
}

int32	delay(int n)
{
	DELAY(n);
	return OK;
}
