#include <v3d/Graphics/VDisplaySettings.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

VDisplaySettings::VDisplaySettings()
{
	m_bFullscreen   = false;
	m_iWidth	    = 640;
	m_iHeight	    = 480;
	m_iBitsPerPixel = 16;
	m_iAccumulationBuffer = 0;
	m_iDepthBits = 16;
	m_iStencilBits = 0;
	m_fFieldOfView = 90;
	m_fNearClippingPlane = 1.0f;
	m_fFarClippingPlane = 1000.0f;
    m_fBackgroundRed = 0.235f;
	m_fBackgroundGreen = 0.39f;
	m_fBackgroundBlue = 0.627f;
	m_fBackgroundAlpha = 1.0f;
	m_sAPIType = "OpenGL";
	m_fClearDepth = 1.0f;
}

//TODO: ziemlich den gleichen code sollte der compiler fuer assignment op und copy c'tor
// generieren.. wozu diese fkt? (sheijk)
void VDisplaySettings::Assign(VDisplaySettings* in_pInfo)
{
	m_bFullscreen   = in_pInfo->m_bFullscreen;
	m_iWidth	    = in_pInfo->m_iWidth;
	m_iHeight	    = in_pInfo->m_iHeight;
	m_iBitsPerPixel = in_pInfo->m_iBitsPerPixel;
	m_iAccumulationBuffer = in_pInfo->m_iAccumulationBuffer;
	m_iDepthBits = in_pInfo->m_iDepthBits;
	m_iStencilBits = in_pInfo->m_iStencilBits;
	m_fFieldOfView = in_pInfo->m_fFieldOfView;
	m_fNearClippingPlane = in_pInfo->m_fNearClippingPlane;
	m_fFarClippingPlane = in_pInfo->m_fFarClippingPlane;
	m_fBackgroundRed = in_pInfo->m_fBackgroundRed;
	m_fBackgroundGreen = in_pInfo->m_fBackgroundGreen;
	m_fBackgroundBlue = in_pInfo->m_fBackgroundBlue;
	m_fBackgroundAlpha = in_pInfo->m_fBackgroundAlpha;
	m_sAPIType = in_pInfo->m_sAPIType;
	
}
//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------

