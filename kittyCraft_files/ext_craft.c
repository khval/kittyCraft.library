

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

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
#include <amosString.h>
#include "stack.h"

#include <kittyErrors.h>

#include "cmdList.h"

#define kittyError instance->kittyError
#define api instance -> api
#define last_var instance -> last_var
#define cmdTmp instance -> cmdTmp

#define alloc_private(x) AllocVecTags( x , AVT_Type, MEMF_PRIVATE, TAG_END )
#define alloc_shared(x) AllocVecTags( x , AVT_Type, MEMF_SHARED, TAG_END )

#define proc_names_printf printf

char *_craftUpCaseSTR(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	struct stringData *str;
	char *s;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	if (args !=1)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}

	str = getStackString( instance,__stack );
	if (str)
	{
		for (s=&str -> ptr;*s;s++) if ((*s>='a')&&(*s<='z')) *s+=('A'-'a');
	}

	return NULL;
}

char *craftUpCaseSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	stackCmdParm( _craftUpCaseSTR, tokenBuffer );	// we need to store the step counter.
	return tokenBuffer;
}

char *_craftLoCaseSTR( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	struct stringData *str;
	char *s;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	if (args !=1)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}

	str = getStackString( instance,__stack );
	if (str)
	{
		for (s=&str ->ptr;*s;s++) if ((*s>='A')&&(*s<='Z')) *s-=('A'-'a');
	}

	return NULL;
}

char *craftLoCaseSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftLoCaseSTR, tokenBuffer );
	return tokenBuffer;
}

char *_craftFlipCaseSTR( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	struct stringData *str;
	char *s;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	if (args !=1)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}

	str = getStackString( instance,__stack );
	if (str)
	{
		for (s=&str ->ptr;*s;s++)
		{
			if ((*s>='A')&&(*s<='Z'))
			{
				 *s-=('A'-'a');
			}
			else if ((*s>='a')&&(*s<='z'))
			{
				 *s-=('a'-'A');
			}
		}
	}

	return NULL;
}


char *craftFlipCaseSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftFlipCaseSTR, tokenBuffer );
	return tokenBuffer;
}

char *_craftLeftTrimSTR( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	struct stringData *str,*remove;
	struct stringData *newStr;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	api.dumpStack();

	switch (args)
	{
		case 1:
			{
				char *src;
				int toRemove = 0;
				int n;
				str = getStackString( instance,__stack);

				src = &(str -> ptr);
				for (n=0;n<str->size;n++)
				{
					if ( src[n] != ' ' ) break;
					toRemove ++;
				}

				newStr = amos_right( str, str->size - toRemove );
				setStackStr( instance, newStr);
			}
			return NULL;

		case 2:
			str = getStackString( instance,__stack -1);
			remove = getStackString( instance,__stack);
			break;

		default:
			popStack( instance, instance_stack - data->stack );
			api.setError(22, data -> tokenBuffer);
			return NULL;
	}

	{
		char *src = &(str -> ptr);
		char *d = &(remove -> ptr);
		int toRemove = 0;
		char c;
		int n;
		int n2;
		bool found;

		for (n=0;n<str->size;n++)
		{
			c = src[n];

			found = false;
			for (n2=0;n2<remove -> size;n2++)
			{
				printf("%c is %c?\n",d[n2],c);

				if (d[n2] == c )
				{
					printf("%c",c);

					found = true;
					break;
				}
			}

			if (found == false)	 break;

			toRemove ++;
		}

		newStr = amos_right( str, str->size - toRemove );
	}

	popStack( instance, instance_stack - data->stack );

	setStackStr( instance, newStr);
	return NULL;
}

char *craftLeftTrimSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftLeftTrimSTR, tokenBuffer );
	return tokenBuffer;
}

