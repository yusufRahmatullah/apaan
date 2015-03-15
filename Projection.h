#ifndef PROJECT_H
#define PROJECT_H

class _3Dpoint{
public:
	double x, y, z;
	_3Dpoint(double xx, double yy, double zz);
	_3Dpoint& operator=(const _3Dpoint& a);
	_3Dpoint();
};

class Camera{
public:
	_3Dpoint from;
	_3Dpoint to;
	_3Dpoint up;
	double angleh, anglev;
	double zoom;
	double front, back;
	short projection;
	Camera();
};

class _2Dpoint{
public:
	int h,v;
	_2Dpoint(int hh, int vv);
	_2Dpoint();
};

class Screen{
public:
	_2Dpoint center;
	_2Dpoint size;
	Screen();
};

class Projection{
private:
	_3Dpoint origin;
	_3Dpoint e1, e2, n1, n2;
	Camera camera;
	Screen screen;
	double tanthetah, tanthetav;
	_3Dpoint basisa, basisb, basisc;
	double EPSILON;
	double DTOR;// 0.01745329252
public:
	_2Dpoint p1;
	_2Dpoint p2;
	Projection();
	void SetCamera(Camera& in);
	void SetScreen(Screen& in);
	bool Trans_Initialise();
	void Trans_World2Eye(_3Dpoint w, _3Dpoint& e);
	bool Trans_ClipEye(_3Dpoint& e1, _3Dpoint& e2);
	void Trans_Eye2Norm(_3Dpoint e, _3Dpoint& n);
	bool Trans_ClipNorm(_3Dpoint& n1, _3Dpoint& n2);
	void Trans_Norm2Screen(_3Dpoint norm, _2Dpoint& projected);
	bool Trans_Line(_3Dpoint w1, _3Dpoint w2);
	void Normalise(_3Dpoint& v);
	_3Dpoint CrossProduct(_3Dpoint p1,_3Dpoint p2);
	bool EqualVertex(_3Dpoint p1, _3Dpoint p2);
};

#endif
