/*
 * InputOutput.cpp
 *
 *  Created on: May 23, 2018
 *      Author: M
 */

#include <InputOutput.h>


/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
namespace IO {

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int write(char *text_out){
	UART::write(text_out);
}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int read(char *buf){
	return UART::read(buf);
}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int initIO(){
	UART::initUART2();
	//UB_VGA_Screen_Init(); // Init VGA-Screen
	//UB_VGA_FillScreen(VGA_COL_GREEN);// Set screen green.
}

} /* namespace IO */
