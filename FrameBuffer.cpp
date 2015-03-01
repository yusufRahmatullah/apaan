#include "FrameBuffer.h"

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

int main(){
	FrameBuffer fb;
	fb.initScreen();
	for(int i=0; i<100; i++){
		for(int j=0; j<100; j++)
			fb.putPixel(i,j,0xFFA0A0A0);
	}
	fb.drawScreen();
	return 0;;
}
