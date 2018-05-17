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
	init_VGA();
}

Vgascreen::~Vgascreen() {
	// TODO Auto-generated destructor stub
}


int Vgascreen::init_VGA(){
	UB_VGA_Screen_Init(); // Init VGA-Screen
	UB_VGA_FillScreen(VGA_COL_GREEN);// Set screen green.
	return 0;
}

int Vgascreen::VGA_pos(int x, int y){
	x_pos = x;// Set x position.
	y_pos = y;// Set y position.
	return 0;
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
		a = false;
	}

	int y;
	int c;
	for(int j = 0; j< width; j++){
		for(int i = x1; i< x2; i++){
			c = i - x1;
			if(a){
				if(dx>dy){
					y = y1 + dy * (c) / dx;
				}else{
					y = y1 + dx * (c) / dy;
				}
			}else {
				if(dx>dy){
					y = y1 - dy * (c) / dx;
				}else{
					y = y1 - dx * (c) / dy;
				}
			}
			int xset = i;
			if (dx>dy){
				UB_VGA_SetPixel((xset),(y),254);
			}else{
				UB_VGA_SetPixel((y),(xset),254);
			}
		}

		y1 += 1;
		y2 += 1;

	}
	return 0;
}

int Vgascreen::draw_ellipse(int x_mp, int y_mp, int x_rad, int y_rad,int color){

	int hh = y_rad * y_rad;
	int ww = x_rad * x_rad;
	int hhww = hh * ww;
	int x0 = x_rad;
	int dx = 0;

	int fill = 1;

	// do the horizontal diameter
	for (int x = -x_rad; x <= x_rad; x++){
		if (fill==false){
			if (x == -x_rad || x == x_rad)
				UB_VGA_SetPixel(x_mp + x, y_mp, color);
		}
		else
			UB_VGA_SetPixel(x_mp + x, y_mp, color);
	}

	  // now do both halves at the same time, away from the diameter
	for (int y = 1; y <= y_rad; y++)
	{
		int x1 = x0 - (dx - 1);  // try slopes of dx - 1 or more
		for ( ; x1 > 0; x1--)
			if (x1*x1*hh + y*y*ww <= hhww)
				break;
	    dx = x0 - x1;  // current approximation of the slope
	    x0 = x1;

	    for (int x = -x0; x <= x0; x++)
	    {
	    	if (fill==false){
	    		if (x==-x0 || x==x0){
	    			UB_VGA_SetPixel(x_mp + x, y_mp - y, color);
	    			UB_VGA_SetPixel(x_mp + x, y_mp + y, color);
	    		}
	    	}
	    	else{
	    		UB_VGA_SetPixel(x_mp + x, y_mp - y, color);
	    		UB_VGA_SetPixel(x_mp + x, y_mp + y, color);
	    	}
	    }
	}


	hh = x_rad * x_rad;
	ww = y_rad * y_rad;
	hhww = hh * ww;
	x0 = y_rad;
	dx = 0;

	// do the horizontal diameter
	for (int x = -y_rad; x <= y_rad; x++) {
		if (fill == false) {
			if (x == -y_rad || x == y_rad)
				UB_VGA_SetPixel(x_mp, y_mp + x, color);
		} else
			UB_VGA_SetPixel(x_mp, y_mp + x, color);
	}

	// now do both halves at the same time, away from the diameter
	for (int y = 1; y <= x_rad; y++) {
		int x1 = x0 - (dx - 1);  // try slopes of dx - 1 or more
		for (; x1 > 0; x1--)
			if (x1 * x1 * hh + y * y * ww <= hhww)
				break;
		dx = x0 - x1;  // current approximation of the slope
		x0 = x1;

		for (int x = -x0; x <= x0; x++) {

			if (x == -x0 || x == x0) {
				UB_VGA_SetPixel(x_mp - y, y_mp + x, color);
				UB_VGA_SetPixel(x_mp + y, y_mp + x, color);
			}

		}
	}


	return 0;
}

int Vgascreen::draw_rectangle(int x_lo, int y_lo, int x_rb, int y_rb, int color){
	  draw_line(x_lo,y_rb,x_rb,y_rb,1,254);
	  draw_line(x_rb,y_rb+1,x_rb,y_lo,1,254);
	  draw_line(x_rb,y_lo,x_lo,y_lo,1,254);
	  draw_line(x_lo,y_lo,x_lo,y_rb,1,254);
}

int Vgascreen::draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color){
	  draw_line(x1,y1,x2,y2,1,254);
	  draw_line(x1,y1,x3,y3,1,254);
	  draw_line(x2,y2,x3,y3,1,254);
}

int Vgascreen::draw_text(int x, int y, char *text, char* font_name, int color, int style){
	return 0;
}

int Vgascreen::draw_bitmap(int nr, int x_lo, int y_lo){
	return 0;
}
