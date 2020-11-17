/*
 * List.cpp
 *
 *  Created on: Aug 12, 2018
 *      Author: OS1
 */

#include <stdio.h>
#include <iostream.h>
#include "PCB.h"
#include "List.h"
#include "Context.h"



List::List(){
	first=last=0;
	num=0;
}


List::~List(){
	while (first)
		{
			Elem* old=first;
			first=first->next;
			delete old;
			num--;
		}
	first=last=0;
}

void List::add(PCB* pcb){

	Elem* newEl = new Elem(pcb);


	if(first==0) first=newEl;  //prazna lista
	else last->next= newEl;
	last=newEl;
	num++;

}

void List::del(PCB* pcb){
	Elem* prev=0, *curr=first;
	while(curr&&(curr->pcb!=pcb)){
		prev=curr;
		curr=curr->next;
	}
	if(curr==0) return;
		if(prev){
			prev->next=curr->next;
		    if(last==curr) last=prev;
		}else{ //brisanje prvog u listi
			first=first->next;
			if(first==0) last=0;  //ako je jedini element u listi
		}
//		asm cli;
		delete curr;
	//	asm sti;
		num--;
}






