/*
 * Thread.h
 *
 *  Created on: Aug 12, 2018
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; //time, x55ms
const Time defaultTimeSlice = 2;
typedef int ID;

class PCB;


class Thread {

public:
	//static ID getRunningId();

	void start();
	void waitToComplete();
	virtual ~Thread();
	static void sleep(Time timeToSleep);

	//ID getId();

protected:

	friend class PCB;
	Thread(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice);
	virtual void run() {}

private:
	PCB* myPCB;
};


void dispatch();





#endif /* THREAD_H_ */
