#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "header.h"
#include "Point.h"
#include "Polygon.h"

class FrameBuffer{
	private :
		struct fb_fix_screeninfo finfo;
		struct fb_var_screeninfo vinfo;
		int fbfd;
		long int screensize;
		char *backbuffer;
		char *fbp;
	public :	
		FrameBuffer();
		~FrameBuffer();

		void putPixel(int x, int y, unsigned int color);
		void putPixel(Point P, unsigned int color);
		void drawLine(Point p0, Point p1, unsigned int color);
		void drawPolygon(Polygon p, unsigned int color);
		unsigned int getPixel(int x, int y);
		unsigned int getPixel(Point P);
		long int getScreensize();
		long getRelativePosition(int x, int y);
		void initScreen();
		void drawScreen();
};
#endif
