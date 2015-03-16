#include "Parasut.h"
#include <ctime>
#include <cstdio>
#include <cstdlib>

Parasut::Parasut(int sz, int spdX, int spdY) {
	size = sz;
	speedX = spdX;
	speedY = spdY;
	buildBody();
}
void Parasut::update() {
	srand(time(NULL));
	int dx = rand() % speedX + 1;
	int sign = rand() % 2;
	if (!sign)
		dx *= -1;
	
	body.moveMe(dx,speedY);
	pc.moveMe(dx,speedY);
}
void Parasut::setCoord(Point coord) {
	/*int dx = coord.getX() - body.getCentroid().getX();
	int dy = coord.getY() - body.getCentroid().getY();
	body.moveMe(dx,dy);
	pc.moveMe(dx,dy);*/
}
Polygon Parasut::getBody() {
	return body;
}
void Parasut::buildBody() {
	vector<Point> v;
	
	v.push_back( Point(0,1) );
	v.push_back( Point(2,0) );
	v.push_back( Point(4,0) );
	v.push_back( Point(6,1) );
	v.push_back( Point(6,5) );
	v.push_back( Point(5,7) );
	v.push_back( Point(4,6) );
	v.push_back( Point(3,7) );
	v.push_back( Point(2,6) );
	v.push_back( Point(1,7) );
	v.push_back( Point(0,5) );
	
	/*Point p1(1,7);
	Point p2(3,7);
	Point p3(5,7);*/
	Point c(3,9);
	
	Polygon p(v);
	c.scaleMe(p.getCentroid(), size);
	p.scaleMe(p.getCentroid(), size);
	
	body = p;
	pc = c;
}
void Parasut::drawParasut(FrameBuffer *fb, unsigned int color) {
	fb->drawPolygon(body, color);
	fb->fillPolygon(body, color);
	fb->drawLine(body.getVertex()[5], pc, color);
	fb->drawLine(body.getVertex()[7], pc, color);
	fb->drawLine(body.getVertex()[9], pc, color);
}
