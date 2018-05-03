//--------------------------------------------------------------
/** @file main.c */
/** @date 24.04.2018 */
// Version  : 1.0
/** @autor Niek Ratering Arntz & Matthijs Daggelders */
// mods by	: J.F. van der Bent
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.x
// Module   : CMSIS_BOOT, M4_CMSIS_CORE
// Function : VGA_core DMA LIB 320x240, 8bit color
//--------------------------------------------------------------

#include "main.h"
#include "stm32_ub_vga_screen.h"
#include <math.h>
#include "includes.h"


int main(void)
{

	//  uint32_t n;
/** @code */
	SystemInit(); // System speed to 168MHz
	UART_init();
	DELAY_init();
	UB_VGA_Screen_Init(); // Init VGA-Screen

  UB_VGA_FillScreen(VGA_COL_GREEN);
  UB_VGA_SetPixel(10,10,10);
/** @endcode */

//  char input[];


  while(1)
  {
	  UART_puts("ok");
	  DELAY_ms(500);
//	  UART_gets(input);
//	  if (sizeof(input) > 0)
//	  {
//		 UART_puts(input);
//
//	  }
  }
}

