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

Vgascreen::Vgascreen()
{
	// TODO Auto-generated constructor stub
	init_VGA();
}

Vgascreen::~Vgascreen()
{
	// TODO Auto-generated destructor stub
}

int Vgascreen::init_VGA()
{
	UB_VGA_Screen_Init(); // Init VGA-Screen
	UB_VGA_FillScreen(VGA_COL_GREEN); // Set screen green.
	return 0;
}

int Vgascreen::VGA_pos(int x, int y)
{
	x_pos = x; // Set x position.
	y_pos = y; // Set y position.
	return 0;
}

int Vgascreen::draw_line(int x1, int y1, int x2, int y2, int width, int color)
{

	const int dx = abs(x1 - x2);
	const int dy = abs(y1 - y2);
	bool a = true;

	if (dx == 0 && dy == 0){
		UB_VGA_SetPixel(x1, y1, color);
	}

	if (dy > dx)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	if (y1 > y2)
	{
		a = false;
	}

	int y;
	int c;
	for (int j = 0; j < width; j++)
	{
		for (int i = x1; i < x2; i++)
		{
			c = i - x1;
			if (a)
			{
				if (dx > dy)
				{
					y = y1 + dy * (c) / dx;
				}
				else
				{
					y = y1 + dx * (c) / dy;
				}
			}
			else
			{
				if (dx > dy)
				{
					y = y1 - dy * (c) / dx;
				}
				else
				{
					y = y1 - dx * (c) / dy;
				}
			}
			int xset = i;
			if (dx > dy)
			{
				UB_VGA_SetPixel((xset), (y), color);
			}
			else
			{
				UB_VGA_SetPixel((y), (xset), color);
			}
		}
		y1 += 1;
		y2 += 1;
	}
	return 0;
}

int Vgascreen::draw_ellipse(int x_mp, int y_mp, int x_rad, int y_rad, int color, int fill)
{
	int w = int(x_rad/2);//deel hoogte en breedte door 2. Dit wordt gedaan omdat deze waardes omdat de straal gebruikt wordt.
	int h = int(y_rad/2);
	int hh = h * h;
	int ww = w * w;
	int hhww = hh * ww;
	int x0 = w; //breedte bij huidige hoogte
	int dx = 0; //delta x

	// teken eerst de horizontale diameter
	for (int x = -w; x <= w; x++) //loop van negatieve straal tot positieve straal
	{
		if (fill != true)//vul niet wanneer fill geen '1' is
		{
			if (x == -w || x == w) //teken alleen pixel op de uiteindes
				UB_VGA_SetPixel(x_mp + x, y_mp, color);
		}
		else
			UB_VGA_SetPixel(x_mp + x, y_mp, color);
	}

	// teken beide helften van de ellips tegelijk vanaf het midden tot de uiteindes
	for (int y = 1; y <= h; y++)//loop de verticale straal af
	{
		int x1 = x0 - (dx - 1);  //vind de juiste waarde voor x1 in verband met de helling
		for (; x1 > 0; x1--)
			if (x1 * x1 * hh + y * y * ww <= hhww)
				break;
		dx = x0 - x1;  // huidige schatting van de helling
		x0 = x1; //maak x0 huidige breedte ten opzichte van de hoogte

		for (int x = -x0; x <= x0; x++) //teken pixels langs de breedte
		{
			if (fill != true)
			{
				if (x == -x0 || x == x0)
				{
					UB_VGA_SetPixel(x_mp + x, y_mp - y, color);
					UB_VGA_SetPixel(x_mp + x, y_mp + y, color);
				}
			}
			else
			{
				UB_VGA_SetPixel(x_mp + x, y_mp - y, color);
				UB_VGA_SetPixel(x_mp + x, y_mp + y, color);
			}
		}
	}

	// teken de ellips nogmaals 90 graden gedraaid om de pixels aan de randen die niet zijn meegepakt alsnog te vullen.
	std::swap(h, w); //verwissel hoogte en breedte om de vorm van de ellips te behouden
	std::swap(hh, ww);
	x0 = w;
	dx = 0;

	// do the vertical diameter
	for (int x = -w; x <= w; x++)
	{
		if (fill != true)
		{
			if (x == -w || x == w)
				UB_VGA_SetPixel(x_mp, y_mp + x, color);
		}
		else
			UB_VGA_SetPixel(x_mp, y_mp + x, color);
	}

	for (int y = 1; y <= w; y++)
	{
		int x1 = x0 - (dx - 1);
		for (; x1 > 0; x1--)
			if (x1 * x1 * hh + y * y * ww <= hhww)
				break;
		dx = x0 - x1;
		x0 = x1;

		for (int x = -x0; x <= x0; x++)
		{
			if (x == -x0 || x == x0)
			{
				UB_VGA_SetPixel(x_mp - y, y_mp + x, color);
				UB_VGA_SetPixel(x_mp + y, y_mp + x, color);
			}
		}
	}
	return 0;
}

int Vgascreen::draw_rectangle(int x_lo, int y_lo, int x_rb, int y_rb, int color, int fill)
{
	const int breedte = abs(y_lo - y_rb); //bereken breedte van de rechthoek

	if (fill != true) //wanneer niet gevuld, teken lijnen tussen elk hoekpunt
	{
		draw_line(x_lo, y_rb, x_rb, y_rb, 1, color);
		draw_line(x_rb, y_rb + 1, x_rb, y_lo, 1, color);
		draw_line(x_rb, y_lo, x_lo, y_lo, 1, color);
		draw_line(x_lo, y_lo, x_lo, y_rb, 1, color);
	}
	else
		draw_line(x_lo, y_lo, x_rb, y_lo, breedte, color);//om te vullen, teken één lijn ter breedte van de rechthoek

	return 0;
}


