#include <xinu.h>

void someprogA() {
	putc(CONSOLE, 'A');

	somefuncA('a');
	
	putc(CONSOLE, 'A');
}


int somefuncA(char inpChar) {
	//sleep for 10 times the time slice size (2)
	sleepms(20);

	//print the arg
	putc(CONSOLE, inpChar);

	return 1;
}


void someprogB() {
	putc(CONSOLE, 'B');

	somefuncA('b');
	
	putc(CONSOLE, 'B');
}
