#ifndef V3D_GRAPHICS_EXCEPTIONS_2004_08_31_H
#define V3D_GRAPHICS_EXCEPTIONS_2004_08_31_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

V3D_DECLARE_EXCEPTION(VGraphicException, VException);
V3D_DECLARE_EXCEPTION(VCreationException, VGraphicException);
V3D_DECLARE_EXCEPTION(VInvalidModeException, VCreationException);

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_GRAPHICS_EXCEPTIONS_2004_08_31_H
