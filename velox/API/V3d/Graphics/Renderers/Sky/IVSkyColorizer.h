#ifndef V3D_IVSKYCOLORIZER_2004_06_13_H
#define V3D_IVSKYCOLORIZER_2004_06_13_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3dLib/Graphics.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
class IVSkyColorizer
{
public:
	IVSkyColorizer() {};
	virtual ~IVSkyColorizer() {};

	virtual VColor4f GetColor(vfloat32 in_fTheta, vfloat32 in_fPhi ) = 0;
};
//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
#endif //V3D_IVSKYCOLORIZER_2004_06_13_H
