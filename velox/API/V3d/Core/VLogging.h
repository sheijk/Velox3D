#ifndef V3D_VLOGGING_H
#define V3D_VLOGGING_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

void SendDebugMessage(const char* in_pcMessage);

/** send a debug message */
#ifdef V3D_DEBUG
#define V3D_DEBUGMSG(x) SendDebugMessage(x);
#else
#define V3D_DEBUGMSG(x) void(0);
#endif

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VLOGGING_H
