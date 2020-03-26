#ifndef PROTO_KITTYCRAFT_H
#define PROTO_KITTYCRAFT_H

/*
**	$Id$
**
**	Prototype/inline/pragma header file combo
**
**	Copyright (c) 2010 Hyperion Entertainment CVBA.
**	All Rights Reserved.
*/

#ifndef EXEC_TYPES_H
#include <exec/types.h>
#endif
#ifndef LIBRARIES_KITTYCRAFT_H
#include <libraries/kittycraft.h>
#endif

/****************************************************************************/

#ifndef __NOLIBBASE__
 #ifndef __USE_BASETYPE__
  extern struct Library * kittyCraftBase;
 #else
  extern struct Library * kittyCraftBase;
 #endif /* __USE_BASETYPE__ */
#endif /* __NOLIBBASE__ */

/****************************************************************************/

#ifdef __amigaos4__
 #include <interfaces/kittyCraft.h>
 #ifdef __USE_INLINE__
  #include <inline4/kittyCraft.h>
 #endif /* __USE_INLINE__ */
 #ifndef CLIB_KITTYCRAFT_PROTOS_H
  #define CLIB_KITTYCRAFT_PROTOS_H 1
 #endif /* CLIB_KITTYCRAFT_PROTOS_H */
 #ifndef __NOGLOBALIFACE__
  extern struct kittyCraftIFace *IkittyCraft;
 #endif /* __NOGLOBALIFACE__ */
#else /* __amigaos4__ */
 #ifndef CLIB_KITTYCRAFT_PROTOS_H
  #include <clib/kittyCraft_protos.h>
 #endif /* CLIB_KITTYCRAFT_PROTOS_H */
 #if defined(__GNUC__)
  #ifndef __PPC__
   #include <inline/kittyCraft.h>
  #else /* __PPC__ */
   #include <ppcinline/kittyCraft.h>
  #endif /* __PPC__ */
 #elif defined(__VBCC__)
  #ifndef __PPC__
   #include <inline/kittyCraft_protos.h>
  #endif /* __PPC__ */
 #else /* __GNUC__ */
  #include <pragmas/kittyCraft_pragmas.h>
 #endif /* __GNUC__ */
#endif /* __amigaos4__ */

/****************************************************************************/

#endif /* PROTO_KITTYCRAFT_H */
