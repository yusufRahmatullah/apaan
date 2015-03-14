#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "header.h"
#include <string.h>
#include <termios.h>
#include <sys/select.h>

class Keyboard{
private:
	static struct termios oldTermios, newTermios;
	static unsigned char keyCode;
public:
	static void initKeyboard();
	static void resetTerminal();
	static int kbhit();
	static int getch();
	static bool isKeyPressed();
	static unsigned char getKeyCode();
};
#endif