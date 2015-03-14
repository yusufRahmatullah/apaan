#include "Keyboard.h"

struct termios Keyboard::oldTermios;
struct termios Keyboard::newTermios;
unsigned char Keyboard::keyCode = 0;

void Keyboard::initKeyboard(){
	tcgetattr(0, &oldTermios);
	memcpy(&newTermios, &oldTermios, sizeof(newTermios));
	atexit(resetTerminal);
	cfmakeraw(&newTermios);
	tcsetattr(0, TCSANOW, &newTermios);
}
void Keyboard::resetTerminal(){
	tcsetattr(0, TCSANOW, &oldTermios);
}
int Keyboard::kbhit(){
	struct timeval tv = {0L, 0L};
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(0, &fds);
	return select(1, &fds, NULL, NULL, &tv);
}
int Keyboard::getch(){
	int rd;
	unsigned char c;
	if((rd = read(0, &c, sizeof(c))) < 0) return rd;
	else return c;
}
bool Keyboard::isKeyPressed(){
	if(kbhit()){
		keyCode = getch();
		return true;
	}else return false;
}
unsigned char Keyboard::getKeyCode(){
	return keyCode;
}