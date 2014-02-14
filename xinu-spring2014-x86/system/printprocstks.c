#include <xinu.h>

void printprocstk(pid32);

void printprocstks() {
	//spawn process myprogA()
	sleep(1);
	int progID = create(myprogA, 1024, 20, "myprogA", 0);
	resume(progID);
	sleep(1);

	//spawn process myfuncA()
	sleep(1);
	int funcID = create(myfuncA, 1024, 20, "myfuncA", 2, 1, 1);
	resume(funcID);
	sleep(1);

	//print the process data
	sleep(1);
	printprocstk(progID);
	sleep(1);
	printprocstk(funcID);
	sleep(1);
}


void printprocstk(pid32 pid) {
	struct procent ent = proctab[pid];
	kprintf("\n\n");
	kprintf("Proc [%s]. Pid=%d\n", ent.prname, pid);
	kprintf("Stack:	Base = %08X\n", (ent.prstkbase));
	kprintf("	Len = %d\n", ent.prstklen);
	kprintf("	Limit = %08X\n", ((ent.prstkbase))+(ent.prstklen)-1);
	kprintf("	StkPtr = %08X\n", (ent.prstkptr));
	kprintf("\n");

}
