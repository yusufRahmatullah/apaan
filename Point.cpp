#include "point.h"

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