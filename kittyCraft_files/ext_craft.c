

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
#include <amosString.h>
#include "stack.h"

#include "kittyCraft.library_rev.h"
#include <kittyErrors.h>
#include "cmdList.h"

#include "context.h"

#define kittyError instance->kittyError
#define api instance -> api
#define last_var instance -> last_var
#define cmdTmp instance -> cmdTmp

#define alloc_private(x) AllocVecTags( x , AVT_Type, MEMF_PRIVATE, TAG_END )
#define alloc_shared(x) AllocVecTags( x , AVT_Type, MEMF_SHARED, TAG_END )

#define proc_names_printf printf

#define max(a,b) ((a)>(b)?(a):(b))

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

char *_craftBwInstr(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	struct stringData *txt=NULL,*item=NULL;
	int size;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	api.dumpStack();

	switch (args)
	{
		case 2:
			txt = getStackString( instance,__stack-1 );
			item = getStackString( instance,__stack );
			size = txt->size;
			break;

		case 3:
			txt = getStackString( instance,__stack-2 );
			item = getStackString( instance,__stack-1 );
			size = getStackNum( instance,__stack );
			size = size < txt->size ? size : txt->size;
			break;

		default:
			popStack( instance, instance_stack - data->stack );
			api.setError(22, data -> tokenBuffer);
			return NULL;
	}


	if ((txt)&&(item))
	{
		char *ptr = &txt -> ptr;
		char *itemPtr = &item -> ptr;

		size -= max(item -> size - 1,0);
		int n,ret =0;

		printf("size: %d\n",size);

		for (n=0;n<size;n++)
		{
			printf("%s--%s\n",ptr+n,itemPtr);

			if (strncasecmp(ptr+n,itemPtr,item->size)==0)
			{
				ret = n+1;
				break;
			}
		}
		
		popStack( instance, instance_stack - data->stack );
		setStackNum( instance, ret );
	}

	return NULL;
}

char *craftBwInstr KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftBwInstr, tokenBuffer );
	return tokenBuffer;
}


char *_craftChrConvSTR(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	switch (args)
	{
		case 3:
			{
				unsigned char *c;
				struct stringData *txt = getStackString( instance,__stack-2 );
				unsigned char from = (unsigned char) getStackNum( instance,__stack-1 );
				unsigned char to = (unsigned char) getStackNum( instance,__stack );

				c = (unsigned char *) &txt -> ptr;
				while (*c)
				{
					if (*c == from) *c=to;
					c++;
				}

				popStack( instance, 1 );	// free two. (this, and current)
				instance_stack--;		// do not change txt string 
			}
			return NULL;

		default:

			popStack( instance, instance_stack - data->stack );
			api.setError(22, data -> tokenBuffer);
			return NULL;
	}

	return NULL;
}


char *craftChrConvSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftChrConvSTR, tokenBuffer );
	return tokenBuffer;
}

char *_craftStrCount(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	struct stringData *txt=NULL,*item=NULL;
	int size;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	api.dumpStack();

	switch (args)
	{
		case 2:
			txt = getStackString( instance,__stack-1 );
			item = getStackString( instance,__stack );
			size = txt->size;
			break;

		default:

			popStack( instance, instance_stack - data->stack );
			api.setError(22, data -> tokenBuffer);
			return NULL;
	}

	if ((txt)&&(item))
	{
		int n,ret =0;
		char *ptr = &txt -> ptr;
		char *itemPtr = &item -> ptr;
		size -= max(item -> size - 1,0);

		for (n=0;n<size;n++)
		{
			if (strncasecmp(ptr+n,itemPtr,item->size)==0) ret++;
		}
		
		popStack( instance, instance_stack - data->stack );
		setStackNum( instance, ret );
	}
	return NULL;
}

char *craftStrCount KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftStrCount, tokenBuffer );
	return tokenBuffer;
}

char *_craftMemStrCount(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	int cnt = 0;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	api.dumpStack();

	switch (args)
	{
		case 2:
			{
				char *adr = (char *) getStackNum( instance,__stack -1 );
				struct stringData *item = getStackString( instance,__stack );

				while (*adr)
				{
					if (strncasecmp(adr,&item ->ptr,item -> size)==0) cnt++;
					adr++;
				}
				popStack( instance, instance_stack - data->stack );
				setStackNum( instance, cnt );
				return NULL;
			}
			break;

		case 3:
			{
				char *adr = (char *) getStackNum( instance,__stack -2 );
				char *adrTo= (char *) getStackNum( instance,__stack -1 );
				struct stringData *item = getStackString( instance,__stack );

				while (adr<adrTo)
				{
					if (strncasecmp(adr,&item ->ptr,item -> size)==0) cnt++;
					adr++;
				}
				popStack( instance, instance_stack - data->stack );
				setStackNum( instance, cnt );
				return NULL;

			}
			break;

		default:

			popStack( instance, instance_stack - data->stack );
			api.setError(22, data -> tokenBuffer);
			return NULL;
	}
	return NULL;
}

char *craftMemStrCount KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftMemStrCount, tokenBuffer );
	return tokenBuffer;
}

void __scramble__( char *txtRaw, char *txtRawTo, struct stringData *pass )
{
	char c;
	int n;
	char *passRaw = &pass->ptr;

	n=0;
	for (;txtRaw<=txtRawTo;txtRaw++)
	{
		c=passRaw[n % pass -> size];
		*txtRaw ^= ( ((c & 0xF0) >> 4) | ((c & 0x0F)<<4) ) ^ (n & 0xFF);
		n++;
	}
}

char *_craftStrScrambleSTR(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	printf("args: %d\n",args);

	api.dumpStack();

	switch (args)
	{
		case 2:
			{
				char *txtRaw;
				struct stringData *txt = getStackString( instance,__stack-1 );
				struct stringData *pass = getStackString( instance,__stack );

				txtRaw = &txt->ptr;
				__scramble__( txtRaw, txtRaw + txt->size - 1, pass );

				setStackNone( instance );
				instance_stack--;
				return NULL;
			}
			break;

		default:

			popStack( instance, instance_stack - data->stack );
			api.setError(22, data -> tokenBuffer);
			return NULL;
	}

	return NULL;
}

