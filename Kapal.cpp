#include "Kapal.h"
		
Kapal::Kapal() {
}
Kapal::Kapal(Point coord, int sz, int spdX, int spdY) : MovingObject(coord, sz, spdX, spdY) {
	buildBody();
}
void Kapal::tembak() {
	peluru.activate();
}
void Kapal::buildBody() {
	//Ukuran panjang:tinggi kapal 5:1
	int m = size;
	
	int x = coord.getX(), y = coord.getY();
	vector<Point> v;
	
	v.push_back( Point(x,		y) );
	v.push_back( Point(x+5*m, 	y) );
	v.push_back( Point(x+4*m, 	y+m));
	v.push_back( Point(x+m,		y+m));
	
	Polygon poly(v);
	body = poly;
	
	Point pos( (x+5*m)/2, y );
	Peluru plr(pos, size/20, 0, -10);
	peluru = plr;
}
void Kapal::move() {
	body.moveMe(speedX, speedY);
	if(!peluru.isExist())
		peluru.geser(speedX, speedY);
}
Peluru& Kapal::getPeluru() {
	return peluru;
}
