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

}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int LogicLayer::setCommand(char *buf){
	int i = 1;
	char *inbuf;
	inbuf = buf;
	//int bufSize = sizeof(strtok(buf, " "));

	char *test;
	char *test2;
	test = strtok_r(inbuf, " ",&inbuf);
	while(test != NULL){
		test = strtok_r(inbuf, " ", &inbuf);
		test2 = test;


	}

	/*
	switch(test[0]){
	case 'repeat':
		break;
	case 'buffer':
		break;

	case 'exec':
		break;

	case 'clear':
		break;

	default :
		i = 0;
		break;
	}

	for(i; i < strlen(test); i= i + 1){
		break;
	}
	*/
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
