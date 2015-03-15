#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "header.h"
#include "Point.h"
#include "Polygon.h"
#include "FrameBuffer.h"
#include "Vertex.h"
#include <vector>
#include <utility>	//std::pair
using std::vector;
using std::pair;

#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min4(w, x, y, z) (min((w), min((x), min((y), (z))))
#define max4(w, x, y, z) (max((w), max((x), max((y), (z))))

class Object3D{
private:
	vector<Vertex> vertices;
	vector<pair<char, char> > edges; //pair of vertices' index
	vector<vector<char> > surfaces;	//vector of vertices' index
public:	
	Object3D();
	Object3D(const vector<Vertex> v, const vector<pair<char, char> > e, const vector<vector<char> > s);
	Object3D(const Object3D& o);
	Object3D(char* filename);
	Object3D& operator=(const Object3D& o);
	~Object3D();
	void setVertices(vector<Vertex> v);
	void setEdges(vector<pair<char, char> > e);
	void setSurfaces(vector<vector<char> > s);
	vector<Vertex> getVertices();
	vector<pair<char, char> > getEdges();
	vector<vector<char> > getSurfaces();
	void createObjectFromFile(char *filename);
	void saveObjectToFile(char *filename);
	Vertex getCenterVertice();
	void rotateXAxis(Vertex center, double angle);
	void rotateYAxis(Vertex center, double angle);
	void rotateZAxis(Vertex center, double angle);
	void scale(Vertex center, double scale);
	void move(int move_x, int move_y, int move_z);
	void drawOblique(FrameBuffer *fb);
	void drawIsometric(FrameBuffer *fb);
	void drawOrthogonal(FrameBuffer *fb);
};
#endif
