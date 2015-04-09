#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <linux/input.h>
#include "Cursor.h"
 
#define MOUSEFILE "/dev/input/mice"
 
int main() {
	
	struct input_event ie;
	FILE* fmouse;
	fmouse = fopen("/dev/input/mice", "r");
	char mouseAttr[3];
	int curPosX, curPosY;
	FrameBuffer fb;
	Cursor cursor(Point(800,400));
	
	fread(mouseAttr, sizeof(char), 3, fmouse);
	curPosX = mouseAttr[1];
	curPosY = mouseAttr[2];
	bool left;
	
	while(true) {
		fb.initScreen();
		fread(mouseAttr, sizeof(char), 3, fmouse);
		//printf("mattr0 %x\n", mouseAttr[0]);
		if((mouseAttr[0]&1)>0){
			if (left){
				//printf("left button drag\n");
			} else {
				left=true;
				//printf("left button pressed\n");
			}
		} else if (left){
			left=false;
			//printf("left button released\n");
		}
		if((mouseAttr[0]&2)>0){
			//printf("right button clicked\n");
		}
		if(curPosX != mouseAttr[1] || curPosY != mouseAttr[2]){
			curPosX =  mouseAttr[1];
			curPosY =  mouseAttr[2];
			//printf("%d, %d\n", curPosX, curPosY);
			cursor.move(curPosX, -curPosY);
		}
		cursor.drawCursor(&fb, 0xFFFFFF);
		//fb.drawPolygon(cursor.cursor, 0xFFFFFF);
		fb.drawLine(Point(0,0), Point(1024, 720), 0xFFFFFF);
		fb.drawScreen();
	}

	return 0;
}
