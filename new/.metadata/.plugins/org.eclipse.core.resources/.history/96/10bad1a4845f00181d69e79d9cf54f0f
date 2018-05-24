/*
 * Userinterface.cpp
 *
 *  Created on: May 23, 2018
 *      Author: M
 */

#include <Userinterface.h>

namespace UI
{
	void initUI()
	{
		IO::initIO();
		LL::initLL();
	}

	void mainLoop()
	{
		int buffered;  //error
		int err = 0;
		char buf[100];

		while (err == 0)
		{
			buffered = IO::read(buf);

			if (buffered == 0)
			{
				LL: setCommand(buf);
			}
		}
	}

	void write_error(int)
	{

	}

} /* namespace UI */
