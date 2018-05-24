/*
 * LogicLevel.cpp
 *
 *  Created on: May 23, 2018
 *      Author: M
 */

#include <LogicLayer.h>

namespace LL
{

#define BUFFER_LENGTH 100

char *inputArray[BUFFER_LENGTH];
Vgascreen screen;


const char *colors[COLORS] =
{ "zwart", "blauw", "lichtblauw", "groen", "lichtgroen", "cyaan",
		"lichtcyaan", "rood", "lichtrood", "magenta", "lichtmagenta",
		"bruin", "geel", "grijs", "wit" };

const int rgb[COLORS] =
{ 0x00, 0x03, 0x0F, 0x1C, 0x0E, 0x1F, 0x7F, 0xE0, 0xED, 0xE3, 0xCE, 0x64,
		0xFC, 0x92, 0xFF };

//Local functions
void clear_Input_Array();
int color_To_Int(char *color);
int init_TIM5();
int exec();
int clear_Commands();
int wait_Ms(int ms);

/*!
 * \brief teken een lijn.
 * \param paramter int.
 */
int init_LL()
{
	// TODO Auto-generated constructor stub
	screen = Vgascreen();

	return 0;
}

int destroy_LL()
{
	return 0;
}

int init_TIM5()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	//Timer-5
	// basefreq = 2*APB1 (APB2=84MHz) => TIM_CLK=84MHz
	// 84Mhz/10000/ = 1kHz
	// 84Mhz = 84 MHz /10/ 8400 = 1000

	TIM_TimeBaseInitTypeDef timerInitStructure;
	timerInitStructure.TIM_Prescaler = TIM5_PRESCALE;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	timerInitStructure.TIM_Period = TIM5_PERIOD;
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	timerInitStructure.TIM_RepetitionCounter = 1;
	TIM_TimeBaseInit(TIM5, &timerInitStructure);

	TIM5->CNT = 0;
	//TIM_Cmd(TIM3, ENABLE);

	// Enable TIM3 interrupt
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	//Set interrupt handler
	NVIC_InitTypeDef nvicStructure;
	nvicStructure.NVIC_IRQChannel = TIM5_IRQn;
	nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
	nvicStructure.NVIC_IRQChannelSubPriority = 0;
	nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvicStructure);


	return 0;
}

void TIM5_IRQHandler(void)
{
	return;
}

int exec()
{
	char *str;
	int a, b, c, d, e, f, g;
	int color;

	str = inputArray[0];

	if (strcmp(str, "clearscherm") == 0)			//Command zonder int.
	{
		color = color_To_Int(inputArray[1]);
		screen.clear_screen(color);
	}
	else
	{												//Command met 1x int.
		a = (int) strtol(inputArray[1], NULL, 10);
		if (strcmp(str, "wacht") == 0)
		{
			wait_Ms(a);
		}
		else										//Command met 2x int.
		{
			b = (int) strtol(inputArray[2], NULL, 10);
			if (strcmp(str, "tekst") == 0)
			{
				color = color_To_Int(inputArray[4]);
				g = (int) strtol(inputArray[6], NULL, 10);
				//style
				screen.draw_text(a, b, inputArray[3], color, inputArray[5],
						g);
			}
			else									//Commands met 3x int.
			{
				c = (int) strtol(inputArray[3], NULL, 10);
				if (strcmp(str, "bitmap") == 0)
				{
					screen.draw_bitmap(a, b, c);
				}
				else								//Commands met 4x int.
				{
					d = (int) strtol(inputArray[4], NULL, 10);
					color = color_To_Int(inputArray[5]);
					if (strcmp(str, "rechthoek") == 0)
					{
						screen.draw_rectangle(a, b, c, d, color);
					}
					else if (strcmp(str, "ellips") == 0)
					{
						screen.draw_ellipse(a, b, c, d, color);
					}
					else							//Commands met 5x int.
					{
						e = (int) strtol(inputArray[5], NULL, 10);
						if (strcmp(str, "lijn") == 0)
						{
							color = color_To_Int(inputArray[6]);
							screen.draw_line(a, b, c, d, e, color);
						}
						else						//Commands met 6x int.
						{
							f = (int) strtol(inputArray[5], NULL, 10);
							if (strcmp(str, "driehoek") == 0)
							{
								color = color_To_Int(inputArray[7]);
								screen.draw_triangle(a, b, c, d, e, f,
										color);
							}
							else
								return 2;
						}

					}
				}
			}
		}
	}

	clear_Input_Array();
	return 0;
}

int set_Command(char *buf)
{
	int i = 1;
	char str[100];
	strcpy(str, buf);
	char *saveptr;
	char *out;

	out = strtok_r(str, ",", &saveptr);
	inputArray[0] = out;

	while (out != NULL)
	{
		out = strtok_r(NULL, ",", &saveptr);
		inputArray[i] = out;
		i++;
	}
	LL::exec();
	return 0;
}

int wait_Ms(int ms)
{

	int calcMs = CORE_CLOCK / 1000 / 18;
	volatile uint32_t total = (calcMs * ms);
	//volatile uint32_t cnt,begin;

	//begin = DWT->CYCCNT;

	for (int i = 0; i < total; i++);

	//cnt = DWT->CYCCNT - begin;

	return 0;
}

int color_To_Int(char *color)
{
	for (int i = 0; i < COLORS; i++)
	{
		if (strcmp(color, colors[i]) == 0)
		{
			if(i == 0)
			{
				return 0;
			}else
			{
				return rgb[i];
			}
		}

	}
	return 0;
}

void clear_Input_Array()
{
	for (int i = 0; i < INPUT_LENGTH; i++)
	{
		inputArray[i] = 0;
	}
}

} /* namespace LL */
