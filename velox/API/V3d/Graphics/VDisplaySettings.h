#ifndef V3D_VDISPLAYSETTINGS_H
#define V3D_VDISPLAYSETTINGS_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VTypes.h>
#include <string>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * This class holds a complete set of display varables
 */

class VDisplaySettings  
{
public:

	//TODO: problematisch, klasse kann nur von gfx service selbst gesetzt werden,
	// sonst gibts linker fehler (sheijk)
	VDisplaySettings();
	void Assign(VDisplaySettings* in_pInfo);

	vbool m_bFullscreen;
	vuint m_iWidth;
	vuint m_iHeight;
	vuint m_iBitsPerPixel;
	vuint m_iAccumulationBuffer;
	vuint m_iDepthBits;
	vuint m_iStencilBits;
	std::string m_sAPIType;
	
	vfloat32 m_fFieldOfView;
	vfloat32 m_fNearClippingPlane;
	vfloat32 m_fFarClippingPlane;

	vfloat32 m_fBackgroundRed;
	vfloat32 m_fBackgroundGreen;
	vfloat32 m_fBackgroundBlue;
	vfloat32 m_fBackgroundAlpha;

	
};
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif V3D_VDISPLAYSETTINGS_H