char *craftStrScrambleSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftStrScrambleSTR, tokenBuffer );
	return tokenBuffer;
}

char *craftStrUnscrambleSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftStrScrambleSTR, tokenBuffer );
	return tokenBuffer;
}

char *_craftHexDumpSTR(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	char *adr = NULL;
	int len = 0, sep =0;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	printf("args: %d\n",args);

	api.dumpStack();

	switch (args)
	{
		case 2:
			adr = (char *) getStackNum( instance,__stack -1);
			len = getStackNum( instance,__stack );
			sep = 4;
			break;

		case 3:
			adr = (char *) getStackNum( instance,__stack -2);
			len = getStackNum( instance,__stack-1 );
			sep = getStackNum( instance,__stack );
			break;

		default:
			popStack( instance, instance_stack - data->stack );
			api.setError(22, data -> tokenBuffer);
			return NULL;
	}

	{
		int n, size;
		char *dest;
		struct stringData *newStr;

		size = sep ? len*2 + len/sep : len*2 ;

		newStr = alloc_amos_string( size );

		dest = &newStr -> ptr;
		for (n=0;n<len;n++)
		{
			if ( (n>0) && (sep) && ( (n%sep) == 0) )
			{
				sprintf( dest, " %02x", adr[n] );
				dest +=3;
			}
			else 
			{
				sprintf( dest, "%02x", adr[n] );
				dest +=2;
			}
		}

		popStack( instance, instance_stack - data->stack );
		setStackStr( instance, newStr );
	}

	return NULL;
}

char *craftHexDumpSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftHexDumpSTR, tokenBuffer );
	return tokenBuffer;
}

char *_craftChrDumpSTR(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	switch (args)
	{
		case 2:
			{
				int n;
				unsigned char c;	
				unsigned char *dest, *adr = (unsigned char *) getStackNum( instance,__stack -1);
				int len = getStackNum( instance,__stack );
				struct stringData *newStr = alloc_amos_string( len );

				dest = (unsigned char *) &newStr -> ptr;
				for (n=0;n<len;n++)
				{
					c=adr[n];
					if ((c<=31))  c=46;
					if ((c>=128)&&(c<=159)) c=46;
					dest[n] = c;
				}

				popStack( instance, instance_stack - data->stack );
				setStackStr( instance, newStr );
				return NULL;
			}
			break;

		default:

			popStack( instance, instance_stack - data->stack );
			api.setError(22, data -> tokenBuffer);
			return NULL;
	}

	return NULL;
}

char *craftChrDumpSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftChrDumpSTR, tokenBuffer );
	return tokenBuffer;
}

char *_craftStrPeekSTR(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	unsigned char *adr;
	int len;
	int termchar = -1;
	struct stringData *newStr;
	unsigned char *dest;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	printf("args: %d\n",args);

	switch (args)
	{
		case 2:
			{
				adr = (unsigned char *) getStackNum( instance,__stack -1);
				len = getStackNum( instance,__stack );
			}
			break;

		case 3:
			{
				struct stringData *term;
				adr = (unsigned char *) getStackNum( instance,__stack -2);
				len = getStackNum( instance,__stack -1 );
				term = getStackString( instance,__stack );
				termchar = (int) ((unsigned char) term -> ptr);

				printf("3 args\n");
			}
			break;

		default:

			popStack( instance, instance_stack - data->stack );
			api.setError(22, data -> tokenBuffer);
			return NULL;
	}

	newStr = alloc_amos_string( len );
	dest = (unsigned char *) &newStr -> ptr;

	if (termchar==-1)
	{
		int n;

		for (n=0;n<len;n++)
		{
			dest[n]=adr[n];
		}

		printf("written\n");
	}
	else
	{
		int n;
		unsigned char c;

		printf("len %d termchar %c\n",len,termchar);

		for (n=0;n<len;n++)
		{
			c=adr[n];
			if (c == (char) termchar ) 
			{
				printf("n %d\n",n);
				newStr -> size  = n;
				dest[n]=0; 
				break; 
			}
			dest[n]=c;
		}
	}

	popStack( instance, instance_stack - data->stack );
	setStackStr( instance, newStr );

	return NULL;
}

char *craftStrPeekSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftStrPeekSTR, tokenBuffer );
	return tokenBuffer;
}

char *_craftStrPoke(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	unsigned char *address;
	unsigned char *source;
	struct stringData *str;
	int n;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	api.dumpStack();

	switch (args)
	{
		case 2:
			{
				address = (unsigned char *) getStackNum( instance,__stack -1);
				str = getStackString( instance,__stack );
			}
			break;

		default:

			popStack( instance, instance_stack - data->stack );
			api.setError(22, data -> tokenBuffer);
			return NULL;
	}

	source = (unsigned char *) &str -> ptr;
	for (n=0;n<str->size;n++)
	{
		*address++=*source++;
	}

	setStackNone( instance );
 	instance_stack --;
	return NULL;
}

char *craftStrPoke KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _craftStrPoke, tokenBuffer );
	return tokenBuffer;
}

char *craftChipMaxBlock KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	setStackNum( instance, AvailMem( MEMF_CHIP | MEMF_LARGEST ) );
	return tokenBuffer;
}

char *craftFastMaxBlock KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	setStackNum( instance, AvailMem( MEMF_FAST | MEMF_LARGEST ) );
	return tokenBuffer;
}

char *_craftMemCopy(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	unsigned char *addressSource,*addressEnd,*addressDest;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	switch (args)
	{
		case 3:
			{
				addressSource = (unsigned char *) getStackNum( instance,__stack -2);
				addressEnd = (unsigned char *) getStackNum( instance,__stack -1);
				addressDest = (unsigned char *) getStackNum( instance,__stack );
			}
			break;

		default:

			popStack( instance, instance_stack - data->stack );
			api.setError(22, data -> tokenBuffer);
			return NULL;
	}

	for (;addressSource<=addressEnd;addressSource++)
	{
		*addressDest++=*addressSource;
	}

	popStack( instance, instance_stack - data->stack );
	return NULL;
}

