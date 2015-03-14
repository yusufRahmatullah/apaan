#include "Vertex.h"
#include <cmath>

Vertex::Vertex(){
	x=0; y=0; z=0;
}
Vertex::~Vertex(){

}
Vertex::Vertex(const Vertex& v){
	x = v.x;
	y = v.y;
	z = v.z;
}
Vertex::Vertex(int x, int y, int z){
	this->x = x;
	this->y = y;
	this->z = z;
}
Vertex& Vertex::operator=(const Vertex& v){
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;	
}
void Vertex::setX(int new_x){
	x = new_x;
}
void Vertex::setY(int new_y){
	y = new_y;
}
void Vertex::setZ(int new_z){
	z = new_z;
}
int Vertex::getX(){
	return x;
}
int Vertex::getY(){
	return y;
}
int Vertex::getZ(){
	return z;
}
void Vertex::rotateXAxis(Vertex center, double angle){
	//rotate in yz plane
	double cy, cz, dy, dz, cosn, sinn;

	cy = (double)center.y;
	cz = (double)center.z;
	dy = (double)y - cy;
	dz = (double)z - cz;

	cosn = cos(angle);
	sinn = sin(angle);

	y = cosn*dy - sinn*dz + cy;
	z = sinn*dy + cosn*dz + cz;
}
void Vertex::rotateYAxis(Vertex center, double angle){
	//rotate in zx plane
	double cz, cx, dz, dx, cosn, sinn;

	cz = (double)center.z;
	cx = (double)center.x;
	dz = (double)z - cz;
	dx = (double)x - cx;

	cosn = cos(angle);
	sinn = sin(angle);

	z = cosn*dz - sinn*dx + cz;
	x = sinn*dz + cosn*dx + cx;
}
void Vertex::rotateZAxis(Vertex center, double angle){
	//rotate in xy plane
	double cx, cy, dx, dy, cosn, sinn;

	cx = (double)center.x;
	cy = (double)center.y;
	dx = (double)x - cx;
	dy = (double)y - cy;

	cosn = cos(angle);
	sinn = sin(angle);

	x = cosn*dx - sinn*dy + cx;
	y = sinn*dx + cosn*dy + cy;
}
void Vertex::scale(Vertex center, double scale){
	double cx, cy, cz, dx, dy, dz;

	cx = (double)center.x;
	cy = (double)center.y;
	cz = (double)center.z;
	dx = (double)x - cx;
	dy = (double)y - cy;
	dz = (double)z - cz;

	x = scale*dx + cx;
	y = scale*dy + cy;
	z = scale*dz + cz;
}
void Vertex::move(int move_x, int move_y, int move_z){
	x += move_x;
	y += move_y;
	z += move_z;
}