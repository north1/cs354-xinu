//Michael North

#include <xinu.h>
#include <stdio.h>

static unsigned long *esp;

void myprogA(){	
	kprintf("\n\r");
	unsigned long *sp;
	asm("movl %esp,esp");
	sp = esp;
	kprintf("Top of runtime stack after myprogA is created:	 		%08X\n\r",
		sp);	
	kprintf("Contents of top of runtime stack after myprogA is created: 	%08X\n\r",
		*sp);
	sleep(1);
	resume(create(myfuncA, 1024, 20, "myfuncA", 2, 1, 1));
	sleep(1);
}

int32 myfuncA(int32 a, int32 b) {
	
	kprintf("\n\r");
	unsigned long *sp;
	asm("movl %esp,esp");
	sp = esp;
	kprintf("Top of runtime stack after myfuncA is called: 			%08X\n\r",
		sp);	
	kprintf("Contents of top of runtime stack after myfuncA is called: 	%08X\n\r",
		*sp);

	kprintf("Locations below stack pointer(0): %08X\n\r", *(sp));
	kprintf("Locations below stack pointer(1): %08X\n\r", *(sp+1));
	kprintf("Locations below stack pointer(2): %08X\n\r", *(sp+2));
	kprintf("Locations below stack pointer(3): %08X\n\r", *(sp+3));
	kprintf("Locations below stack pointer(4): %08X\n\r", *(sp+4));
	kprintf("Locations below stack pointer(5): %08X\n\r", *(sp+5));
	kprintf("Locations below stack pointer(6): %08X\n\r", *(sp+6));
	kprintf("Locations below stack pointer(7): %08X\n\r", *(sp+7));
	kprintf("Locations below stack pointer(8): %08X\n\r", *(sp+8));
	
	return a + b;

}
