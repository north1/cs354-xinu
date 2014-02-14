#include <xinu.h>

void takeUpSpace(char);

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

void rogueB() {
	//print something and give up control
	putc(CONSOLE, 'B');
	sleepms(20);

	//try to fill up the stack
	takeUpSpace((char)0);

	//give up control again
	sleepms(20);
}

void takeUpSpace(char foo) {
	char bar = foo++;
	if (foo < 256) {
		takeUpSpace(bar);
	}
	else { return; }	
}
