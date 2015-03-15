#ifndef _PARASUT_H
#define _PARASUT_H

#include "Polygon.h"
#include "FrameBuffer.h"

class Parasut {	
	public:
		Parasut(int sz, int spdX, int spdY);
		void setCoord(Point coord);
		void update();
		Polygon getBody();
		void drawParasut(FrameBuffer *fb, unsigned int color);
	private:
		int size, speedX, speedY;
		Point pc;
		Polygon body;
		void buildBody();
};

#endif
