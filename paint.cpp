#include "header.h" 
#include "FrameBuffer.h"
#include "Keyboard.h"
#include "Point.h"
#include "Cursor.h"
#include <cmath>
#include <pthread.h>

#define MOUSE_POS 100
#define EXTREME_LEFT	0
#define EXTREME_RIGHT	1366
#define EXTREME_TOP		0
#define EXTREME_BOTTOM	768

//global variable
FrameBuffer fb;
char shape;
int xt, yt, xn, ynn;
int curPosX, curPosY;
unsigned char threadLoop = 1;
unsigned char isPalleteShow = 0;
unsigned int storedColor = 0xFFFFFF;

void* handleInput(void * arg)
{
	Keyboard::initKeyboard();

	while(threadLoop)
	{
		if(Keyboard::isKeyPressed())
		{
			if(Keyboard::getKeyCode() == '1')
			{
				shape = 'r';
			}
			else if(Keyboard::getKeyCode() == '2')
			{
				shape = 'c';
			}
			else if (Keyboard::getKeyCode() == '3')
			{
				shape = 'p';
			}else if (Keyboard::getKeyCode() == '4')
			{
				shape = 'f';
			}else if (Keyboard::getKeyCode() == 'p')
			{
				isPalleteShow = 1;
			}
			else if (Keyboard::getKeyCode() == 27)
			{
				threadLoop = 0;
			}
		}	
	}
	
	Keyboard::resetTerminal();
	return NULL;
}

void putPixelOnLayer(int x, int y, unsigned int color, char* layer){
	long int location = fb.getRelativePosition(x, y);
	*(layer+location) = (color&0xFF);
	*(layer+location+1) = ((color&0xFF00)>>8);
	*(layer+location+2) = ((color&0xFF0000)>>16);
	*(layer+location+3) = ((color&0xFF000000)>>24);
}
void drawLineOnLayer(int x0, int y0, int x1, int y1, unsigned int color, char * layer){
	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int err = (dx>dy ? dx : -dy)/2, e2;

	for(;;){
		putPixelOnLayer(x0,y0,color, layer);
		if(x0==x1 && y0==y1) break;
		e2 = err;
		if(e2 > -dx) { err -= dy; x0 += sx;}
		if(e2 < dy) { err += dx; y0 += sy;}
	}
}

void drawShapeToLayer(char * layer){
	if (shape=='r'){
		drawLineOnLayer(xt, yt, xn, yt, 0xFFFFFF, layer);
		drawLineOnLayer(xn, yt, xn, ynn, 0xFFFFFF, layer);
		drawLineOnLayer(xn, ynn, xt, ynn, 0xFFFFFF, layer);
		drawLineOnLayer(xt, ynn, xt, yt, 0xFFFFFF, layer);
	}
	else if (shape=='c')
	{
		int dx = xn-xt;
		int dy = ynn-yt;
		int xm = (xt+xn)/2;
		int ym = (yt+ynn)/2;
		int r = sqrt(dx*dx + dy*dy)/2;
		int x = -r, y = 0, err = 2-2*r; /* II. Quadrant */ 
	   do {
	      putPixelOnLayer(xm-x, ym+y, 0xFFFFFF, layer); /*   I. Quadrant */
	      putPixelOnLayer(xm-y, ym-x, 0xFFFFFF, layer); /*  II. Quadrant */
	      putPixelOnLayer(xm+x, ym-y, 0xFFFFFF, layer); /* III. Quadrant */
	      putPixelOnLayer(xm+y, ym+x, 0xFFFFFF, layer); /*  IV. Quadrant */
	      r = err;
	      if (r <= y) err += ++y*2+1;           /* e_xy+e_y < 0 */
	      if (r > x || err > y) err += ++x*2+1; /* e_xy+e_x > 0 or no 2nd y-step */
	   } while (x < 0);
	}
}	

unsigned int getPixelFromLayer(int x, int y, char * layer)
{
	long int location = fb.getRelativePosition(x, y);
	return *((unsigned int*)(layer+location));
}

void floodFillOnLayer(int x, int y, unsigned int color, char * layer)
{
	if(color!=0 && getPixelFromLayer(x, y, layer)==0){
		putPixelOnLayer(x, y, color, layer);
		if(x>EXTREME_LEFT)
			floodFillOnLayer(x-1,y,color, layer); //kiri 
		if(x<EXTREME_RIGHT-1)
			floodFillOnLayer(x+1,y,color, layer); //kanan
		if(y>EXTREME_TOP)
			floodFillOnLayer(x,y-1,color, layer); //atas
		if(y<EXTREME_BOTTOM-1)
			floodFillOnLayer(x,y+1,color, layer); //bawah
	}
}

