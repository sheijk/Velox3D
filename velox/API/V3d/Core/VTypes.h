#ifndef V3D_VTYPES_H
#define V3D_VTYPES_H

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

/**
 * The velox types. Use these types instead of the standard ones
 */

typedef int vint;
typedef unsigned int vuint;
typedef __int8 vint8;
typedef unsigned __int8 vuint8;
typedef __int16 vint16;
typedef unsigned __int16 vuint16;
typedef __int32 vint32;
typedef unsigned __int32 vuint32;
typedef __int64 vint64;		//support by other compilers than VC?? borland: ok
typedef unsigned __int64 vuint64;
typedef short vshort;
typedef unsigned short vushort;
typedef char vchar;
typedef unsigned char vuchar;
typedef unsigned char vbyte;
typedef long vlong;
typedef unsigned long vulong;
typedef float vfloat32;
typedef double vfloat64;
typedef bool vbool;

//TODO: wozu wird das gebraucht? - sheijk
#define V3D_MULTITHREADING_SUPPORT

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTYPES_H