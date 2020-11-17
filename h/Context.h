/*
 * Context.h
 *
 *  Created on: Aug 12, 2018
 *      Author: OS1
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_

extern volatile unsigned lockFlag; //globalna promenljiva, definisana u Context.cpp
extern volatile unsigned explicit_context_switch;

void interrupt timer();

void init();
void restore();

extern void tick() ;



#endif /* CONTEXT_H_ */
