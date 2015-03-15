#ifndef _MOVINGOBJECT_H
#define _MOVINGOBJECT_H
#include "Polygon.h"

class MovingObject {
	public:
		MovingObject();
		MovingObject(Point coor, int sz, int spdX, int spdY);
		MovingObject(const MovingObject& v);
		MovingObject& operator=(const MovingObject& v);
		~MovingObject();
		Polygon getBody();
		int getSpeedX();
		int getSpeedY();
		int getSize();
		Point getCoord();
		Point getCentroid();
		virtual void move();
	protected:
		Polygon body;
		int size, speedX, speedY;
		Point coord;
		virtual void buildBody();
};

#endif
