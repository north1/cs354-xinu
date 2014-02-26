#include <xinu.h>

#define OUTERB 10 //dictated by lab
#define INNERB 1000000

void printloop(char val) {
	int outerc;
	for (outerc = 0; outerc < OUTERB; outerc++) {
		int innerc;
		kputc(val);
		//for (innerc = 0; innerc < INNERB; innerc++) { /* waste time */ }
		sleepms(0);
	}
}
