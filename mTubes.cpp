#include "header.h"
#include "FrameBuffer.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Rect.h"
#include "Polygon.h"
#include <utility>
#include <vector>
#include <sys/wait.h>

using std::pair;
using std::vector;

int main(){
	FrameBuffer fb;
	int pid=0;
	int stat;

	system("clear");
	cout << "Aplikasi pertama adalah colorpicker" << endl;
	cout << "Tekan wasd untuk menjalankan picker" << endl;
	cout << "Tekan p atau Esc untuk keluar dari aplikasi" << endl;
	cout << "Tekan sembarang tombol untuk melanjutkan" << endl;
	getchar();

	pid = fork();
	if(pid==0){
		execl("colorpicker", "colorpicker", NULL);
	}else{
		waitpid(pid, &stat, 0);
	}

	system("clear");
	cout << "Aplikasi kedua adalah 3dmap" << endl;
	cout << "Tekan wasd untuk menjalankan kamera" << endl;
	cout << "Tekan p atau Esc untuk keluar dari aplikasi" << endl;
	cout << "Tekan sembarang tombol untuk melanjutkan" << endl;
	getchar();

	pid = fork();
	if(pid==0){
		execl("m3dmap", "m3dmap", NULL);
	}else{
		waitpid(pid, &stat, 0);
	}

	getchar();
	system("clear");
	cout << "Aplikasi ketiga adalah clipping" << endl;
	cout << "Tekan wasd untuk menjalankan clip" << endl;
	cout << "Tekan qe untuk melakukan zooming" << endl;
	cout << "Tekan p atau Esc untuk keluar dari aplikasi" << endl;
	cout << "Tekan sembarang tombol untuk melanjutkan" << endl;
	getchar();

	pid = fork();
	if(pid==0){
		execl("main", "main", NULL);
	}else{
		waitpid(pid, &stat, 0);
	}

	getchar();
	system("clear");
	cout << "Aplikasi keempat adalah perang" << endl;
	cout << "Tekan p atau Esc untuk keluar dari aplikasi" << endl;
	cout << "Tekan sembarang tombol untuk melanjutkan" << endl;

	pid = fork();
	if(pid==0){
		execl("maintes", "maintes", NULL);
	}else{
		waitpid(pid, &stat, 0);
	}	
	return 0;
}