/*
 * KernelEv.h
 *
 *  Created on: Aug 21, 2018
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_

#include "Event.h"
#include "IVTEntry.h"
#include "PCB.h"

typedef unsigned char IVTNo;

class KernelEv{
public:
	KernelEv(IVTNo ivtNo);
	~KernelEv();
	void wait();
	void signal();

protected:

	void block();
	void deblock();

private:
	IVTNo ivt;
	int value;
	PCB* blocked;
	PCB* owner;
};



#endif /* KERNELEV_H_ */
