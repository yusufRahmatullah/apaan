#include "Cursor.h"

Cursor::Cursor(Point coor) {
	coord = coor;
	vector<Point> v;
	v.push_back( Point(0,0) );
	v.push_back( Point(1,5) );
	v.push_back( Point(2,3) );
	v.push_back( Point(4,5) );
	v.push_back( Point(5,4) );
	v.push_back( Point(3,2) );
	v.push_back( Point(5,1) );
	Polygon poly(v);
	cursor = poly;
	cursor.moveMe(coord.getX(), coord.getY());
}

void Cursor::drawCursor(FrameBuffer *fb, unsigned int color) {
	fb->drawPolygon(cursor, color);
	fb->fillPolygon(cursor.getCentroid(), color);
}

void Cursor::move(int dx, int dy) {
	cursor.moveMe(dx, dy);
	coord.moveMe(dx, dy);
}

Point Cursor::getCoord() {
	return coord;
}
