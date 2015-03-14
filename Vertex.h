#ifndef VERTEX_H
#define VERTEX_H

#include "header.h"

class Vertex{
private:
	int x,y,z;
public:
	Vertex();
	~Vertex();
	Vertex(const Vertex& v);
	Vertex(int x, int y, int z);
	Vertex& operator=(const Vertex& v);
	void setX(int new_x);
	void setY(int new_y);
	void setZ(int new_z);
	int getX();
	int getY();
	int getZ();
	void rotateXAxis(Vertex center, double angle);
	void rotateYAxis(Vertex center, double angle);
	void rotateZAxis(Vertex center, double angle);
	void scale(Vertex center, double scale);
	void move(int move_x, int move_y, int move_z);
};

#endif