/*
 * InputOutput.h
 *
 *  Created on: May 23, 2018
 *      Author: M
 */

#ifndef INPUTOUTPUT_H_
#define INPUTOUTPUT_H_

//#include <stm32_ub_vga_screen.h>
#include <Uart.h>

using namespace UART;

namespace IO {

int write(char *text_out);
int read(char *buf);
int initIO();

} /* namespace IO */

#endif /* INPUTOUTPUT_H_ */
