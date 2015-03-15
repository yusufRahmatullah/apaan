#include "Ledakan.h"

Ledakan::Ledakan() {
}
Ledakan::Ledakan(int size, int maxsize, int time) {
	coord = Point(0,0);
	this->size = size;
	this->maxsize = maxsize;
	this->time = time;
	currsz = size;
	membesar = true;
	buildBody();
}
int Ledakan::getTime() {
	return time;
}
void Ledakan::animate(Point meledak) {
	float scale = (float)(maxsize-size)/10.0;
	
	if(membesar && currsz > maxsize)
		membesar = false;
	if(!membesar && currsz < size)
		membesar = true;
		
	if(membesar)
		currsz += scale;
	else
		currsz -= scale;
		
	body = cons.scale(cons.getCentroid(), currsz/size);
	body.moveMe(meledak.getX(), meledak.getY());
	
	time--;
}
Polygon Ledakan::getBody() {
	return body;
}
void Ledakan::buildBody() {
	int x = coord.getX();
	int y = coord.getY() - size/2;
	
	Point c(coord.getX(), coord.getY());
	Point p(x,y);
	double angle = 0.0;
	
	vector<Point> v1;
	for(int i=0; i<8; i++) {
		v1.push_back(p.rotate(c, angle));
		angle += 0.25*PI;
	}
	
	Polygon po1(v1);
	Polygon po2 = po1.scale(po1.getCentroid(), 0.5);
	po2.rotateMe(po2.getCentroid(), 0.125*PI);
	
	vector<Point> v;
	for(int i=0; i<8; i++) {
		v.push_back(po1.getVertex()[i]);
		v.push_back(po2.getVertex()[i]);
	}
	Polygon po(v);
	body = po;
	cons = po;
}
	
