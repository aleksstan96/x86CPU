/*
 * IVTEntry.h
 *
 *  Created on: Aug 21, 2018
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "KernelEv.h"
#include "Event.h"


typedef void interrupt (*pInterrupt)(...);

typedef unsigned char IVTNo;

class IVTEntry{
public:
	IVTEntry(IVTNo ivtNo, pInterrupt newRout);
	~IVTEntry();
	void signal();
	void callOldR();
	static IVTEntry * entryArray[];
	friend class KernelEv;
private:
	KernelEv* myEvent;
	IVTNo ivt;
	pInterrupt oldRout;
};



#endif /* IVTENTRY_H_ */
