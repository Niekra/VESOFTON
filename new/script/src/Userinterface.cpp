/*
 * Userinterface.cpp
 *
 *  Created on: May 23, 2018
 *      Author: M
 */

#include <Userinterface.h>

namespace UI {

void initUI(){
	IO::initIO();
	LL::initLL();
}

void mainLoop(){
	int buffered;  //error
	int err = 0;
	char buf[100];

	LL::waitMs(5000);
	LL::setCommand("lijn,10,100,200,220,4,blauw");
	LL::waitMs(1000);
	LL::setCommand("clearscherm,groen");
	LL::waitMs(1000);
	LL::setCommand("driehoek,150,60,101,101,201,101,lichtblauw");


	//char test[] = "hallo";
	while(err==0){
		//test();
		//IO.write(test);


		buffered = IO::read(buf);

		if(buffered == 0){
			LL:setCommand(buf);
		}
		//LL::waitMs(100);

	}
}

void write_error(int){

}

} /* namespace UI */
