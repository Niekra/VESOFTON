/*
 * LogicLayer.h
 *
 *  Created on: May 20, 2018
 *      Author: M
 */


#ifndef LOGICLAYER_H_
#define LOGICLAYER_H_

//--------INCLUDES-----------
#include <Vgascreen.h>

#define BUFFER_LENGTH 10
#define INPUT_LENGTH 10

class LogicLayer {
public:
	LogicLayer();
	virtual ~LogicLayer();
	int exec();
	int setCommand(char *buf);
	int clearCommands();
	char *input1;
private:
	Vgascreen screen;
	int bufCount;
	int lastCount;
	char *lastCommands[BUFFER_LENGTH];
	char *bufferedCommands[BUFFER_LENGTH];
	char *inputArray[INPUT_LENGTH];

	//Functies private
	int repeat();
	int addLastCommand();
	int clearLastCommands();
	int execBuffer();
	int addBufCommand();
	int clearBufCommands();
	int waitMs();
	void clearInputArray();
	char* getInput(int index);
};


#endif /* LOGICLAYER_H_ */
