#include <cstdio>
#include <iostream>
#include <unistd.h>
#include "Pesawat.h"
#include "Kapal.h"
#include "Peluru.h"
#include "Ledakan.h"
#include "Parabola.h"
#include "Parasut.h"
#include "FrameBuffer.h"
using namespace std;

// Sleep dalam mikrosekon
unsigned int delay = 100000;
void animation();

void handleInput(){
	int keyCode;
	int r;
	unsigned char c;
	struct timeval tv = {0L, 0L};
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(0, &fds);
	if(select(1, &fds, NULL, NULL, &tv)){
		if((r = read(0, &c, sizeof(c)))<0)
			keyCode = r;
		else
			keyCode = c;

		if(keyCode == 27 || keyCode == 'p'){
			system("clear");
			exit(0);
		}
	}
}

int main() {
	animation();
	
	return 0;
}

void animation() {
	int ground = 600;
	FrameBuffer fb;
	Pesawat pesawat(Point(1100,80), 20, -12, 0);
	Kapal kapal(Point(0,ground), 30, 10, 0);
	Ledakan ledakan(100, 300, 30);
	Parasut parasut(10, 3, 5);
	Peluru &peluru = kapal.getPeluru();
	Parabola frag1(pesawat.getPointerFrag1(), -10, 0, 4, ground, 0.5);
	Parabola frag2(pesawat.getPointerFrag2(), 10, 0, 4, ground, 0.5);
	Parabola frag3(pesawat.getPointerFrag3(), 5, 4, 4, ground, 0.5);
	Parabola roda(pesawat.getPointerRoda(), 4, 4, 4, ground, 0.5);
	Parabola baling(pesawat.getPointerBaling(), 6, 4, 4, ground, 0.5);
	
	int i=0;
	bool ketembak = false;
	double angle = 0.1;
	for(;;) {
		handleInput();
		fb.initScreen();
		
		/*Debug*/
		
		/* Cek ketembak */
		pesawat.cekKetembak(kapal.getPeluru());
		
		/* Menggambar objek */
		fb.drawLine(Point(0,ground), Point(fb.getWidth()-1, ground), 0x0000FF);		// Laut
		fb.drawPolygon(kapal.getBody(), 0x00FF00);
		if(pesawat.isExist()) {
			//fb.drawPolygon(pesawat.getBody(), 0x00FF00);
			pesawat.drawPesawat(&fb, 0x00FF00);
		} else {
			if (!ketembak) {
				ketembak = true;
				parasut.setCoord(pesawat.getCentroid().move(pesawat.getSize()*2, pesawat.getSize()*2));
			}
			if(ledakan.getTime() > 0)
				fb.drawPolygon(ledakan.getBody(), 0xFF0000);
			fb.drawPolygon(pesawat.getFrag1(), 0x00FF00);
			fb.drawPolygon(pesawat.getFrag2(), 0x00FF00);
			fb.drawPolygon(pesawat.getFrag3(), 0x00FF00);
			//fb.drawPolygon(pesawat.getRoda(), 0x00FF00);
			pesawat.drawRoda(&fb, 0x00FF00);
			fb.drawPolygon(pesawat.getBaling(), 0x00FF00);
			//fb.drawPolygon(parasut.getBody(), 0x0000FF);
			parasut.drawParasut(&fb, 0xFF0000);
		}
		if (peluru.isExist())
			fb.drawPolygon(peluru.getBody(), 0xFF0000);
			
		fb.drawScreen();
		
		/* Update objek */
		if (pesawat.isExist())
			pesawat.maju();
		else {
			ledakan.animate(pesawat.getCentroid());
			pesawat.rotateFragments(angle * 3.14159);
			frag1.update();
			frag2.update();
			frag3.update();
			roda.update();
			baling.update();
			parasut.update();
			angle -= 0.001;
			if (angle < 0.0)
				angle = 0.0;
		}
		if(peluru.isExist())
			peluru.move();
		kapal.move();
		
		/* Kondisi nembak */
		if(i == 20)
			kapal.tembak();
		i++;
		
		/* Delay */
		usleep(delay);

		if(parasut.getBody().getEkstremBawah().getY() >= ground) exit(0);
	}
}
