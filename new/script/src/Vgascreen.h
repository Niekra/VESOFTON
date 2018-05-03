/*
 * VGA.h
 *
 *  Created on: May 3, 2018
 *      Author: M
 */
/*!
 * \brief de VGA class
 */
#ifndef VGASCREEN_H_
#define VGASCREEN_H_

class Vgascreen {
private:
	int x_pos;
	int y_pos;

public:
	Vgascreen();
	virtual ~Vgascreen();
	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */
	int draw_line(int x1, int y1, int x2, int y2, int width, int color);
};

#endif /* VGASCREEN_H_ */
