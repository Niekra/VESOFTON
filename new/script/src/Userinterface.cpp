/*
 * Userinterface.cpp
 *
 *  Created on: May 20, 2018
 *      Author: M
 */

#include <Userinterface.h>
//#include <Dma_usart.h>
/* Include core modules */
#include "stm32f4xx.h"
#include "string.h"



Userinterface::Userinterface() {
	// TODO Auto-generated constructor stub
	LL = LogicLayer();
	IO = InputOutput();
	err = 0;
	//clock_Init();

}

Userinterface::~Userinterface() {
	// TODO Auto-generated destructor stub
}

void Userinterface::mainLoop(){
	int buffered;
	LL.waitMs(5000);
	LL.setCommand("lijn,10,100,200,220,4,blauw");
	LL.waitMs(1000);
	LL.setCommand("clearscherm,groen");
	LL.waitMs(1000);
	LL.setCommand("driehoek,150,60,101,101,201,101,lichtblauw");

	//char test[] = "hallo";
	while(err==0){
		//test();
		//IO.write(test);


		buffered = IO.read(buf);

		if(buffered == 0){
			LL.setCommand(buf);
		}
		LL.waitMs(100);

	}
}

void Userinterface::write_error(int){

}
