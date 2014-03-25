/* mlfq.c - firstready, demlfq */

#include <xinu.h>

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
