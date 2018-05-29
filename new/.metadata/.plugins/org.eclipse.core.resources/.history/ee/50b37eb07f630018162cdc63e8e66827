/** @file UserInterface.h
 *  @brief Function prototypes of the Userinterface.
 *
 *	Gets the user input from the IO layer and parses it to the LogicLayer.
 *	Takes care of the error handling.
 *
 *  @author Matthijs Daggelders
 *  @author Niek Ratering Arntz
 */

#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------

/** @brief Namespace UI
 *
 * 	In the namespace UI are all the functions and variables concerning the User interface.
 *
 */
namespace UI
{

/** @brief (GLOBAL)initiates the UI.
 *
 *	The UI sits at the hearth of the program en initiates the other layers.
 *
 *  @param void
 *  @return void
 */
void init_UI(void);

/** @brief (GLOBAL)initiates the UI.
 *
 *	Deletes the UI-layer. Calls the LL::delete_LL() and the IO::delete_IO() functions
 *
 *  @param void
 *  @return void
 */
void delete_UI(void);

/** @brief (Global)Starts the main UI loop.
 *
 * 	In the mainLoop the UART is read using the IO-layer.
 * 	If there's an input given send the input to the LL-layer with the set_command.
 * 	If the IO read is cancelled by the wait interrupt call the LL-layer exec()
 * 	function to execute the buffered commands.
 *
 *  @param void
 *  @return void
 */
void main_Loop(void);

/** @brief (LOCAL)Write error.
 *
 * 	Writes the error message back to the user.
 *
 *  @param void
 *  @return void
 */
void write_Error(int);

} /* namespace UI */

#endif /* USERINTERFACE_H_ */