char *_craftRightTrimSTR( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	struct stringData *str,*remove;
	struct stringData *newStr;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	api.dumpStack();

	switch (args)
	{
		case 1:
			{
				char *src;
				int toRemove = 0;
				int n;
				str = getStackString( instance,__stack);

				src = &(str -> ptr);
				for (n=str->size-1;n>-1;n--)
				{
					printf("[%d]=%c\n",n,src[n]);

					if ( src[n] != ' ' ) break;
					toRemove ++;
				}

				printf("remove %d\n", toRemove);

				newStr = amos_strndup( str, str->size - toRemove );
				setStackStr( instance, newStr);
			}
			return NULL;

		case 2:
			str = getStackString( instance,__stack -1);
			remove = getStackString( instance,__stack);
			break;

		default:
			popStack( instance, instance_stack - data->stack );
			api.setError(22, data -> tokenBuffer);
			return NULL;
	}

	{
		char *src = &(str -> ptr);
		char *d = &(remove -> ptr);
		int toRemove = 0;
		char c;
		int n;
		int n2;
		bool found;

		for (n=str->size-1;n>-1;n--)
		{
			c = src[n];

			found = false;
			for (n2=0;n2<remove -> size;n2++)
			{
				if (d[n2] == c )
				{
					found = true;
					break;
				}
			}

			if (found == false)	 break;

			toRemove ++;
		}

		newStr = amos_strndup( str, str->size - toRemove );
	}

	popStack( instance, instance_stack - data->stack );

	setStackStr( instance, newStr);

	return NULL;
}

char *craftRightTrimSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftRightTrimSTR, tokenBuffer );
	return tokenBuffer;
}

char *craftBwInstr KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftChrConvSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftStrCount KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftMemStrCount KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftStrScrambleSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftStrUnscrambleSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftHexDumpSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftChrDumpSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftStrPeekSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftStrPoke KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftChipMaxBlock KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftFastMaxBlock KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftMemCopy KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftMemType KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftMemScramble KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftMemUnscramble KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftDrFileSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftDrPathSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftDbFree KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftDbUsed KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftDbSize KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftDiscState KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftDiscTypeSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftFileProtect KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftFileCommentSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftFileLength KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}
char *craftFileType KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftSetProtect KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftSetComment KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftDrNameSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftDrNextSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftDrCommentSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftDrProtect KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftDrLength KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftDrType KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftDrFib KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftDrForget KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftDiscError KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftSetRed KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftPalRed KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftSetGreen KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftPalGreen KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftSetBlue KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftPalBlue KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftPalSpread KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftPalSwap KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftPalCopy KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftReserveAsPalette KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftPalCount KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftPalToBank KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftPalFromBank KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftPalSwapBank KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftSetBankColour KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftBankColour KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftDelBankColour KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrExec KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrError KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrReset KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrAngle KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrGetAngle KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrLeft KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrRight KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrTowards KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrForward KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrForw KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrBack KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrDistance KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrPenUp KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrPenDown KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrPenState KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrMoveRel KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrMove KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrDrawRel KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrDraw KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrXPos KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrYPos KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrProportions KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrSetHome KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrHome KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrXHome KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrYHome KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrRememberX KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrRememberY KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrRememberA KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrMemorizeX KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrMemorizeY KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrMemorizeA KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftTrBase KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftFrReset KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftFrXPosition KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftFrYPosition KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftFrPosition KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftFrXStep KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftFrYStep KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftFrStep KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftFrColour KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftFrGetColour KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftFrWindow KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftFrScanAll KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftFrScan KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftFrJulia KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftFrMandelbrot KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftOpenWorkbench KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftWbToBack KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftWbToFront KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftCliExecute KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftCliPrint KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftGuruMeditation KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftGuruAlert KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftMultiOn KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftMultiOff KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftSetAmosPri KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftAmosPri KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftWbDefPrefs KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftWbPrefs KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftSysRequest KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftHardReset KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftWarmReset KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftHwMouseKey KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftYBeam KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftBeamWait KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftGrInk KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftGrBack KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftGrBorder KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftGrCentre KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftAmosBase KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftCraftVersion KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftB_swap KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftCliHere KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftAmosPro KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftSetWbPrefs KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *craftL_swap KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}


char *craftW_swap KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}