char *craftMemCopy KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _craftMemCopy, tokenBuffer );
	return tokenBuffer;
}

char *_craftMemType( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	char *adr;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	if (args !=1)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}

	adr =(char *) getStackNum( instance,__stack );
	setStackNum( instance, TypeOfMem(adr) );

	return NULL;
}

char *craftMemType KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftMemType, tokenBuffer );
	return tokenBuffer;
}


char *_craftMemScramble(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	printf("args: %d\n",args);

	api.dumpStack();

	switch (args)
	{
		case 2:
			{
				int bankNr = getStackNum( instance,__stack-1 );
				struct stringData *pass = getStackString( instance,__stack );
				struct kittyBank *bank;

				bank = api.findBank( bankNr );

				if (bank)
				{
					__scramble__( bank -> start, bank -> start + bank->length - 1, pass );
				}
				else api.setError(22, data -> tokenBuffer);
			}
			popStack( instance, instance_stack - data->stack );
			return NULL;

		case 3:
			{
				char *txtRaw = (char *) getStackNum( instance,__stack-2 );
				char *txtRawTo = (char *) getStackNum( instance,__stack-1 );
				struct stringData *pass = getStackString( instance,__stack );

				__scramble__( txtRaw, txtRawTo, pass );
			}
			popStack( instance, instance_stack - data->stack );
			return NULL;

		default:

			popStack( instance, instance_stack - data->stack );
			api.setError(22, data -> tokenBuffer);
			return NULL;
	}

	return NULL;
}

char *craftMemScramble KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _craftMemScramble, tokenBuffer );
	return tokenBuffer;
}

char *craftMemUnscramble KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _craftMemScramble, tokenBuffer );
	return tokenBuffer;
}


char *craftDrFileSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError( 22, tokenBuffer );
	return tokenBuffer;
}

char *_craftDrPathSTR( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	if (args !=1)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}
	else
	{
		int n;
		register char c;
		int r = -1;
		struct stringData *pathWithName = getStackString( instance,__stack );
		
		if (pathWithName)	// if its a string.
		{

			BPTR lock;
			APTR oldRequest;
			char *ptr = &pathWithName->ptr;

			oldRequest = SetProcWindow((APTR)-1);
			lock = Lock( ptr, SHARED_LOCK );
			SetProcWindow(oldRequest);

			if ( ! lock )	// If file / path do not exist should return error.
			{
				api.setError(81, data -> tokenBuffer);
				return NULL;
			}

			UnLock( lock );

			for (n=pathWithName -> size -1; n>=0;n--)
			{
				c = ptr[n];
				if ((c=='/') || (c==':')) 
				{
					r=n; 	break;
				}
			}

			if (r!=-1) // found path
			{
				ptr[r+1] = 0;
				instance->kittyStack[instance_stack].str -> size = r+1;	// truncate stack string.
			}
			else	// no path found.
			{
				instance->kittyStack[instance_stack].str -> size = 0;	// truncate stack string.
			}
		}
		else api.setError( 22, data -> tokenBuffer );
	}
	return NULL;
}

char *craftDrPathSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftDrPathSTR, tokenBuffer );
	return tokenBuffer;
}

enum
{
	e_freeDiskSize = 1,
	e_usedDiskSize,
	e_diskSize
};

uint64 getDiskBlockSize( int opt, struct stringData *volumeName)
{
	int result = -1;
	struct InfoData info;
	APTR oldRequest = SetProcWindow(NULL);

	result = GetDiskInfoTags( 
		GDI_StringNameInput, &volumeName -> ptr,
		GDI_InfoData, &info, TAG_END );

	SetProcWindow(oldRequest);

	if (result)
	{
		switch (opt)
		{
			case e_diskSize:
				return (uint64_t) info.id_NumBlocks;

			case e_freeDiskSize:
				return (uint64_t) info.id_NumBlocks - (uint64_t) info.id_NumBlocksUsed;

			case e_usedDiskSize:
				return (uint64_t) info.id_NumBlocksUsed;
		}
	}
	return 0;
}

char *_craftDbFree(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	uint64 ret;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	api.dumpStack();

	printf("args: %d\n",args);

	if (args !=1)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}

	ret = getDiskBlockSize(  e_freeDiskSize, getStackString( instance,__stack ) );

	if (ret<0x80000000)
	{
		setStackNum( instance, (int) ret ); 
	}
	else
	{
		setStackDecimal( instance, (double) ret );
	}
	return NULL;
}

char *craftDbFree KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftDbFree, tokenBuffer );
	return tokenBuffer;
}

char *_craftDbUsed(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	uint64 ret;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	printf("args: %d\n",args);

	if (args !=1)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}

	ret = getDiskBlockSize( e_usedDiskSize, getStackString( instance,__stack ) );

	if (ret<0x80000000)
	{
		setStackNum( instance, (int) ret ); 
	}
	else
	{
		setStackDecimal( instance, (double) ret );
	}
	return NULL;
}

char *craftDbUsed KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftDbUsed, tokenBuffer );
	return tokenBuffer;
}

char *_craftDbSize(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	uint64 ret;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	printf("args: %d\n",args);

	if (args !=1)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}

	ret = getDiskBlockSize(  e_diskSize, getStackString( instance,__stack ) );

	if (ret<0x80000000)
	{
		setStackNum( instance, (int) ret ); 
	}
	else
	{
		setStackDecimal( instance, (double) ret );
	}
	return NULL;
}

char *craftDbSize KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftDbSize, tokenBuffer );
	return tokenBuffer;
}

char *_craftDiscState(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	struct stringData  *name;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	printf("args: %d\n",args);

	if (args !=1)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}

	name = getStackString( instance,__stack );

	if (name)
	{
		int32 result = 0;
		struct InfoData *info = AllocDosObject(DOS_INFODATA,0);

		if (info) result = GetDiskInfoTags(
				GDI_StringNameInput, &name -> ptr,
				GDI_InfoData, info,
				TAG_END);

		if (result)	{
			setStackNum(instance, info -> id_DiskState );
		}
		else	{
			setStackNum(instance, -1 );
		}

		if (info) FreeDosObject(DOS_INFODATA, info);
	}

	return NULL;
}

