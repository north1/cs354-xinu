/* mlfq.c - firstready, demlfq */

#include <xinu.h>

/* LAB 3 -- firstready(qid16[]) is firstkey(qid16) for my mlfq */
int32 firstready(qid16 r[]) {
	int i = TSTAB_SIZE;
	while (i >=0) {
		if (!isempty(r[i])) {
			return i;
		}
		i--;
	}
	return EMPTY;

}

/* LAB 3 -- demlfq(qid16[]) is dequeue(qid16) for mlfq */
pid32 demlfq(qid16 r[]) {

	int i = TSTAB_SIZE;
	while (i >=0) {
		if (!isempty(r[i])) {
			return dequeue(r[i]);
		}
		i--;
	}
	return EMPTY;

}
