/*
 * SleepList.h
 *
 *  Created on: Aug 12, 2018
 *      Author: OS1
 */

#ifndef SLEEPL_H_
#define SLEEPL_H_
#include "Thread.h"

class PCB;

class SleepList{
public:
	struct Elem{
		PCB* pcb;
		Time t;
		Elem* next;
		Elem(PCB* pcbb, Time tt){
			pcb=pcbb;
			t=tt;
			next=0;
		}
	};

	Elem* first;

	void add(PCB*, Time);
	SleepList();
	~SleepList();

};



#endif /* SLEEPL_H_ */
