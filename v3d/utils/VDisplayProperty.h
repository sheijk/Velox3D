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

#ifndef V3D_VDISPLAYPROPERTY_H
#define V3D_VDISPLAYPROPERTY_H

#include <Core/VTypes.h>


class VDisplayProperty  
{

private:

	vbool m_bFullscreen;
	vuint m_iWidth;
	vuint m_iHeight;
	vuint m_iBitsPerPixel;


public:
	VDisplayProperty();
	
	vuint GetWidth();
	vuint GetHeight();
	vuint GetBitsPerPixel();
	vbool GetFullscreen();

	void SetWidth(vuint iWidth);
	void SetHeight(vuint iHeight);
	void SetBitsPerPixel(vuint iBitsPerPixel);
	void SetFullscreen(vbool bFullscreen);

};

#endif
