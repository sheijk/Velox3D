#ifndef V3D_VOPENGLUTILS_H
#define V3D_VOPENGLUTILS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/VMeshDescription.h>

#include <windows.h>
#include <gl/GL.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

GLint GetGeometryMode(VMeshDescription::GeometryType in_eType);

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VOPENGLUTILS_H
