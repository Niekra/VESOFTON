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



int main(void)
{

	//  uint32_t n;
/** @code */
	SystemInit(); // System speed to 168MHz

	UB_VGA_Screen_Init(); // Init VGA-Screen

  UB_VGA_FillScreen(VGA_COL_BLACK);
  //UB_VGA_SetPixel(10,10,10);

/** @endcode */
  drawline(10,50,150,50,254);
  //drawline(10,50,10,100,254);
  //drawline(150,100,150,50,254);
  //drawline(150,100,10,100,254);
  //square(10,50,150,100,254);




  while(1)
  {
	  // put the code here
  }
}

void drawline(int x1, int y1, int x2, int y2, int color){
	int dx = abs(x1-x2);
	int dy = abs(y1-y2);
	int xy = dx/dy;


	int j = 0;
	int i = 0;

		for(i = x1; i< x2; i++){
			int y = y1 + dy * (i - x1) / dx;
			int xset = x1+i;
			UB_VGA_SetPixel((xset),(y),254);
		}
}

void square(int x1, int y1, int x2, int y2, int color){
	drawline(x1,y1,x2,y1, color);
	drawline(x1,y1,x1,y2, color);
	drawline(x2,y2,x2,y1, color);
	drawline(x2,y2,x1,y2, color);

}
