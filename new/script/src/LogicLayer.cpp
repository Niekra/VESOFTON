/*
 * LogicLayer.cpp
 *
 *  Created on: May 20, 2018
 *      Author: M
 */

#include <LogicLayer.h>
//#include <cstring>
//#include <iostream>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
//#include <vector>
using namespace std;

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
LogicLayer::LogicLayer() {
	// TODO Auto-generated constructor stub
	screen = Vgascreen();
	bufCount = 0;
	lastCount = 0;
	//command = command;
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
int LogicLayer::exec(){
	int i = 0;
	i = 1-1;
	char *str;
	char str2[10],str3[10],str4[10],str5[10],str6[10];
	int k;
	str = getInput(i);
	//strcpy(str, inputArray[0]);

	if (strcmp(str,"exec") == 0){
		execBuffer();
		return 0;
	}else if (strcmp(str,"buffer") == 0){

		for(int j = 0; j<BUFFER_LENGTH; j++){
			inputArray[j] = inputArray[j + 1];
		}
		bufferedCommands[bufCount] = *inputArray;
		bufCount++;

		if (bufCount >= 10){
			bufCount = 0;
		}

		clearInputArray();
		return 0;
	}else if (strcmp(str,"repeat") == 0){
		repeat();
		return 0;
	}

	//char *str2;
	strcpy(str2,inputArray[1]);
	strcpy(str3,inputArray[2]);
	strcpy(str4,inputArray[3]);
	strcpy(str5,inputArray[4]);
	strcpy(str6,inputArray[5]);
	//str2 = inputArray[1];
	//int z = atoi(str2);

	if (strcmp(str,"lijn") == 0){
		int a = (int)strtol(str2, NULL, 10);
		int b = (int)strtol(str3, NULL, 10);
		int c = (int)strtol(str4, NULL, 10);
		int d = (int)strtol(str5, NULL, 10);
		int e = (int)strtol(str6, NULL, 10);
		//a = 12;
		screen.draw_line(a,b,c,d,e,55);
	}/*else if (strcmp(str,"ellips") == 0){

	}else if (strcmp(str,"rechthoek") == 0){

	}else if (strcmp(str,"driehoek") == 0){

	}else if (strcmp(getInput[i],"tekst") == 0){

	}else if (strcmp(getInput[i],"bitmap") == 0){

	}else if (strcmp(getInput[i],"wacht") == 0){

	}else{
		return 10;
	}*/

	lastCommands[lastCount] = *inputArray;
	lastCount++;

	if(lastCount >= BUFFER_LENGTH){
		lastCount = 0;
	}

	//clearInputArray();
	return 0;
}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int LogicLayer::setCommand(char *buf){
	int i = 1;
	int j = 1;
	char str[100];
	strcpy(str, buf);
	char *saveptr;
	char *out;

	out = strtok_r(str, ",", &saveptr);
	inputArray[0] = out;

	while(out != NULL){
		out = strtok_r(NULL, ",", &saveptr);
		inputArray[i] = out;
		i++;
	}
	return 0;
}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int LogicLayer::clearCommands(){

}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int LogicLayer::repeat(){

}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int LogicLayer::addLastCommand(){

}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int LogicLayer::clearLastCommands(){

}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int LogicLayer::execBuffer(){

}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int LogicLayer::addBufCommand(){

}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int LogicLayer::clearBufCommands(){

}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int LogicLayer::waitMs(){

}

void LogicLayer::clearInputArray(){
	for(int i = 0; i< INPUT_LENGTH; i++){
		inputArray[i] = 0;
	}
}

char* LogicLayer::getInput(int index){
	return inputArray[index];
}



