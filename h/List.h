/*
 * List.h
 *
 *  Created on: Aug 12, 2018
 *      Author: OS1
 */

#ifndef LIST_H_
#define LIST_H_

class PCB;

typedef int ID;
class List{
public:

	struct Elem{
		PCB* pcb;
		Elem* next;
		Elem(PCB* pcbb){
			pcb=pcbb;
			next=0;
		}
	};

	Elem* first, *last;
	int num;
	List();
	~List();

	void add(PCB*);
	void del(PCB*);



};




#endif /* LIST_H_ */
