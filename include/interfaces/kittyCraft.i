#ifndef KITTYCRAFT_INTERFACE_DEF_H
#define KITTYCRAFT_INTERFACE_DEF_H
/*
** This file is machine generated from idltool
** Do not edit
*/ 

#include <exec/types.i>
#include <exec/exec.i>
#include <exec/interfaces.i>

STRUCTURE kittyCraftIFace, InterfaceData_SIZE
	    FPTR IkittyCraft_Obtain
	    FPTR IkittyCraft_Release
	    FPTR IkittyCraft_Expunge
	    FPTR IkittyCraft_Clone
	    FPTR IkittyCraft_makeLookupTable
	    FPTR IkittyCraft_FreeLookupTable
	    FPTR IkittyCraft_makeContext
	    FPTR IkittyCraft_FreeContext
	LABEL kittyCraftIFace_SIZE

#endif
