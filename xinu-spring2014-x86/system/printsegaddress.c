///Michael North
//Lab1 - assignment 2
//
//


#include <xinu.h>
#include <stdio.h>

//extern char etext, edata, end;

void printsegaddress() {	
	kprintf("\nProgram addresses:\n\r");	
	kprintf("	4 Bytes before end of text:	%08X\n\r", &etext-1);
	kprintf("	4 Bytes after end of text:	%08X\n\r", &etext);
	kprintf("\n\n\r");
	kprintf("	4 Bytes before end of data:	%08X\n\r", &edata-1);
	kprintf("	4 Bytes after end of data:	%08X\n\r", &edata);
	kprintf("\n\n\r");
	kprintf("	4 Bytes before end of bss:	%08X\n\r", &end-1);
	kprintf("	4 Bytes after end of bss:	%08X\n\r", &end);
}
