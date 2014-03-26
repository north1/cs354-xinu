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

	/* LAB 3 -- */
	//kprintf("proctab[0].tqexp: %d", tstab[0].ts_tqexp);
	//cpuintensive();
	resume(create(cpuintensive, 1024, 20, "cpu0", 0));
	resume(create(cpuintensive, 1024, 20, "cpu1", 0));
	resume(create(cpuintensive, 1024, 20, "cpu2", 0));
	resume(create(cpuintensive, 1024, 20, "cpu3", 0));
	
	resume(create(iointensive, 1024, 20, "io0", 0));
	resume(create(iointensive, 1024, 20, "io1", 0));
	resume(create(iointensive, 1024, 20, "io2", 0));
	resume(create(iointensive, 1024, 20, "io3", 0));
	/* LAB 3 -- */
	
	
	//shell stuff
	//while (1);
	sleep(1);
	resume(create(shell, 8192, 50, "shell", 1, CONSOLE));
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
