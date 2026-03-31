#include "types.h"
#include "proc.h"
#include "defs.h"
#include "scheduler.h"

void scheduler(void) {
    struct proc *p;

    for (;;) {
        for (p = proc; p < &proc[NPROC]; p++) {

            if (p->state != RUNNABLE)
                continue;

            p->state = RUNNING;
            mycpu()->proc = p;

            swtch(&mycpu()->context, &p->context);

            mycpu()->proc = 0;
        }
    }
}
void yield(void) {
    struct proc *p = myproc();

    p->state = RUNNABLE;
    swtch(&p->context, &mycpu()->context);
}