/*
 * SemList.h
 *
 *  Created on: Aug 16, 2018
 *      Author: OS1
 */

#ifndef SEMLIST_H_
#define SEMLIST_H_

class KernelSem;

class SemList{
public:
	struct Elem{
		KernelSem* sem;
		Elem* next;
		Elem(KernelSem* semm){
			sem=semm;
			next=0;
		}
	};

	Elem *first, *last;

	SemList();
	~SemList();

	void add(KernelSem*);
	void del(KernelSem*);

};



#endif /* SEMLIST_H_ */
