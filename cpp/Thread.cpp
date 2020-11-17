/*
 * Thread.cpp
 *
 *  Created on: Aug 12, 2018
 *      Author: OS1
 */

#include <iostream.h>
#include <stdio.h>
#include "Thread.h"
#include "Context.h"
#include "PCB.h"

/*
 ID Thread:: getRunningId()
{
	 //lockFlag=0;
	 ID id= PCB::getRunningId();
	// lockFlag=1;

	 return id;
}
*/

Thread::Thread(StackSize stackSize, Time timeSlice){
lockFlag=0;
	myPCB = new PCB(this, stackSize, timeSlice);
lockFlag=1;
if(explicit_context_switch)
		dispatch();
}

/*
ID Thread::getId(){
	//lockFlag=0;
	return myPCB->getId();
	//lockFlag=1;
}
*/

void Thread::start(){
	myPCB->start();
}

void Thread::waitToComplete(){
	myPCB->waitToComplete();
}

Thread::~Thread(){

	waitToComplete();
	lockFlag=0;
	delete myPCB;
	myPCB = 0;
	lockFlag=1;
	if(explicit_context_switch)
			dispatch();

}

void Thread::sleep(Time timeToSleep){
	PCB::sleep(timeToSleep);
}

