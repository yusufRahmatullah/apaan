#ifndef _PESAWAT_H
#define _PESAWAT_H
#include "MovingObject.h"
#include "Peluru.h"
#include "FrameBuffer.h"

class Pesawat : public MovingObject {
	public:
		Pesawat();
		Pesawat(Point coord, int sz, int spdX, int spdY);
		~Pesawat();
		bool isExist();
		void cekKetembak(Peluru& peluru);
		Polygon* getPointerBody();
		Polygon getFrag1();
		Polygon getFrag2();
		Polygon getFrag3();
		Polygon getRoda();
		Polygon getBaling();
		Polygon* getPointerFrag1();
		Polygon* getPointerFrag2();
		Polygon* getPointerFrag3();
		Polygon* getPointerRoda();
		Polygon* getPointerBaling();
		void rotateFragments(double rotate);
		void drawRoda(FrameBuffer *fb, unsigned int ban, unsigned int velg);
		void maju();
		void drawPesawat(FrameBuffer* fb, unsigned int colorBody, unsigned int colorBaling);
	protected:
		void buildBody();
	private:
		bool exist;
		Polygon balingActive1, balingActive2;
		Polygon frag1, frag2, frag3, roda, baling;
		void buildFragments();
		void settingFragments();
};

#endif
