/*
 * Userinterface.h
 *
 *  Created on: May 23, 2018
 *      Author: M
 */

#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include <InputOutput.h>
#include <LogicLayer.h>
using namespace IO;
using namespace LL;

namespace UI {

void initUI();
void mainLoop();
void write_error(int);

} /* namespace UI */

#endif /* USERINTERFACE_H_ */
