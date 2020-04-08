
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include <utility/tagitem.h> 
#include <libraries/asl.h> 
#include <interfaces/asl.h>

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/intuition.h>

#include <proto/graphics.h>
#include <proto/gadtools.h>
#include <proto/asl.h>
#include <proto/requester.h>

#include <classes/requester.h>
#include <reaction/reaction_macros.h>

#include <proto/retroMode.h>
#include <AmosKittens.h>
#include <amosString.h>

struct context_request
{
	struct Library *ReqBase;
	struct RequesterIFace *IRequester;
	char *buttons;
	char *body;
};

void init_request_classes(struct context_request *this)
{
	this -> IRequester = NULL;
	this -> ReqBase = NULL;
	this -> buttons = NULL;
	this -> body = NULL;
}

void close_request_classes(struct context_request *this)
{
	if (this -> IRequester) DropInterface( (struct Interface *) this -> IRequester );
	if (this -> ReqBase) CloseLibrary( this -> ReqBase );
	if (this -> buttons) free( this -> buttons );
	if (this -> body) free( this -> body );

	init_request_classes( this );
}

#undef REQUESTER_GetClass

extern BOOL open_lib( const char *name, int ver , const char *iname, int iver, struct Library **base, struct Interface **interface);

int request(
		char *title, 
		int nargs, 
		struct stringData **args, 
		struct stringData *okButton,
		struct stringData *cancelButton, 
		ULONG image )
{  
	struct context_request this;
	Object *req = NULL;
	int n=0,size = 0;
	int ret = 0,reply =0;

	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	init_request_classes( &this );

	if (open_lib("requester.class", 51L,"main", 1L, &this.ReqBase, (void **) &this.IRequester ))
  	{
		for (n=0;n<nargs;n++) size += args[n] -> size;
		size +=nargs+1;

		this.body = (char *) malloc( size );
		this.buttons = (char *) malloc( okButton -> size + cancelButton -> size + 2 );

		if ((this.body) && (this.buttons))
		{
			this.body[0]=0;
			if (nargs>0) sprintf( this.body, "%s", &(args[0] -> ptr));
			for (n=1;n<nargs;n++) sprintf( this.body + strlen(this.body), "\n%s", &(args[n] -> ptr));
			sprintf(this.buttons,"%s|%s",&(okButton -> ptr), &(cancelButton -> ptr));

			req = NewObject( this.IRequester -> REQUESTER_GetClass(), NULL, 
					REQ_Type,       REQTYPE_INFO,
					REQ_TitleText,  (ULONG) title,
					REQ_BodyText,   (ULONG) this.body,
					REQ_GadgetText, (ULONG) this.buttons ,
					REQ_Image,      image,
					TAG_DONE);
		}

		if (req) 
		{
			struct Screen* screen = LockPubScreen(NULL);
			if (screen) 
			{
				reply = IDoMethod(req, RM_OPENREQ, NULL, NULL, screen);
				UnlockPubScreen(NULL, screen);
				screen = NULL;

				ret = -reply;
			}
			DisposeObject(req);
		} 
        } 

	close_request_classes( &this );
	return ret;
}
