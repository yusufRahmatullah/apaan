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
		Point& operator=(const Point& p);
		~Point();
		void setX(int new_x);
		void setY(int new_y);
		int getX();
		int getY();
		void rotateMe(Point center, double angle);
		void scaleMe(Point center, double skala);
		void moveMe(int moveX, int moveY);
		Point rotate(Point center, double angle);
		Point scale(Point center, double skala);
		Point move(int moveX, int moveY);
};
#endif
