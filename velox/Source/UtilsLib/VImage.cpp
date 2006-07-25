#include <V3d/Image/VImage.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace image {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

//TODO: insert definitions here

VImage::VImage()
{
	pData = 0;
	iHeight = 0;
	iWidth = 0;
	iBPP = 0;
};

VImage::VImage(vuint width, vuint height, vuint bpp)
{
	V3D_VERIFY(bpp == 8 || bpp == 16 || bpp == 24 || bpp == 32);

	const vuint bufSize = width * height * bpp/8;
	pData = new ImageData(new vuchar[bufSize], bufSize);

	iHeight = height;
	iWidth = width;
	iBPP = bpp;
}

VImage::VImage(const VImage& in_Source)
{
	pData = new ImageData(in_Source.pData, ImageData::CopyData);
	iHeight = in_Source.iHeight;
	iWidth = in_Source.iWidth;
	iBPP = in_Source.iBPP;
}

VImage::~VImage()
{
	//TODO: ich fass es nicht.. -- sheijk
	// delete, und copy c'tor und = operator fehlen... das ding schreit 
	// ja foermlich nach speicherfehlern
	if( pData != 0 )
	{
		pData->~VBuffer();
	}
}

vuint VImage::GetBPP() const { return iBPP; }

VImage::ImageData& VImage::GetData() { return *pData; }
const VImage::ImageData& VImage::GetData() const { return *pData; }

vbyte* VImage::GetPixelData() { return pData->GetDataAddress(); }
const vbyte* VImage::GetPixelData() const { return pData->GetDataAddress(); }

vuint VImage::GetBitsPerPixel() const {	return iBPP; }

vuint VImage::GetWidth() const { return iWidth; }
vuint VImage::GetHeight() const { return iHeight; }

void VImage::SetPixel(vuint x, vuint y, vuint color)
{
	switch(iBPP)
	{
	case 8:
		{
			pData->GetDataAddress()[x+y*iWidth] = vuchar(color);
		} break;
	case 16:
		{
			vuint16* dest = reinterpret_cast<vuint16*>(
				pData->GetDataAddress() + (x+y*iWidth)*2);
			*dest = vuint16(color);
		} break;
	case 32:
		{
			vuint32* dest = reinterpret_cast<vuint32*>(
				pData->GetDataAddress() + (x+y*iWidth)*4);
			*dest = vuint32(color);
		} break;
	default:
		vuint invalidFormat = 500;
		V3D_VERIFY(iBPP != invalidFormat);
		invalidFormat++;
		V3D_VERIFY(iBPP != invalidFormat);
	}
}

vuint VImage::GetPixel(vuint x, vuint y) const
{
	vuint color = 0;

	switch(iBPP)
	{
	case 8:
		{
			color = pData->GetDataAddress()[x+y*iWidth];
		} break;
	case 16:
		{
			vuint16* dest = reinterpret_cast<vuint16*>(
				pData->GetDataAddress() + (x+y*iWidth)*2);
			color = *dest;
		} break;
	case 32:
		{
			vuint32* dest = reinterpret_cast<vuint32*>(
				pData->GetDataAddress() + (x+y*iWidth)*4);
			color = *dest;
		} break;
	default:
		vuint invalidFormat = 500;
		V3D_VERIFY(iBPP != invalidFormat);
		invalidFormat++;
		V3D_VERIFY(iBPP != invalidFormat);
	}

	return color;
}

/* check for equal width, height and bpp */
vbool VImage::IsEqualInProperties(VImage& in_Image)
{
	if(iHeight == in_Image.GetHeight() &&
		iWidth == in_Image.GetWidth()  &&
		iBPP   == in_Image.GetBitsPerPixel())
		return true;

	return false;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::image
//-----------------------------------------------------------------------------
