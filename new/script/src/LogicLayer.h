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
#define COLORS 16
#define CORE_CLOCK 168000000

class LogicLayer {
public:
	LogicLayer();
	virtual ~LogicLayer();
	int exec();
	int setCommand(char *buf);
	int clearCommands();
	int waitMs(int ms);
private:
	Vgascreen screen;
	/*
	int  bufCount;
	int  *lastCount;
	char *lastCommands[BUFFER_LENGTH];
	char *bufferedCommands[BUFFER_LENGTH];
	*/
	char *inputArray[BUFFER_LENGTH];
	const char *colors[COLORS]= {"zwart","blauw","lichtblauw","groen","lichtgoren","cyaan","lichtcyaan","rood","lichtrood","magenta", "lichtmagenta","bruin","geel","grijs","wit"};
	int rgb[COLORS]= {0x00, 0x03, 0x0F, 0x1C, 0x0E, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF};

	//Functies private
	void clearInputArray();
	char* getInput(int index);
	int colorToInt(char *color);
};


#endif /* LOGICLAYER_H_ */
