/*
 * PCB.h
 *
 *  Created on: Aug 12, 2018
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "Thread.h"

class List;
class SleepList;
class Idle;


const StackSize maxStackSize = 65535;
enum State {NEW, BLOCKED, FINISHED, IDLE, READY};


class PCB{
public:
	//static ID getRunningId();


	PCB(Thread*, StackSize, Time);

	void start();

	static void wrapper();

	void waitToComplete();

	~PCB();

	static void sleep(Time timeToSleep);

	//ID getId() const { return id; };  //inspektor

	friend void interrupt timer();

	static void createMain();
	static void deleteMain();
	static void createIdle();
	static void deleteIdle();

	static volatile PCB* running;  // ako bude zezalo stavi u public

	State state;

private:

	unsigned* stack;

	unsigned sp;
	unsigned ss;
	unsigned bp;


	Thread* me;

	Time timeSlice;


	 //volatile?
	static PCB* main;
	static PCB* idle;

	//static List* allPCBs;
	List* waitingForMe;
	static SleepList* sleepPCBs;

	//static ID lastID;
	//ID id;



};




#endif /* PCB_H_ */
