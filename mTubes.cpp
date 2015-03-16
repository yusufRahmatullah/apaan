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
	int pid=0;
	int stat;

	pid = fork();
	if(pid==0){
		execl("colorpicker", "colorpicker", NULL);
	}else{
		waitpid(pid, &stat, 0);
	}

	pid = fork();
	if(pid==0){
		execl("m3dmap", "m3dmap", NULL);
	}else{
		waitpid(pid, &stat, 0);
	}

	pid = fork();
	if(pid==0){
		execl("main", "main", NULL);
	}else{
		waitpid(pid, &stat, 0);
	}

	pid = fork();
	if(pid==0){
		execl("maintes", "maintes", NULL);
	}else{
		waitpid(pid, &stat, 0);
	}
	return 0;
}