char *craftDiscState KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftDiscState, tokenBuffer );
	return tokenBuffer;
}

char *_craftDiscTypeSTR(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	struct stringData  *name,*ret;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	printf("args: %d\n",args);

	if (args !=1)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}

	name = getStackString( instance,__stack );
	ret = alloc_amos_string( 4 );

	if (name)
	{
		int32 result = 0;
		struct InfoData *info = AllocDosObject(DOS_INFODATA,0);

		if (info) result = GetDiskInfoTags(
				GDI_StringNameInput, &name -> ptr,
				GDI_InfoData, info,
				TAG_END);

		if (result)	{
			*((uint32 *) &ret -> ptr) = info -> id_DiskType;
			setStackStr(instance, ret );
		}
		else	{
			*((uint32 *) &ret -> ptr) = -1;
			setStackStr(instance, ret );
		}

		if (info) FreeDosObject(DOS_INFODATA, info);
	}
	else
	{
		if (ret) sys_free( ret);
		ret = NULL;
		api.setError( 22, data -> tokenBuffer );
	}

	return NULL;
}

char *craftDiscTypeSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftDiscTypeSTR, tokenBuffer );
	return tokenBuffer;
}

char *_craftFileProtect( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	struct ExamineData *fdata = NULL;

	printf("instance -> current_extension: %d\n",instance -> current_extension);

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	api.dumpStack();

	if (args !=1)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}
	else
	{

printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

		struct stringData *file = getStackString( instance,__stack);
		if (file)
		{

printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

			fdata =ExamineObjectTags( EX_StringNameInput, &file -> ptr, TAG_END );
			if (fdata)
			{

printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

				if (fdata -> Comment)
				{
					printf("%s\n",fdata -> Comment);
					struct stringData *comment = toAmosString( fdata -> Comment, strlen( fdata -> Comment ) );

printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
printf("comment - 0x%08x\n",comment);

					setStackStr( instance, comment ) ;
				}

printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

				FreeDosObject(DOS_EXAMINEDATA,fdata); 
				fdata = NULL;
			}

printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

			return NULL;
		}
	}

	api.setError(22, data -> tokenBuffer);
	return NULL;
}

char *craftFileProtect KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftFileProtect, tokenBuffer );
	return tokenBuffer;
}

char *_craftFileCommentSTR( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	struct ExamineData *fdata = NULL;

	printf("instance -> current_extension: %d\n",instance -> current_extension);

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	api.dumpStack();

	if (args !=1)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}
	else
	{

printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

		struct stringData *file = getStackString( instance,__stack);
		if (file)
		{

printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
			fdata =ExamineObjectTags( EX_StringNameInput, &file -> ptr, TAG_END );
			if (fdata)
			{

printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
				setStackStr( instance, toAmosString( fdata -> Comment, strlen( fdata -> Comment ) ) ) ;
				FreeDosObject(DOS_EXAMINEDATA,fdata); 
				fdata = NULL;
			}

printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

			return NULL;
		}
	}

	api.setError(22, data -> tokenBuffer);
	return NULL;
}

char *craftFileCommentSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftFileCommentSTR, tokenBuffer );
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

char *_craftSetProtect( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;

	printf("instance -> current_extension: %d\n",instance -> current_extension);

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	api.dumpStack();

	if (args !=2)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}
	else
	{
		struct stringData *file = getStackString( instance,__stack-1);
		uint32 mask = (uint32) getStackNum( instance,__stack);
		if (file) SetProtection( &file -> ptr, mask );
	}

	popStack( instance, instance_stack - data->stack );
	return NULL;
}

char *craftSetProtect KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _craftSetProtect, tokenBuffer );
	return tokenBuffer;
}

char *_craftSetComment( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	api.dumpStack();

	if (args !=2)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}
	else
	{
		struct stringData *file = getStackString( instance,__stack-1);
		struct stringData *comment = getStackString( instance,__stack);
		if ((file)&&(comment)) SetComment( &file -> ptr, &comment -> ptr );
	}

	popStack( instance, instance_stack - data->stack );
	return NULL;
}

char *craftSetComment KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _craftSetComment, tokenBuffer );
	return tokenBuffer;
}


void start_dir_context(struct context *context, char *path)
{
printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

printf("context %08x\n", context );

	printf("context -> used_dir_contexts %d\n",context -> used_dir_contexts);
	printf("path: %s\n",path);

	context -> dir_context[ context -> used_dir_contexts ] =  ObtainDirContextTags(
			EX_StringNameInput, path,
			EX_DoCurrentDir,TRUE, 
			EX_DataFields,(EXF_NAME|EXF_LINK|EXF_TYPE), 
			TAG_END);

	// if success we count up

	if (context -> dir_context[ context -> used_dir_contexts ]) context -> used_dir_contexts ++; 
}

char *_craftDrNameSTR( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	struct context *context = instance -> extensions_context[ instance -> current_extension ];

	printf("instance -> current_extension: %d\n",instance -> current_extension);

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	api.dumpStack();

	if (args !=1)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}
	else
	{
		int n;
		register char c;
		int r = -1;
		struct stringData *path = getStackString( instance,__stack );
		
		if (path)	// if its a string.
		{
			BPTR lock;
			APTR oldRequest;
			char *ptr = &path->ptr;

			oldRequest = SetProcWindow((APTR)-1);
			lock = Lock( ptr, SHARED_LOCK );
			SetProcWindow(oldRequest);

printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

			if ( ! lock )	// If file / path do not exist should return error.
			{
				api.setError(81, data -> tokenBuffer);
				return NULL;
			}
			UnLock( lock );

			start_dir_context(context, &path -> ptr);

			if (path -> size -1>0)
			{
			 	char c = ptr[path -> size -1];

				if (c==':')	
				{
					return NULL;
				}

				if (c=='/') 
				{
					ptr[path -> size -1] = 0;
					path -> size--;
				}
			}

			for (n=path -> size -1; n>=0;n--)
			{
				c = ptr[n];
				if ((c=='/') || (c==':')) break;
				r = n;
			}

			if (r!=-1) // found name
			{
				int s = r;

				// move to front, saves me allocating new mem.
				n = 0;
				for (;ptr[s];s++,n++)
				{
					ptr[n]=ptr[s];
				}
				ptr[n]=0;
				instance->kittyStack[instance_stack].str -> size = n;	// truncate stack.
			}
			else	// no name found.
			{
				instance->kittyStack[instance_stack].str -> size = 0;	// truncate stack.
			}
		}
		else 
		{
			printf("we ended up here some how\n");
			api.setError( 22, data -> tokenBuffer );
		}
	}

	api.dumpStack();

	return NULL;
}

