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


//--------------------------------------------------------------
// Namespace IO
//--------------------------------------------------------------
/** @brief namespace IO
 *
 * 	Acts as a mediator between the UART and the rest of the program.
 * 	Gets commands from the UI and the LL and parses it to UART.
 *
 */
namespace IO {
//--------------------------------------------------------------
// Defines
//--------------------------------------------------------------
/** @addtogroup Global defines
  * @{
  */
/** @brief Input buffer length. */
#define BUFFER_LENGTH 100
/**
  * @}
  */


//--------------------------------------------------------------
// Global functions
//--------------------------------------------------------------
/** @brief (Global) Writes back through UART.
 *
 *	Write the char *text_out using the UART::write() function.
 *
 *  @param char *text_out
 *  @return void
 */
void write(char *text_out);

/** @brief (Global) Read from UART.
 *
 * 	Calls the UART::read() function of the UART. The user input is saved in the char *buf.
 * 	The return state is whether a new user input was given(SET) or if the read was canceled (RESET).
 *
 *  @param char *buf Buffer to fill with the user input.
 *  @return int exit_state returns whether the read functions was returned with new user input or by the stop_Read() function.
 *
 */
int read(char *buf);

/** @brief (Global) Stops the UART::read() function.
 *
 *	Calls the UART::stop_Read() function to stop waiting for user input and check if there are buffered inputs.
 *
 *  @param void
 *  @return void
 */
void stop_Read();

/** @brief (Global) Initiate the IO layer.
 *
 * 	Calls the UART::init_UART function to start the UART.
 * 	(Optional) call the UART::init_IDLE_Line() for inputs without the carriage return char.
 *
 *  @param void
 *  @return void
 */
void init_IO();

/** @brief (Global) Deletes the IO layer.
 *
 *	Deletes the IO-layer. Calls the UART::delete_UART() function.
 *
 *  @param void
 *  @return void
 */
void delete_IO();

} /* namespace IO */

#endif /* INPUTOUTPUT_H_ */
