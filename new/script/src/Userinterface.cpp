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
	LL.setCommand("lijn,10,100,200,220,4");

	LL.exec();

	char test[] = "hallo";
	while(err==0){

		//IO.write(test);

	//IO.read(buf);

	//LL.setCommand("lijn,100,1,100,1,4");

	//LL.exec();

		for(int i = 0; i < 100000000; i++){
			i++;
		}

	LL.setCommand("lijn,100,10,100,100,8");
	LL.exec();

	}
}

void Userinterface::write_error(int){

}
