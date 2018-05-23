/*
 * Uart.cpp
 *
 *  Created on: May 9, 2018
 *      Author: M
 */


#include <Uart.h>

namespace UART {

int inputIndex = 0;
char inputBuffer[100];
volatile int bReady = 0;

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int write(char *text_out){
	volatile unsigned int i;
	for (i=0; text_out[i]; i++)
	{
		UART::putchar(text_out[i]);
	}
	return 0;
}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int read(char *buf){

	while(!bReady){

	}

	if(bReady){
		for (int i = 0; i<= inputIndex; i++){
			buf[i] = inputBuffer[i];
		}
	}
	inputIndex = 0;
	bReady = 0;

	return 0;
}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int initUART2(){
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

	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	USART_Init(USART2, &USART_InitStructure);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);

	USART_Cmd(USART2, ENABLE);
	//NVIC_EnableIRQ(USART2_IRQn);

	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStruct);

}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int putchar(char c){
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // Wait for Empty
	USART_SendData(USART2, c);
}

/*!
 * \brief de VGA class
 */
char getchar(void){
	char Uart_char = -1;
	if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE)== SET)  // check for data available
		 Uart_char= USART2->DR & 0xFF; // and read the data from peripheral
	return Uart_char;
}

void USART2_IRQHandler(void)
{
    /* RXNE handler */
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET && bReady != 1)
    {
    		inputBuffer[inputIndex] = (char)USART_ReceiveData(USART2);

    		if(inputBuffer[inputIndex] == CR){
    			inputBuffer[inputIndex] = '\0';
    			bReady = 1;
    			return;
    		}
    		inputIndex++;
    		//USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }


    USART_ClearITPendingBit(USART1, USART_IT_RXNE);
    /* ------------------------------------------------------------ */
    /* Other USART1 interrupts handler can go here ...             */
}

}

