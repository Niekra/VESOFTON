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
		LL::init_LL();
	}

	void mainLoop()
	{
		int buffered;  //error

		int err = 0;
		char buf[100];

		while (1)
		{
			buffered = IO::read(buf);

			if (buffered == 0)
			{
				err = LL::set_Command(buf);
			}

			if(err ==1)
			{
				int f = 5 + 6;
			}
		}
	}

	void write_error(int)
	{

	}

} /* namespace UI */
