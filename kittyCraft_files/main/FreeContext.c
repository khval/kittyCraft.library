/* :ts=4
 *  $VER: FreeContext.c $Revision$ (22-Mar-2020)
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

#include <exec/exec.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <dos/dos.h>
#include <exec/types.h>
#include <libraries/kittycraft.h>
#include <proto/kittyCraft.h>
#include <stdarg.h>
#include "context.h"

/****** kittyCraft/main/FreeContext ******************************************
*
*   NAME
*      FreeContext -- Description
*
*   SYNOPSIS
*      void FreeContext(void * table);
*
*   FUNCTION
*
*   INPUTS
*       table - 
*
*   RESULT
*       This function does not return a result
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

void _kittycraft_FreeContext(struct kittyCraftIFace *Self,  struct context * context)
{
	int n;

	printf("Free context %08x\n", (unsigned int) context);

	if (context)
	{
		if (context -> multiOffCount)
		{
			printf("Craft had hanging Forbid!\n");
			Permit();
			context -> multiOffCount =0;
		}

		printf("context -> used_dir_contexts: %d\n", (unsigned int) context -> used_dir_contexts);

		for ( n=0; n < context -> used_dir_contexts; n++ )
		{
			printf("check dir_context[%d]\n", n);
			if (context -> dir_context[n])
			{
				printf("free dir_context[%d]\n",n);
				ReleaseDirContext(context -> dir_context[n]);
				context -> dir_context[n] = NULL;
			}
		}
		free (context);
	}
}

