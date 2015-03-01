#ifndef _POLYGON_H
#define _POLYGON_H
#include <vector>
#include "Point.h"
using namespace std;

class Polygon {
	public:
		Polygon();	//constructor default tanpa parameter
		Polygon(vector<Point> p);	//constructor dengan parameter
		Polygon(const Polygon& p);	//copy constructor
		Polygon& operator=(const Polygon& p);	//assignment
		~Polygon();	//destructor
		vector<Point> getVertex() const;
		Point getCentroid() const;
		void setVertex(vector<Point> p);
		void rotateMe(Point center, double angle);
		void scaleMe(Point center, double skala);
		void moveMe(int moveX, int moveY);
		Polygon rotate(Point center, double angle);
		Polygon scale(Point center, double skala);
		Polygon move(int moveX, int moveY);
	private:
		vector<Point> vertex;
		Point centroid;
		void findCentroid();
};

#endif
