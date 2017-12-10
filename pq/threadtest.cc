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
int testnum = 1;

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
    
    for (num = 0; num < 5; num++) {
	printf("*** thread %d looped %d times\n", which, num);
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

    //initializing the thread priority
    Thread *thread_1 = new Thread("forked thread" ,100);
    thread_1->Fork(SimpleThread , 1);
    Thread *thread_2 = new Thread("forked thread" ,2);
    thread_2->Fork(SimpleThread , 2);
    Thread *thread_3 = new Thread("forked thread" ,300);
    thread_3->Fork(SimpleThread , 3);
    Thread *thread_4 = new Thread("forked thread" ,4);
    thread_4->Fork(SimpleThread , 4);
    Thread *thread_5 = new Thread("forked thread" ,500);
    thread_5->Fork(SimpleThread , 5);
    Thread *thread_6 = new Thread("forked thread" ,6);
    thread_6->Fork(SimpleThread , 6);
    Thread *thread_7 = new Thread("forked thread" ,700);
    thread_7->Fork(SimpleThread , 7);
    //SimpleThread(0);
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
    default:
	printf("No test specified.\n");
	break;
    }
}

