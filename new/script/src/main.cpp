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
#include <Vgascreen.h>
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"


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
  int i = 0;
  int b = 65;
  int x1 =10;
  int y1 = 50;
  int x2 = 150;
  int y2 = 150;

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

  Vgascreen s1 = Vgascreen();

  //sqaure
  s1.draw_rectangle(x1,y1,x2,y2,5);

  //linetest
  s1.draw_line(180,0,180,240,2,254);
  //s1.draw_line(120,60,180,180,5,254);

  //triangle
  s1.draw_triangle(300, 20, 180,180, 120,60,1);

  /* Initialize LEDs */
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);

  /* Turn on LEDs */
  STM_EVAL_LEDOn(LED3);
  STM_EVAL_LEDOn(LED4);
  STM_EVAL_LEDOn(LED5);
  STM_EVAL_LEDOn(LED6);


  /* Infinite loop */
  while (1)
  {
	i++;
  }
}


/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
extern "C" void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
extern "C" uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