char *craftDrNameSTR KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftDrNameSTR, tokenBuffer );
	return tokenBuffer;
}

char *craftDrNextSTR KITTENS_CMD_ARGS
{
	struct context *context = instance -> extensions_context[ instance -> current_extension ];
	unsigned int current_dir_context;

printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	if (( ! context ) || (context -> used_dir_contexts == 0))
	{
		api.setError(22, tokenBuffer);
		return tokenBuffer;
	}

	current_dir_context = context -> used_dir_contexts - 1;

	printf("current_dir_context %08x\n",context -> dir_context[ current_dir_context ]);
	printf("examineData %08x" , context -> examineData[ current_dir_context ]);

	if ( ! context -> dir_context[ current_dir_context ] )  
	{
		api.setError(22, tokenBuffer);
		return tokenBuffer;
	}

	if ((context -> examineData[ current_dir_context ] = ExamineDir( context -> dir_context[ current_dir_context ] ))) 
	{
		setStackStr( instance, toAmosString_char( context -> examineData[ current_dir_context ]->Name, 0 ));
	}
	else	// no data;
	{
		ReleaseDirContext(context -> dir_context[ current_dir_context ]);
		context -> dir_context[ current_dir_context ] = NULL;
		context -> used_dir_contexts --;
		setStackStr( instance, toAmosString("",0));
	}
	
	return tokenBuffer;
}

char *craftDrCommentSTR KITTENS_CMD_ARGS
{
	struct context	*context = (struct context *) instance -> extensions_context[ instance -> current_extension ];
	STRPTR	Comment;

	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	if (context -> used_dir_contexts==0)
	{
		api.setError(22, tokenBuffer);
		return tokenBuffer;
	}

	Comment = context -> examineData[ context -> used_dir_contexts - 1 ] -> Comment;
	setStackStr( instance, toAmosString( Comment, strlen(Comment) ) );
	return tokenBuffer;
}

char *craftDrProtect KITTENS_CMD_ARGS
{
	struct context	*context = (struct context *) instance -> extensions_context[ instance -> current_extension ];
	uint32		Protection;

	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	if (context -> used_dir_contexts==0)
	{
		api.setError(22, tokenBuffer);
		return tokenBuffer;
	}

	Protection = context -> examineData[ context -> used_dir_contexts - 1 ] -> Protection;
	setStackNum( instance, Protection);
	return tokenBuffer;
}

char *craftDrLength KITTENS_CMD_ARGS
{
	struct context *context = (struct context *) instance -> extensions_context[ instance -> current_extension ];
	int64            FileSize;

	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	if (context -> used_dir_contexts==0)
	{
		api.setError(22, tokenBuffer);
		return tokenBuffer;
	}

	FileSize = context -> examineData[ context -> used_dir_contexts - 1 ] -> FileSize;

	if (FileSize>INT_MAX)
	{
		setStackDecimal( instance, (double) FileSize );
	}
	else
	{
		setStackNum( instance, (int) FileSize);
		printf("fileSize %lld\n",FileSize);
	}

	return tokenBuffer;
}

char *craftDrType KITTENS_CMD_ARGS
{
	struct context *context = (struct context *) instance -> extensions_context[ instance -> current_extension ];
	uint32	Type;

	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	if (context -> used_dir_contexts==0)
	{
		api.setError(22, tokenBuffer);
		return tokenBuffer;
	}

	Type = context -> examineData[ context -> used_dir_contexts - 1 ] -> Type;
	setStackNum( instance, Type);
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
	struct context *context = instance -> extensions_context[ instance -> current_extension ];
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	if (context -> used_dir_contexts)
	{
		int current_dir_context = context -> used_dir_contexts - 1;

		ReleaseDirContext(context -> dir_context[ current_dir_context ]);
		context -> dir_context[ current_dir_context ] = NULL;
		context -> used_dir_contexts --;
	}

	return tokenBuffer;
}

char *craftDiscError KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	api.setError(22, tokenBuffer);
	return tokenBuffer;
}

char *_craftSetRed( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	printf("args: %d\n",args);

	if (args !=2)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}
	else
	{
		struct retroScreen *screen = instance -> screens[ instance -> current_screen ];

		if (screen)
		{
			struct retroRGB *pal;
			int32 num = getStackNum( instance,__stack-1);
			int32 v = getStackNum( instance,__stack );

			pal = screen->orgPalette + num;
			if (v&0x100) {
				pal -> r = v & 0xFF;
			} else {
				pal -> r = v << 4 | v;
			}
			screen->rowPalette[num] = *pal;
		}
		else api.setError(22, data -> tokenBuffer);
	}

	popStack( instance, instance_stack - data->stack );
	return NULL;
}

char *craftSetRed KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _craftSetRed, tokenBuffer );
	return tokenBuffer;
}

char *_craftPalRed( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	uint32 v =0;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	printf("args: %d\n",args);

	if (args !=1)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}
	else
	{
		struct retroScreen *screen = instance -> screens[ instance -> current_screen ];

		if (screen)
		{
			int32 num = getStackNum( instance,__stack);
			v = screen->orgPalette[num].r >> 4;
		}
		else api.setError(22, data -> tokenBuffer);
	}
	setStackNum( instance, v );

	return NULL;
}

char *craftPalRed KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftPalRed, tokenBuffer );
	return tokenBuffer;
}

