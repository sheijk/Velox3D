#ifndef V3D_VTGALOADER_H
#define V3D_VTGALOADER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Image/IVImageLoader.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace image {
//-----------------------------------------------------------------------------

class VTgaImageLoader : public IVImageLoader
{
public:
	VTgaImageLoader();
	virtual VImage* Create(vfs::IVStream* in_pStream, VStringParam in_sExt);

private:

	typedef struct TgaHeader
	{
		vuchar IDLength;
		vuchar ColorMapType;
		vuchar ImageType;
		vuchar ColorMapSize;
		vuchar BPP;
		vuchar Attributes;
		vushort ColorMapIndex;
		vushort ColorMapLength;
		vushort XOrigin;
		vushort YOrigin;
		vushort Width;
		vushort Height;

	};

	enum Error
	{
		WRONG_COLOR_MAP,
		WRONG_IMAGE_TYPE,
		WRONG_BPP,
		WRONG_DATA,
		NO_ERROR
	};

	TgaHeader m_FileHeader;

	Error ReadBuffer(vuchar* in_pBuffer);

	vuchar* GetData(vuchar* in_pBuffer);
	vuchar* GetCompressedData(vuchar* in_pBuffer);
	
	vuchar* Get8Bit(vuchar* in_pBuffer);
	vuchar* Get24Bit(vuchar* in_pBuffer);
	vuchar* Get32Bit(vuchar* in_pBuffer);

	vuint m_iWidth;
	vuint m_iHeight;
	vuint m_iBPP;
	vuchar* m_pData;



protected:
	virtual void Register();
};

//-----------------------------------------------------------------------------
} // namespace image
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTGALOADER_H
