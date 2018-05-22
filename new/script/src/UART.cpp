/*
 * UART.cpp
 *
 *  Created on: May 9, 2018
 *      Author: M
 */

#include <UART.h>

UART::UART() {
	// TODO Auto-generated constructor stub
	init();

}

UART::~UART() {
	// TODO Auto-generated destructor stub
}


/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int UART::write(char *text_out){
	volatile unsigned int i;
	for (i=0; text_out[i]; i++)
	{
		putchar(text_out[i]);
	}
}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int UART::read(char *buf){
	while (1)
	{
	 	*buf = getchar();

	 	if (*buf==-1)             // check for data available
	 		continue;

	 	if (*buf==0xff) // if no data or LF, continue
			return 0;

	 	if(*buf == LF){
	 		continue;
	 	}

		if (*buf==CR)            // if enter pressed
		{
			*buf = '\0';         // ignore char and close string
		    return 0;            // buf ready, exit loop
		}
		buf++;
	}
}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int UART::init(){
	  /* --------------------------- System Clocks Configuration -----------------*/
	  /* USART2 clock enable */
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	  /* GPIOA clock enable */
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	  GPIO_InitTypeDef GPIO_InitStructure;

	  /*-------------------------- GPIO Configuration ----------------------------*/
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	  GPIO_Init(GPIOA, &GPIO_InitStructure);

	  /* Connect USART pins to AF */
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);   // USART2_TX
	  GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);  // USART2_RX

	  USART_InitTypeDef USART_InitStructure;

	/* USARTx configuration ------------------------------------------------------*/
	/* USARTx configured as follow:
	      - BaudRate = 115200 baud
	      - Word Length = 8 Bits
	      - One Stop Bit
	      - No parity
	      - Hardware flow control disabled (RTS and CTS signals)
	      - Receive and transmit enabled
	*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART2, &USART_InitStructure);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);

	USART_Cmd(USART2, ENABLE);
}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int UART::putchar(char c){
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // Wait for Empty
	USART_SendData(USART2, c);
}

/*!
 * \brief de VGA class
 */
char UART::getchar(void){
	char uart_char = -1;
	if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE)== SET)  // check for data available
		 uart_char= USART2->DR & 0xFF; // and read the data from peripheral
	return uart_char;
}

