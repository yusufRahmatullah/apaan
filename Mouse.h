#ifndef MOUSE_H
#define MOUSE_H

#include "header.h"
#include "Point.h"

class Mouse{
private:
	static FILE *fmouse;
	static Point mousePos;
public:	
	static void initMouse();
	static Point getMousePos();
	static void finishMouse();
	static void getMouseAttr(char *mouseAttr);
};
#endif