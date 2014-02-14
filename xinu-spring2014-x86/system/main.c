/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

static unsigned long *esp;


int main(int argc, char **argv)
{
	uint32 retval;

	/*
	kprintf("main: calling getlocalip\n");
	retval = getlocalip();

	if (retval == SYSERR) {
		kprintf("I'm here to stop!\n");
	} else {
		kprintf("I'm here to continue!\n");
		kprintf("\n\n###########################################################\n\n");
		kprintf("IP address is %d.%d.%d.%d   %08x\n\r",
			(retval>>24)&0xff, (retval>>16)&0xff, (retval>>8)&0xff,
		 	retval&0xff,retval);

	    	kprintf("Subnet mask is %d.%d.%d.%d and router is %d.%d.%d.%d\n\r",
			(NetData.addrmask>>24)&0xff, (NetData.addrmask>>16)&0xff,
			(NetData.addrmask>> 8)&0xff,  NetData.addrmask&0xff,
			(NetData.routeraddr>>24)&0xff, (NetData.routeraddr>>16)&0xff,
			(NetData.routeraddr>> 8)&0xff, NetData.routeraddr&0xff);
	}
	*/

	//shell stuff
	//while (1);
	sleep(1);
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
	sleep(1);

	//3.1
	kprintf("\n\n\nLab 1 - Assignment 3.1\n");
	kprintf("%x : %x", 8, host2netl_asm(8));
	
	//3.2
	kprintf("\n\n\nLab 1 - Assignment 3.2\n");
	printsegaddress();

	//3.3
	kprintf("\n\n\nLab 1 - Assignment 3.3\n");
	unsigned long *sp;
	asm("movl %esp,esp");
	sp = esp;
	kprintf("Top of runtime stack before myprogA is created: 		%08X\n\r",
		sp);	
	kprintf("Contents of top of runtime stack before myprogA is created: 	%08X\n\r",
		*sp);
	//kprintf("stack trace for comparison:\n\r");
	//stacktrace(getpid());
	sleep(1);
	myprogA();
	sleep(1);

	//3.4
	kprintf("\n\n\nLab 1 - Assignment 3.4\n");
	sleep(1);
	printprocstks();
	sleep(1);


	//4
	kprintf("\n\n\nLab 1 - Assignment 4\n");
	sleep(1);
	resume(create(someprogB, 1024, 20, "someprogB", 0));
	resume(create(someprogA, 1024, 20, "someprogA", 0));
	sleep(1);

	/* Wait for shell to exit and recreate it */
	recvclr();
	while (TRUE) {
		retval = receive();
		kprintf("\n\n\rMain process recreating shell\n\n\r");
		resume(create(shell, 4096, 1, "shell", 1, CONSOLE));
	}

	return OK;
}
