/*
 * IVTEntry.cpp
 *
 *  Created on: Aug 21, 2018
 *      Author: OS1
 */
#include <dos.h>
#include "IVTEntry.h"
#include "Context.h"
#include "KernelEv.h"

IVTEntry* IVTEntry::entryArray[256];

IVTEntry::IVTEntry(IVTNo ivtNo, pInterrupt newRout): ivt(ivtNo), myEvent(0), oldRout(0){

	lockFlag=0;
#ifndef BCC_BLOCK_IGNORE
	oldRout = getvect(ivt);
	setvect(ivt, newRout);
#endif
	entryArray[ivtNo]=this;
	lockFlag=1;
	if(explicit_context_switch==1)
		dispatch();

}

IVTEntry::~IVTEntry(){
	lockFlag=0;
#ifndef BCC_BLOCK_IGNORE
	setvect(ivt,oldRout);
#endif
	myEvent=0;
	oldRout=0;
	entryArray[ivt]=0;
	lockFlag=1;
	if(explicit_context_switch==1)
		dispatch();
}

void IVTEntry::callOldR(){
	if(oldRout!=0)
		(*oldRout)();
}

void IVTEntry::signal(){
	if(myEvent!=0)
		myEvent->signal();
}

