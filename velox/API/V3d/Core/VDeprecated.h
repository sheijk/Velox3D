#ifndef V3D_VDEPRECATED_2005_07_18_H
#define V3D_VDEPRECATED_2005_07_18_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VBuild.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

#ifdef V3D_MSVC
#define V3D_DEPRECATED __declspec(deprecated)
#endif

#ifdef V3D_GCC
#define V3D_DEPRECATED __attribute__((deprecated))
#endif

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VDEPRECATED_2005_07_18_H
