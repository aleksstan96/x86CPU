/*
 * KernelEv.cpp
 *
 *  Created on: Aug 21, 2018
 *      Author: OS1
 */

#include "KernelEv.h"
#include "SCHEDULE.H"
#include "Context.h"


KernelEv::KernelEv(IVTNo ivtNo):ivt(ivtNo), value(0), blocked(0), owner((PCB*)PCB::running){
if(IVTEntry::entryArray[ivt]!=0 && IVTEntry::entryArray[ivt]->myEvent==0)
	IVTEntry::entryArray[ivt]->myEvent=this;
}

KernelEv::~KernelEv(){
	if(blocked!=0) {
		lockFlag=0;
		deblock();
		lockFlag=1;
	}
	delete IVTEntry::entryArray[ivt];
}

void KernelEv::wait(){
	if(PCB::running==owner){
		lockFlag=0;
		if(value==0) block();
		else value=0;
		lockFlag=1;
	}
}

void KernelEv::signal(){
	lockFlag=0;
	if(blocked==0) value=1;
	else deblock();
	lockFlag=1;
}

void KernelEv::block(){
	PCB::running->state=BLOCKED;
	blocked=(PCB*)PCB::running;
	lockFlag=1;
	dispatch();
}

void KernelEv::deblock(){
	blocked->state=READY;
	Scheduler::put(blocked);
	blocked=0;
}
