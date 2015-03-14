#include "header.h"
#include "Keyboard.h"
#include "Rect.h"

Rect view;

void handleInput(){
	if(Keyboard::isKeyPressed()){
		if(Keyboard::getKeyCode() == 'a'){
			view.move(-2,0);
		}else if(Keyboard::getKeyCode() == 's'){
			view.move(2,0);
		}else if(Keyboard::getKeyCode() == 'p' || Keyboard::getKeyCode() == 27){
			exit(0);
		}
	}
}
void update(){
	
}
void render(){
	cout << "x : " << view.getPoint().getX() << endl;
	cout << "y : " << view.getPoint().getY() << endl;
}

int main(){
	view.setLeftTop(Point(300,300));
	view.setWidth(100);
	view.setHeight(100);
	view.setColor(0xFFFF0000);

	Keyboard::initKeyboard();

	while(true){
		handleInput();
		render();
	}
	return 0;
}