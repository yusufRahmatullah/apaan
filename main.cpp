#include "FrameBuffer.h"
#include "Polygon.h"
#include "Rect.h"
#include <cstdio>
#include <string>
#include <cstring>
#include <termios.h>
#include <sys/select.h>
#define PI 3.14159265359
using namespace std;

Rect view, window;
struct termios orig_termios;
struct termios new_termios;

/*void loadMap(string mapname, vector<Point> &v, double scale) {
	FILE * filemap = fopen(mapname.c_str(), "r");
	int x,y;
	while(fscanf(filemap, "%d %d", &x, &y) != EOF) {
		Point p(x*scale,y*scale);
		v.push_back(p);
	}
	fclose(filemap);
}*/

void loadMap(string mapname, Polygon &poly, double scale) {
	FILE * filemap = fopen(mapname.c_str(), "r");
	int x,y;
	vector<Point> v;
	while(fscanf(filemap, "%d %d", &x, &y) != EOF) {
		Point p(x*scale,y*scale);
		v.push_back(p);
	}
	poly.setVertex(v);
	fclose(filemap);	
}

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

		if(keyCode == 'w'){
			window.move(0,-2);
		}else if(keyCode == 'a'){
			window.move(-2,0);
		}else if(keyCode == 's'){
			window.move(0,2);
		}else if(keyCode == 'd'){
			window.move(2, 0);
		}else if(keyCode == 'q'){
			window.setHeight(window.getHeight()+5);
			window.setWidth(window.getWidth()+5);
		}else if(keyCode == 'e'){
			window.setHeight(window.getHeight()-5);
			window.setWidth(window.getWidth()-5);
		}else if(keyCode == 27 || keyCode == 'p'){
			system("clear");
			exit(0);
		}
	}
}

void resetTerminal(){
	tcsetattr(0, TCSANOW, &orig_termios);
}

int main() {
	
	Polygon vsumatra, vjawa, vkalimantan, vsulawesi, vpapua;
	
	double scale = 0.5;
	loadMap("sumatra.txt", vsumatra, scale);
	loadMap("jawa.txt", vjawa, scale);
	loadMap("kalimantan.txt", vkalimantan, scale);
	loadMap("sulawesi.txt", vsulawesi, scale);
	loadMap("papua.txt", vpapua, scale);
	FrameBuffer fb;
	Point viewPoint(fb.getWidth()-301, fb.getHeight()-301);
	Point windowPoint(330, 330);
	
	// Set Rect
	view.setLeftTop(viewPoint);
	view.setWidth(300);
	view.setHeight(300);
	view.setColor(0xFFFF0000);
	window.setLeftTop(windowPoint);
	window.setHeight(50);
	window.setWidth(50);
	window.setColor(0xFF00FF00);
	
	//init keyboard listener
	tcgetattr(0, &orig_termios);
	memcpy(&new_termios, &orig_termios, sizeof(new_termios));
	atexit(resetTerminal);
	cfmakeraw(&new_termios);
	tcsetattr(0, TCSANOW, &new_termios);
	
	// Baling - baling
	vector<Point> vbaling1; 
	vbaling1.push_back(Point(0,0));
	vbaling1.push_back(Point(100,0));
	vbaling1.push_back(Point(52,50));
	vbaling1.push_back(Point(100,100));
	vbaling1.push_back(Point(0,100));
	vbaling1.push_back(Point(48,50));
	Polygon baling1(vbaling1);
	baling1.moveMe(0, 300);
	
	// Kapal
	vector<Point> vkapal;
	vkapal.push_back(Point(30,0));
	vkapal.push_back(Point(130,0));
	vkapal.push_back(Point(160,20));
	vkapal.push_back(Point(130,40));
	vkapal.push_back(Point(30,40));
	vkapal.push_back(Point(0,20));
	Polygon kapal(vkapal);
	kapal.moveMe(600, 320);
	
	//Peluru
	vector<Point> vpeluru;
	vpeluru.push_back(Point(0,0));
	vpeluru.push_back(Point(2,0));
	vpeluru.push_back(Point(2,2));
	vpeluru.push_back(Point(0,2));
	Polygon peluru(vpeluru);
	peluru.moveMe(500, 340);
	
	int i=0;
	double angle = 0;
	double rotate = PI * 0.1;
	int moveX = 0;
	double skala = 1.0;
	bool ketembak = false;
	bool nembak = false;
	
	/*** Bahan debug ***/
	Polygon balingkw = baling1;
	balingkw.move(-50, -30);
	vector<Point> vkotak;
	vkotak.push_back(Point(0,0));
	vkotak.push_back(Point(100, 0));
	vkotak.push_back(Point(100,100));
	vkotak.push_back(Point(0,100));
	Polygon kotak(vkotak);
	kotak.moveMe(340, 340);
	
	while(1) {
		handleInput();
		fb.initScreen();
		
		// Map
		fb.drawPolygon(vsumatra, 0x00FF00);
		fb.drawPolygon(vjawa, 0x00FF00);
		fb.drawPolygon(vkalimantan, 0x00FF00);
		fb.drawPolygon(vsulawesi, 0x00FF00);
		fb.drawPolygon(vpapua, 0x00FF00);
		//fb.drawPolygon(kotak, 0xFF0000);
		
		// Transformasi objek
		Polygon temp1,temp2;
		if (!ketembak) {
			temp1 = baling1.rotate(baling1.getCentroid(), angle);
			temp1.moveMe(moveX, 0);
		}
		if (nembak) {
			temp2 = peluru.scale(peluru.getCentroid(), skala);
		}
		kapal.moveMe(-2, 0);
		balingkw.rotateMe(baling1.getCentroid()	, angle);
		
		// Gambar objek
		if (!ketembak)
			fb.drawPolygon(temp1, 0xFF0000);
		if (nembak && !ketembak)
			fb.drawPolygon(temp2, 0x0FF0FF);
		fb.drawPolygon(kapal, 0x0000FF);
		fb.drawPolygon(balingkw, 0xF0F0F0);
		
		// Draw view dan window
		view.draw(&fb);
		window.draw(&fb);
		window.drawClip(vsumatra, view, &fb);
		window.drawClip(vjawa, view, &fb);
		window.drawClip(vkalimantan, view, &fb);
		window.drawClip(vsulawesi, view, &fb);
		window.drawClip(vpapua, view, &fb);
		window.drawClip(kapal, view, &fb);
		if(!ketembak) window.drawClip(temp1, view, &fb);
		if(nembak && !ketembak) window.drawClip(temp2, view, &fb);
		//window.drawClip(kotak, view, &fb);
		
		// Gambar semua
		fb.drawScreen();
		
		// Update objek
		angle += rotate;
		moveX += 2;
		if (!ketembak && nembak) {
			skala += 0.1;
			Point c = temp1.getCentroid();
			vector<Point> vp = temp2.getVertex();
			if (c.getX() >= vp[0].getX() && c.getX() <= vp[1].getX()
				&& c.getY() >= vp[0].getY() && c.getY() <= vp[3].getY())
				ketembak = true;
		}
		if (!nembak) {
			Point a = kapal.getCentroid();
			if( a.getX() <= 500 )
				nembak = true;
		}
	}
	return 0;
}
