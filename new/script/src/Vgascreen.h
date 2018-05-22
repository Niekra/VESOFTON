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

	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */
	int init_VGA();

	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */
	int VGA_pos(int x, int y);

public:
	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */
	Vgascreen();

	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */
	virtual ~Vgascreen();

	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */
	int draw_line(int x1, int y1, int x2, int y2, int width, int color);

	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */
	int draw_ellipse(int x_mp, int y_mp, int x_rad, int y_rad,int color);

	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */
	int draw_rectangle(int x_lo, int y_lo, int x_rb, int y_rb, int color);

	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */
	int draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color);

	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */
	int draw_text(int x, int y, char *text, char* font_name, int color, int style);

	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */
	int draw_bitmap(int nr, int x_lo, int y_lo);

	/*!
	 * \brief teken een lijn.
	 * \param paramter int.
	 */

	int clear_screen(int color);
};

#endif /* VGASCREEN_H_ */
