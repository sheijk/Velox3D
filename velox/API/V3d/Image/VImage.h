#ifndef V3D_VIMAGE_H
#define V3D_VIMAGE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/VBuffer.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace image{
//-----------------------------------------------------------------------------

/**
 * Represents a decoded image file as pixel buffer
 waers nicht sinnvoller, die Werte zu kapseln damit sie nicht veraendert
 werden koennen? die buffer groesse kann ja auch nicht mehr geaendert werden
 -- sheijk
 */
class VImage
{
public:
	typedef graphics::VBuffer<vuchar> ImageData;

	VImage() 
	{
		pData = 0;
		iHeight = 0;
		iWidth = 0;
		iBPP = 0;
	};

	VImage(vuint width, vuint height, vuint bpp)
	{
		V3D_VERIFY(bpp == 8 || bpp == 16 || bpp == 24 || bpp == 32);

		const vuint bufSize = width * height * bpp;
		pData = new ImageData(new vuchar[bufSize], bufSize);

		iHeight = height;
		iWidth = width;
		iBPP = bpp;
	}

	~VImage()
	{
		//TODO: ich fass es nicht.. -- sheijk
		// delete, und copy c'tor und = operator fehlen... das ding schreit 
		// ja foermlich nach speicherfehlern
		if( pData != 0 )
		{
			pData->~VBuffer();
		}
	}

	vuint GetBPP() const { return iBPP; }

	ImageData& GetData() { return *pData; }

	vuint GetBitsPerPixel() const {	return iBPP; }

	vuint GetWidth() const { return iWidth; }
	vuint GetHeight() const { return iHeight; }

	void SetPixel(vuint x, vuint y, vuint color)
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

	vuint GetPixel(vuint x, vuint y) const
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

public: // ja, das soll mal private werden
	vuint iHeight;
	vuint iWidth;
	vuint iBPP;

	ImageData* pData;
};
//-----------------------------------------------------------------------------
} // namespace image
} // namespace v3d
//-----------------------------------------------------------------------------

#endif // V3D_VIMAGE_H
