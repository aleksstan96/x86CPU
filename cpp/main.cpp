/*
 * main.cpp
 *
 *  Created on: Aug 12, 2018
 *      Author: OS1
 */

#include "PCB.h"
#include "Context.h"
#include "SpecThr.h"
#include <STDIO.H>
#include <iostream.h>



extern int userMain(int argc, char* argv[]);


int main(int argc, char* argv[]){

	init();
    PCB::createIdle();
    PCB::createMain();

	int ret = userMain(argc, argv);
	//printf("RET: %d\n", ret);

	PCB::deleteIdle();     //redosled + proveri restauraciju main niti
	PCB::deleteMain();

	restore();

	return ret;


	return 0;
}




