#ifndef POINT_H
#define POINT_H

#include "header.h"

class Point{
	private :
		int x,y;

	public :	
		Point();
		Point(int x, int y);
		Point(const Point &P);
		~Point();
		void setX(int new_x);
		void setY(int new_y);
		int getX();
		int getY();
};
#endif