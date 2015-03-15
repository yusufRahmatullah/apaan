#include <cstdio>
#include "Projection.h"
#include "FrameBuffer.h"
#include "Point.h"

using namespace std;

FrameBuffer fb;

void DrawLine(int p1x, int p1y, int p2x, int p2y, unsigned int color){
	//Dummy
	/*
	if (color==0xF0F0F0F0){
		printf("RED\n");
	} else {
		printf("BLACK\n");
	}*/

	fb.drawLine(Point(p1x, p1y), Point(p2x, p2y), color);
}

int main(){
	double neg = -20;
	double pov =  20;
	double near = 100;
	double far =  140;
	unsigned int RED=0xFFFF0000, BLACK=0xFFFFFFFF;
	Projection proc;

	//init frame buffer
	fb.initScreen();

	//draw border for window
	DrawLine(320, 20, 1120, 20, BLACK);
	DrawLine(320, 820, 1120, 820, BLACK);
	DrawLine(320, 20, 320, 820, BLACK);
	DrawLine(1120, 20, 1120, 820, BLACK);
	//59 68 65
	_3Dpoint Dpoint1, Dpoint2, Dpoint3, Dpoint4, Dpoint5, Dpoint6, Dpoint7, Dpoint8;
	//draw front
	Dpoint1 = _3Dpoint(neg, near, pov);
	Dpoint2 = _3Dpoint(pov, near, pov);
	Dpoint3 = _3Dpoint(pov, near, pov);
	Dpoint4 = _3Dpoint(pov, near, neg);
	Dpoint5 = _3Dpoint(pov, near, neg);
	Dpoint6 = _3Dpoint(neg, near,neg);
	Dpoint7 = _3Dpoint(neg, near, neg);
	Dpoint8 = _3Dpoint(neg, near, pov);
	proc.Trans_Line(Dpoint1, Dpoint2);
	DrawLine(proc.p1.h, proc.p1.v, proc.p2.h, proc.p2.v, RED);
	proc.Trans_Line(Dpoint3, Dpoint4);
	DrawLine(proc.p1.h, proc.p1.v, proc.p2.h, proc.p2.v, RED);
	proc.Trans_Line(Dpoint5, Dpoint6);
	DrawLine(proc.p1.h, proc.p1.v, proc.p2.h, proc.p2.v, RED);
	proc.Trans_Line(Dpoint7, Dpoint8);
	DrawLine(proc.p1.h, proc.p1.v, proc.p2.h, proc.p2.v, RED);
	//draw back
	Dpoint1 = _3Dpoint(neg + 20, far, pov + 20);
	Dpoint2 = _3Dpoint(pov + 20, far, pov + 20);
	Dpoint3 = _3Dpoint(pov + 20, far, pov + 20);
	Dpoint4 = _3Dpoint(pov + 20, far, neg + 20);
	Dpoint5 = _3Dpoint(pov + 20, far, neg + 20);
	Dpoint6 = _3Dpoint(neg + 20, far, neg + 20);
	Dpoint7 = _3Dpoint(neg + 20, far, neg + 20);
	Dpoint8 = _3Dpoint(neg + 20, far, pov + 20);
	proc.Trans_Line(Dpoint1, Dpoint2);
	DrawLine(proc.p1.h, proc.p1.v, proc.p2.h, proc.p2.v, RED);
	proc.Trans_Line(Dpoint3, Dpoint4);
	DrawLine(proc.p1.h, proc.p1.v, proc.p2.h, proc.p2.v, RED);
	proc.Trans_Line(Dpoint5, Dpoint6);
	DrawLine(proc.p1.h, proc.p1.v, proc.p2.h, proc.p2.v, RED);
	proc.Trans_Line(Dpoint7, Dpoint8);
	DrawLine(proc.p1.h, proc.p1.v, proc.p2.h, proc.p2.v, RED);
	//draw left side
	Dpoint1 = _3Dpoint(neg, near, pov);
	Dpoint2 = _3Dpoint(neg + 20, far, pov + 20);
	Dpoint3 = _3Dpoint(neg + 20, far, pov + 20);
	Dpoint4 = _3Dpoint(neg + 20, far, -pov + 20);
	Dpoint5 = _3Dpoint(neg + 20, far, -pov + 20);
	Dpoint6 = _3Dpoint(neg + 20, near, -pov + 20);
	Dpoint7 = _3Dpoint(neg + 20, near, -pov + 20);
	Dpoint8 = _3Dpoint(neg, near, -pov);
	proc.Trans_Line(Dpoint1, Dpoint2);
	DrawLine(proc.p1.h, proc.p1.v, proc.p2.h, proc.p2.v, RED); 
	proc.Trans_Line(Dpoint3, Dpoint4);
	DrawLine(proc.p1.h, proc.p1.v, proc.p2.h, proc.p2.v, RED);
	proc.Trans_Line(Dpoint5, Dpoint6);
	DrawLine(proc.p1.h, proc.p1.v, proc.p2.h, proc.p2.v, RED);
	proc.Trans_Line(Dpoint7, Dpoint8);
	DrawLine(proc.p1.h, proc.p1.v, proc.p2.h, proc.p2.v, RED);
	//draw right side
	Dpoint1 = _3Dpoint(pov, near, pov);
	Dpoint2 = _3Dpoint(pov + 20, far, pov + 20);
	Dpoint3 = _3Dpoint(pov + 20, far, pov + 20);
	Dpoint4 = _3Dpoint(pov + 20, far, -pov + 20);
	Dpoint5 = _3Dpoint(pov + 20, far, -pov + 20);
	Dpoint6 = _3Dpoint(pov , near, -pov);
	Dpoint7 = _3Dpoint(pov , near, -pov);
	Dpoint8 = _3Dpoint(pov, near, -pov);
	proc.Trans_Line(Dpoint1, Dpoint2);
	DrawLine(proc.p1.h, proc.p1.v, proc.p2.h, proc.p2.v, RED);
	proc.Trans_Line(Dpoint3, Dpoint4);
	DrawLine(proc.p1.h, proc.p1.v, proc.p2.h, proc.p2.v, RED);
	proc.Trans_Line(Dpoint5, Dpoint6);
	DrawLine(proc.p1.h, proc.p1.v, proc.p2.h, proc.p2.v, RED);
	proc.Trans_Line(Dpoint7, Dpoint8);
	DrawLine(proc.p1.h, proc.p1.v, proc.p2.h, proc.p2.v, RED);

	fb.drawScreen();
}
