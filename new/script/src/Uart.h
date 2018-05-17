/*
 * Uart.h
 *
 *  Created on: May 9, 2018
 *      Author: M
 */

#ifndef Uart_H_
#define Uart_H_

#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "Uart.h"

#define CR 13 // carriage return char
#define LF 10 // linefeed char

/*!
 * \brief De Uart class
 */
class Uart {
public:
	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */
	Uart();
	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */
	virtual ~Uart();
	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */
	int write(char *text_out);
	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */
	int read(char *buf);
private:
	char buf[120];
	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */
	int init();
	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */
	int putchar(char c);
	/*!
	 * \brief de VGA class
	 */
	char getchar(void);
};

#endif /* Uart_H_ */
