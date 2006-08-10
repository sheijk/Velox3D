#ifndef V3D_VDAYLIGHTSKYCOLORIZER_2004_06_13_H
#define V3D_VDAYLIGHTSKYCOLORIZER_2004_06_13_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3dLib/Graphics/Renderers/Sky/IVSkyColorizer.h>
#include <v3dLib/Utils/ColorConversion.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // aaaaaaaaaaaaaaaaaaaaaaaaaarrrrrrrrrrrrrgggggggghhh

class VDaylightSkyColorizer : public IVSkyColorizer
{
	vfloat32 m_fSunTheta;
	vfloat32 m_fSunPhi;
	vfloat32 m_fTurbidity;
	// precalculatet distribution coefficients
	vfloat32 m_DCY[5];
	vfloat32 m_DCx[5];
	vfloat32 m_DCy[5];

	utils::YxyColor m_ZenithColor;
	
	void CalculateZenith();
	utils::YxyColor CalculateDistribution(vfloat32 in_fTheta, vfloat32 in_fGamma);
	vfloat32 PerezFunction( vfloat32 in_fA,
							vfloat32 in_fB,
							vfloat32 in_fC,
							vfloat32 in_fD,
							vfloat32 in_fE,
                            vfloat32 in_fTheta,
							vfloat32 in_fGamma );
public:
	VDaylightSkyColorizer(vfloat32 in_fSunTheta, vfloat32 in_fSunPhi, vfloat32 in_fTurbidity);
	~VDaylightSkyColorizer();

	VColor4f GetColor(vfloat32 in_fTheta, vfloat32 in_fPhi);
	void SetSunPosition(vfloat32 in_fSunTheta, vfloat32 in_fSunPhi);
	void SetTurbidity(vfloat32 in_fTurbidity);
};
//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
#endif //V3D_IVSKYCOLORIZER_2004_06_13_H
