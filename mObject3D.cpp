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
	vector<Vertex> vertices;
	vector<pair<char,char> > edges;
	vector<vector<char> > surfaces;
	vector<char> temp;
	Object3D cube, cube1;
	FrameBuffer fb;

	//define vertices
	vertices.push_back(Vertex(6,0,0));
	vertices.push_back(Vertex(6,6,0));
	vertices.push_back(Vertex(0,6,0));
	vertices.push_back(Vertex(0,0,0));
	vertices.push_back(Vertex(6,0,6));
	vertices.push_back(Vertex(6,6,6));
	vertices.push_back(Vertex(0,6,6));
	vertices.push_back(Vertex(0,0,6));

	//define edges
	edges.push_back(pair<char, char>(0,1));
	edges.push_back(pair<char, char>(1,2));
	edges.push_back(pair<char, char>(2,3));
	edges.push_back(pair<char, char>(3,0));
	edges.push_back(pair<char, char>(0,4));
	edges.push_back(pair<char, char>(1,5));
	edges.push_back(pair<char, char>(2,6));
	edges.push_back(pair<char, char>(3,7));
	edges.push_back(pair<char, char>(4,5));
	edges.push_back(pair<char, char>(5,6));
	edges.push_back(pair<char, char>(6,7));
	edges.push_back(pair<char, char>(7,4));

	//define surfaces
	push4(&temp, 0,1,2,3);
	surfaces.push_back(temp);
	temp.clear();
	push4(&temp, 4,5,6,7);
	surfaces.push_back(temp);
	temp.clear();
	push4(&temp, 1,2,6,5);
	surfaces.push_back(temp);
	temp.clear();
	push4(&temp, 0,3,7,4);
	surfaces.push_back(temp);
	temp.clear();
	push4(&temp, 0,1,5,4);
	surfaces.push_back(temp);
	temp.clear();
	push4(&temp, 2,3,7,6);
	surfaces.push_back(temp);
	temp.clear();

	//define Object3D
	cube = Object3D(vertices, edges, surfaces);

	//try to save Object3D
	cube.saveObjectToFile("cube.o3d");

	//try to load Object3D
	cube1.createObjectFromFile("cube.o3d");

	//transform cube and cube1
	cube.scale(Vertex(0,0,0), 10);
	cube.move(50, 200, 0);
	cube1.scale(Vertex(0,0,0), 10);
	cube1.move(200,200,0);

	//init screen
	fb.initScreen();

	//draw cube
	cube.drawOblique(&fb);
	cube1.drawOblique(&fb);

	//draw all
	fb.drawScreen();

	return 0;
}