int Vgascreen::draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3,
		int color, int fill)
{

	if (fill != true) //als de driehoek niet gevuld hoeft te worden, teken een lijn tussen elk punt
	{
		draw_line(x1, y1, x2, y2, 1, color);
		draw_line(x1, y1, x3, y3, 1, color);
		draw_line(x2, y2, x3, y3, 1, color);
	}
	else
	{
		int pt0[3] = {x1, y1}; //definieer hoekpunten
		int pt1[3] = {x2, y2};
		int pt2[3] = {x3, y3};

		if (pt0[1] > pt1[1]) //sorteer punten op hoogte. pt0 is het hoogst op het scherm, pt2 laagst
			std::swap(pt0, pt1);
		if (pt0[1] > pt2[1])
			std::swap(pt0, pt2);
		if (pt1[1] > pt2[1])
			std::swap(pt1, pt2);

		int total_height = pt2[1] - pt0[1]; //totale hoogte van de driehoek
		for (int y = pt0[1]; y <= pt1[1]; y++) //teken de bovenste helft van de driehoek
		{
			int segment_height = pt1[1] - pt0[1] + 1; //hoogte van de bovenste helft van de driehoek+1
			float alpha = (float) (y - pt0[1]) / total_height; //bereken de verhouding van y op totale hoogte
			float beta = (float) (y - pt0[1]) / segment_height;//bereken de verhouding van y op de bovenste helft
			int A = int(pt0[0] + (pt2[0] - pt0[0]) * alpha);//bereken hoeveel pixels er getekend moeten worden tot de middenlijn van de driehoek
			int B = int(pt0[0] + (pt1[0] - pt0[0]) * beta);//nu van de andere kant van de driehoek
			if (A > B)
				std::swap(A, B);
			for (int j = A; j <= B; j++) //teken pixels van breedtecoördinaat A tot B
			{
				UB_VGA_SetPixel(j, y, color);
			}
		}

		for (int y = pt1[1]; y <= pt2[1]; y++)//nu hetzelfde voor de onderzijde van de driehoek
		{
			int segment_height = pt2[1] - pt1[1] + 1;
			float alpha = (float) (y - pt0[1]) / total_height;
			float beta = (float) (y - pt1[1]) / segment_height;
			int A = int(pt0[0] + (pt2[0] - pt0[0]) * alpha);
			int B = int(pt1[0] + (pt2[0] - pt1[0]) * beta);

			if (A > B)
				std::swap(A, B);
			for (int j = A; j <= B; j++)
			{
				UB_VGA_SetPixel(j, y, color);
			}
		}

	}
	return 0;
}


int Vgascreen::draw_bitmap(int nr, int x_lo, int y_lo)
{
	int color;
	int count = 0;
	const int *bitmap;

	switch (nr)
	{
		case 0:
			bitmap = smileyBmp;
			break;
		case 1:
			bitmap = angryBmp;
			break;
		case 2:
			bitmap = arrowUp;
			break;
		case 3:
			bitmap = arrowDown;
			break;
		case 4:
			bitmap = arrowRight;
			break;
		case 5:
			bitmap = arrowLeft;
			break;
		default:
			return 1; // Geen geldig bitmap nummer
	}

	for (int i = 0; i < 32; i++)//alle bitmaps zijn 32 bij 32. Loop elk element van de bitmap af
	{
		for (int j = 0; j < 32; j++)
		{
			color = bitmap[count];
			if (color < 100) // filter de witte achtergrond weg
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
	int i, j, cursief, charWidth;
	int charHeight = 8;
	int index = c - 32;// zorg dat charakterwaarde overeenkomt met die in de bitmap font

	if (index < 0 || index > 95)
		return 1; //ongeldige karakters ingevoerd

	const unsigned char* chr;
	chr = font2[index];

	switch (fontNr)
	{
		case 1:
			chr = font1[index];
			charWidth = 7;
			break;
		case 2:
			chr = font2[index];
			charWidth = 6;
			break;
		default:
			chr = font1[index];
			charWidth = 7;
			break;
	}

	// Draw pixels
	for (j = 0; j < charWidth; j++)//loop charakter in de breedte af
	{
		cursief = 0;
		for (i = 0; i < charHeight; i++)//teken een van de verticale lijnen van een charakter
		{
			if (chr[j] & (1 << i))// Elk charakter is opgebouwd uit een aantal hex waardes. Elke waarde omgezet naar binair, is een verticale lijn waaruit een charakter is opgebouwd
			{
				if (stijl == 0)
					UB_VGA_SetPixel(x + j - cursief, y + i, color);//verschuif de breedte elke laag iets meer voor een cursief effect
				else if (stijl == 1)
				{
					UB_VGA_SetPixel(x + j, y + i, color);
					UB_VGA_SetPixel(x + j + 1, y + i, color);
				}
				else
					UB_VGA_SetPixel(x + j, y + i, color);
			}
			cursief++;
		}
	}
	return 0;
}

int Vgascreen::draw_text(int x, int y, const char *str, int color,
		const char* style, int fontNr)
{

	int stijl;//zet stijl om naar int
	if (strcmp(style, "cursief") == 0)
		stijl = 0;
	else if (strcmp(style, "vet") == 0)
		stijl = 1;
	else
		stijl = 3;

	while (*str)//teken charakters een voor een
	{
		DrawChar(*str++, x, y, color, stijl, fontNr);
		x += 6;//spring één charakterbreedte naar rechts voor het volgende charakter
	}
	return 0;
}

int Vgascreen::clear_screen(int color)
{
	UB_VGA_FillScreen(color);
	return 0;
}
