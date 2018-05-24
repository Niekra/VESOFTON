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
#include "string.h"

 // Namespace UART.
namespace UART {

//Defines
#define CR 13 // carriage return char
#define LF 10 // linefeed char

//--------------------------------------------------------------
// Timer-3
// Function  = Idle line detect.
//
// basefreq = 2*APB1 (APB1=48MHz) => TIM_CLK=84MHz
// Frq       = 84MHz/1/16000 = 10,5kHz =>
//--------------------------------------------------------------
#define  TIM3_PERIOD   16000
#define  TIM3_PRESCALE     1

#define USART2_BAUT 115200

//Buffer length
#define BUFFER_LENGTH 100

// public functions
int write(char *text_out);
int read(char *buf);
int init_UART2(void);
int init_IDLE_Line(void);
int disable_IDLE_line(void);

//Global intterupt handlers
void TIM3_IRQHandler(void);
void USART2_IRQHandler(void);

} //namesspace

#endif /* Uart_H_ */

#ifdef __cplusplus
}
#endif
