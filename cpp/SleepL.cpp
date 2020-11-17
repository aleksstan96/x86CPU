/*
 * SleepL.cpp
 *
 *  Created on: Aug 12, 2018
 *      Author: OS1
 */

#include "SleepL.h"
#include "Thread.h"
#include <stdio.h>
#include <iostream.h>
#include "PCB.h"
#include "Context.h"

SleepList::SleepList(){
	first=0;
}

SleepList::~SleepList(){
	Elem * prev = 0;
		while(first){
			prev=first;
			first= first->next;
			delete prev;
		}
		first=0;
}

void SleepList::add(PCB* pcbb, Time tt){
	//asm pushf;
	asm cli;
	Elem* newEl = new Elem(pcbb, tt);
	if(newEl==0) return;

	if(first==0){  //u praznu listu
		first=newEl;
	}else{

	if(newEl->t<=first->t){  //ako je vreme krace od vremena u prvom elementu (na pocetak)
		newEl->next=first;
		first->t-=newEl->t;
		first=newEl;
	}else {
		Elem* prev=0, *curr=first;
		Time sum=0;
		while(curr && (sum+curr->t)<=newEl->t){
			sum+=curr->t;
			prev=curr;
			curr=curr->next;
		}

		Time newTime = newEl->t - sum;
		newEl->t = newTime;

		if(curr){         //u sredinu
			prev->next= newEl;
			newEl->next=curr;
			if(newTime!=0) {
				curr->t -= newTime;
			}
		} else{         //na kraj
			prev->next = newEl;
		}

	}
	}	 //asm popf;
	asm sti;
}







