#include "Pesawat.h"


Pesawat::Pesawat() : MovingObject() {
}
Pesawat::Pesawat(Point coord, int sz, int spdX, int spdY) : MovingObject(coord, sz, spdX, spdY){
	buildBody();
	buildFragments();
	exist = true;
}
Pesawat::~Pesawat() {
}
bool Pesawat::isExist() {
	return exist;
}
void Pesawat::cekKetembak(Peluru& peluru) {
	if (exist) {
		if( body.isInside(peluru.getCentroid()) ) {
			exist = false;
			peluru.deactivate();
			settingFragments();
		}
	}
}
void Pesawat::maju() {
	move();
	balingActive1.rotateMe(balingActive1.getVertex()[0], 0.6*3.14159);
	balingActive2.rotateMe(balingActive2.getVertex()[0], 0.6*3.14159);
	balingActive1.moveMe(speedX, speedY);
	balingActive2.moveMe(speedX, speedY);
}
void Pesawat::buildBody() {
	vector<Point> v, b1, b2;
	
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
	
	/* Main body */
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
	
	/* Baling active */
	b1.push_back( Point(7,2) );
	b1.push_back( Point(6,1) );
	b1.push_back( Point(8,1) );
	
	b2.push_back( Point(7,2) );
	b2.push_back( Point(8,3) );
	b2.push_back( Point(6,3) );
	
	
	Polygon P(v);
	Polygon bl1(b1);
	Polygon bl2(b2);
	
	P.scaleMe(P.getCentroid(), size);
	bl1.scaleMe(bl1.getCentroid(), size);
	bl2.scaleMe(bl2.getCentroid(), size);
	
	P.moveMe(coord.getX(), coord.getY());
	
	int x = P.getVertex()[1].getX();
	int y = P.getVertex()[1].getY();
	bl1.moveMe(x-bl1.getVertex()[0].getX(), y-bl1.getVertex()[0].getY());
	bl2.moveMe(x-bl2.getVertex()[0].getX(), y-bl2.getVertex()[0].getY());
	
	body = P;
	balingActive1 = bl1;
	balingActive2 = bl2;
}
Polygon* Pesawat::getPointerBody() {
	return &body;
}
void Pesawat::buildFragments() {
	vector<Point> f1, f2, f3, rd, bl;
	
	/* Fragment 1 */
	f1.push_back( Point(3,2) );
	f1.push_back( Point(5,2) );
	f1.push_back( Point(4,3) );
	f1.push_back( Point(5,3) );
	f1.push_back( Point(6,4) );
	f1.push_back( Point(0,4) );
	f1.push_back( Point(2,3) );
	
	/* Fragment 2 */
	f2.push_back( Point(5,2) );
	f2.push_back( Point(7,2) );
	f2.push_back( Point(8,0) );
	f2.push_back( Point(9,0) );
	f2.push_back( Point(9,4) );
	f2.push_back( Point(6,4) );
	f2.push_back( Point(5,3) );
	f2.push_back( Point(4,3) );
	
	/* Fragment 3 */
	f3.push_back( Point(4,4) );
	f3.push_back( Point(7,4) );
	f3.push_back( Point(9,6) );
	f3.push_back( Point(6,6) );
	
	/* Roda */
	int x = 0;
	int y = -size;
	
	Point c(0,0);
	Point p(x,y);
	double angle = 0.0;
	
	vector<Point> v1;
	for(int i=0; i<40; i++) {
		rd.push_back(p.rotate(c, angle));
		angle += 3.14159/20;
	}
	
	
	/* Baling */
	bl.push_back( Point(0,0) );
	bl.push_back( Point(1,0) );
	bl.push_back( Point(1,10) );
	bl.push_back( Point(0,10) );
	
	/* Bentuk polygon */
	Polygon p1(f1);
	Polygon p2(f2);
	Polygon p3(f3);
	Polygon pr(rd);
	Polygon pb(bl);
	
	/* Transformasi */
	p1.scaleMe(p1.getCentroid(), size);
	p2.scaleMe(p2.getCentroid(), size);
	p3.scaleMe(p3.getCentroid(), size);
	pb.scaleMe(pb.getCentroid(), size/2);
	
	
	/* Assignment */
	frag1 = p1;
	frag2 = p2;
	frag3 = p3;
	roda = pr;
	baling = pb;
}

void Pesawat::settingFragments() {
	int x = body.getCentroid().getX();
	int y = body.getCentroid().getY();
	
	frag1.moveMe(x,y);
	frag2.moveMe(x,y);
	frag3.moveMe(x,y);
	roda.moveMe(x,y);
	baling.moveMe(x,y);
	
	frag1.moveMe(-7*size, 0);
	frag2.moveMe(7*size, 0);
	frag3.moveMe(0, 5*size);
	roda.moveMe(size, size);
	baling.moveMe(size, size);
}

Polygon Pesawat::getFrag1() {
	return frag1;
}
Polygon Pesawat::getFrag2() {
	return frag2;
}
Polygon Pesawat::getFrag3() {
	return frag3;
}
Polygon Pesawat::getRoda() {
	return roda;
}
Polygon Pesawat::getBaling() {
	return baling;
}
Polygon* Pesawat::getPointerFrag1() {
	return &frag1;
}
Polygon* Pesawat::getPointerFrag2() {
	return &frag2;
}
Polygon* Pesawat::getPointerFrag3() {
	return &frag3;
}
Polygon* Pesawat::getPointerRoda() {
	return &roda;
}
Polygon* Pesawat::getPointerBaling() {
	return &baling;
}

void Pesawat::rotateFragments(double rotate) {
	frag1.rotateMe(frag1.getCentroid(), rotate);
	frag2.rotateMe(frag2.getCentroid(), rotate);
	frag3.rotateMe(frag3.getCentroid(), rotate);
	//roda.rotateMe(roda.getCentroid(), rotate);
	baling.rotateMe(baling.getCentroid(), 5*rotate);
}

void Pesawat::drawRoda(FrameBuffer *fb, unsigned int color) {
	fb->drawPolygon(roda, color);
	fb->drawPolygon(roda.scale(roda.getCentroid(), 0.5), color);
}
void Pesawat::drawPesawat(FrameBuffer* fb, unsigned int color) {
	fb->drawPolygon(body, color);
	fb->drawPolygon(balingActive1, color);
	fb->drawPolygon(balingActive2, color);
}
