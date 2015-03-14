#include "Mouse.h"
#include <pthread.h>

void* mouseFunc(void* arg){
	char mouseAttr[3];
	int curPosX, curPosY;

	Mouse::initMouse();
	Mouse::getMouseAttr(mouseAttr);
	curPosX = mouseAttr[1];
	curPosY = mouseAttr[2];
	while(true){
		Mouse::getMouseAttr(mouseAttr);
		
		if((mouseAttr[0]&1)>0){
			cout << "left button clicked" <<endl;
		}else if((mouseAttr[0]&2)>0){
			cout << "right button clicked" <<endl;
		}
		if(curPosX != mouseAttr[1] || curPosY != mouseAttr[2]){
			curPosX =  mouseAttr[1];
			curPosY =  mouseAttr[2];
			cout << "mouse position : (" << curPosX << ", " << curPosY << ")\n";
		}
	}
	Mouse::finishMouse();
}

int main(){
	pthread_t p;

	Mouse::initMouse();	
	pthread_create(&p, NULL, mouseFunc, NULL);
	pthread_join(p, NULL);
	return 0;
}