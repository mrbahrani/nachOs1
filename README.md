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

_________________________________
** Changes for Multi Level Queue **
Let’s have a little definition about MLQ : we have 2 queues , all threads will be added to the first queue and the second queue is empty at this time.now we will check the time that each thread will take to run and finish.According to this time , threads with greater runtime will be removed from the first queue and added to the second queue . Program starts running the threads in the 1st queue using “the shortest Job first” and when the 1st queue gets empty , we will switch to the second one and program will run these threads using “ priority queue “ algorithm.

Classes which changed =>

1) threadtest.cc
2) threads.cc
3) threads.h :
	these functions added : {
	int getPriority(){return (priority);}
	
	void setPriority(int prio){priority=prio;}
	
	unsigned long int getRunningTime(){return (runningTime);}
	
	void setRunningTime(unsigned long int getR) {runningTime= getR;}
	
	bool timeExcess(); //a function that determine the maximum time threads should take to stay in the 1st queue 
}
4)scheduler.h :
	List *sjfReadyList; // First List 
    	List *pqReadyList; // Second List 
    	int sTime; // it holds the time that the thread runs 
    	int eTime; // it holds the time that the thread is Over;

5)scheduler.cc :
	unsigned long time_generator(){ //gives us the time in nano secs
    		struct timeval tv; 
    		gettimeofday(&tv,NULL); 
    		unsigned long timestamp; 
    		timestamp = 1000*tv.tv_sec + tv.tv_usec; 
    		return timestamp; 
	}
	
	Scheduler::Scheduler(){  //constructor changed
  		sjfReadyList = new List; 
    		pqReadyList = new List; 
	}
	void Scheduler::ReadyToRun (Thread *thread) { 
    		DEBUG('t', "Putting thread %s on ready list.\n", thread->getName()); 
		thread->setStatus(READY); 
    		if (!thread->timeExcess()){ 
      			sjfReadyList->SortedInsert((void *)thread,thread->getRunningTime());} 
    		else{
			pqReadyList->SortedInsert((void *)thread,thread->getPriority());} 
	}
	
	
//edited by hanie salman taheri
