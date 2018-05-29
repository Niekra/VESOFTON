/** @file InputOutput.cpp
 *  @brief Function prototypes of the Userinterface.
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
#include <InputOutput.h>

//--------------------------------------------------------------
// Namespace IO
//--------------------------------------------------------------
namespace IO {

//--------------------------------------------------------------
// IO::write()
//--------------------------------------------------------------
int write(char *text_out)
{
	return UART::write(text_out);
}

//--------------------------------------------------------------
// IO::read()
//--------------------------------------------------------------
int read(char *buf)
{
	return UART::read(buf);
}

//--------------------------------------------------------------
// IO::stop_Read()
//--------------------------------------------------------------
void stop_Read()
{
	UART::stop_Read();
	return;
}

//--------------------------------------------------------------
// Initiate the IO-layer
//--------------------------------------------------------------
int init_IO()
{
	UART::init_UART2();
	//UART::init_IDLE_Line();
	return 0;
}

} /* namespace IO */
