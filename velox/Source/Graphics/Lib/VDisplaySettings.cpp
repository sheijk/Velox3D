#include <V3d/Graphics/VDisplaySettings.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

VDisplaySettings::VDisplaySettings()
{
	m_bFullscreen   = false;
	m_nWidth	    = 800;
	m_nHeight	    = 600;
	m_nWinCoordX    = 300;
	m_nWinCoordY    = 10;
	m_nBitsPerPixel = 16;
	m_nAccumulationBuffer = 0;
	m_nDepthBits = 16;
	m_nStencilBits = 0;
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

void VDisplaySettings::SetFullscreen(vbool f)
{
	m_bFullscreen = f;
}

vbool VDisplaySettings::IsFullscreen() const
{
	return m_bFullscreen;
}

void VDisplaySettings::SetSize(vuint width, vuint height)
{
    SetWidth(width);
	SetHeight(height);
}

void VDisplaySettings::SetWidth(vuint w)
{
	m_nWidth = w;
}

vuint VDisplaySettings::GetWidth() const
{
    return m_nWidth;
}

void VDisplaySettings::SetHeight(vuint h)
{
    m_nHeight = h;	
}

vuint VDisplaySettings::GetHeight() const
{
	return m_nHeight;	
}


void VDisplaySettings::SetPosition(vuint x, vuint y)
{
    SetX(x);
	SetY(y);
}

void VDisplaySettings::SetX(vuint x)
{
	m_nWinCoordX = x;
}

vuint VDisplaySettings::GetX() const
{
	return m_nWinCoordX;	
}

void VDisplaySettings::SetY(vuint y)
{
	m_nWinCoordY = y;	
}

vuint VDisplaySettings::GetY() const
{
	return m_nWinCoordY;	
}


void VDisplaySettings::SetBitsPerPixel(vuint bpp)
{
	m_nBitsPerPixel = bpp;	
}

vuint VDisplaySettings::GetBitsPerPixel() const
{
	return m_nBitsPerPixel;	
}

std::string VDisplaySettings::GetAPI() const
{
	return m_sAPIType;
}

void VDisplaySettings::SetAPI(const std::string& api)
{
	m_sAPIType = api;
}

void VDisplaySettings::SetDepthBits(vuint depth)
{
	m_nDepthBits = depth;
}

vuint VDisplaySettings::GetDepthBits() const
{
	return m_nDepthBits;
}

vuint VDisplaySettings::GetStencilBits() const
{
	return m_nStencilBits;
}

vuint VDisplaySettings::GetAccumulationBits() const
{
	return m_nAccumulationBuffer;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
