#ifndef _CURSOR_H
#define _CURSOR_H

#include "FrameBuffer.h"

class Cursor {	
	public :
		Cursor(Point coor);
		void drawCursor(FrameBuffer *fb, unsigned int color);
		void move(int dx, int dy);
		Point getCoord();
		Polygon cursor;
	private :
		Point coord;
};

#endif
