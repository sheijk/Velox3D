#ifndef V3D_VJPEGIMAGELOADER_H
#define V3D_VJPEGIMAGELOADER_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Image/IVImageLoader.h>
#include <jpeglib.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace image {
//-----------------------------------------------------------------------------

class VJpegImageLoader : public IVImageLoader
{
public:
	VJpegImageLoader();
	
	virtual VImage* Create(vfs::IVStream* in_pStream);
	
	vuint m_iWidth;
	vuint m_iHeight;
	vuint m_iBPP;
	vuchar* m_pData;
private:

	tImageJPG* pImageData;

	

protected:
	
	void DecodeJPG(jpeg_decompress_struct* cinfo, tImageJPG *pImageData);
	
	// Uglz hack but i wanna have jpeg decoding...
	void StreamToFile(vuchar* in_pBuffer, vuint in_nByte);
	void DeleteFile();

	virtual void Register();
};

//-----------------------------------------------------------------------------
} // namespace image
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VJPEGIMAGELOADER_H
