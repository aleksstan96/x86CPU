/*
 * PCB.cpp
 *
 *  Created on: Aug 12, 2018
 *      Author: OS1
 */
#include <STDLIB.H>
#include "PCB.h"
#include "SCHEDULE.h"
#include "List.h"
#include "SleepL.h"
#include "Context.h"
#include <dos.h>
#include <iostream.h>
#include "SpecThr.h"


//List* PCB::allPCBs = new List();
SleepList* PCB::sleepPCBs = new SleepList();

volatile PCB* PCB::running = 0;
PCB* PCB::main = 0;
PCB* PCB::idle = 0;

//ID PCB::lastID = 0;

/*
ID PCB::getRunningId()
{
	if (PCB::running != 0) return PCB::running->id;
	return -1;
}
*/

PCB::PCB(Thread* mee, StackSize sz, Time t): me(mee), sp(0), ss(0), bp(0), stack(0), state(NEW){


	//id=++lastID;

	if(t<0) timeSlice=0;
	timeSlice=t;

	//PCB::allPCBs->add(this);

	waitingForMe = new List();

	//StackSize st = sz;


	//create stack

	if(sz!=0){  //not main
		if(sz>maxStackSize) sz = maxStackSize;
		if(sz<0) sz = defaultStackSize;
		sz/=sizeof(unsigned);

		stack = new unsigned[sz];

		stack[sz-1] = 0x200;
#ifndef BCC_BLOCK_IGNORE
		stack[sz-2]=FP_SEG(PCB::wrapper);  //FP_SEG(&(PCB::wrapper)) ili ovako??
		stack[sz-3] = FP_OFF(PCB::wrapper);
		ss = FP_SEG(stack + sz - 12);
	    sp = FP_OFF(stack + sz - 12);
#endif
		bp = sp;

	}
}

void PCB::start(){

	if(state==NEW){
		state=READY;
		Scheduler::put(this);
	}
}

PCB::~PCB(){
	//allPCBs->del(this);
	if (stack!=0) {
		delete [] stack;
	}
	stack=0;
	if(waitingForMe!=0){
		delete waitingForMe;
	}
	waitingForMe=0;

}


void PCB::waitToComplete(){
	if(this!=0 && this!=running && this->state!=FINISHED && this!=idle && this->state!=IDLE && this->state!=NEW){
		lockFlag=0;
		running->state=BLOCKED;
		this->waitingForMe->add((PCB*)PCB::running);
		lockFlag=1;
		dispatch();
	}
}

void PCB::wrapper(){
	running->me->run();
	lockFlag=0;
		running->state= FINISHED;
		//svi koji su cekali da zavrsim mogu da nastave:
		if(running->waitingForMe->num>0){  // mozda i nije potrebno jer ima while(curr)
		List::Elem* curr = running->waitingForMe->first, *next=0;
		while(curr){
			next = curr->next;
			curr->pcb->state = READY;
			Scheduler::put(curr->pcb);
			running->waitingForMe->del(curr->pcb);
		curr=next;
	}
	}
lockFlag=1;
	dispatch();
}

void PCB::sleep(Time timeToSleep){
	if(timeToSleep>0 && running->state!=IDLE){
		lockFlag=0;
		running->state=BLOCKED;
		//printf("Sleep thread %d\n", running->me->getId());
		sleepPCBs->add((PCB*)running, timeToSleep);
		lockFlag=1;
		dispatch();
	}
}

void PCB::createIdle(){
	if(idle) return;
	Idle* i = new Idle();
	idle = i->myPCB;
	idle->state=IDLE;
}

void PCB::deleteIdle(){
	if (idle){
		delete idle;
		idle = 0;
	}
}

void PCB::createMain(){
	if (main) return;
	Main* m = new Main();
	main = m->myPCB;
	main->state = READY;
	running = main;
}

void PCB::deleteMain(){
	if(main){
		delete main;
		main=0;
	}

	//deleteMain se poslednje izvrsava pa brise sve
	if(PCB::running)
		PCB::running = 0;
	PCB::sleepPCBs=0;

	//delete PCB::allPCBs;
	//allPCBs=0;
}

