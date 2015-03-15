#include <cstdio>
#include <cmath>
#include "Projection.h"

using namespace std;

_3Dpoint::_3Dpoint(double xx, double yy, double zz){
	x=xx;
	y=yy;
	z=zz;
}
_3Dpoint& _3Dpoint::operator=(const _3Dpoint& a){
	// protect against invalid self-assignment
	if (this != &a){
		x=a.x;
		y=a.y;
		z=a.z;
	}
	return *this;
}
_3Dpoint::_3Dpoint(){
	x=0;
	y=0;
	z=0;
}


Camera::Camera():
	from(0,-50,0),
	to(0,50,0),
	up(0,0,1){
	angleh=45.0;
	anglev=45.0;
	zoom=1.0;
	front=1.0;
	back=200.0;
	projection=0;
}

_2Dpoint::_2Dpoint(int hh, int vv){
	h = hh;
	v = vv;
}
_2Dpoint::_2Dpoint(){
	h = 0;
	v = 0;
}

Screen::Screen():
	center(720,420),
	size(800, 800){
	}


Projection::Projection():
	camera(), screen(), origin(),
	basisa(), basisb(), basisc(),
	p1(), p2(), e1(),
	e2(), n1(), n2(){
	EPSILON = 0.001;
	DTOR = 0.01745329252;
	if (Trans_Initialise() != true){
		printf("Error in initializing variable");
	}
}
void Projection::SetCamera(Camera& in){
	camera.from=in.from;
	camera.to=in.to;
	camera.up=in.up;
	camera.angleh=in.angleh;
	camera.anglev=in.anglev;
	camera.zoom=in.zoom;
	camera.front=in.front;
	camera.back=in.back;
	camera.projection=in.projection;
}
void Projection::SetScreen(Screen& in){
	screen.center=in.center;
	screen.size=in.size;
}
bool Projection::Trans_Initialise(){
	/* Is the camera position and view vector coincident ? */
	if (EqualVertex(camera.to, camera.from)){
		return (false);
	}
	/* Is there a legal camera up vector ? */
	if (EqualVertex(camera.up, origin)){
		return (false);
	}
	basisb.x = camera.to.x - camera.from.x;
	basisb.y = camera.to.y - camera.from.y;
	basisb.z = camera.to.z - camera.from.z;
	Normalise(basisb);
	basisa= CrossProduct(camera.up, basisb);
	Normalise(basisa);
	/* Are the up vector and view direction colinear */
	if (EqualVertex(basisa, origin)){
		return (false);
	}
	basisc=CrossProduct(basisb, basisa);
	/* Do we have legal camera apertures ? */
	if (camera.angleh < EPSILON || camera.anglev < EPSILON){
		return (false);
	}
	/* Calculate camera aperture statics, note: angles in degrees */
	tanthetah = tan(camera.angleh * DTOR / 2);
	tanthetav = tan(camera.anglev * DTOR / 2);
	/* Do we have a legal camera zoom ? */
	if (camera.zoom < EPSILON){
		return (false);
	}
	/* Are the clipping planes legal ? */
	if (camera.front < 0 || camera.back < 0 || camera.back <= camera.front){
		return (false);
	}
	return true;
}
void Projection::Trans_World2Eye(_3Dpoint w, _3Dpoint& e){
	/* Translate world so that the camera is at the origin */
	w.x -= camera.from.x;
	w.y -= camera.from.y;
	w.z -= camera.from.z;
	/* Convert to eye coordinates using basis vectors */
	e.x = w.x * basisa.x + w.y * basisa.y + w.z * basisa.z;
	e.y = w.x * basisb.x + w.y * basisb.y + w.z * basisb.z;
	e.z = w.x * basisc.x + w.y * basisc.y + w.z * basisc.z;
}
bool Projection::Trans_ClipEye(_3Dpoint& e1, _3Dpoint& e2){
	double mu;
	/* Is the vector totally in front of the front cutting plane ? */
	if ((e1.y <= camera.front)&&(e2.y <= camera.front)){
		return (false);
	}
	/* Is the vector totally behind the back cutting plane ? */
	if ((e1.y >= camera.back)&&(e2.y >= camera.back)){
		return (false);
	}
	/* Is the vector partly in front of the front cutting plane ? */
	if (((e1.y < camera.front)&&(e2.y > camera.front))||
		((e1.y > camera.front)&&(e2.y < camera.front))){
		mu = (camera.front - e1.y) / (e2.y - e1.y);
		if (e1.y < camera.front){
			e1.x = e1.x + mu * (e2.x - e1.x);
			e1.z = e1.z + mu * (e2.z - e1.z);
			e1.y = camera.front;
		}else{
			e2.x = e1.x + mu * (e2.x - e1.x);
			e2.z = e1.z + mu * (e2.z - e1.z);
			e2.y = camera.front;
		}
	}
	/* Is the vector partly behind the back cutting plane ? */
	if (((e1.y < camera.back)&&(e2.y > camera.back))||
		((e1.y > camera.back)&&(e2.y < camera.back))) {
		mu = (camera.back - e1.y) / (e2.y - e1.y);
		if (e1.y < camera.back){
			e2.x = e1.x + mu * (e2.x - e1.x);
			e2.z = e1.z + mu * (e2.z - e1.z);
			e2.y = camera.back;
		}else{
			e1.x = e1.x + mu * (e2.x - e1.x);
			e1.z = e1.z + mu * (e2.z - e1.z);
			e1.y = camera.back;
		}
	}
	return (true);
}
void Projection::Trans_Eye2Norm(_3Dpoint e, _3Dpoint& n){
	double d;
	if (camera.projection == 0){
		d = camera.zoom / e.y;
		n.x = d * e.x / tanthetah;
		n.y = e.y; 
		n.z = d * e.z / tanthetav;
	}else{
		n.x = camera.zoom * e.x / tanthetah;
		n.y = e.y;
		n.z = camera.zoom * e.z / tanthetav;
	}
}
bool Projection::Trans_ClipNorm(_3Dpoint& n1, _3Dpoint& n2){
	double mu;
	/* Is the line segment totally right of x = 1 ? */
	if ((n1.x >= 1)&&(n2.x >= 1))
		return (false);
	/* Is the line segment totally left of x = -1 ? */
	if ((n1.x <= -1)&&(n2.x <= -1))
		return (false);
	/* Does the vector cross x = 1 ? */
	if (((n1.x > 1)&&(n2.x < 1))||((n1.x < 1)&&(n2.x > 1))){
		mu = (1 - n1.x) / (n2.x - n1.x);
		if (n1.x < 1){
			n2.z = n1.z + mu * (n2.z - n1.z);
			n2.x = 1;
		}else{
			n1.z = n1.z + mu * (n2.z - n1.z);
			n1.x = 1;
		}
	}
	/* Does the vector cross x = -1 ? */
	if (((n1.x < -1)&&(n2.x > -1))||((n1.x > -1)&&(n2.x < -1))){
		mu = (-1 - n1.x) / (n2.x - n1.x);
		if (n1.x > -1){
			n2.z = n1.z + mu * (n2.z - n1.z);
			n2.x = -1;
		}else{
			n1.z = n1.z + mu * (n2.z - n1.z);
			n1.x = -1;
		}
	}
	/* Is the line segment totally above z = 1 ? */
	if ((n1.z >= 1)&&(n2.z >= 1))
		return (false);
	/* Is the line segment totally below z = -1 ? */
	if ((n1.z <= -1)&&(n2.z <= -1))
		return (false);
	/* Does the vector cross z = 1 ? */
	if (((n1.z > 1)&&(n2.z < 1))||((n1.z < 1)&&(n2.z > 1))){
		mu = (1 - n1.z) / (n2.z - n1.z);
		if (n1.z < 1){
			n2.x = n1.x + mu * (n2.x - n1.x);
			n2.z = 1;
		}else{
			n1.x = n1.x + mu * (n2.x - n1.x);
			n1.z = 1;
		}
	}
	/* Does the vector cross z = -1 ? */
	if (((n1.z < -1)&&(n2.z > -1))||((n1.z > -1)&&(n2.z < -1))){
		mu = (-1 - n1.z) / (n2.z - n1.z);
		if (n1.z > -1){
			n2.x = n1.x + mu * (n2.x - n1.x);
			n2.z = -1;
		}else{
			n1.x = n1.x + mu * (n2.x - n1.x);
			n1.z = -1;
		}
	}
	return (true);
}
void Projection::Trans_Norm2Screen(_3Dpoint norm, _2Dpoint& projected){
	//printf("the value of  are");
	projected.h = (int)(screen.center.h - screen.size.h * norm.x / 2);
	projected.v = (int)(screen.center.v - screen.size.v * norm.z / 2);
}
bool Projection::Trans_Line(_3Dpoint w1, _3Dpoint w2){
	Trans_World2Eye(w1, e1);
	Trans_World2Eye(w2, e2);
	if (Trans_ClipEye(e1, e2)){
		Trans_Eye2Norm(e1, n1);
		Trans_Eye2Norm(e2, n2);
		if (Trans_ClipNorm(n1, n2)){
			Trans_Norm2Screen(n1,p1);
			Trans_Norm2Screen(n2,p2);
			return (true);
		}
	}
	return (true);
}
void Projection::Normalise(_3Dpoint& v){
	double length;
	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x /= length;
	v.y /= length;
	v.z /= length;
}
_3Dpoint Projection::CrossProduct(_3Dpoint p1,_3Dpoint p2){
	_3Dpoint p3(0,0,0);
	p3.x = p1.y * p2.z - p1.z * p2.y;
	p3.y = p1.z * p2.x - p1.x * p2.z;
	p3.z = p1.x * p2.y - p1.y * p2.x;
	return p3;
}
bool Projection::EqualVertex(_3Dpoint p1, _3Dpoint p2){
		if (abs(p1.x - p2.x) > EPSILON)
			return(false);
		if (abs(p1.y - p2.y) > EPSILON)
			return(false);
		if (abs(p1.z - p2.z) > EPSILON)
			return(false);
		return(true);
	}
