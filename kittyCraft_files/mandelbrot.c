
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

#ifdef __amigaos4__
#include <proto/exec.h>
#include <proto/retroMode.h>
#endif

#ifdef __linux__
#include <string.h>
#include "os/linux/stuff.h"
#include <retromode.h>
#include <retromode_lib.h>
#endif

#include <amosKittens.h>
#include "context.h"


#define _m_ = 4.0

void mandelbrot(  struct retroScreen *screen , int iterations, struct fractal *f)
{
	int kt = iterations ;// 319;
//	int  m = 4.0;
	int wix,wiy,wiw,wih;
	int x,y;
	int k;

//	kt =;

	wix = f -> window.x;
	wiy = f -> window.y;
	wiw = f -> window.width - f->window.x;
	wih = f -> window.height - f->window.y;

	double scalex = 1.5;
	double scaley = 1.5;

	double xmin = -2.5;
	double xmax = 1.5; 
	double ymin = -1.5;
	double ymax = 1.5;

	double jx,jy;
	double wx,wy;
	double tx,ty;
	double r;

//	xmin *=scalex;
//	xmax *=scalex;


	double dx = (xmax - xmin) / wiw; 
	double dy = (ymax - ymin) / wih;

	unsigned char *mem = screen -> Memory[ screen -> double_buffer_draw_frame ];

	for ( x= 0; x<wiw ; x++)
	{
		jx = xmin + x * dx;
		for (y= 0 ; y < wih; y++)
		{
			jy = ymin + y * dy;
			k = 0 ; wx =0.0f; wy = 0.0f;

			do
			{
				tx = wx *wx - wy *wy + jx;
				ty = 2.0 * wx * wy + jy;
				wx = tx;
				wy = ty;
				r = wx*wx+wy *wy;
				k=k+1;
			}
			while (!((r>4.0f)||(k>kt)));
	
			if (k>kt) k = 0;
			retroPixel( screen, mem , x+wix, y+wiy, k); 
		}
	}
}

