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
		int width, height;
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
		void drawLayer(char * layer);
		int getWidth();
		int getHeight();
		void drawCircle(int xm, int ym, int r, unsigned int color);

		void fillPolygon(int x, int y, unsigned int color);
		void fillPolygon(Point P, unsigned int color);
		/*********************************************************/
		void fillPolygon(Polygon p, unsigned int color);
		void fillGrafik(int x, int y, vector< vector<int> > &grafik);
		vector< vector<int> > makeGrafik(Polygon p);
		void drawLineOnGrafik(vector< vector<int> > &grafik, int x0, int y0, int x1, int y1);
};
#endif
