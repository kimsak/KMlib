/*
 * Color.h
 *
 *  Created on: 2013/02/03
 *      Author: kimurayuusaku
 */

#ifndef COLOR_H_
#define COLOR_H_

struct Color {
	float R, G, B, A;

	Color() : R(1), G(1), B(1), A(1) {}
	Color(float r, float g, float b, float a) : R(r), G(g), B(b), A(a) {}
};

#define COLOR_WHITE		Color(1,1,1,1)
#define COLOR_RED		Color(1,0,0,1)
#define COLOR_GREEN		Color(0,1,0,1)
#define COLOR_BLUE		Color(0,0,1,1)
#define COLOR_YELLOW	Color(1,1,0,1)
#define COLOR_MAZENTA	Color(1,0,1,1)
#define COLOR_CYAN		Color(0,1,1,1)

#endif /* COLOR_H_ */
