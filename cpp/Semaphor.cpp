/*
 * Semaphor.cpp
 *
 *  Created on: Aug 16, 2018
 *      Author: OS1
 */
#include "Semaphor.h"
#include "PCB.h"
#include"KerSem.h"
#include "Context.h"

Semaphore::Semaphore(int init){
	lockFlag=0;
	myImpl = new KernelSem(init);
	lockFlag=1;
	if(explicit_context_switch)
			dispatch();
}

Semaphore::~Semaphore(){
	lockFlag=0;
	delete myImpl;
	lockFlag=1;
	if(explicit_context_switch)
				dispatch();
}

int Semaphore::wait(int toBlock){
	int ret = myImpl->wait(toBlock);
	return ret;
}

void Semaphore:: signal()
{
	myImpl->signal();
}

int Semaphore::val() const{
	return myImpl->val();
}

