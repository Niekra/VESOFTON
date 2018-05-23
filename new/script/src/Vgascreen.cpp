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
#include <string.h>

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

	int fill = 0;

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

	// do the vertical diameter
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
	  return 0;
}

int Vgascreen::draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color){
	  draw_line(x1,y1,x2,y2,1,254);
	  draw_line(x1,y1,x3,y3,1,254);
	  draw_line(x2,y2,x3,y3,1,254);
	  return 0;
}


int Vgascreen::draw_bitmap(int nr, int x_lo, int y_lo){
	int color;
	int count = 0;
	const int *bitmap;

	switch(nr)
	{
		case 1: bitmap = smileyBmp;
		break;
		case 2: bitmap = angryBmp;
		break;
		case 3: bitmap = arrowUp;
		break;
		case 4: bitmap = arrowDown;
		break;
		case 5: bitmap = arrowRight;
		break;
		case 6: bitmap = arrowLeft;
		break;
		default: return 1; // Geen geldig bitmap nummer
	}

	for(int i=0; i<32; i++)
	{
		for(int j=0; j<32; j++)
		{
			color = bitmap[count];
			if(color < 100)
			{
				UB_VGA_SetPixel(x_lo + j, y_lo + i, color);
			}
			count++;

		}
	}
	return 0;
}


int DrawChar(char c, int x, int y, int color, int stijl, int fontNr)
{
    int i,j, cursief, charWidth;
	int charHeight = 8;

//    }
    // Convert the character to an index
//    c = c & 0x7F;
//    if (c < ' ') {
//        c = 0;
//    } else {
//        c -= ' ';
//    }
//    c = 0x62;
    // 'font' is a multidimensional array of [96][char_width]
    // which is really just a 1D array of size 96*char_width.
//
    int index = c - 32;
    if (index<0 || index>95)
    	return 1; //ongeldige karakters ingevoerd

    const unsigned char* chr;
    chr = font2[index];

    switch(fontNr)
    {
    	case 1: chr = font1[index];
    			charWidth = 7;
    	break;
    	case 2: chr = font2[index];
    			charWidth = 6;
    	break;
    	default: chr = font1[index];
    			 charWidth = 7;
    	break;
    }

    // Draw pixels
    for (j=0; j<charWidth; j++) {
    	cursief = 0;
        for (i=0; i<charHeight; i++) {

            if (chr[j] & (1<<i)) {
            	if (stijl == 0)
            		UB_VGA_SetPixel(x+j-cursief, y+i, color);
            	else if(stijl == 1){
            		UB_VGA_SetPixel(x+j, y+i, color);
        			UB_VGA_SetPixel(x+j+1, y+i, color);
            	}
            	else
            		UB_VGA_SetPixel(x+j, y+i, color);
            }
            cursief++;
        }
    }
    return 0;
}

int Vgascreen::draw_text(int x, int y, const char *str, int color, const char* style, int fontNr)
{

	int stijl;
	if (strcmp(style, "cursief")==0)
		stijl = 0;
	else if (strcmp(style, "vet")==0)
		stijl = 1;
	else
		stijl = 3;

	while (*str) {
	        DrawChar(*str++, x, y, color, stijl, fontNr);
	        x += 6;
	    }
	return 0;
}