char *_craftSetGreen( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	if (args !=2)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}
	else
	{
		struct retroScreen *screen = instance -> screens[ instance -> current_screen ];

		if (screen)
		{
			struct retroRGB *pal;
			int32 num = getStackNum( instance,__stack-1);
			int32 v = getStackNum( instance,__stack );

			pal = screen->orgPalette + num;
			if (v&0x100) {
				pal -> g = v & 0xFF;
			} else {
				pal -> g = v << 4 | v;
			}
			screen->rowPalette[num] = *pal;
		}
		else api.setError(22, data -> tokenBuffer);
	}

	popStack( instance, instance_stack - data->stack );
	return NULL;
}

char *craftSetGreen KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _craftSetGreen, tokenBuffer );
	return tokenBuffer;
}

char *_craftPalGreen( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	uint32 v =0;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	printf("args: %d\n",args);

	if (args !=1)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}
	else
	{
		struct retroScreen *screen = instance -> screens[ instance -> current_screen ];

		if (screen)
		{
			int32 num = getStackNum( instance,__stack);
			v = screen->orgPalette[num].g >> 4;
		}
		else api.setError(22, data -> tokenBuffer);
	}
	setStackNum( instance, v );

	return NULL;
}

char *craftPalGreen KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftPalGreen, tokenBuffer );
	return tokenBuffer;
}

char *_craftSetBlue( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	if (args !=2)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}
	else
	{
		struct retroScreen *screen = instance -> screens[ instance -> current_screen ];

		if (screen)
		{
			struct retroRGB *pal;
			int32 num = getStackNum( instance,__stack-1);
			int32 v = getStackNum( instance,__stack );

			pal = screen->orgPalette + num;
			if (v&0x100) {
				pal -> b = v & 0xFF;
			} else {
				pal -> b = v << 4 | v;
			}
			screen->rowPalette[num] = *pal;
		}
		else api.setError(22, data -> tokenBuffer);
	}

	popStack( instance, instance_stack - data->stack );
	return NULL;
}

char *craftSetBlue KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _craftSetBlue, tokenBuffer );
	return tokenBuffer;
}

char *_craftPalBlue( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	uint32 v =0;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	printf("args: %d\n",args);

	if (args !=1)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}
	else
	{
		struct retroScreen *screen = instance -> screens[ instance -> current_screen ];

		if (screen)
		{
			int32 num = getStackNum( instance,__stack);
			v = screen->orgPalette[num].b >> 4;
		}
		else api.setError(22, data -> tokenBuffer);
	}
	setStackNum( instance, v );

	return NULL;
}

char *craftPalBlue KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftPalBlue, tokenBuffer );
	return tokenBuffer;
}

char *_craftPalSpread( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	if (args !=2)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}
	else
	{
		struct retroScreen *screen = instance -> screens[ instance -> current_screen ];

		if (screen)
		{
			struct retroRGB *oc,*c1,*c2;
			int32 color1 = getStackNum( instance,__stack-1);
			int32 color2 = getStackNum( instance,__stack );
			int dr,dg,db,d,n;

			if (color1>color2)
			{
				int t;
				t = color2; color2 = color1; color1 = t;
			}

			c1 = screen->orgPalette + color1;
			c2 = screen->orgPalette + color2;

			d = color2-color1;

			dr = c2 -> r - c1 -> r;
			dg = c2 -> g - c1 -> g;
			db = c2 -> b - c1 -> b;

			oc = c1;
			c1++;
			for (n=1;n<d;n++)
			{
				c1 -> r = oc -> r + (n*dr/d);
				c1 -> g = oc -> g + (n*dg/d);
				c1 -> b = oc -> b + (n*db/d);
				screen->rowPalette[color1+n] = *c1;
				c1++;
			}


		}
		else api.setError(22, data -> tokenBuffer);
	}

	popStack( instance, instance_stack - data->stack );
	return NULL;
}

char *craftPalSpread KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _craftPalSpread, tokenBuffer );
	return tokenBuffer;
}

char *_craftPalSwap( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	if (args !=2)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}
	else
	{
		struct retroScreen *screen = instance -> screens[ instance -> current_screen ];

		if (screen)
		{
			struct retroRGB tmp;

			int32 color1 = getStackNum( instance,__stack-1);
			int32 color2 = getStackNum( instance,__stack );

			tmp = screen->orgPalette[color2];
			screen->orgPalette[color2] = screen->orgPalette[color1];
			screen->rowPalette[color2] = screen->orgPalette[color1];
			screen->orgPalette[color1] = tmp;
			screen->rowPalette[color1] = tmp;
		}
		else api.setError(22, data -> tokenBuffer);
	}

	popStack( instance, instance_stack - data->stack );
	return NULL;
}

char *craftPalSwap KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _craftPalSwap, tokenBuffer );
	return tokenBuffer;
}

char *_craftPalCopy( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	if (args !=2)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}
	else
	{
		struct retroScreen *screen = instance -> screens[ instance -> current_screen ];

		if (screen)
		{
			int32 color1 = getStackNum( instance,__stack-1);
			int32 color2 = getStackNum( instance,__stack );

			screen->orgPalette[color2] = screen->orgPalette[color1];
			screen->rowPalette[color2] = screen->orgPalette[color1];

		}
		else api.setError(22, data -> tokenBuffer);
	}

	popStack( instance, instance_stack - data->stack );
	return NULL;
}

char *craftPalCopy KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _craftPalCopy, tokenBuffer );
	return tokenBuffer;
}

char *_craftReserveAsPalette(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	int bankId,pals,mask;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	api.dumpStack();

	switch (args)
	{
		case 1:
			bankId = getStackNum( instance,__stack );
			pals = 1;
			mask = 0;
			break;

		case 2:
			bankId = getStackNum( instance,__stack -1);
			pals = getStackNum( instance,__stack );
			mask = 0;
			break;

		case 3:
			bankId = getStackNum( instance,__stack -2);
			pals = getStackNum( instance,__stack -1);
			mask = getStackNum( instance,__stack );
			break;

		default:

			popStack( instance, instance_stack - data->stack );
			api.setError(22, data -> tokenBuffer);
			return NULL;
	}

	api.reserveAs( 1, bankId , 256 * 4 * pals, "Palettes", NULL );

	popStack( instance, instance_stack - data->stack );
	return NULL;
}

