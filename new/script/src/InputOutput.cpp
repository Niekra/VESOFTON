/*
 * InputOutput.cpp
 *
 *  Created on: May 20, 2018
 *      Author: M
 */

#include <InputOutput.h>

InputOutput::InputOutput() {
	// TODO Auto-generated constructor stub
	err = 0;
	err = initUART();
}

InputOutput::~InputOutput() {
	// TODO Auto-generated destructor stub
}

int InputOutput::write(char *text_out){
	u1.write(text_out);
}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int InputOutput::read(char *buf){
	return u1.read(buf);
}

int InputOutput::initUART(){
	u1 = UART();
}
