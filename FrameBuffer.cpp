#include "FrameBuffer.h"
#include <string.h>
#include <cmath>

FrameBuffer::FrameBuffer(){
	fbfd = open("/dev/fb0", O_RDWR);

	//get var screen info
	ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo);
	vinfo.grayscale=0;
	vinfo.bits_per_pixel=32;
	ioctl(fbfd, FBIOPUT_VSCREENINFO, &vinfo);
	ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo);
	
     //Get fix screen information
	ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo);

	screensize = vinfo.yres_virtual * finfo.line_length;
	
	backbuffer = new char[screensize];
	fbp = (char*) mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, (off_t)0);
}
FrameBuffer::~FrameBuffer(){
	delete [] backbuffer;
	munmap(fbp, screensize);
	close(fbfd);
}
void FrameBuffer::putPixel(int x, int y, unsigned int color){
	long int location = getRelativePosition(x,y);
	if(location <= screensize && location > 0)
		*((char*)(backbuffer + location)) = color;

	*(backbuffer+location) = (color&0xFF);
	*(backbuffer+location+1) = ((color&0xFF00)>>8);
	*(backbuffer+location+2) = ((color&0xFF0000)>>16);
	*(backbuffer+location+3) = ((color&0xFF000000)>>24);
}
void FrameBuffer::putPixel(Point P, unsigned int color){
	long int location = getRelativePosition(P.getX(),P.getY());
	if(location <= screensize && location > 0)
		*((char*)(backbuffer + location)) = color;

	*(backbuffer+location) = (color&0xFF);
	*(backbuffer+location+1) = ((color&0xFF00)>>8);
	*(backbuffer+location+2) = ((color&0xFF0000)>>16);
	*(backbuffer+location+3) = ((color&0xFF000000)>>24);
}
void FrameBuffer::drawLine(Point p0, Point p1, unsigned int color) {
	int x0 = p0.getX();
	int y0 = p0.getY();
	int x1 = p1.getX();
	int y1 = p1.getY();
	
	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
	int err = (dx>dy ? dx : -dy)/2, e2;

	for(;;){
		putPixel(x0,y0,color);
		if(x0==x1 && y0==y1) break;
		e2 = err;
		if(e2 > -dx) { err -= dy; x0 += sx;}
		if(e2 < dy) { err += dx; y0 += sy;}
	}
}
void FrameBuffer::drawPolygon(Polygon p, unsigned int color) {
	int i;
	for(i=0; i<p.getVertex().size()-1; i++)
		drawLine(p.getVertex()[i], p.getVertex()[i+1], color);
	drawLine(p.getVertex()[i], p.getVertex()[0], color);
}
unsigned int FrameBuffer::getPixel(int x, int y){
	long int location = getRelativePosition(x, y);
	return *((unsigned int*)(backbuffer+location));
}
unsigned int FrameBuffer::getPixel(Point P){
	long int location = getRelativePosition(P.getX(), P.getY());
	return *((unsigned int*)(backbuffer+location));
}
long int FrameBuffer::getScreensize(){
	return screensize;
}
long FrameBuffer::getRelativePosition(int x, int y){
	return (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+vinfo.yoffset) * finfo.line_length;
}
void FrameBuffer::initScreen(){
	memset(backbuffer, 0, screensize);
}

void FrameBuffer::drawScreen(){
	memcpy(fbp, backbuffer, screensize);
}
