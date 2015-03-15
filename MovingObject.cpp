#include "MovingObject.h"

MovingObject::MovingObject() {
}
MovingObject::MovingObject(Point coor, int sz, int spdX, int spdY) {
	coord = coor;
	size = sz;
	speedX = spdX;
	speedY = spdY;
}
MovingObject::MovingObject(const MovingObject& v) {
	coord = v.coord;
	size = v.size;
	speedX = v.speedX;
	speedY = v.speedY;
	body = v.body;
}
MovingObject& MovingObject::operator=(const MovingObject& v) {
	coord = v.coord;
	size = v.size;
	speedX = v.speedX;
	speedY = v.speedY;
	body = v.body;
	return *this;
}
MovingObject::~MovingObject(){
}
Polygon MovingObject::getBody() {
	return body;
}
int MovingObject::getSpeedX() {
	return speedX;
}
int MovingObject::getSpeedY() {
	return speedY;
}
int MovingObject::getSize() {
	return size;
}
Point MovingObject::getCoord() {
	return coord;
}
Point MovingObject::getCentroid() {
	return body.getCentroid();
}
void MovingObject::move() {
	body.moveMe(speedX, speedY);
	coord.moveMe(speedX, speedY);
}
void MovingObject::buildBody() {
}
