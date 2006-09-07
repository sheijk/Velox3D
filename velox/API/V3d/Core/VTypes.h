/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VTYPES_H
#define V3D_VTYPES_H
//-----------------------------------------------------------------------------

#ifndef _MSC_VER
#include <stdint.h>
#endif

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

/**
 * The velox types. Use these types instead of the standard ones
 */
#ifdef _MSC_VER
typedef int vint;
typedef unsigned int vuint;
typedef __int8 vint8;
typedef unsigned __int8 vuint8;
typedef __int16 vint16;
typedef unsigned __int16 vuint16;
typedef __int32 vint32;
typedef unsigned __int32 vuint32;
typedef __int64 vint64;
typedef unsigned __int64 vuint64;
typedef short vshort;
typedef unsigned short vushort;
typedef unsigned short vword; // added by ins
typedef char vchar;
typedef unsigned char vuchar;
typedef unsigned char vbyte;
typedef long vlong;
typedef unsigned long vulong;
typedef float vfloat32;
typedef double vfloat64;
typedef bool vbool;
#else
typedef int vint;
typedef unsigned int vuint;
typedef int8_t vint8;
typedef uint8_t vuint8;
typedef int16_t vint16;
typedef uint16_t vuint16;
typedef int32_t vint32;
typedef uint32_t vuint32;
typedef int64_t vint64;
typedef uint64_t vuint64;
typedef short vshort;
typedef unsigned short vushort;
typedef unsigned short vword;
typedef char vchar;
typedef unsigned char vuchar;
typedef unsigned char vbyte;
typedef long vlong;
typedef unsigned long vulong;
typedef float vfloat32;
typedef double vfloat64;
typedef bool vbool;
#endif

/**
 * Conventions for VStringParam and VStringRetVal:
 * const char* c = param [VStringParam param] is valid
 * VStringRetVal v = c [const char* c] is valid
 *
 * thus, VStringParam and VStringRetVal can be used like const char*
 */

/** use this when a string parameter is needed */
typedef const vchar* VStringParam;

class VString;

/** use this when returning a string */
typedef VString VStringRetVal;

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTYPES_H

