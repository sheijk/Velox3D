#ifndef V3D_VIMAGE_H
#define V3D_VIMAGE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/VBuffer.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace image{
//-----------------------------------------------------------------------------


/* Represents a decoded image file as pixel buffer */


struct VImage
{
	VImage(){};
	vuint m_iHeight;
	vuint m_iWidth;
	vuint m_iBPP;

	typedef graphics::VBuffer<vuchar> ImageData;
	ImageData* m_pData;
};

typedef VPointer<VImage>::SharedPtr VImagePtr;
//-----------------------------------------------------------------------------
} // namespace image
} // namespace v3d
//-----------------------------------------------------------------------------

#endif // V3D_VIMAGE_H
