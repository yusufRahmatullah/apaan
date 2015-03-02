#include "Rect.h"

Rect::Rect() : leftTop(0,0){
	width=0;
	height=0;
	color = 0xFFFFFFFF;
}
Rect::~Rect(){

}
Rect::Rect(Point left_Top, int height, int width, unsigned int color){
	leftTop = left_Top;
	this->height = height;
	this->width = width;
	this->color = color;
}
int Rect::getWidth(){
	return width;
}
int Rect::getHeight(){
	return height;
}
unsigned int Rect::getColor(){
	return color;
}
void Rect::setWidth(int newWidth){
	width = newWidth;
}
void Rect::setHeight(int newHeight){
	height = newHeight;
}
void Rect::setColor(unsigned int newColor){
	color = newColor;
}
void Rect::move(int moveX, int moveY){
	int x = leftTop.getX();
	int y = leftTop.getY();
	leftTop.setX(x+moveX);
	leftTop.setY(y+moveY);
}

void Rect::draw(FrameBuffer *fb){
	int x = leftTop.getX();
	int y = leftTop.getY();
	Point rT(x+width, y);
	Point rB(x+width, y+height);
	Point lB(x, y+height);

	fb->drawLine(leftTop, rT, color);
	fb->drawLine(rT, rB, color);
	fb->drawLine(rB, lB, color);
	fb->drawLine(lB, leftTop, color);
}
Point Rect::getLeftTop(){
	return leftTop;
}
void Rect::setLeftTop(Point P){
	leftTop.setX(P.getX());
	leftTop.setY(P.getY());
}
void Rect::setLeftTop(int x, int y){
	leftTop.setX(x);
	leftTop.setY(y);
}
