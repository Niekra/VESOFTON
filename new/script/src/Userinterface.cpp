/*
 * Userinterface.cpp
 *
 *  Created on: May 20, 2018
 *      Author: M
 */

#include <Userinterface.h>

Userinterface::Userinterface() {
	// TODO Auto-generated constructor stub
	LL = LogicLayer();
	IO = InputOutput();
	err = 0;
}

Userinterface::~Userinterface() {
	// TODO Auto-generated destructor stub
}

void Userinterface::mainLoop(){

	char test[] = "hallo";
	while(err==0){

		//IO.write(test);

		//IO.read(buf);

		LL.setCommand("hallo test dit eens");

		LL.exec();

	}
}

void Userinterface::write_error(int){

}