char *craftReserveAsPalette KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _craftReserveAsPalette, tokenBuffer );
	return tokenBuffer;
}

char *_craftPalCount(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	int bankId = -1;
	int _size = 0;
	struct kittyBank *bank;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	api.dumpStack();

	switch (args)
	{
		case 1:
			bankId = getStackNum( instance,__stack );
			break;

		default:

			popStack( instance, instance_stack - data->stack );
			api.setError(22, data -> tokenBuffer);
			return NULL;
	}

	if (bankId>-1)
	{
		bank = api.findBank( bankId );
		if (bank)
		{
			_size = bank -> length / (256*4);
		}
	}

	setStackNum( instance, _size );

	return NULL;
}

char *craftPalCount KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftPalCount, tokenBuffer );
	return tokenBuffer;
}

char *_craftPalToBank(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	int bankId,palId;
	struct kittyBank *bank;
	struct retroScreen *screen;
	unsigned char *pal ;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	api.dumpStack();

	switch (args)
	{
		case 1:
			bankId = getStackNum( instance,__stack );
			palId = 0;
			break;

		case 2:
			bankId = getStackNum( instance,__stack -1);
			palId = getStackNum( instance,__stack ) -1;
			break;

		default:
			popStack( instance, instance_stack - data->stack );
			api.setError(22, data -> tokenBuffer);
			return NULL;
	}

	pal = NULL;
	bank = api.findBank( bankId );
	screen = instance -> screens[ instance -> current_screen ];

	if ((bank)&&(screen)&&(palId>-1))
	{
		int _size = bank -> length / (256*4);
		if (palId < _size) 
			pal = (unsigned char *) bank -> start + (palId * 256 * 4);
	}

	if (pal)
	{
		int n;
		struct retroRGB *oPal = screen->orgPalette;

		for (n=0;n<256;n++)
		{
			*pal++=0xFF;
			*pal++=oPal -> r;
			*pal++=oPal -> g;
			*pal++=oPal -> b;
			oPal ++;
		}
	}
	else api.setError(22, data -> tokenBuffer);

	popStack( instance, instance_stack - data->stack );
	return NULL;
}

char *craftPalToBank KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _craftPalToBank, tokenBuffer );
	return tokenBuffer;
}

char *_craftPalFromBank(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	int bankId,palId;
	struct kittyBank *bank;
	struct retroScreen *screen;
	unsigned char *pal ;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	switch (args)
	{
		case 1:
			bankId = getStackNum( instance,__stack );
			palId = 0;
			break;

		case 2:
			bankId = getStackNum( instance,__stack -1);
			palId = getStackNum( instance,__stack ) -1;
			break;

		default:
			popStack( instance, instance_stack - data->stack );
			api.setError(22, data -> tokenBuffer);
			return NULL;
	}

	pal = NULL;
	bank = api.findBank( bankId );
	screen = instance -> screens[ instance -> current_screen ];

	if ((bank)&&(screen)&&(palId>-1))
	{
		int _size = bank -> length / (256*4);
		if (palId < _size) 
			pal = (unsigned char *) bank -> start + (palId * 256 * 4);
	}

	if (pal)
	{
		int n;
		struct retroRGB *oPal = screen->orgPalette;

		for (n=0;n<256;n++)
		{
			if (*pal++)
			{
				oPal -> r = *pal++;
				oPal -> g = *pal++;
				oPal -> b = *pal++;
			}
			else pal+=3;

			oPal ++;
		}

		memcpy( screen->rowPalette , screen->orgPalette , sizeof(struct retroRGB ) * 256 );
	}
	else api.setError(22, data -> tokenBuffer);

	popStack( instance, instance_stack - data->stack );
	return NULL;
}

char *craftPalFromBank KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _craftPalFromBank, tokenBuffer );
	return tokenBuffer;
}


char *_craftPalSwapBank(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	int bankNr=0,paletteNr=0,mask=0;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);


	printf("args: %d\n",args);

	switch (args)
	{
		case 1:
			bankNr = getStackNum( instance,__stack );
			break;

		case 2:
			bankNr = getStackNum( instance,__stack -1 );
			paletteNr = getStackNum( instance,__stack )-1;
			popStack( instance, instance_stack - data->stack );
			break;

		case 3:
			bankNr = getStackNum( instance,__stack -2 );
			paletteNr = getStackNum( instance,__stack -1)-1;
			mask = getStackNum( instance,__stack );
			popStack( instance, instance_stack - data->stack );
			break;

		default:
			popStack( instance, instance_stack - data->stack );
			api.setError(22, data -> tokenBuffer);
			return NULL;
	}

	{
		unsigned char *pal;
		struct retroRGB *oPal;
		struct kittyBank *bank;
		struct retroScreen *screen;
		register short t;
		int n;

		bank = api.findBank( bankNr );
		screen = instance -> screens[ instance -> current_screen ];

		printf("bank: %08x\n",bank);
		printf("screen: %08x\n",screen);

		if ((bank)&&(screen)&&(paletteNr>-1))
		{
			oPal = screen->orgPalette;
			pal = (unsigned char *) bank -> start + (paletteNr * 4 * 256) ;

			for (n=0;n<256;n++)
			{
				if (*pal++)
				{
					t = *pal;
					*pal++=oPal -> r;
					oPal -> r = t;

					t = *pal;
					*pal++=oPal -> g;
					oPal -> g = t;

					t = *pal;
					*pal++=oPal -> b;
					oPal -> b = t;
				}
				else pal+=3;

				oPal ++;
			}

			memcpy( screen->rowPalette , screen->orgPalette , sizeof(struct retroRGB ) * 256 );
		}
		else api.setError(22, data -> tokenBuffer);
	}

	return NULL;
}

char *craftPalSwapBank KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _craftPalSwapBank, tokenBuffer );
	return tokenBuffer;
}

