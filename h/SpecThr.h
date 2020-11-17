/*
 * SpecThr.h
 *
 *  Created on: Aug 12, 2018
 *      Author: OS1
 */

#ifndef SPECTHR_H_
#define SPECTHR_H_
#include <STDIO.H>
#include "Thread.h"
#include "PCB.h"


class Idle : public Thread{

public:
	Idle(): Thread(defaultStackSize, 10) {}
protected:
	void run();
};

class Main: public Thread{
public:
	Main(): Thread(0, defaultTimeSlice) {}
};

#endif /* SPECTHR_H_ */
