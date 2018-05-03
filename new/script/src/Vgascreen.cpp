/*
 * Vgascreen.cpp
 *
 *  Created on: May 3, 2018
 *      Author: M
 */

#include <stm32_ub_vga_screen.h>
#include <stdlib.h>
#include <Vgascreen.h>
#include <algorithm>

Vgascreen::Vgascreen() {
	// TODO Auto-generated constructor stub
	UB_VGA_Screen_Init(); // Init VGA-Screen

	UB_VGA_FillScreen(VGA_COL_GREEN);
}

Vgascreen::~Vgascreen() {
	// TODO Auto-generated destructor stub
}

int Vgascreen::draw_line(int x1, int y1, int x2, int y2, int width, int color){
	const int dx = abs(x1-x2);
	const int dy = abs(y1-y2);
	bool a= true;

	if(dy>dx){
		std::swap(x1, y1);
		std::swap(x2, y2);

	}

	if(x1>x2){
		std::swap(x1,x2);
		std::swap(y1,y2);
	}

	if(y1>y2){
		//std::swap(x1,x2);
		//std::swap(y1,y2);
		a = false;
	}

	int y;
	for(int i = x1; i< x2; i++){

		if(a){
			y = y1 + dy * (i - x1) / dx;
		}else {
			y = y1 - dy * (i - x1) / dx;
		}
		int xset = i;
		if (dx>dy){
			UB_VGA_SetPixel((xset),(y),254);
		}else{
			UB_VGA_SetPixel((y),(xset),254);
		}
	}


}

