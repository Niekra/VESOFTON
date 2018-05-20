/*
 * Userinterface.h
 *
 *  Created on: May 20, 2018
 *      Author: M
 */

#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include <LogicLayer.h>
#include <InputOutput.h>

class Userinterface {
public:
	Userinterface();
	virtual ~Userinterface();
	void mainLoop();

private:
	char buf[100];
	int err;
	LogicLayer LL;
	InputOutput IO;
	void write_error(int);
};

#endif /* USERINTERFACE_H_ */