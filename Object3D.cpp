#include "Object3D.h"
#include <cmath>

Object3D::Object3D(){

}
Object3D::Object3D(const vector<Vertex> v, const vector<pair<char, char> > e, const vector<vector<char> > s){
	vertices = v;
	edges = e;
	surfaces = s;
}
Object3D::Object3D(const Object3D& o){
	vertices = o.vertices;
	edges = o.edges;
	surfaces = o.surfaces;
}
Object3D::Object3D(char* filename){
	createObjectFromFile(filename);
}
Object3D& Object3D::operator=(const Object3D& o){
	vertices = o.vertices;
	edges = o.edges;
	surfaces = o.surfaces;
	return *this;
}
Object3D::~Object3D(){
	vertices.clear();
	edges.clear();
	surfaces.clear();
}
void Object3D::setVertices(vector<Vertex> v){
	vertices = v;
}
void Object3D::setEdges(vector<pair<char, char> > e){
	edges = e;
}
void Object3D::setSurfaces(vector<vector<char> > p){
	surfaces = p;
}
vector<Vertex> Object3D::getVertices(){
	return vertices;
}
vector<pair<char, char> > Object3D::getEdges(){
	return edges;
}
vector<vector<char> > Object3D::getSurfaces(){
	return surfaces;
}
void Object3D::createObjectFromFile(char *filename){
	FILE *f = fopen(filename, "r");
	int i, verticesSize, edgesSize, surfaceSize, surfaceElementSize;
	vector<char> tempPolygon;

	vertices.clear();
	edges.clear();
	surfaces.clear();

	fread(&verticesSize, 4, 1, f);
	fread(&edgesSize, 4, 1, f);
	fread(&surfaceSize, 4, 1, f);
	for(i=0; i<verticesSize; i++){
		int ibuf[3];

		fread(ibuf, 4, 3, f);
		vertices.push_back(Vertex(ibuf[0], ibuf[1], ibuf[2]));
	}
	for(i=0; i<edgesSize; i++){
		char cbuf[2];

		fread(cbuf, 1, 2, f);
		edges.push_back(pair<char,char>(cbuf[0], cbuf[1]));
	}
	for(i=0; i<surfaceSize; i++){
		fread(&surfaceElementSize, 4, 1, f);
		for(int j=0; j<surfaceElementSize; j++){
			char cbuf;
			fread(&cbuf, 1, 1, f);
			tempPolygon.push_back(cbuf);
		}
		surfaces.push_back(tempPolygon);
	}

	fclose(f);
}
void Object3D::saveObjectToFile(char *filename){
	FILE *f = fopen(filename, "w");
	int i;
	int vSize = vertices.size();
	int eSize = edges.size();
	int sSize = surfaces.size();

	fwrite(&vSize, 4, 1, f);
	fwrite(&eSize, 4, 1, f);
	fwrite(&sSize, 4, 1, f);
	for(i=0; i<vertices.size(); i++){
		int x = vertices[i].getX();
		int y = vertices[i].getY();
		int z = vertices[i].getZ();

		fwrite(&x, 4, 1, f);
		fwrite(&y, 4, 1, f);
		fwrite(&z, 4, 1, f);
	}
	for(i=0; i<edges.size(); i++){
		char fs = edges[i].first;
		char s = edges[i].second;
		fwrite(&fs, 1, 1, f);
		fwrite(&s, 1, 1, f);
	}
	for(i=0; i<surfaces.size(); i++){
		int sElmtSize = surfaces[i].size();
		fwrite(&sElmtSize, 4, 1, f);
		for(int j=0; j<surfaces[i].size(); j++){
			char buf = surfaces[i][j];
			fwrite(&buf, 1, 1, f);
		}
	}

	fclose(f);
}
Vertex Object3D::getCenterVertice(){
	int x, y, z;

	for(int i=0; i<vertices.size(); i++){
		x += vertices[i].getX();
		y += vertices[i].getY();
		z += vertices[i].getZ();
	}

	x = x/vertices.size();
	y = y/vertices.size();
	z = z/vertices.size();

	return Vertex(x, y, z);
}
void Object3D::rotateXAxis(Vertex center, double angle){
	for(int i=0; i<vertices.size(); i++){
		vertices[i].rotateXAxis(center, angle);
	}
}
void Object3D::rotateYAxis(Vertex center, double angle){
	for(int i=0; i<vertices.size(); i++){
		vertices[i].rotateYAxis(center, angle);
	}	
}
void Object3D::rotateZAxis(Vertex center, double angle){
	for(int i=0; i<vertices.size(); i++){
		vertices[i].rotateZAxis(center, angle);
	}
}
void Object3D::scale(Vertex center, double scale){
	for(int i=0; i<vertices.size(); i++){
		vertices[i].scale(center, scale);
	}
}
void Object3D::move(int move_x, int move_y, int move_z){
	for(int i=0; i<vertices.size(); i++){
		vertices[i].move(move_x, move_y, move_z);
	}
}
void Object3D::drawOblique(FrameBuffer *fb){
	double dz = sqrt(2)/2;

	for(int i=0; i<edges.size(); i++){
		double tempX = (double)vertices[edges[i].first].getX() + (double)vertices[edges[i].first].getZ()*dz;
		double tempY = (double)vertices[edges[i].first].getY() + (double)vertices[edges[i].first].getZ()*dz;
		Point first(tempX, tempY);

		tempX = (double)vertices[edges[i].second].getX() + (double)vertices[edges[i].second].getZ()*dz;
		tempY = (double)vertices[edges[i].second].getY() + (double)vertices[edges[i].second].getZ()*dz;
		Point second(tempX, tempY);

		fb->drawLine(first, second, 0xFFFFFFFF);
	}
}
void Object3D::drawIsometric(FrameBuffer *fb){
	double s = sqrt(3)/2;

	for(int i=0; i<edges.size(); i++){
		double tempX = (double)vertices[edges[i].first].getX()*s - (double)vertices[edges[i].first].getZ()*s;
		double tempY = (double)vertices[edges[i].first].getX()/2 + (double)vertices[edges[i].first].getZ()/2 + (double)vertices[edges[i].first].getY();
		Point first(tempX, tempY);

		tempX = (double)vertices[edges[i].second].getX()*s - (double)vertices[edges[i].second].getZ()*s;
		tempY = (double)vertices[edges[i].second].getX()/2 + (double)vertices[edges[i].second].getZ()/2 + (double)vertices[edges[i].second].getY();
		Point second(tempX, tempY);

		fb->drawLine(first, second, 0xFFFFFFFF);
	}
}
void Object3D::drawOrthogonal(FrameBuffer *fb){
	double d = 500;
	Point center(fb->getWidth()/2, fb->getHeight()/2);

	for(int i=0; i<edges.size(); i++){
		double cx = (double)(vertices[edges[i].first].getX() );
		double cy = (double)(vertices[edges[i].first].getY() );

		double u = (d * cx / ((double)vertices[edges[i].first].getZ() + d));
		double v = (d * cy / ((double)vertices[edges[i].first].getZ() + d));
		Point first(u,v);
		
		cx = (double)(vertices[edges[i].second].getX());
		cy = (double)(vertices[edges[i].second].getY());

		u = (d * cx / ((double)vertices[edges[i].second].getZ() + d));
		v = (d * cy / ((double)vertices[edges[i].second].getZ() + d));
		Point second(u,v);
		
		fb->drawLine(first, second, 0xFFFFFFFF);
	}
}