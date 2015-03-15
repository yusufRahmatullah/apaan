#ifndef _PELURU_H
#define _PELURU_H
#include "MovingObject.h"

class Peluru : public MovingObject {
	public:
		Peluru();
		Peluru(Point coord, int sz, int spdX, int spdY);
		void activate();
		void deactivate();
		void geser(int x, int y);
		bool isExist();
	protected:
		void buildBody();
	private:
		bool exist;
};

#endif