void drawPallete(){
	//grid is between 0 and EXTREME_LEFT
	//make 8x2 grid w/ each size 40x40
	int i, j;
	int size = 45;

	unsigned int color = (R<<16) | (G<<8) | B;
		for (unsigned int x=0;x<256;x++)
		{
			for (unsigned int y=0;y<256;y++)
			{
				fb.putPixel(x,y,(x << 16) | (y << 8) | B);
			}
		}
		for (unsigned int y=0;y<256;y++)
		{
			for (unsigned int x=300;x<350;x++)
			{
				fb.putPixel(x,y,y);
			}
		}
		if (panel)
		{
			for (unsigned int x=300;x<350;x++)
			{
				fb.putPixel(x,B,0xffffff);
			}
		}
		else
		{
			fb.putPixel(R,G,~color);
		}
		for (unsigned int x=0;x<100;x++)
		{
			for (unsigned int y=0;y<100;y++)
			{
				if (x == 0 || x == 99 || y == 0 || y == 99)
				{
					fb.putPixel(400+x,y,0xffffff);
				}
				else
				{
					fb.putPixel(400+x,y,color);
				}
			}
		}
}

int main() {
	
	//struct input_event ie;
	FILE* fmouse;
	fmouse = fopen("/dev/input/mice", "r");
	char mouseAttr[3];
	curPosX = MOUSE_POS;
	curPosY = MOUSE_POS;
	Cursor cursor(Point(MOUSE_POS, MOUSE_POS));
	char * layer;
	
	layer = new char[fb.getScreensize()];
	//fread(mouseAttr, sizeof(char), 3, fmouse);
	//curPosX = mouseAttr[1];
	//curPosY = mouseAttr[2];
	bool left;
	vector<Point> tempPoly;

	shape = 'x';

	pthread_t pth_keyboard;
	pthread_create(&pth_keyboard, NULL, handleInput, NULL);
	fb.initScreen();
	fb.drawScreen();
	while(threadLoop) {
		//handleInput();
		//membaca mouse
		fread(mouseAttr, sizeof(char), 3, fmouse);
		fb.initScreen();
		if((mouseAttr[0]&1)>0){
			if(isPalleteShow)
			{
				fb.getPixel(cursor.getCoord());
				isPalleteShow = 0;
			}
			if(shape == 'p')
			{
				tempPoly.push_back(Point(cursor.getCoord()));
			}else if (shape=='f')
			{
				unsigned int color = 0x0000FF;
				floodFillOnLayer(cursor.getCoord().getX(), cursor.getCoord().getY(), color, layer);
			}
			else if (left){
				xn = cursor.getCoord().getX();
				ynn = cursor.getCoord().getY();
			} else {
				xn = cursor.getCoord().getX();
				ynn = cursor.getCoord().getY();
				left=true;
				xt = cursor.getCoord().getX();
				yt = cursor.getCoord().getY();
			}
		} else if (left){
			left=false;
			drawShapeToLayer(layer);		
			shape='x';
		}
		if((mouseAttr[0]&2)>0){
			if(shape == 'p'){
				if(tempPoly.size() > 1)
				{
					for(int i=0; i<(tempPoly.size()-1); i++)
					{
						drawLineOnLayer(tempPoly[i].getX(), tempPoly[i].getY(),
							tempPoly[i+1].getX(), tempPoly[i+1].getY(), 0xFFFFFF, layer);
					}
					drawLineOnLayer(cursor.getCoord().getX(), cursor.getCoord().getY(),
							tempPoly[tempPoly.size()-1].getX(), tempPoly[tempPoly.size()-1].getY(), 0xFFFFFF, layer);
					drawLineOnLayer(tempPoly[0].getX(), tempPoly[0].getY(),
						cursor.getCoord().getX(), cursor.getCoord().getY(), 0xFFFFFF, layer);
				}
				shape == 'x';
				tempPoly.clear();
			}
		}
		cursor.move(mouseAttr[1], -mouseAttr[2]);
		if(cursor.getCoord().getX() <0 || cursor.getCoord().getX()>EXTREME_RIGHT)
		{
			cursor.move(-mouseAttr[1], 0);
		}
		if (cursor.getCoord().getY() <EXTREME_TOP || cursor.getCoord().getY()>EXTREME_BOTTOM)
		{
			cursor.move(0, mouseAttr[2]);	
		}

		//render
		fb.drawLayer(layer);
		if(shape=='r'){
			fb.drawLine(Point(xt, yt), Point(xn, yt), 0xFFFFFF);
			fb.drawLine(Point(xn, yt), Point(xn, ynn), 0xFFFFFF);
			fb.drawLine(Point(xn, ynn), Point(xt, ynn), 0xFFFFFF);
			fb.drawLine(Point(xt, ynn), Point(xt, yt), 0xFFFFFF);
		}else if(shape=='c'){
			int dx = xn-xt;
			int dy = ynn-yt;
			int xm = (xt+xn)/2;
			int ym = (yt+ynn)/2;
			int r = sqrt(dx*dx + dy*dy)/2;
			fb.drawCircle(xm, ym, r, 0xFFFFFF);
		}else if(shape=='p' && tempPoly.size()>0)
		{
			for(int i=0; i<(tempPoly.size()-1); i++)
			{
				fb.drawLine(tempPoly[i], tempPoly[i+1], 0xFFFFFF);
			}
			fb.drawLine(tempPoly[0], cursor.getCoord(), 0xFFFFFF);
			fb.drawLine(tempPoly[tempPoly.size()-1], cursor.getCoord(), 0xFFFFFF);
		}
		cursor.drawCursor(&fb, 0xFFFFFF);
		//drawPallete();
		fb.drawScreen();
	}

	pthread_join(pth_keyboard, NULL);
	fclose(fmouse);

	return 0;
}
