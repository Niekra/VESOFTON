//--------------------------------------------------------------
/** @file main.cpp */
/** @date 24.04.2018 */
// Version  : 1.0
/** @autor Niek Ratering Arntz & Matthijs Daggelders */
// mods by	: J.F. van der Bent
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.x
// Module   : CMSIS_BOOT, M4_CMSIS_CORE
// Function : VGA_core DMA LIB 320x240, 8bit color
//--------------------------------------------------------------

/* Includes */
#include <Userinterface.h>
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include <new>


/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */

/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/
int main(void)
{

  /**
  *  IMPORTANT NOTE!
  *  The symbol VECT_TAB_SRAM needs to be defined when building the project
  *  if code has been located to RAM and interrupts are used.
  *  Otherwise the interrupt table located in flash will be used.
  *  See also the <system_*.c> file and how the SystemInit() function updates
  *  SCB->VTOR register.
  *  E.g.  SCB->VTOR = 0x20000000;
  */
  /** @code */
  /* TODO - Add your application code here */
  SystemInit(); // System speed to 168MHz
  Userinterface UI = Userinterface();


  /* Infinite loop */
  while (1)
  {
	UI.mainLoop();
  }
}



