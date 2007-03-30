/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Graphics/VDisplaySettings.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d;

VSize::VSize() : width(0), height(0)
{
}

VSize::VSize(vuint w, vuint h) : width(w), height(h)
{
}

VPosition::VPosition() : x(0), y(0)
{
}

VPosition::VPosition(vuint xp, vuint yp) : x(xp), y(yp)
{
}

//-----------------------------------------------------------------------------

VDisplaySettings::VDisplaySettings()
{
	SetDefaultValues();
}

VDisplaySettings::VDisplaySettings(VSize size, VPosition pos)
{
	SetDefaultValues();

	SetSize(size);
	SetPosition(pos);
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

void VDisplaySettings::SetSize(VSize size)
{
	SetSize(size.width, size.height);
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

void VDisplaySettings::SetPosition(VPosition pos)
{
	SetPosition(pos.x, pos.y);
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

void VDisplaySettings::SetDefaultValues()
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
//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------

