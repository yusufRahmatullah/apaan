#ifndef _KAPAL_H
#define _KAPAL_H
#include "MovingObject.h"
#include "Peluru.h"

class Kapal : public MovingObject {
	public:
		Kapal();
		Kapal(Point coord, int sz, int spdX, int spdY);
		void tembak();
		Peluru& getPeluru();
		void move();
	protected:
		void buildBody();
	private:
		Peluru peluru;
};

#endif

