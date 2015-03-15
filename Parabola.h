#ifndef _PARABOLA_H
#define _PARABOLA_H

#include "Polygon.h"

class Parabola {
	public:
		Parabola();
		Parabola(Polygon *obj, int vx, int vy, int ay, int ground, float restitusi);
		void setVx(int v);
		void setVy(int v);
		void setAy(int ay);
		void setGround(int gr);
		void setRestitusi(float res);
		void setObject(Polygon *obj);
		int getVx();
		int getVy();
		int getAy();
		int getGround();
		float getRestitusi();
		void update();
	private:
		int vx, vy, ay, ground;
		float restitusi;
		Polygon *object;
};

#endif
