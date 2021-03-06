/** @file InputOutput.cpp
 *  @brief Function prototypes of the Userinterface.
 *
 *	Acts as a mediator for the UART and the rest of the program.
 *
 *  @author Matthijs Daggelders
 *  @author Niek Ratering Arntz
 */

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include <InputOutput.h>
#include <Uart.h>

using namespace UART;

//--------------------------------------------------------------
// Namespace IO
//--------------------------------------------------------------
namespace IO {

//--------------------------------------------------------------
// IO::write()
//--------------------------------------------------------------
void write(char *text_out)
{
	UART::write(text_out);
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
void init_IO()
{
	UART::init_UART2();
	//UART::init_IDLE_Line();
	return;
}

//--------------------------------------------------------------
// Destroy the IO-layer
//--------------------------------------------------------------
void delete_IO()
{
	UART::delete_UART();
	//UART::init_IDLE_Line();
	return;
}//delete_IO

} /* namespace IO */
