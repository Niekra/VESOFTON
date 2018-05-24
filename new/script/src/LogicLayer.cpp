/*
 * LogicLevel.cpp
 *
 *  Created on: May 23, 2018
 *      Author: M
 */

#include <LogicLayer.h>

namespace LL
{

	char *inputArray[BUFFER_LENGTH];
	const char *colors[COLORS] =
	{ "zwart", "blauw", "lichtblauw", "groen", "lichtgroen", "cyaan",
			"lichtcyaan", "rood", "lichtrood", "magenta", "lichtmagenta",
			"bruin", "geel", "grijs", "wit" };
	const int rgb[COLORS] =
	{ 0x00, 0x03, 0x0F, 0x1C, 0x0E, 0x1F, 0x7F, 0xE0, 0xED, 0xE3, 0xCE, 0x64,
			0xFC, 0x92, 0xFF };

	void clearInputArray();
	int colorToInt(char *color);
	Vgascreen screen;

	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */
	int initLL()
	{
		// TODO Auto-generated constructor stub
		screen = Vgascreen();
		return 0;
	}

	int exec()
	{
		int i = 0;
		char *str;
		int a, b, c, d, e, f, g;
		int color;

		str = inputArray[0];

		if (strcmp(str, "clearscherm") == 0)			//Command zonder int.
		{
			color = colorToInt(inputArray[1]);
			screen.clear_screen(color);
		}
		else
		{												//Command met 1x int.
			a = (int) strtol(inputArray[1], NULL, 10);
			if (strcmp(str, "wacht") == 0)
			{
				waitMs(a);
			}
			else										//Command met 2x int.
			{
				b = (int) strtol(inputArray[2], NULL, 10);
				if (strcmp(str, "tekst") == 0)
				{
					color = colorToInt(inputArray[5]);
					g = (int) strtol(inputArray[6], NULL, 10);
					//style
					screen.draw_text(a, b, inputArray[3], color, inputArray[4],
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
						color = colorToInt(inputArray[5]);
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
								color = colorToInt(inputArray[6]);
								screen.draw_line(a, b, c, d, e, color);
							}
							else						//Commands met 6x int.
							{
								f = (int) strtol(inputArray[5], NULL, 10);
								if (strcmp(str, "driehoek") == 0)
								{
									color = colorToInt(inputArray[7]);
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

		LL: clearInputArray();
		return 0;
	}

	int setCommand(char *buf)
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

	int waitMs(int ms)
	{

		int calcMs = CORE_CLOCK / 1000 / 18;
		volatile uint32_t total = (calcMs * ms);
		//volatile uint32_t cnt,begin;

		//begin = DWT->CYCCNT;

		for (int i = 0; i < total; i++)
			;

		//cnt = DWT->CYCCNT - begin;

		return 0;
	}

	int colorToInt(char *color)
	{
		for (int i = 0; i < COLORS; i++)
		{
			if (strcmp(color, colors[i]) == 0)
			{
				return rgb[i];
			}
		}
		return 0;
	}

	void clearInputArray()
	{
		for (int i = 0; i < INPUT_LENGTH; i++)
		{
			inputArray[i] = 0;
		}
	}

} /* namespace LL */