//
// Created by alibi on 12/12/17.
//

#ifndef CODE_MLSCHEDULER_H
#define CODE_MLSCHEDULER_H

#include "scheduler.h"

class MLScheduler : public Scheduler
{
public:
    MLScheduler();
    Thread* FindNextToRun();
    void ReadyToRun(Thread* thread);
    void Run(Thread* nextThread);

private:
    List *sjfReadyList; // First List
    List *pqReadyList; // Second List
    int sTime; // it holds the time that the thread runs
    int eTime; // it holds the time that the thread is Over;
};
#endif //CODE_MLSCHEDULER_H
