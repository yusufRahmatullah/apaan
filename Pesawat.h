#ifndef _PESAWAT_H
#define _PESAWAT_H
#include "MovingObject.h"
#include "Peluru.h"

class Pesawat : public MovingObject {
	public:
		Pesawat();
		Pesawat(Point coord, int sz, int spdX, int spdY);
		bool isExist();
		void cekKetembak(Peluru& peluru);
	protected:
		void buildBody();
	private:
		bool exist;
};

#endif
