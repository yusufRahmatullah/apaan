#include "FrameBuffer.h"
#include "Polygon.h"
#include "Rect.h"
#include <cstdio>
#include <string>
#include <cstring>
#include <termios.h>
#include <sys/select.h>
using namespace std;

Rect view, window;
struct termios orig_termios;
struct termios new_termios;

void loadMap(string mapname, vector<Point> &v, double scale) {
	FILE * filemap = fopen(mapname.c_str(), "r");
	int x,y;
	while(fscanf(filemap, "%d %d", &x, &y) != EOF) {
		Point p(x*scale,y*scale);
		v.push_back(p);
	}
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
	
	vector<Point> vsumatra, vjawa, vkalimantan, vsulawesi, vpapua;
	double scale = 0.5;
	loadMap("sumatra.txt", vsumatra, scale);
	loadMap("jawa.txt", vjawa, scale);
	loadMap("kalimantan.txt", vkalimantan, scale);
	loadMap("sulawesi.txt", vsulawesi, scale);
	loadMap("papua.txt", vpapua, scale);
	FrameBuffer fb;
	Point viewPoint(fb.getWidth()-301, fb.getHeight()-301);
	Point windowPoint(100, 100);

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

	while(true){
		handleInput();
		fb.initScreen();
		fb.drawPolygon(vsumatra, 0x00FF00);
		fb.drawPolygon(vjawa, 0x00FF00);
		fb.drawPolygon(vkalimantan, 0x00FF00);
		fb.drawPolygon(vsulawesi, 0x00FF00);
		fb.drawPolygon(vpapua, 0x00FF00);
		view.draw(&fb);
		window.draw(&fb);
		window.drawClip(vsumatra, view, &fb);
		window.drawClip(vjawa, view, &fb);
		window.drawClip(vkalimantan, view, &fb);
		window.drawClip(vsulawesi, view, &fb);
		view.drawClip(vpapua, window, &fb);
		fb.drawScreen();
	}	
	return 0;
}
