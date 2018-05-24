/*
 * LogicLevel.h
 *
 *  Created on: May 23, 2018
 *      Author: M
 */
#ifndef LOGICLAYER_H_
#define LOGICLAYER_H_

//--------INCLUDES-----------
#include <Vgascreen.h>
#include "stm32f4xx.h"
//#include <cstring>
#include <iostream>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>

#define BUFFER_LENGTH 10
#define INPUT_LENGTH 10
#define COLORS 16
#define CORE_CLOCK 168000000


namespace LL {

	int initLL();
	int exec();
	int setCommand(char *buf);
	int clearCommands();
	int waitMs(int ms);

} /* namespace LL */

#endif /* LOGICLEVEL_H_ */