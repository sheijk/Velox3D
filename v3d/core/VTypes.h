#ifndef V3D_VTYPES_H
#define V3D_VTYPES_H

typedef int vint;
typedef __int8 vint8;
typedef __int16 vint16;
typedef __int32 vint32;
typedef __int64 vint64;		//support by other compilers than VC??
typedef unsigned __int8 vuint8;
typedef unsigned __int16 vuint16;
typedef unsigned __int32 vuint32;
typedef unsigned __int64 vuint64;
typedef unsigned int vuint;
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


enum VRESULT
{
	VOK = 0,
	VCANCEL,
	VERROR_FILE_NOTFOUND,
	
	VERROR_INPUT_NOPARAM,				//no param was given
	VERROR_INPUT_DXOBJECT,				//creation failed
	VERROR_INPUT_KEYBOARDDEVICE,		//keyboard creation failed
	VERROR_INPUT_KEYBOARDFORMAT,		//keyboard data format failed
	VERROR_INPUT_KEYBOARDCOOPERATIVE,	//keyboard cooperative level not set
	VERROR_INPUT_KEYBOARDEVENT,			//keyboard event notigfication failed
	VERROR_INPUT_KEYBOARDPROPERTY,		//keyboard property setting faild
	VERROR_INPUT_KEYBOARDACQUIRE,       //keyboard acquiring failed
	VERROR_INPUT_MOUSEDEVICE,
	VERROR_INPUT_MOUSEFORMAT,
	VERROR_INPUT_MOUSECOOPERATIVE,
	VERROR_INPUT_MOUSEEVENT,
	VERROR_INPUT_MOUSEPROPERTY,
	VERROR_INPUT_MOUSEACQUIRE,
	VERROR_INPUT_MOUSEWHEELSTATE,
	
	VERROR_WINDOW_REGISTRATION,
	VERROR_WINDOW_DESTRUCTION,
	VERROR_WINDOW_UNREGISTRATION,
	
	VERROR_GRAPHICS_OGLDEVICECONTEXT,
	VERROR_GRAPHICS_OGLSUITABLEPIXELFORMAT,
	VERROR_GRAPHICS_OGLREQUESTPIXELFORMAT,
	VERROR_GRAPHICS_OGLCREATECONTEXT,
    VERROR_GRAPHICS_OGLACTIVATINGCONTEXT,
	VERROR_GRAPHICS_MAKECURRENT,
	VERROR_GRAPHICS_OGLRELEASECONTEXT,
	VERROR_GRAPHICS_OGLDELETECONTEXT,
	VERROR_GRAPHICS_DEVICENOTSUPPORTED,
	VERROR_GRAPHICS_DEVICECASTFAILED,
	
	VERROR_IMAGE_BADCOLORMAP,
	VERROR_IMAGE_BADTYPE,
	VERROR_IMAGE_BADBPP,
	VERROR_IMAGE_DECODE,

	VERROR_MEMORY_NOMEM,
	
	VERROR_LIST_FULL,

	VERROR_VFS_READFAILED,		// could not read everything from source
	VERROR_VFS_WRITEFAILED,		// could not write everything to dest
	VERROR_VFS_NOFILEOPENED 	

	 	
	
};

#define V3D_MULTITHREADING_SUPPORT

#endif