#ifndef V3D_VSERVICEPROXY_H
#define V3D_VSERVICEPROXY_H
//------------------------------------------------------------------------


// TODO: find a better way to do this - abstract base class?
// include correct VServiceProxy implementation
#ifdef V3D_WIN32
#include "win32/VServiceProxyWin32.h"
#else // V3D_WIN32
#include "linux/VServiceProxyLinux.h"
#endif // V3D_WIN32


//------------------------------------------------------------------------
#endif // V3D_VSERVICEPROXY_H