char *_craftSetBankColour(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	int bankNr=0,paletteNr=0,colorNr=0,value=0;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	switch (args)
	{
		case 4:
			bankNr = getStackNum( instance,__stack -3 );
			paletteNr = getStackNum( instance,__stack -2)-1;
			colorNr = getStackNum( instance,__stack -1);
			value = getStackNum( instance,__stack );
			popStack( instance, instance_stack - data->stack );
			break;

		default:
			popStack( instance, instance_stack - data->stack );
			api.setError(22, data -> tokenBuffer);
			return NULL;
	}

	{

		struct kittyBank *bank;

		bank = api.findBank( bankNr );

		if ((bank)&&(paletteNr>-1))
		{
			if (value & 0xFF000000)
			{
				unsigned int *pal = (unsigned int *) (bank -> start + (paletteNr * 4 * 256) + (4 * colorNr));
				// this is for bigendien
				*pal = value;
			}
			else
			{
				unsigned char *pal = (unsigned char *) (bank -> start + (paletteNr * 4 * 256) + (4 * colorNr));

				printf("paletteNr %d colorNr %d value %03x\n",paletteNr, colorNr,value);
				printf("%ld\n", (char *) pal - bank -> start );

				*pal++ = 0xFF;
				*pal++= ((value & 0xF00) >> 8) * 0x11;
				*pal++= ((value & 0x0F0) >> 4) * 0x11;
				*pal++= (value & 0x00F) * 0x11;
			}
		}
		else api.setError(22, data -> tokenBuffer);
	}

	return NULL;
}

char *craftSetBankColour KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _craftSetBankColour, tokenBuffer );
	return tokenBuffer;
}

char *_craftBankColour(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	int bankNr=0,paletteNr=0,colorNr=0;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	printf("args: %d\n",args);

	switch (args)
	{
		case 3:
			bankNr = getStackNum( instance,__stack -2 );
			paletteNr = getStackNum( instance,__stack -1)-1;
			colorNr = getStackNum( instance,__stack );
			popStack( instance, instance_stack - data->stack );
			break;

		default:
			popStack( instance, instance_stack - data->stack );
			api.setError(22, data -> tokenBuffer);
			return NULL;
	}

	{
		unsigned int *pal;
		struct kittyBank *bank;

		bank = api.findBank( bankNr );

		if ((bank)&&(paletteNr>-1))
		{
			pal = (unsigned int *) (bank -> start + (paletteNr * 4 * 256) + (4 * colorNr));
			// convert to OCS / ECS
			setStackNum( instance, 
				(( *pal & 0x00F00000 ) >>12) | 
				(( *pal & 0x0000F000 ) >>8) |
				(( *pal & 0x000000F0 ) >> 4)  );
		}
		else api.setError(22, data -> tokenBuffer);
	}

	return NULL;
}

char *craftBankColour KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftBankColour, tokenBuffer );
	return tokenBuffer;
}

char *_craftDelBankColour(  struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	int bankNr=0,paletteNr=0,colorNr=0;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	printf("args: %d\n",args);

	switch (args)
	{
		case 3:
			bankNr = getStackNum( instance,__stack -2 );
			paletteNr = getStackNum( instance,__stack -1)-1;
			colorNr = getStackNum( instance,__stack );
			popStack( instance, instance_stack - data->stack );
			break;

		default:
			popStack( instance, instance_stack - data->stack );
			api.setError(22, data -> tokenBuffer);
			return NULL;
	}

	{
		unsigned char *pal;
		struct kittyBank *bank;

		bank = api.findBank( bankNr );

		if ((bank)&&(paletteNr>-1))
		{
			pal = (unsigned char *) bank -> start + (paletteNr * 4 * 256) + (4 * colorNr);

			*pal++ =0x00;	// deactivate colour
			*pal++= 0xFF;
			*pal++= 0xFF;
			*pal++= 0xFF;
		}
		else api.setError(22, data -> tokenBuffer);
	}

	return NULL;
}

char *craftDelBankColour KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdNormal( _craftDelBankColour, tokenBuffer );
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

	struct retroScreen *screen = instance -> screens[ instance -> current_screen ];

	if (screen)
	{
		setStackNum( instance, screen -> ink0 );
	}
	else api.setError(22, tokenBuffer);

	return tokenBuffer;
}

char *craftGrBack KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	struct retroScreen *screen = instance -> screens[ instance -> current_screen ];

	if (screen)
	{
		setStackNum( instance, screen -> ink1 );
	}
	else api.setError(22, tokenBuffer);

	return tokenBuffer;
}

char *craftGrBorder KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	struct retroScreen *screen = instance -> screens[ instance -> current_screen ];

	if (screen)
	{
		setStackNum( instance, screen -> ink2 );
	}
	else api.setError(22, tokenBuffer);

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

	setStackNum( instance, VERSION * 10 + REVISION );

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

char *_craftB_swap( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	uint32 ret;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	if (args !=1)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}

	ret = (uint32) getStackNum( instance,__stack );
	setStackNum( instance, 
		((ret & 0x0F) << 4) | 
		((ret & 0xF0) >> 4)  );

	return NULL;
}

char *craftB_swap KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftB_swap, tokenBuffer );
	return tokenBuffer;
}

char *_craftW_swap( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	uint32 ret;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	if (args !=1)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}

	ret = (uint32) getStackNum( instance,__stack );
	setStackNum( instance, 
		((ret & 0x00FF) << 8) | 
		((ret & 0xFF00) >> 8)  );

	return NULL;
}

char *craftW_swap KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftW_swap, tokenBuffer );
	return tokenBuffer;
}


char *_craftL_swap( struct glueCommands *data, int nextToken )
{
	struct KittyInstance *instance = data -> instance;
	int args = instance_stack - data->stack +1;
	uint32 ret;

	proc_names_printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);

	if (args !=1)
	{
		popStack( instance, instance_stack - data->stack );
		api.setError(22, data -> tokenBuffer);
		return NULL;
	}

	ret = (uint32) getStackNum( instance,__stack );
	setStackNum( instance, ((ret & 0x0000FFFF) << 16) | ((ret & 0xFFFF0000 ) >> 16) );
	return NULL;
}

char *craftL_swap KITTENS_CMD_ARGS
{
	printf("%s:%s:%d\n",__FILE__,__FUNCTION__,__LINE__);
	stackCmdParm( _craftL_swap, tokenBuffer );
	return tokenBuffer;
}




