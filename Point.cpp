#include "Point.h"
#include <cmath>

Point::Point(){
	x = 0; y=0;
}
Point::~Point(){

}
Point::Point(int x, int y){
	this->x = x;
	this->y = y;
}
Point::Point(const Point& P){
	x = P.x;
	y = P.y;
}
Point& Point::operator=(const Point& p) {
	x=p.x;
	y=p.y;
	return *this;
}
void Point::setX(int new_x){
	x = new_x;
}
void Point::setY(int new_y){
	y = new_y;
}
int Point::getX(){
	return x;
}
int Point::getY(){
	return y;
}
void Point::rotateMe(Point center, double angle) {
	double fx, fy, cx, cy, cosn, sinn;
	
	cx = (double)center.getX();
	cy = (double)center.getY();
	fx = (double)x - cx;
	fy = (double)y - cy;
	
	cosn = cos(angle);
	sinn = sin(angle);
	
	x = cosn*fx - sinn*fy + cx;
	y = sinn*fx + cosn*fy + cy;
}
void Point::scaleMe(Point center, double skala) {
	double cx, cy, fx, fy;
	
	cx = (double)center.getX();
	cy = (double)center.getY();
	fx = (double)x - cx;
	fy = (double)y - cy;
	
	x = skala*fx + cx;
	y = skala*fy + cy;
}
void Point::moveMe(int moveX, int moveY) {
	x += moveX;
	y += moveY;
}
Point Point::rotate(Point center, double angle) {
	Point p = *this;
	p.rotateMe(center, angle);
	return p;
}
Point Point::scale(Point center, double skala) {
	Point p = *this;
	p.scaleMe(center, skala);
	return p;
}
Point Point::move(int moveX, int moveY) {
	Point p = *this;
	p.moveMe(moveX, moveY);
	return p;
}
