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
	return UART::write(text_out);
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
	UART::init_UART2();
	UART::init_IDLE_Line();
}

} /* namespace IO */
