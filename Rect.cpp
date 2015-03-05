#include "Rect.h"

Rect::Rect() : leftTop(0,0){
	width=0;
	height=0;
	color = 0xFFFFFFFF;
}
Rect::~Rect(){

}
Rect::Rect(Point left_Top, int height, int width, unsigned int color){
	leftTop = left_Top;
	this->height = height;
	this->width = width;
	this->color = color;
}
int Rect::getWidth(){
	return width;
}
int Rect::getHeight(){
	return height;
}
unsigned int Rect::getColor(){
	return color;
}
void Rect::setWidth(int newWidth){
	width = newWidth;
}
void Rect::setHeight(int newHeight){
	height = newHeight;
}
void Rect::setColor(unsigned int newColor){
	color = newColor;
}
void Rect::move(int moveX, int moveY){
	int x = leftTop.getX();
	int y = leftTop.getY();
	leftTop.setX(x+moveX);
	leftTop.setY(y+moveY);
}

void Rect::draw(FrameBuffer *fb){
	int x = leftTop.getX();
	int y = leftTop.getY();
	Point rT(x+width, y);
	Point rB(x+width, y+height);
	Point lB(x, y+height);

	fb->drawLine(leftTop, rT, color);
	fb->drawLine(rT, rB, color);
	fb->drawLine(rB, lB, color);
	fb->drawLine(lB, leftTop, color);
}
Point Rect::getLeftTop(){
	return leftTop;
}
void Rect::setLeftTop(Point P){
	leftTop.setX(P.getX());
	leftTop.setY(P.getY());
}
void Rect::setLeftTop(int x, int y){
	leftTop.setX(x);
	leftTop.setY(y);
}
int Rect::findRegion(Point P){
	int code=0;
    if(P.getY() >= leftTop.getY()+height)
    	code |= 1; //top
    else if( P.getY() < leftTop.getY())
    	code |= 2; //bottom
    if(P.getX() >= leftTop.getX()+width)
    	code |= 4; //right
    else if ( P.getX() < leftTop.getX())
    	code |= 8; //left
    return(code);
}
int Rect::findRegion(int x, int y){
	int code=0;
    if(y >= leftTop.getY()+height)
    	code |= 1; //top
    else if( y < leftTop.getY())
    	code |= 2; //bottom
    if(x >= leftTop.getX()+width)
    	code |= 4; //right
    else if ( x < leftTop.getX())
    	code |= 8; //left
    return(code);
}	

bool Rect::clipLine(Point P1, Point P2, Point& P3, Point& P4)
{
    int code1, code2, codeout;
    int x1 = P1.getX(),
    	x2 = P2.getX(),
    	y1 = P1.getY(),
    	y2 = P2.getY();

    bool accept = 0, done=0;
    code1 = findRegion(P1); //the region outcodes for the endpoints
    code2 = findRegion(P2);
    do  //In theory, this can never end up in an infinite loop, it'll always come in one of the trivial cases eventually
    {
        if(!(code1 | code2)) accept = done = 1;  //accept because both endpoints are in screen or on the border, trivial accept
        else if(code1 & code2) done = 1; //the line isn't visible on screen, trivial reject
        else  //if no trivial reject or accept, continue the loop
        {
            int x, y;
            double dox, doy;
            codeout = code1 ? code1 : code2;
            if(codeout & 1) //top
            {
				dox = (double)(x2 - x1) * (double)(leftTop.getY()+height - y1) / (double)(y2 - y1);
				x = x1 + dox;
                y = leftTop.getY()+height - 1;
            }
            else if(codeout & 2) //bottom
            {	
				dox = (double)(x2 - x1) * (double)(leftTop.getY()-y1) / (double)(y2 - y1);
				x = x1 + dox;
                y = leftTop.getY();
            }
            else if(codeout & 4) //right
            {	
				doy = (double)(y2 - y1) * (double)(leftTop.getX()+width - x1) / (double)(x2 - x1);
				y = y1 + doy;
                x = leftTop.getX()+width - 1;
            }
            else //left
            {
				doy = (double)(y2 - y1) * (double)(leftTop.getX()-x1) / (double)(x2 - x1);
				y = y1 + doy;
                x = leftTop.getX();
            }
            
            if(codeout == code1) //first endpoint was clipped
            {
                x1 = x; y1 = y;
                code1 = findRegion(x1, y1);
            }
            else //second endpoint was clipped
            {
                x2 = x; y2 = y;
                code2 = findRegion(x2, y2);
            }
        }
    }
    while(done == 0);
    if(accept)
    {
    	P3.setX(x1);
    	P4.setX(x2);
    	P3.setY(y1);
    	P4.setY(y2);
        return 1;
    }
    else
    {
    	P3.setX(0);
    	P4.setX(0);
    	P3.setY(0);
    	P4.setY(0);
        return 0;
    }
}
/*void Rect::drawClip(vector<Point> v, Rect r, FrameBuffer *fb){
	Point P1, P2;
	for(int i=0; i<v.size()-1; i++){
		if(clipLine(v[i], v[i+1], P1, P2)){
			P1.moveMe(r.leftTop.getX() - leftTop.getX(), r.leftTop.getY() - leftTop.getY());
			P2.moveMe(r.leftTop.getX() - leftTop.getX(), r.leftTop.getY() - leftTop.getY());
			P1.scaleMe(r.leftTop, r.height/height);
			P2.scaleMe(r.leftTop, r.height/height);
			fb->drawLine(P1, P2, 0xFF00FF00);
		}
	}
	if(clipLine(v[v.size()-1], v[0], P1, P2)){
			P1.moveMe(r.leftTop.getX() - leftTop.getX(), r.leftTop.getY() - leftTop.getY());
			P2.moveMe(r.leftTop.getX() - leftTop.getX(), r.leftTop.getY() - leftTop.getY());
			P1.scaleMe(r.leftTop, r.height/height);
			P2.scaleMe(r.leftTop, r.height/height);
			fb->drawLine(P1, P2, 0xFF00FF00);
		}
}*/
void Rect::drawClip(Polygon p, Rect r, FrameBuffer *fb){
	Point P1, P2;
	vector<Point> v = p.getVertex();
	for(int i=0; i<v.size()-1; i++){
		if(clipLine(v[i], v[i+1], P1, P2)){
			P1.moveMe(r.leftTop.getX() - leftTop.getX(), r.leftTop.getY() - leftTop.getY());
			P2.moveMe(r.leftTop.getX() - leftTop.getX(), r.leftTop.getY() - leftTop.getY());
			P1.scaleMe(r.leftTop, (double)r.height/(double)height);
			P2.scaleMe(r.leftTop, (double)r.height/(double)height);
			fb->drawLine(P1, P2, 0xFF00FF00);
		}
	}
	if(clipLine(v[v.size()-1], v[0], P1, P2)){
			P1.moveMe(r.leftTop.getX() - leftTop.getX(), r.leftTop.getY() - leftTop.getY());
			P2.moveMe(r.leftTop.getX() - leftTop.getX(), r.leftTop.getY() - leftTop.getY());
			P1.scaleMe(r.leftTop, (double)r.height/(double)height);
			P2.scaleMe(r.leftTop, (double)r.height/(double)height);
			fb->drawLine(P1, P2, 0xFF00FF00);
		}
}

