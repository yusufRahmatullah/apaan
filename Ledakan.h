#ifndef _LEDAKAN_H
#define _LEDAKAN_H

#include "Polygon.h"

class Ledakan {
	public :
		Ledakan();
		Ledakan(int size, int maxsize, int time);
		int getTime();
		void animate(Point meledak);
		Polygon getBody();
	private:
		int time, size, maxsize;
		static const double PI = 3.14159;
		float currsz;
		bool membesar;
		Point coord;
		Polygon body, cons;
		void buildBody();
};

#endif
