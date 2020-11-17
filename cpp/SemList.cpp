/*
 * SemList.cpp
 *
 *  Created on: Aug 16, 2018
 *      Author: OS1
 */
#include "SemList.h"

SemList::SemList(){
	first=last=0;
}

SemList::~SemList(){
	while(first){
		Elem* old= first;
		first=first->next;
		delete old;
	}
}

void SemList::add(KernelSem* ksem){

		Elem* newEl = new Elem(ksem);

		if(first==0) first=newEl;  //prazna lista
		else last->next= newEl;
		last=newEl;
}

void SemList::del(KernelSem* ksem){
	Elem* prev=0, *curr=first;
		while(curr&&(curr->sem=ksem)){
			prev=curr;
			curr=curr->next;
		}
		if(curr){
			if(prev){
				prev->next=curr->next;
			    if(last==curr) last=prev;
			}else{ //brisanje prvog u listi
				first=first->next;
				if(first==0) last=0;  //ako je jedini element u listi
			}
			delete curr;
		}
}



