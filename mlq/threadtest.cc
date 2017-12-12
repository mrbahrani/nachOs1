// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"

// testnum is set in main.cc
int testnum = 2;

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < 100; num++) {
    	for (int i =0;i<2000;i++);
	printf("*** thread %d looped %d times in %d nsecs\n", which, num,currentThread->getRunningTime());
        currentThread->Yield();
    }
}

void
SimpleThread2(int which)
{
    int num;

    for (num = 0; num < 100; num++) {
    	for (int i =0;i<8000;i++);
    	printf("*** thread %d looped %d times in %d secs\n", which, num,currentThread->getRunningTime());
        currentThread->Yield();
    }
}
void
SimpleThread3(int which)
{
    int num;

    for (num = 0; num < 100; num++) {
    	for (int i =0;i<16000;i++);
    	printf("*** thread %d looped %d times in %d nsecs\n", which, num,currentThread->getRunningTime());
        currentThread->Yield();
    }
}
//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void
ThreadTest1()
{
    DEBUG('t', "Entering ThreadTest1");

    Thread *t = new Thread("forked thread");

    t->Fork(SimpleThread, 1,2);
    SimpleThread(0);
}

void
ThreadTest2()
{
    DEBUG('t', "Entering ThreadTest1");

    Thread *t1 = new Thread("first thread");
    Thread *t2 = new Thread("second thread");
    Thread *t3 = new Thread("third thread");
    Thread *t4 = new Thread("fourth thread");


    t1->Fork(SimpleThread3,1,10);
    t2->Fork(SimpleThread, 2,4);
    t3->Fork(SimpleThread, 3, 4);
    t4->Fork(SimpleThread3, 4,10);


}

//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    switch (testnum) {
    case 1:
	ThreadTest1();
	break;
    case 2:
    ThreadTest2();
	break;
    default:
	printf("No test specified.\n");
	break;
    }
}

