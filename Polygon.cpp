#include <cmath>
#include <cstdlib>
#include "Polygon.h"
#include <cmath>

Polygon::Polygon() {
}
Polygon::Polygon(vector<Point> p) {
	for (int i=0; i<p.size(); i++) {
		Point q(p[i].getX(), p[i].getY());
		vertex.push_back(q);
	}
	findCentroid();
	findExtreme();
}
Polygon::Polygon(const Polygon& p) {
	vertex = p.vertex;
	centroid = p.centroid;
	ekstremKiri = p.ekstremKiri;
	ekstremKanan = p.ekstremKanan;
	ekstremAtas = p.ekstremAtas;
	ekstremBawah = p.ekstremBawah;
}
Polygon& Polygon::operator=(const Polygon& p) {
	vertex = p.vertex;
	centroid = p.centroid;
	ekstremKiri = p.ekstremKiri;
	ekstremKanan = p.ekstremKanan;
	ekstremAtas = p.ekstremAtas;
	ekstremBawah = p.ekstremBawah;
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
vector<Point> Polygon::getVertex(){
	return vertex;
}
Point Polygon::getCentroid() {
	return centroid;
}
void Polygon::setVertex(vector<Point> p) {
	vertex = p;
	findCentroid();
	findExtreme();
}
void Polygon::rotateMe(Point center, double angle) {
	for(int i=0; i<vertex.size(); i++) {
		vertex[i].rotateMe(center, angle);
	}
	findCentroid();
	findExtreme();
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
	findExtreme();
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
	findExtreme();
}
Polygon Polygon::move(int moveX, int moveY) {
	Polygon p = *this;
	p.moveMe(moveX, moveY);
	return p;
}
Point Polygon::getEkstremKiri() {
	return ekstremKiri;
}
Point Polygon::getEkstremKanan(){
	return ekstremKanan;
}
Point Polygon::getEkstremAtas() {
	return ekstremAtas;
}
Point Polygon::getEkstremBawah() {
	return ekstremBawah;
}
void Polygon::findExtreme() {
	ekstremKiri = vertex[0];
	ekstremKanan = vertex[0];
	ekstremAtas = vertex[0];
	ekstremBawah = vertex[0];
	for(int i=1; i<vertex.size(); i++) {
		if(vertex[i].getX() < ekstremKiri.getX())
			ekstremKiri = vertex[i];
		if(vertex[i].getX() > ekstremKanan.getX())
			ekstremKanan = vertex[i];
		if(vertex[i].getY() < ekstremAtas.getY())
			ekstremAtas = vertex[i];
		if(vertex[i].getY() > ekstremBawah.getY())
			ekstremBawah = vertex[i];
	}
}

/*************************************************************************************
 * Fungsi-fungsi dibawah didapat dari 
 * http://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/ 
 * dengan modifikasi
*************************************************************************************/

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool Polygon::onSegment(Point p, Point q, Point r) {
    if (q.getX() <= max(p.getX(), r.getX()) && q.getX() >= min(p.getX(), r.getX()) &&
            q.getY() <= max(p.getY(), r.getY()) && q.getY() >= min(p.getY(), r.getY()))
        return true;
    return false;
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int Polygon::orientation(Point p, Point q, Point r) {
    int val = (q.getY() - p.getY()) * (r.getX() - q.getX()) -
              (q.getX() - p.getX()) * (r.getY() - q.getY());
 
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

bool Polygon::doIntersect(Point p1, Point q1, Point p2, Point q2)
{
    // Find the four orientations needed for general and
    // special cases
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
 
    // General case
    if (o1 != o2 && o3 != o4)
        return true;
 
    // Special Cases
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
 
    // p1, q1 and p2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
 
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
 
     // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;
 
    return false; // Doesn't fall in any of the above cases
}

// Returns true if the point p lies inside the polygon[] with n vertices
bool Polygon::isInside(Point p) {
    // There must be at least 3 vertices in polygon[]
    int n = vertex.size();
    if (n < 3)  return false;
 
    // Create a point for line segment from p to infinite
    Point extreme(INF, p.getY());
 
    // Count intersections of the above line with sides of polygon
    int count = 0, i = 0;
    do
    {
        int next = (i+1)%n;
 
        // Check if the line segment from 'p' to 'extreme' intersects
        // with the line segment from 'polygon[i]' to 'polygon[next]'
        if (doIntersect(vertex[i], vertex[next], p, extreme))
        {
            // If the point 'p' is colinear with line segment 'i-next',
            // then check if it lies on segment. If it lies, return true,
            // otherwise false
            if (orientation(vertex[i], p, vertex[next]) == 0)
               return onSegment(vertex[i], p, vertex[next]);
 
            count++;
        }
        i = next;
    } while (i != 0);
 
    // Return true if count is odd, false otherwise
    return count&1;  // Same as (count%2 == 1)
}
