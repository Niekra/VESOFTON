/*
 * VGA.cpp
 *
 *  Created on: May 3, 2018
 *      Author: M
 */

#include <VGA.h>
#include <stm32_ub_vga_screen.h>

VGA::VGA() {
	// TODO Auto-generated constructor stub
	UB_VGA_Screen_Init(); // Init VGA-Screen

	UB_VGA_FillScreen(VGA_COL_GREEN);
}

VGA::~VGA() {
	// TODO Auto-generated destructor stub
}

int VGA::draw_line(int x1, int y1, int x2, int y2, int width, int color){
	int dx = (x1-x2);
	int dy = (y1-y2);
	int xy = dx/dy;


	int j = 0;
	int i = 0;

		for(i = x1; i< x2; i++){
			int y = y1 + dy * (i - x1) / dx;
			int xset = x1+i;
			UB_VGA_SetPixel((xset),(y),254);
		}
}