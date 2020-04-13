
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

void julia(  struct retroScreen *screen, int _cr, int _cy, int iterations, struct fractal *f)
{
	int wix,wiy,wiw,wih;
	double wiw2,wih2,wiw4,wih4;
	int x,y,i;
	double cyo,cx,cy,xt,creal,cimag;
	double cr;

	wix = f -> window.x;
	wiy = f -> window.y;
	wiw = f -> window.width - f->window.x;
	wih = f -> window.height - f->window.y;

	unsigned char *mem = screen -> Memory[ screen -> double_buffer_draw_frame ];

	printf( "%d %d\n",wiw,wih);

	cr = (double) _cr /1000000.0;	// convert to float

	creal = -0.8+0.6*sin(cr/(M_PI*20.0));
	cimag = 0.159 + 0.4*cos( _cr/(M_PI*40) );

	wih2=wih/2.0;
	wiw2=wiw/2.0;
	wih4=wih/4.0;
	wiw4=wiw/4.0;

	for ( y= 0;y<wih;y++)
	{
		cyo = -2.0+ ((double) y) / wih4;
		for ( x = 0; x< wiw; x++)
		{
			cx=-2.0+ ((double) x) / wiw4;
			cy=cyo;	// reset y
			i=0;
			do
			{
				xt=cx*cx-cy*cy+creal;
				cy=2.0*cx*cy+cimag;
				cx=xt;
				i++;
			} while ( ! (  ( (cx*cx + cy*cy) >=4.0) || (i>=iterations) ));

			retroPixel( screen, mem , x+wix, y+wiy, i); 
		}
	}

	Delay(10);
}

