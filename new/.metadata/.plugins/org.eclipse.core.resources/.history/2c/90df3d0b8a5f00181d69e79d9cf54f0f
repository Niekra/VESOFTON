/*
 * Uart.h
 *
 *  Created on: May 9, 2018
 *      Author: M
 */
#ifdef __cplusplus
 extern "C" {
#endif

#ifndef Uart_H_
#define Uart_H_



#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_dma.h"
#include "string.h"

namespace UART {

#define CR 13 // carriage return char
#define LF 10 // linefeed char



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

//char buf[120];
/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int initUART2();
/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int putchar(char c);

/*!
 * \brief de VGA class
 */
char getchar(void);

void TIM3_IRQHandler(void);
void USART2_IRQHandler(void);
void DMA1_Stream5_IRQHandler(void);

} //namesspace

#endif /* Uart_H_ */

#ifdef __cplusplus
}
#endif
