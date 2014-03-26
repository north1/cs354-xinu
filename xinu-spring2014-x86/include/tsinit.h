//Michael North
//Lab 2

#define TSTAB_SIZE 60

struct ts_ent {
	int ts_tqexp;         // new priority: CPU-intensive (time quantum expired)
	int ts_slpret;        // new priority: I/O-intensive (sleep return)
	int ts_quantum;       // new time slice
};

extern struct ts_ent tstab[];

/* MLFQ function prototypes */
int32 firstready(qid16[]);
pid32 demlfq(qid16[]);

/* testing prototypes */
extern void cpuintensive();
extern void iointensive();

