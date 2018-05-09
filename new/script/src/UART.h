/*
 * UART.h
 *
 *  Created on: May 9, 2018
 *      Author: M
 */

#ifndef UART_H_
#define UART_H_

/*!
 * \brief De UART class
 */
namespace UART {

class UART {
public:
	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */
	UART();
	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */
	virtual ~UART();
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
	char buf[36];
	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */
	int UART_init();
	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */
	int putchar(char c);
	/*!
	 * \brief de VGA class
	 */
	int getchar(char c);



};

} /* namespace UART */

#endif /* UART_H_ */
