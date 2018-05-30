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
 * 	The UI gets the user input from the IO layer and parses it to the Logic-layer.
 * 	The LL may encounter and return a error code.
 * 	The error text is send to the IO layer to be send back to the user if ERROR = on.
 *
 */
namespace UI
{
/** @addtogroup Global defines
  * @{
  */
/** @brief Error feedback 1=on/0=off. */
#define ERRORS 1
/**
  * @}
  */

/** @brief (GLOBAL)Initiates the UI.
 *
 *	Initializes the UI and initiates the logic layer and the IO-layer.
 *
 *  @param void
 *  @return void
 */
void init_UI(void);

/** @brief (GLOBAL)Deletes the UI.
 *
 *	Deletes the UI-layer. Calls the LL::delete_LL() and the IO::delete_IO() functions.
 *
 *  @param void
 *  @return void
 */
void delete_UI(void);

/** @brief (Global)Starts the main UI loop.
 *
 * 	Main UI loop. This is where the rest of the program happens.
 * 	First the UART::read function is called. If there�s a new user input.
 * 	LL::set_command() with the user input is called. If UART::read returns empty call the LL::exec().
 * 	Errors from the LL will be printed using the UI::write_Error() function
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
void write_Error(int err);
/** @} */ // end of UI Global functions

} /* namespace UI */

#endif /* USERINTERFACE_H_ */
