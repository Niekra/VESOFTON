/*
 * Uart.cpp
 *
 *  Created on: May 9, 2018
 *      Author: M
 */

//Includes
#include <Uart.h>

namespace UART {

/*local variables*/
volatile int iIndex = 0;					//Input index. Keeps track of which is the next buffer input.
volatile int bReady = 0;					//Bool, to signal inputBuffer is ready for transfer.
volatile int iLine = 0;
volatile int uBusy = 0;
uint8_t inputBuffer[BUFFER_LENGTH];

//Local functions
int put_Char(char c);
void init_RCC(void);
void init_GPIO(void);
void init_USART(void);
void init_NVIC(void);

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int write(char *text_out){
	volatile unsigned int i;
	for (i=0; text_out[i]; i++)
	{
		UART::put_Char(text_out[i]);
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
		for (int i = 0; i<= iIndex; i++){
			buf[i] = inputBuffer[i];
		}
	}
	iIndex = RESET;
	bReady = RESET;

	return 0;
}


int init_IDLE_Line(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	//Timer-3
	// basefreq = 2*APB1 (APB2=84MHz) => TIM_CLK=84MHz
	// 1/115200/11 = 10.5kHz
	//2x 84Mhz = 168 MHz /1/ 16000 = 10500

	TIM_TimeBaseInitTypeDef timerInitStructure;
	timerInitStructure.TIM_Prescaler = TIM3_PRESCALE;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = TIM3_PERIOD;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM3, &timerInitStructure);

	TIM3->CNT = RESET;
	//TIM_Cmd(TIM3, ENABLE);

	// Enable TIM3 interrupt
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	//Set interrupt handler
	NVIC_InitTypeDef nvicStructure;
	nvicStructure.NVIC_IRQChannel = TIM3_IRQn;
	nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
	nvicStructure.NVIC_IRQChannelSubPriority = 0;
	nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStructure);

	iLine = SET;

	return 0;
}


int disable_IDLE_line(void)
{
	iLine = RESET;
	TIM3->CNT = RESET;
	TIM3->SR = ~(TIM_FLAG_Update);
	TIM3->CR1&=~TIM_CR1_CEN; // stop

	return 0;
}


void init_RCC(void)
{
	  /* --------------------------- System Clocks Configuration -----------------*/
	  /* USART2 clock enable */
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	  /* GPIOA clock enable */
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	  return;
}

void init_GPIO(void)
{
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
}

void init_USART(void)
{
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
	USART_InitStructure.USART_BaudRate = USART2_BAUT;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	USART_Init(USART2, &USART_InitStructure);
}

void init_NVIC(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&NVIC_InitStruct);

	USART_Cmd(USART2, ENABLE);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int init_UART2(){

	init_RCC();
	init_GPIO();
	init_USART();
	init_NVIC();

	return 0;
}

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int put_Char(char c){
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); // Wait for Empty
	USART_SendData(USART2, c);

	return 0;
}

void TIM3_IRQHandler(void)
{
	// Checks whether the TIM2 interrupt has occurred or not
	if (TIM_GetITStatus(TIM3, TIM_IT_Update)!=RESET)
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);					//Clear interrupt flag

		if(uBusy == SET){
			for(int i = 0; i < 3; i++){
				if(inputBuffer[iIndex - i] == '\n' || inputBuffer[iIndex - i] == '\r'){
					inputBuffer[iIndex - i] = '\0';
				}
			}
			inputBuffer[iIndex] = '\0';

			bReady = SET;
			uBusy = RESET;

			TIM3->CNT = RESET;
			TIM3->SR = ~(TIM_FLAG_Update);
			TIM3->CR1&=~TIM_CR1_CEN; // stop
		}
	return;
	}

}


void USART2_IRQHandler(void)
{

    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET && bReady != SET)
    {

    		inputBuffer[iIndex] = (char)USART_ReceiveData(USART2);
    		iIndex++;

    		USART_ClearITPendingBit(USART2, USART_IT_RXNE);

    		if(iLine == 1)
    		{
				if (uBusy == RESET){
					uBusy = SET;
					// Start de uBusy timer
					TIM3->CNT = RESET;
					TIM3->SR = ~(TIM_FLAG_Update);
					TIM3->CR1 |= TIM_CR1_CEN; // start
				}else{
					// Reset de Ubusy timer
					TIM3->CNT = RESET;
					TIM3->SR = ~(TIM_FLAG_Update);
				}
    		}else
    		{
				if(inputBuffer[iIndex - 1] == '\n'){
					inputBuffer[iIndex - 1] = '\0';
				}else if(inputBuffer[iIndex -1] == CR){
					inputBuffer[iIndex] = '\0';
					bReady = SET;
				}
    		}
    }
    return;
}

}  //namesspace UART

