#include "Object3D.h"
#include "Keyboard.h"


void handleInput(){
	char keyCode;

	if(Keyboard::isKeyPressed()){
		keyCode = Keyboard::getKeyCode();
		if(keyCode == 'a'){

		}
	}
}

void push4(vector<char> * v, char w, char x, char y, char z){
	v->push_back(w);
	v->push_back(x);
	v->push_back(y);
	v->push_back(z);
}

int main(){
	Object3D cube, cube1, balok;
	FrameBuffer fb;

	//try to load Object3D
	//cube.createObjectFromFile("cube.o3d");
	//cube1.createObjectFromFile("cube.o3d");
	
	balok.createObjectFromFile("balok.o3d");
	
	//transform object
	//cube.scale(Vertex(0,0,0), 20);
	//cube.move(400, 150, 0);
	//cube1.scale(Vertex(0,0,0), 20);
	//cube1.move(700, 250, 0);
	balok.scale(Vertex(0,0,0), 20);
	balok.move(600, 300, 0);

	//init screen
	fb.initScreen();

	//draw cube
	//cube.drawOblique(&fb);
	//cube1.drawIsometric(&fb);
	
	balok.drawOrthogonal(&fb);
	

	//draw all
	fb.drawScreen();

	return 0;
}
