#include "FrameBuffer.h"
#include "Polygon.h"
#include <cstdio>
#include <string>
using namespace std;

void loadMap(string mapname, vector<Point> &v, double scale) {
	FILE * filemap = fopen(mapname.c_str(), "r");
	int x,y;
	while(fscanf(filemap, "%d %d", &x, &y) != EOF) {
		Point p(x*scale,y*scale);
		v.push_back(p);
	}
	fclose(filemap);
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
	fb.initScreen();
	fb.drawPolygon(vsumatra, 0x00FF00);
	fb.drawPolygon(vjawa, 0x00FF00);
	fb.drawPolygon(vkalimantan, 0x00FF00);
	fb.drawPolygon(vsulawesi, 0x00FF00);
	fb.drawPolygon(vpapua, 0x00FF00);
	fb.drawScreen();
	
	return 0;
}
