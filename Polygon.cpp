#include <cmath>
#include <cstdlib>
#include "Polygon.h"

Polygon::Polygon() {
}
Polygon::Polygon(vector<Point> p) {
	for (int i=0; i<p.size(); i++) {
		Point q(p[i].getX(), p[i].getY());
		vertex.push_back(q);
	}
	findCentroid();
}
Polygon::Polygon(const Polygon& p) {
	vertex = p.vertex;
	centroid.setX(p.getCentroid().getX());
	centroid.setY(p.getCentroid().getY());
}
Polygon& Polygon::operator=(const Polygon& p) {
	vertex = p.vertex;
	centroid.setX(p.getCentroid().getX());
	centroid.setY(p.getCentroid().getY());
	return *this;
}
Polygon::~Polygon() {
}
void Polygon::findCentroid() {
	int i;
	int x0, y0, x1, y1, cx, cy, A, a;
	
	A = 0; cx=0; cy=0;
	for(i=0; i<vertex.size()-1; i++) {
		x0 = vertex[i].getX();
		y0 = vertex[i].getY();
		x1 = vertex[i+1].getX();
		y1 = vertex[i+1].getY();
		a = x0*y1 - x1*y0;
		A += a;
		cx += (x0+x1) * a;
		cy += (y0+y1) * a;
	}
	x0 = vertex[i].getX();
	y0 = vertex[i].getY();
	x1 = vertex[0].getX();
	y1 = vertex[0].getY();
	a = x0*y1 - x1*y0;
	A += a;
	cx += (x0+x1) * a;
	cy += (y0+y1) * a;
	
	A *= 3;
	cx /= A;
	cy /= A;
	
	centroid.setX(cx);
	centroid.setY(cy);
}
vector<Point> Polygon::getVertex() const {
	return vertex;
}
Point Polygon::getCentroid() const {
	return centroid;
}
void Polygon::setVertex(vector<Point> p) {
	vertex = p;
	findCentroid();
}
void Polygon::rotateMe(Point center, double angle) {
	for(int i=0; i<vertex.size(); i++) {
		vertex[i].rotateMe(center, angle);
	}
	findCentroid();
}
Polygon Polygon::rotate(Point center, double angle) {
	Polygon p = *this;
	p.rotateMe(center, angle);
	return p;
}
void Polygon::scaleMe(Point center, double skala) {
	for(int i=0; i<vertex.size(); i++) {
		vertex[i].scaleMe(center, skala);
	}
	findCentroid();
}
Polygon Polygon::scale(Point center, double skala) {
	Polygon p = *this;
	p.scaleMe(center, skala);
	return p;
}
void Polygon::moveMe(int moveX, int moveY) {
	for(int i=0; i<vertex.size(); i++) {
		vertex[i].moveMe(moveX, moveY);
	}
	findCentroid();
}
Polygon Polygon::move(int moveX, int moveY) {
	Polygon p = *this;
	p.moveMe(moveX, moveY);
	return p;
}

