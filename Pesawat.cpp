#include "Pesawat.h"

Pesawat::Pesawat() : MovingObject() {
}
Pesawat::Pesawat(Point coord, int sz, int spdX, int spdY) : MovingObject(coord, sz, spdX, spdY){
	buildBody();
	exist = true;
}
bool Pesawat::isExist() {
	return exist;
}
void Pesawat::cekKetembak(Peluru& peluru) {
	if (exist)
		if( body.isInside(peluru.getCentroid()) ) {
			exist = false;
			peluru.deactivate();
		}
}
void Pesawat::buildBody() {
	
	int size_x=-1, size_y=1;
	int szx = size*size_x;
	int szy = size*size_y;
	
	//int x=0;
	//int y= (3*szy)/2;
	
	int x = coord.getX();
	int y = coord.getY();
	
	vector<Point> v;

	//Menentukan 20 titik pesawat
	/*Point p1(3,2);
	Point p2(7,2);
	Point p3(8,0);
	Point p4(9,0);
	Point p5(9,4);
	Point p6(7,4);
	Point p7(9,6);
	Point p8(6,6);
	Point p9(4,4);
	Point p10(0,4);
	Point p11(2,3);*/
	
	v.push_back( Point(3,2) );
	v.push_back( Point(7,2) );
	v.push_back( Point(8,0) );
	v.push_back( Point(9,0) );
	v.push_back( Point(9,4) );
	v.push_back( Point(7,4) );
	v.push_back( Point(9,6) );
	v.push_back( Point(6,6) );
	v.push_back( Point(4,4) );
	v.push_back( Point(0,4) );
	v.push_back( Point(2,3) );
	
	Polygon P(v);
	P.scaleMe(P.getCentroid(), size);
	P.moveMe(coord.getX(), coord.getY());
	body = P;
}
