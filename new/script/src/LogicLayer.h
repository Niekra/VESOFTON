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
#include <iostream>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "string.h"


#define INPUT_LENGTH 10
#define COLORS 16
#define CORE_CLOCK 168000000

#define TIM5_PRESCALE 10
#define TIM5_PERIOD 8400

namespace LL {

//	public functions
int init_LL();
int destroy_LL();
int set_Command(char *buf);

// Global interrupt handler
void TIM5_IRQHandler(void);

} /* namespace LL */

#endif /* LOGICLEVEL_H_ */
