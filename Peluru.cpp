#include "Peluru.h"

Peluru::Peluru(){
}
Peluru::Peluru(Point coord, int sz, int spdX, int spdY) : MovingObject(coord,sz,spdX,spdY) {
	buildBody();
	exist = false;
}
void Peluru::geser(int x, int y) {
	body.moveMe(x, y);
}
void Peluru::activate() {	
	exist = true;
}
void Peluru::deactivate() {
	exist = false;
}
bool Peluru::isExist() {
	return exist;
}
void Peluru::buildBody() {
	vector<Point> v;
	
	int x = coord.getX();
	int y = coord.getY();
	
	v.push_back(Point(x+1, y));
	v.push_back(Point(x+2, y+5));
	v.push_back(Point(x+2, y+10));
	v.push_back(Point(x, y+10));
	v.push_back(Point(x, y+5));
	
	Polygon p(v);
	p.scaleMe(p.getCentroid(), (double)size);
	
	body = p;
}
