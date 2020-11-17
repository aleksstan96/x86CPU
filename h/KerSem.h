/*
 * KerSem.h
 *
 *  Created on: Aug 16, 2018
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_

class SemList;
class List;

class KernelSem{
public:
	KernelSem(int);
	~KernelSem();

	int wait(int toBlock);
	void signal();

	int val() const { return value;}

protected:
	void block();
	void deblock();

private:
	int value;

	//static SemList* allSem;

	List* blocked;
};



#endif /* KERSEM_H_ */
