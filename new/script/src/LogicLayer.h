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

struct Command {
	char type;
	char attr1;
	char attr2;
	char attr3;
	char attr4;
	char attr5;
	char attr6;
	char attr7;
	char attr8;
	char attr9;
};

class LogicLayer {
public:
	LogicLayer();
	virtual ~LogicLayer();
	int exec();
	int setCommand(char *buf);
	int clearCommands();
private:
	Vgascreen screen;
	int bufCount;
	int lastCount;
	Command lastCommands[10];
	Command bufferedCommands[10];

	//Functies private
	int repeat();
	int addLastCommand();
	int clearLastCommands();
	int execBuffer();
	int addBufCommand();
	int clearBufCommands();
	int waitMs();
};


#endif /* LOGICLAYER_H_ */
