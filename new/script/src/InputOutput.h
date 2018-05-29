/** @file InputOutput.h
 *  @brief Function prototypes of the IO-layer.
 *
 *	Acts as a mediator for the UART and the rest of the program.
 *
 *  @author Matthijs Daggelders
 *  @author Niek Ratering Arntz
 */

#ifndef INPUTOUTPUT_H_
#define INPUTOUTPUT_H_

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include <Uart.h>
using namespace UART;

/** @brief namespace IO
 *
 * 	Acts as a mediator between the UART and the rest of the program.
 *
 */
namespace IO {

/** @brief (Global) Write to UART.
 *
 *  @param char *text_out
 *  @return int error
 */
int write(char *text_out);

/** @brief (Global) Read from UART.
 *
 * 	Calls the UART::read() function.
 *
 *  @param char *buf Buffer to fill with the user input.
 *  @return int error
 */
int read(char *buf);

/** @brief (Global) Stops the UART::read() function.
 *
 *	Stops the UART::read() function and return to the UI.
 *
 *  @param void
 *  @return void
 */
void stop_Read();

/** @brief (Global) Initiate the IO-layer.
 *
 * 	Calls the UART::init_UART function to start the UART.
 * 	(Optional) call the UART::init_IDLE_LINE() for inputs without the carriage return char.
 *
 *  @param void
 *  @return void
 */
int init_IO();

} /* namespace IO */

#endif /* INPUTOUTPUT_H_ */
