# nachOs1
This repository contains the source code of the first project of nachos for the "Operating Systems" course of IUST in fall semester of 2017.  


_________________________________
Changes for Priority Queue :

Classes which changed =>

1) threads.h :
	- int priority; // this attribute defined as the thread’s priority
	- the constructor was changed due to set the priority when initialing thread. “ Thread(char* debugName , int prio); // initialize a Thread “
	- “ int get_priority(){ return (priority);};	//it gives us the priority ” were added.
_________________________________
2) threads.cc :
	- the constructor was changed due to set the priority when initialing thread. “priority = prio;  //set the priority” =>added to the body of constructor.
_________________________________
3) scheduler.cc :
ReadyToRun() : // instead of “readyList->Append((void*)thread); ” we used “readyList->SortedInsert((void*)thread,prio); “ NOTE : ( “prio” is the thread’s priority.)
_________________________________
4) system.cc :
	- a little change in “void initialize ()” => currentThread = new Thread("main", 900);  //set the main thread priority
_________________________________
5) threadtest.cc :
	- initializing threads in “void ThreadTest1()” => {
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
}

//edited by Fatemeh_TJZ
