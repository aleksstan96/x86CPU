/*
 * Context.cpp
 *
 *  Created on: Aug 12, 2018
 *      Author: OS1
 */
#include <iostream.h>
#include <stdio.h>
#include <dos.h>
#include "Context.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "SleepL.h"
#include <stdlib.h>


volatile unsigned lockFlag=1;
volatile unsigned int counter = 0;
volatile unsigned explicit_context_switch = 0;

unsigned tsp;
unsigned tss;
unsigned tbp;

unsigned oldTimerOFF, oldTimerSEG;


void init() {
#ifndef BCC_BLOCK_IGNORE
	asm{
			cli
			push es
			push ax

			mov ax,0
			mov es,ax

			mov ax, word ptr es : 0022h
			mov word ptr oldTimerSEG, ax
			mov ax, word ptr es : 0020h
			mov word ptr oldTimerOFF, ax

			mov word ptr es : 0022h, seg timer
			mov word ptr es : 0020h, offset timer

			mov ax, oldTimerSEG
			mov word ptr es : 0182h, ax
			mov ax, oldTimerOFF
			mov word ptr es : 0180h, ax

			pop ax
			pop es
			sti
		}
#endif

}

void restore()
{
#ifndef BCC_BLOCK_IGNORE
		asm{
			cli
			push es
			push ax

			mov ax,0
			mov es,ax


			mov ax, word ptr oldTimerSEG
			mov word ptr es : 0022h, ax
			mov ax, word ptr oldTimerOFF
			mov word ptr es : 0020h, ax

			pop ax
			pop es
			sti
		}

		#endif
}


void interrupt timer(){

	if (!explicit_context_switch) {
		//printf("Asinhroni prekid!!\n");
		asm int 60h;
		tick();

		//WAKE: budjenje niti koje su zavrsile sleep:
		if(PCB::sleepPCBs->first && PCB::sleepPCBs->first->t>=0){//za svaki sl dodato ali ne bi smelo da ode u minus

			//printf("Usao u wake\n");
				PCB::sleepPCBs->first->t--;

			if(PCB::sleepPCBs->first->t==0){

				while(PCB::sleepPCBs->first->next!=0 && PCB::sleepPCBs->first->t==0){
					SleepList::Elem* temp=PCB::sleepPCBs->first;
					PCB::sleepPCBs->first=PCB::sleepPCBs->first->next;
					//printf("Budjenje niti %d\n",temp->pcb->me->getId());
					temp->pcb->state=READY;
					Scheduler::put(temp->pcb);
					delete temp;
				}
				if(PCB::sleepPCBs->first->t==0){
					PCB::sleepPCBs->first->pcb->state= READY;
					//printf("Budjenje nit %d\n",PCB::sleepPCBs->first->pcb->me->getId());
					Scheduler::put(PCB::sleepPCBs->first->pcb);
					delete PCB::sleepPCBs->first;
					PCB::sleepPCBs->first=0;
				}
				//lockFlag=1;  //msm da ne treba dispatch raditi
				//dispatch();
			}
			//printf("Zavrsio wake\n");
		}


		if(counter!=0 && PCB::running->timeSlice>0) counter--;
		/*//za test6 da ne bi uvek bio idle
		if(counter==0 && PCB::running==PCB::idle){
			PCB::main->state= READY;
			Scheduler::put(PCB::main);
		}
		*/
	}

	if((counter==0 && PCB::running->timeSlice>0) || explicit_context_switch==1){
		if(lockFlag){
			//if(counter==0){printf("isteklo vreme niti %d\n", PCB::running->me->getId());}

			explicit_context_switch=0;

			//cuvanje konteksta
			//printf("Saving context of thread %d\n", PCB::running->me->getId());
#ifndef BCC_BLOCK_IGNORE
			asm{
						// cuva sp
						mov tsp, sp
						mov tss, ss
						mov tbp, bp
					}
#endif
					PCB::running->sp = tsp;
					PCB::running->ss = tss;
					PCB::running->bp = tbp;


					if(PCB::running->state!=IDLE && PCB::running->state==READY)
						Scheduler::put((PCB*)PCB::running);

					PCB::running=Scheduler::get();
					if(PCB::running==0) PCB::running=PCB::idle;
					//printf("Running nit je thread %d\n",PCB::running->me->getId());

			//restauracija konteksta

					tsp = PCB::running->sp;
					tss = PCB::running->ss;
					tbp = PCB::running->bp;

					counter = (unsigned)PCB::running->timeSlice;
#ifndef BCC_BLOCK_IGNORE
			asm {
						mov sp, tsp   // restore sp
						mov ss, tss
						mov bp, tbp
					}
#endif
		}else explicit_context_switch = 1;
	//}
}
	///printf("Izlazak iz timera\n");
}

void dispatch(){   //proveri zasto ne moze da koristi lock


	asm pushf;
	asm cli;

	explicit_context_switch = 1;
	asm int 08h
	//timer();

	//asm sti;

    asm popf;
}




