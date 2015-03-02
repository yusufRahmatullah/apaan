#ifndef RECT_H
#define RECT_H

#include "header.h"
#include "Point.h"
#include "FrameBuffer.h"

class Rect{
	private :
		Point leftTop;
		int width, height;
		unsigned int color;
	public :
		Rect();
		~Rect();
		Rect(Point left_Top, int height, int width, unsigned int color);
		int getWidth();
		int getHeight();
		unsigned int getColor();
		Point getLeftTop();
		void setWidth(int newWidth);
		void setHeight(int newHeight);
		void setColor(unsigned int newColor);
		void setLeftTop(Point P);
		void setLeftTop(int x, int y);
		void move(int moveX, int moveY);
		void draw(FrameBuffer *fb);
};
#endif
