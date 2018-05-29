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

//--------------------------------------------------------------
// Namespace UI
//--------------------------------------------------------------
namespace UI
{

//--------------------------------------------------------------
// Initiate UI.
//--------------------------------------------------------------
void initUI()
{
	IO::init_IO();
	LL::init_LL();
} // initUI

//--------------------------------------------------------------
// MainLoop UI.
//-------------------------------------------------------------
void mainLoop()
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
	}
}	//Mainloop

//--------------------------------------------------------------
// Write error message.
//--------------------------------------------------------------
void write_error(int)
{

}	// Write error

} /* namespace UI */
