/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VLOGGING_H
#define V3D_VLOGGING_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

/** do not use this directly, use V3D_DEBUGMSG instead */
void SendDebugMessage(VStringParam in_pcMessage);

/**
 *TODO: this might not work..
 * send a debug message, only in debug builds
 */
#ifdef V3D_DEBUG
#define V3D_DEBUGMSG(x) SendDebugMessage(x);
#else
#define V3D_DEBUGMSG(x) void(0);
#endif

#ifdef V3D_DEBUG
#define V3D_LOG(msg) vout << "[" << __FILE__ << ":" << __LINE__ << "] " << msg;
#else
#define V3D_LOG(msg)
#endif

#define V3D_LOGLN(msg) V3D_LOG(msg << vendl)

/** 
 * send this message only one time (in some cases two times if a file is linked
 * into several DLLs 
 */
#define V3D_LOGONCE(eventName)\
{\
	static vbool logged_##eventName = false;\
	if( ! logged_##eventName ) {\
	V3D_LOG(#eventName);\
	logged_##eventName = true;\
	}\
}

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VLOGGING_H

