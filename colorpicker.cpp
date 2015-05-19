#include "FrameBuffer.h"
#include <cstdio>
#include <string>
#include <cstring>
#include <termios.h>
#include <sys/select.h>

using namespace std;

struct termios orig_termios;
struct termios new_termios;

void resetTerminal(){
	tcsetattr(0, TCSANOW, &orig_termios);
}

int main()
{
	FrameBuffer fb;
	
	//init keyboard listener
	// inisialisasi event keyboard pada Linux
	tcgetattr(0, &orig_termios);
	memcpy(&new_termios, &orig_termios, sizeof(new_termios));
	atexit(resetTerminal);
	cfmakeraw(&new_termios);
	tcsetattr(0, TCSANOW, &new_termios);
	
	bool panel = false;
	unsigned int R = 0;
	unsigned int G = 0;
	unsigned int B = 0;

	// loop utama program
	while(1)
	{
		// pada awal loop membaca input dari keyboard
		int keyCode;
		int r;
		unsigned char c;
		struct timeval tv = {0L, 0L};
		fd_set fds;
		FD_ZERO(&fds);
		FD_SET(0, &fds);
		if(select(1, &fds, NULL, NULL, &tv)){
			if((r = read(0, &c, sizeof(c)))<0)
				keyCode = r;
			else
				keyCode = c;

			//////////////////////////////
			// membaca input dari keyboard
			//////////////////////////////

			// panel colorpicker sebelah kiri untuk mengambil warna yang diinginkan
			// tekan w, a, s, d untuk memindahkan cursor

			// panel colorpicker sebelah kanan untuk mengatur nilai Blue pada warna
			// tekan angka 9 untuk mengaktifkan panel
			// tekan w atau a untuk mengubah nilai Blue pada panel sebelah kanan

			// tekan Esc atau p untuk keluar dari program
			if(keyCode == 'w'){
				if (panel)
				{
					if (B > 0)
					{
						B--;
					}
					else
					{
						B = 255;
					}
				}
				else
				{
					if (G > 0)
					{
						G--;
					}
					else
					{
						G = 255;
					}
				}
			}else if(keyCode == 'a'){
				if (!panel)
				{
					if (R > 0)
					{
						R--;
					}
					else
					{
						R = 255;
					}
				}
			}else if(keyCode == 's'){
				if (panel)
				{
					if (B < 255)
					{
						B++;
					}
					else
					{
						B = 0;
					}
				}
				else
				{
					if (G < 255)
					{
						G++;
					}
					else
					{
						G = 0;
					}
				}
			}else if(keyCode == 'd'){
				if (!panel)
				{
					if (R < 255)
					{
						R++;
					}
					else
					{
						R = 0;
					}
				}
			}else if(keyCode == 9){
				panel = !panel;
			}else if(keyCode == 'e'){
				
			}else if(keyCode == 27 || keyCode == 'p'){
				system("clear");
				exit(0);
			}
		}

		// inisialisasi framebuffer dengan mengosongkan layar
		fb.initScreen();

		//////////////////////////////
		// menggambar panel colorpicker
		//////////////////////////////
		unsigned int color = (R<<16) | (G<<8) | B;
		for (unsigned int x=0;x<256;x++)
		{
			for (unsigned int y=0;y<256;y++)
			{
				fb.putPixel(x,y,(x << 16) | (y << 8) | B);
			}
		}
		for (unsigned int y=0;y<256;y++)
		{
			for (unsigned int x=300;x<350;x++)
			{
				fb.putPixel(x,y,y);
			}
		}
		if (panel)
		{
			for (unsigned int x=300;x<350;x++)
			{
				fb.putPixel(x,B,0xffffff);
			}
		}
		else
		{
			fb.putPixel(R,G,~color);
		}
		for (unsigned int x=0;x<100;x++)
		{
			for (unsigned int y=0;y<100;y++)
			{
				if (x == 0 || x == 99 || y == 0 || y == 99)
				{
					fb.putPixel(400+x,y,0xffffff);
				}
				else
				{
					fb.putPixel(400+x,y,color);
				}
			}
		}

		// menggambarkan setiap pixel pada framebuffer ke layar
		fb.drawScreen();

		// setelah framebuffer ditampilkan ke layar
		// program kembali ke awal loop untuk mendeteksi input keyboard
	}
	return 0;
}
