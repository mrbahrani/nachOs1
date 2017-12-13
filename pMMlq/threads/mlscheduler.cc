//
// Created by alibi on 12/12/17.
//

#include <sys/time.h>
#include "mlscheduler.h"
#include "system.h"
#ifndef TG
#define TG
unsigned long
time_generator()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    unsigned long timestamp;
    timestamp = 1000*tv.tv_sec + tv.tv_usec;
    return timestamp;
}

#endif
MLScheduler::MLScheduler() {
    sjfReadyList = new List;
    pqReadyList = new List;

}

void
MLScheduler::ReadyToRun (Thread *thread)
{
    DEBUG('t', "Putting thread %s on ready list.\n", thread->getName());

    thread->setStatus(READY);
    if (!thread->timeExcess())
    {printf("*** the thread with %d runtime to sjflist ***\n", thread->getRunningTime());
        sjfReadyList->SortedInsert((void *)thread,thread->getRunningTime());}
    else {
        printf("*** the thread with %d runtime to pqlist ***\n", thread->getRunningTime());
        pqReadyList->SortedInsert((void *)thread,thread->getPriority());}
}

Thread *
MLScheduler::FindNextToRun () {
    if (!sjfReadyList->IsEmpty()) {
        printf("** The sjflist is empty **\n");
        if (!sjfReadyList->IsEmpty()) return (Thread *) sjfReadyList->Remove();
        else return (Thread *) pqReadyList->Remove();
    }



}



void
MLScheduler ::Run(Thread* nextThread)
{
    printf("RUn function\n");
    Thread *oldThread = currentThread;

#ifdef USER_PROGRAM			// ignore until running user programs
    if (currentThread->space != NULL) {	// if this thread is a user program,
        currentThread->SaveUserState(); // save the user's CPU registers
	currentThread->space->SaveState();
    }
#endif

    oldThread->CheckOverflow();		    // check if the old thread
    // had an undetected stack overflow
    eTime = time_generator();	//end time of the oldThread
    if (currentThread != NULL)
        currentThread->setRunningTime(eTime-sTime);
    currentThread = nextThread;// switch to the next thread
    currentThread->setStatus(RUNNING);// nextThread is now running
    sTime = time_generator();	//start time of the nextThread
    DEBUG('t', "Switching from thread \"%s\" to thread \"%s\"\n",
          oldThread->getName(), nextThread->getName());

    // This is a machine-dependent assembly language routine defined
    // in switch.s.  You may have to think
    // a bit to figure out what happens after this, both from the point
    // of view of the thread and from the perspective of the "outside world".

    SWITCH(oldThread, nextThread);

    DEBUG('t', "Now in thread \"%s\"\n", currentThread->getName());

    // If the old thread gave up the processor because it was finishing,
    // we need to delete its carcass.  Note we cannot delete the thread
    // before now (for example, in Thread::Finish()), because up to this
    // point, we were still running on the old thread's stack!
    if (threadToBeDestroyed != NULL) {

        delete threadToBeDestroyed;
        threadToBeDestroyed = NULL;
    }

#ifdef USER_PROGRAM
    if (currentThread->space != NULL) {		// if there is an address space
        currentThread->RestoreUserState();     // to restore, do it.
	currentThread->space->RestoreState();
    }
#endif
}


