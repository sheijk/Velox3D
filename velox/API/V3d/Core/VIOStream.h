//TODO: correct file guard
#ifndef V3D_VIOSTREAM_H
#define V3D_VIOSTREAM_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Utils/IVStringStream.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

/** a std::cout style output stream. outputs to the velox console */
extern utils::IVStringStream& vout;

/** equivalent to std::endl */
extern const char* vendl;

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VIOSTREAM_H
