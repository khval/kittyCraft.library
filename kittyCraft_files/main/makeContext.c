/* :ts=4
 *  $VER: makeContext.c $Revision$ (22-Mar-2020)
 *
 *  This file is part of kittyCraft.
 *
 *  Copyright (c) 2020 LiveForIt Software.
 *  MIT License..
 *
 * $Id$
 *
 * $Log$
 *
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <exec/exec.h>
#include <proto/exec.h>
#include <dos/dos.h>
#include <proto/dos.h>
#include <exec/types.h>
#include <libraries/kittycraft.h>
#include <proto/kittyCraft.h>
#include <stdarg.h>
#include "context.h"

/****** kittyCraft/main/makeContext ******************************************
*
*   NAME
*      makeContext -- Description
*
*   SYNOPSIS
*      void * makeContext(void);
*
*   FUNCTION
*
*   INPUTS
*
*   RESULT
*       The result ...
*
*   EXAMPLE
*
*   NOTES
*
*   BUGS
*
*   SEE ALSO
*
*****************************************************************************
*
*/



void * _kittycraft_makeContext(struct kittyCraftIFace *Self)
{
	struct context *context;

	context =  malloc(sizeof(struct context));
	if (context)
	{
		bzero( context, sizeof(struct context) );
		printf("context -> used_dir_contexts: %d\n", (unsigned int) context -> used_dir_contexts);
	}

	return context;
}

