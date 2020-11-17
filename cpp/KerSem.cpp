/*
 * KerSem.cpp
 *
 *  Created on: Aug 16, 2018
 *      Author: OS1
 */
#include "KerSem.h"
#include "Context.h"
#include "SemList.h"
#include "List.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include <STDIO.H>

//SemList* KernelSem::allSem = 0;

KernelSem::KernelSem(int init): value(init){
	//allSem->add(this);
	blocked = new List();
}

KernelSem::~KernelSem(){
	//deblokiranje niti koje su blokirane na datom semaforu
	if(blocked){
		while(blocked->first){
			deblock(); //postavlja na ready, stavlja u scheduler, brise, pomera first, samnjuje num
		}
	}
	delete blocked; //nema potrebe ali za svaki slucaj
	blocked=0;

	//allSem->del(this);
}

int KernelSem::wait(int toBlock){
	lockFlag=0;
	int ret=0;
	if(!toBlock && value<=0)
		ret= -1;
	else
		if(--value<0){
			ret=1;
			block();
		}
	lockFlag=1;
	return ret;
}

void KernelSem::signal(){
	lockFlag=0;
	if(value++<0) deblock();
	lockFlag=1;
}

void KernelSem::block(){
	PCB::running->state = BLOCKED;
	blocked->add((PCB*)PCB::running);
	lockFlag=1;
	dispatch();
}

void KernelSem::deblock(){
	if(blocked && blocked->num>0){
		PCB* pcb = blocked->first->pcb;
		pcb->state = READY;
		Scheduler::put(pcb);
		blocked->del(pcb);

	}
}
