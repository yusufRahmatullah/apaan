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
	
	/*v.push_back( Point(x,		y) );
	v.push_back( Point(x+5*m, 	y) );
	v.push_back( Point(x+4*m, 	y+m));
	v.push_back( Point(x+m,		y+m));*/
	
	v.push_back( Point(0,1) );
	v.push_back( Point(2,1) );
	v.push_back( Point(2,0) );
	v.push_back( Point(5,0) );
	v.push_back( Point(5,1) );
	v.push_back( Point(7,1) );
	v.push_back( Point(6,2) );
	v.push_back( Point(1,2) );
	
	Polygon poly(v);
	poly.scaleMe(poly.getCentroid(), size);
	poly.moveMe(coord.getX(), coord.getY());
	body = poly;
	
	Point pos( (body.getVertex()[2].getX()+body.getVertex()[3].getX())/2, body.getVertex()[2].getY() );
	Peluru plr(pos, (int)((float)size/20.0), 0, -10);
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
