/*
 MLQClass.h
*/

#ifndef THREADS_MLQCLASS_H_
#define THREADS_MLQCLASS_H_

class MLQ_Class {

	public:
	MLQ_Class();
	virtual ~MLQ_Class();

	void ReadyToRun(Thread* thread);	// Thread can be dispatched.
	    Thread* FindNextToRun();		// Dequeue first thread on the ready
						// list, if any, and return thread.
	    void Run(Thread* nextThread);	// Cause nextThread to start running
	    void Print();			// Print contents of ready list

	private:
	    List *sjfReadyList; // First List
	    List *pqReadyList; // Second List
	    int sTime; // it holds the time that the thread runs
	    int eTime; // it holds the time that the thread is Over;

};

#endif /* THREADS_MLQCLASS_H_ */
