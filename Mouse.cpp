#include "Mouse.h"

FILE* Mouse::fmouse;
Point Mouse::mousePos;
void Mouse::initMouse(){
	fmouse = fopen("/dev/input/mice", "r");
	mousePos = Point(0,0);
}
Point Mouse::getMousePos(){
	return mousePos;
}
void Mouse::finishMouse(){
	fclose(fmouse);
}
void Mouse::getMouseAttr(char *mouseAttr){
	fread(mouseAttr, sizeof(char), 3, fmouse);
}