//
// *** VDisplayProperty ***
//
// Synopsis:
//    - holds display information
//
// Description:
//    - 
//
// See also:
//    - 
//


#include <Utils/VDisplayProperty.h>


VDisplayProperty::VDisplayProperty()
{
	m_bFullscreen   = false;
	m_iWidth	    = 640;
	m_iHeight	    = 480;
	m_iBitsPerPixel = 16;
}

vuint VDisplayProperty::GetBitsPerPixel()
{
	return m_iBitsPerPixel;
}

vuint VDisplayProperty::GetHeight()
{
	return m_iHeight;
}

vuint VDisplayProperty::GetWidth()
{ 
	return m_iWidth;
}

vbool VDisplayProperty::GetFullscreen()
{
	return m_bFullscreen;
}

void VDisplayProperty::SetBitsPerPixel(vuint iBitsPerPixel)
{
	m_iBitsPerPixel = iBitsPerPixel;
}

void VDisplayProperty::SetFullscreen(vbool bFullscreen)
{
	m_bFullscreen = bFullscreen;
}

void VDisplayProperty::SetHeight(vuint iHeight)
{
	m_iHeight = iHeight;
}

void VDisplayProperty::SetWidth(vuint iWidth)
{
	m_iWidth = iWidth;
}



