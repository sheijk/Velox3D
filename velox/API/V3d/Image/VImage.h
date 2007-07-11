/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VIMAGE_H
#define V3D_VIMAGE_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VTypeInfo.h>

#include <V3d/Graphics/VBuffer.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace image{
//-----------------------------------------------------------------------------

/**
 * Represents a decoded image file as pixel buffer
 */
class VImage
{
public:
	friend class VImageFactory;
	friend class VImageManipulator;

	typedef graphics::VBuffer<vuchar> ImageData;

	VImage();
	VImage(vuint width, vuint height, vuint bpp);
	explicit VImage(const VImage& in_Source);

	~VImage();

	//TODO: remove
	vuint GetBPP() const;

	ImageData& GetData();
	const ImageData& GetData() const;

	vbyte* GetPixelData();
	const vbyte* GetPixelData() const;

	vuint GetBitsPerPixel() const;

	vuint GetWidth() const;
	vuint GetHeight() const;

	void SetPixel(vuint x, vuint y, vuint color);
	vuint GetPixel(vuint x, vuint y) const;

	/* check for equal width, height and bpp */
	vbool IsEqualInProperties(VImage& in_Image);

private:
	vuint iHeight;
	vuint iWidth;
	vuint iBPP;

	ImageData* pData;
};
//-----------------------------------------------------------------------------
} // namespace image
} // namespace v3d
V3D_TYPEINFO(v3d::image::VImage);
//-----------------------------------------------------------------------------
#endif // V3D_VIMAGE_H
