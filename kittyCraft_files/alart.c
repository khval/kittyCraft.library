#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/intuition.h>
#include <intuition/intuition.h>
#include <proto/graphics.h>

#include <proto/retroMode.h>
#include <AmosKittens.h>
#include <amosString.h>

struct Window *alart_window = NULL;

#define IDCMP_COMMON IDCMP_MOUSEBUTTONS | IDCMP_REFRESHWINDOW | IDCMP_RAWKEY | IDCMP_EXTENDEDMOUSE | IDCMP_INTUITICKS 
 
struct Window *open_window()
{
	struct Screen *screen = LockPubScreen(NULL);

	if (screen)
	{
		alart_window = OpenWindowTags( NULL,
				WA_Left,			0,
				WA_Top,			0,
				WA_InnerWidth,		screen -> Width,
				WA_InnerHeight,	screen -> Height,
				WA_SimpleRefresh,	TRUE,
				WA_CloseGadget,	FALSE,
				WA_DepthGadget,	FALSE,
				WA_DragBar,		FALSE,
				WA_Borderless,	TRUE,
				WA_SizeGadget,	FALSE,
				WA_SizeBBottom,	FALSE,
				WA_NewLookMenus,	FALSE,
				WA_Title, 			NULL,
				WA_Activate,        TRUE,
				WA_Flags, WFLG_RMBTRAP| WFLG_REPORTMOUSE,
				WA_IDCMP,           IDCMP_COMMON,
			TAG_DONE);


		UnlockPubScreen(NULL, screen);
		screen = NULL;
	}


	return alart_window ;
}

void empty_que( struct MsgPort *port )
{
	struct IntuiMessage *msg;

	msg = (struct IntuiMessage *) GetMsg( port );
	while ( msg )
	{
		ReplyMsg( (struct Message*) msg );
		msg = (struct IntuiMessage *) GetMsg( port );
	}
}

void close_window( )
{
	if (alart_window)
	{
		CloseWindow( alart_window );
		alart_window = NULL;
	}
}

struct alartcontext
{
	struct RastPort *rp;
	ULONG xmin, ymin, xmax, ymax;
};

void drawTextLines( struct alartcontext *alart,  int nargs, struct stringData **args )
{
	int n;
	struct TextExtent te;
	int sx,th,yt,tah;

	TextExtent( alart -> rp, &(args[0]->ptr), args[0] -> size, &te );

	SetRPAttrs( alart -> rp,
		RPTAG_DrMd, JAM1,
		RPTAG_APenColor,0xFFFF0000,
		RPTAG_BPenColor,0xFF000000,
		TAG_END);

	th = -te.te_Extent.MinY;

	tah=nargs * th;
	
	sx = (alart -> xmax/2);
	yt = (alart -> ymax/2) - (tah/2);

	for (n=0;n<nargs;n++)
	{
		TextExtent( alart -> rp, &(args[n]->ptr), args[n] -> size, &te );
		Move( alart -> rp, sx - (te.te_Width/2),n*th+yt );
		Text( alart -> rp, &(args[n]->ptr), args[n] -> size );	
	}
}

int guruAlert( int nargs, struct stringData **args )
{
	struct IntuiMessage *msg = NULL;
	struct MsgPort *mp;
	LONG ret = 0;
	ULONG cnt = 0;
	ULONG color = 0xFFFF0000;
	int b = 5;

	if ( open_window() )
	{
		struct alartcontext alart;

		alart.xmin = 0;	
		alart.ymin =0;
		alart.xmax = alart_window -> Width-1;
		alart.ymax = alart_window -> Height-1;

		alart.rp = alart_window -> RPort;

		mp = alart_window -> UserPort;

		RectFillColor(alart.rp, alart.xmin, alart.ymin, alart.xmax, alart.ymax, 0x000000);

		alart.ymax = alart.xmax * 10 / 100;

		drawTextLines( &alart,  nargs, args );

		do
		{
			msg = (struct IntuiMessage *) GetMsg( mp );
			while ( msg )
			{
				switch ( msg -> Class )
				{
					case IDCMP_MOUSEBUTTONS:

						switch (msg -> Code)
						{
							case SELECTDOWN:	ret = 1;
								break;
							case MENUDOWN:	ret = 2;
								break;
						}
						break;
				}

				ReplyMsg( (struct Message*) msg );
				msg = (struct IntuiMessage *) GetMsg( mp );
			}

			Delay(1);
			cnt++;
			if (cnt==20)
			{
				color ^=0xFF0000;
				RectFillColor(alart.rp, alart.xmin, alart.ymin, alart.xmax, alart.ymin+b, color);
				RectFillColor(alart.rp, alart.xmin, alart.ymax-b, alart.xmax, alart.ymax, color);
				RectFillColor(alart.rp, alart.xmin, alart.ymin, alart.xmin+b, alart.ymax, color);
				RectFillColor(alart.rp, alart.xmax-b, alart.ymin, alart.xmax, alart.ymax, color);
				cnt = 0;
			}
		} while ( ! ret );

		empty_que( mp );
		close_window();
	}

	return ret;
}

