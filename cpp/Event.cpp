/*
 * Event.cpp
 *
 *  Created on: Aug 21, 2018
 *      Author: OS1
 */

#include "Event.h"
#include "KernelEv.h"
#include "Context.h"
#include "PCB.h"

Event::Event(IVTNo ivtNo){
	lockFlag=0;
	myEv = new KernelEv(ivtNo);
	lockFlag=1;
	if(explicit_context_switch)
		dispatch();
}

Event::~Event(){
	lockFlag=0;
	delete myEv;
	myEv=0;
	lockFlag=1;
	if(explicit_context_switch)
		dispatch();
}

void Event::wait(){
	myEv->wait();
}

void Event::signal(){
	myEv->signal();
}
