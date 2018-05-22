/*
 * LogicLayer.cpp
 *
 *  Created on: May 20, 2018
 *      Author: M
 */

#include <LogicLayer.h>
#include "stm32f4xx.h"
//#include <cstring>
#include <iostream>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <exception>
#include <new>
//#include <vector>
using namespace std;


/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
LogicLayer::LogicLayer() {
	// TODO Auto-generated constructor stub
	screen = Vgascreen();
	//bufCount = 0;
	//lastCount = 0;
	//inputArray = (char**)malloc(10 * sizeof(char*));
	for(int i = 0;i < INPUT_LENGTH; i++){
		inputArray[i] = (char*)malloc(10* sizeof(char));
	}
	//command = command_10;
	//malloc(sizeof(char)* 10);
	//DWT->CTRL |= 1;
}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
LogicLayer::~LogicLayer() {
	// TODO Auto-generated destructor stub
}


/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int LogicLayer::exec()
{
	int i = 0;
	const char *str;
	int a,b,c,d,e,f;
	int color;

	str = getInput(i);

	if (strcmp(str, "clearscherm") == 0)					//Command zonder int.
	{
		color = colorToInt(inputArray[1]);
		screen.clear_screen(color);
	}else
	{													//Command met 1x int.
		a = (int)strtol(inputArray[1], NULL, 10);
		if (strcmp(str, "wacht") == 0)
		{
			waitMs(a);
		}else											//Command met 2x int.
		{
			b = (int)strtol(inputArray[2], NULL, 10);
			if (strcmp(str, "tekst") == 0)
			{
				color = colorToInt(inputArray[6]);
				//style
				screen.draw_text(a,b,inputArray[3],inputArray[4],color,4);
			}else										//Commands met 3x int.
			{
				c = (int)strtol(inputArray[3], NULL, 10);
				if (strcmp(str, "bitmap") == 0){
					screen.draw_bitmap(a,b,c);
				}else									//Commands met 4x int.
				{
					d = (int)strtol(inputArray[4], NULL, 10);
					if (strcmp(str, "rechthoek") == 0)
					{
						color = colorToInt(inputArray[5]);
						screen.draw_rectangle(a,b,c,d,color);
					}else								//Commands met 5x int.
					{
						e = (int)strtol(inputArray[5], NULL, 10);
						if (strcmp(str, "lijn") == 0)
						{
							color = colorToInt(inputArray[6]);
							screen.draw_line(a,b,c,d,e,color);
						}else							//Commands met 6x int.
						{
							f = (int)strtol(inputArray[5], NULL, 10);
							if (strcmp(str, "driehoek") == 0)
							{
								color = colorToInt(inputArray[7]);
								screen.draw_triangle(a,b,c,d,e,f,color);
							}
						}

					}
				}
			}
		}

	}

	clearInputArray();
	return 0;
}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int LogicLayer::setCommand(char *buf){
	int i = 1;
	char str[100];
	strcpy(str, buf);
	char *saveptr;
	char *out;

	out = strtok_r(str, ",", &saveptr);
	inputArray[0]=out;

	while(out != NULL){
		out = strtok_r(NULL, ",", &saveptr);
		inputArray[i] = out;
		i++;
	}
	exec();
	return 0;
}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int LogicLayer::waitMs(int ms){

	int calcMs = CORE_CLOCK/1000/18;
	volatile uint32_t total = (calcMs * ms);
	//volatile uint32_t cnt,begin;

	//begin = DWT->CYCCNT;

	for(int i = 0; i<total;i++);

	//cnt = DWT->CYCCNT - begin;

	return 0;
}

int LogicLayer::colorToInt(char *color){
	for(int i = 0; i<COLORS; i++){
		if(strcmp(color,colors[i]) == 0){
			return rgb[i];
		}
	}
	return 0;
}

void LogicLayer::clearInputArray(){
	for(int i = 0; i< INPUT_LENGTH; i++){
		inputArray[i] = 0;
	}
}

char* LogicLayer::getInput(int index){
	return inputArray[index];
}



