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
 * This class holds a complete set of display variables
 *
 * @author insane
 */
class VDisplaySettings  
{
public:

	//TODO: problematisch, klasse kann nur von gfx service selbst gesetzt werden,
	// sonst gibts linker fehler (sheijk)
	inline VDisplaySettings();

	vbool m_bFullscreen;
	vuint m_iWidth;
	vuint m_iHeight;
	vuint m_iWinCoordX;
	vuint m_iWinCoordY;
	vuint m_iBitsPerPixel;
	vuint m_iAccumulationBuffer;
	vuint m_iDepthBits;
	vuint m_iStencilBits;
	std::string m_sAPIType;
	
	vfloat32 m_fFieldOfView;
	vfloat32 m_fNearClippingPlane;
	vfloat32 m_fFarClippingPlane;
	vfloat32 m_fClearDepth;

	vfloat32 m_fBackgroundRed;
	vfloat32 m_fBackgroundGreen;
	vfloat32 m_fBackgroundBlue;
	vfloat32 m_fBackgroundAlpha;

	
};

VDisplaySettings::VDisplaySettings()
{
	m_bFullscreen   = false;
	m_iWidth	    = 1200;
	m_iHeight	    = 1000;
	m_iWinCoordX    = 300;
	m_iWinCoordY    = 100;
	m_iBitsPerPixel = 16;
	m_iAccumulationBuffer = 0;
	m_iDepthBits = 16;
	m_iStencilBits = 0;
	m_fFieldOfView = 90;
	m_fNearClippingPlane = 1.0f;
	m_fFarClippingPlane = 900000.0f;
    m_fBackgroundRed = 0.235f;
	m_fBackgroundGreen = 0.39f;
	m_fBackgroundBlue = 0.627f;
	m_fBackgroundAlpha = 1.0f;
	m_sAPIType = "OpenGL";
	m_fClearDepth = 1.0f;
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif V3D_VDISPLAYSETTINGS_H
