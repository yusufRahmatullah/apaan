#include "Parabola.h"

Parabola::Parabola(){
}
Parabola::Parabola(Polygon *obj, int vx, int vy, int ay, int ground, float restitusi) {
	object = obj;
	this->vx = vx;
	this->vy = vy;
	this->ay = ay;
	this->ground = ground;
	this->restitusi = restitusi;
}
void Parabola::setVx(int v) {
	vx = v;
}
void Parabola::setVy(int v) {
	vy = v;
}
void Parabola::setAy(int ay) {
	this->ay = ay;
}
void Parabola::setGround(int gr) {
	ground = gr;
}
void Parabola::setRestitusi(float res) {
	restitusi = res;
}
void Parabola::setObject(Polygon* obj) {
	object = obj;
}
int Parabola::getVx() {
	return vx;
}
int Parabola::getVy() {
	return vy;
}
int Parabola::getAy() {
	return ay;
}
int Parabola::getGround() {
	return ground;
}
float Parabola::getRestitusi() {
	return restitusi;
}
void Parabola::update() {
	object->moveMe(vx, vy);
	vy += ay;
	Point p = object->getEkstremBawah();
	if ( p.getY() >= ground && vy > 0) {
		vy = (int)((float)vy * restitusi * -1);
	}
}
