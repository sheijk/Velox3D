#ifndef V3D_CONVERSIONS_2005_08_27_H
#define V3D_CONVERSIONS_2005_08_27_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Math/VVector.h>

#include <V3dLib/Graphics/Geometry/VColor4f.h>

//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

VVector4f ToVector4f(const VVector3f& in_Vec, vfloat32 in_fW);

VVector3f ToVector3f(const VColor4f& in_Color);
VVector4f ToVector4f(const VColor4f& in_Color);


//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
#endif // V3D_CONVERSIONS_2005_08_27_H

