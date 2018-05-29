/** @file UserInterface.cpp
 *  @brief Functions of the UserInterface.
 *
 *	Gets the user input from the IO layer and parses it to the LogicLayer.
 *	Takes care of the error handling.
 *
 *  @author Matthijs Daggelders
 *  @author Niek Ratering Arntz
 */

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include <Userinterface.h>
#include <InputOutput.h>
#include <LogicLayer.h>
#include <stm32f4xx.h>

using namespace IO;
using namespace LL;

//--------------------------------------------------------------
// Namespace UI
//--------------------------------------------------------------
namespace UI
{

//--------------------------------------------------------------
// Initiate UI.
//--------------------------------------------------------------
void init_UI()
{
	IO::init_IO();
	LL::init_LL();
} // initUI

//--------------------------------------------------------------
// Deletes the UI layer.
//--------------------------------------------------------------
void delete_UI(int)
{
	IO::delete_IO();
	LL::delete_LL();
}	// Delete UI

//--------------------------------------------------------------
// MainLoop UI.
//-------------------------------------------------------------
void main_Loop()
{
	int buffered;  				//Buffered flag
	int err = RESET;			//Error flag
	char buf[BUFFER_LENGTH];	//Input buffer.

	while (true)
	{
		buffered = IO::read(buf);		//Get input from the IO-layer.

		if (buffered == SET)			//Check if theres a new input.
		{
			err = LL::set_Command(buf);
		}else if(buffered == RESET){		//If there's no new input.
			err = LL::exec();				//Execute the buffered commands.
		}

		if(err > 0)
		{
			write_Error(err);
		}
	}
}	//Mainloop

//--------------------------------------------------------------
// Write error message.
//--------------------------------------------------------------
void write_Error(int err)
{
	char *str;
	if(ERRORS==1)
	{
		switch(err)
		{

			case 11:
				str = (char*)"Command buffer leeg/Slechte input ontvangen.";
				IO::write(str);
				break;
			case 12:
				str = (char*)"Commmannd buffer vol. eerste commands worden verwijderd.";
				IO::write(str);
				break;
			default:
				return;
				break;
		}

	}
}	// Write error

} /* namespace UI */
