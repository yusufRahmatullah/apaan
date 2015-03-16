#include "FrameBuffer.h"
#include "Polygon.h"
#include "header.h"
#include "Keyboard.h"

Polygon vsumatra, vjawa, vkalimantan, vsulawesi, vpapua;
Polygon vsumatra2, vjawa2, vkalimantan2, vsulawesi2, vpapua2;

void handleInput(){
	if(Keyboard::isKeyPressed()){
		int move = 20;
		if(Keyboard::getKeyCode() == 'w'){
			vsumatra.moveMe(0,move);
			vsumatra2.moveMe(0,move);
			vjawa.moveMe(0,move);
			vjawa2.moveMe(0,move);
			vkalimantan.moveMe(0,move);
			vkalimantan2.moveMe(0,move);
			vsulawesi.moveMe(0,move);
			vsulawesi2.moveMe(0,move);
			vpapua.moveMe(0,move);
			vpapua2.moveMe(0,move);
		}else if(Keyboard::getKeyCode() == 'a'){
			vsumatra.moveMe(move,0);
			vsumatra2.moveMe(move,0);
			vjawa.moveMe(move,0);
			vjawa2.moveMe(move,0);
			vkalimantan.moveMe(move,0);
			vkalimantan2.moveMe(move,0);
			vsulawesi.moveMe(move,0);
			vsulawesi2.moveMe(move,0);
			vpapua.moveMe(move,0);
			vpapua2.moveMe(move,0);
		}else if(Keyboard::getKeyCode() == 's'){
			vsumatra.moveMe(0,-move);
			vsumatra2.moveMe(0,-move);
			vjawa.moveMe(0,-move);
			vjawa2.moveMe(0,-move);
			vkalimantan.moveMe(0,-move);
			vkalimantan2.moveMe(0,-move);
			vsulawesi.moveMe(0,-move);
			vsulawesi2.moveMe(0,-move);
			vpapua.moveMe(0,-move);
			vpapua2.moveMe(0,-move);
		}else if(Keyboard::getKeyCode() == 'd'){
			vsumatra.moveMe(-move,0);
			vsumatra2.moveMe(-move,0);
			vjawa.moveMe(-move,0);
			vjawa2.moveMe(-move,0);
			vkalimantan.moveMe(-move,0);
			vkalimantan2.moveMe(-move,0);
			vsulawesi.moveMe(-move,0);
			vsulawesi2.moveMe(-move,0);
			vpapua.moveMe(-move,0);
			vpapua2.moveMe(-move,0);
		}else if(Keyboard::getKeyCode() == 'p' || Keyboard::getKeyCode() == 27){
			exit(0);
		}
	}
}

void loadMap(string mapname, Polygon &poly, double scale) {
	FILE * filemap = fopen(mapname.c_str(), "r");
	int x,y;
	vector<Point> v;
	while(fscanf(filemap, "%d %d", &x, &y) != EOF) {
		Point p(x*scale,y*scale);
		v.push_back(p);
	}
	poly.setVertex(v);
	fclose(filemap);	
}

int main(){
	double scale = 0.5;
	FrameBuffer fb;

	loadMap("sumatra.txt", vsumatra, scale);
	loadMap("jawa.txt", vjawa, scale);
	loadMap("kalimantan.txt", vkalimantan, scale);
	loadMap("sulawesi.txt", vsulawesi, scale);
	loadMap("papua.txt", vpapua, scale);

	loadMap("sumatra.txt", vsumatra2, scale);
	loadMap("jawa.txt", vjawa2, scale);
	loadMap("kalimantan.txt", vkalimantan2, scale);
	loadMap("sulawesi.txt", vsulawesi2, scale);
	loadMap("papua.txt", vpapua2, scale);

	int moveY = 20;

	vsumatra2.moveMe(0,moveY);
	vjawa2.moveMe(0,moveY);
	vkalimantan2.moveMe(0,moveY);
	vsulawesi2.moveMe(0,moveY);
	vpapua2.moveMe(0,moveY);

	Keyboard::initKeyboard();

	while(true){
		handleInput();
		fb.initScreen();

		fb.drawPolygon(vsumatra, 0xFF00);
		fb.drawPolygon(vjawa, 0xFF00);
		fb.drawPolygon(vkalimantan, 0xFF00);
		fb.drawPolygon(vsulawesi, 0xFF00);
		fb.drawPolygon(vpapua, 0xFF00);
		fb.drawPolygon(vsumatra2, 0xFF);
		fb.drawPolygon(vjawa2, 0xFF);
		fb.drawPolygon(vkalimantan2, 0xFF);
		fb.drawPolygon(vsulawesi2, 0xFF);
		fb.drawPolygon(vpapua2, 0xFF);

		vector<Point> temp, temp1;

		temp.clear();
		temp = vsumatra2.getVertex();
		temp1 = vsumatra.getVertex();
		for(int i=0; i<temp.size(); i++){
			fb.drawLine(temp[i], temp1[i], 0xFF0000);
		}

		temp.clear();
		temp1.clear();
		temp = vjawa2.getVertex();
		temp1 = vjawa.getVertex();
		for(int i=0; i<temp.size(); i++){
			fb.drawLine(temp[i], temp1[i], 0xFF0000);
		}

		temp.clear();
		temp1.clear();
		temp = vkalimantan2.getVertex();
		temp1 = vkalimantan.getVertex();
		for(int i=0; i<temp.size(); i++){
			fb.drawLine(temp[i], temp1[i], 0xFF0000);
		}

		temp.clear();
		temp1.clear();
		temp = vsulawesi2.getVertex();
		temp1 = vsulawesi.getVertex();
		for(int i=0; i<temp.size(); i++){
			fb.drawLine(temp[i], temp1[i], 0xFF0000);
		}

		temp.clear();
		temp1.clear();
		temp = vpapua2.getVertex();
		temp1 = vpapua.getVertex();
		for(int i=0; i<temp.size(); i++){
			fb.drawLine(temp[i], temp1[i], 0xFF0000);
		}

		fb.drawScreen();
	}
	return 0;
}