#ifndef V3D_IVIMAGESAVER_04_07_13_H
#define V3D_IVIMAGESAVER_04_07_13_H
//-------------------------------------------------------------------------
#include <v3d/Image/VImage.h>
#include <v3d/VFS/IVStream.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace image{
//-----------------------------------------------------------------------------

/* Interface for image saving routines
 * @author: ins
 */

class IVImageSaver
{
public:

	enum ImageType
	{
		SaveBMP,
		SaveJPG,
		SaveTGA
	};


	/* Create an image out of a vfs stream */
	virtual void SaveImageToFile(VImage& in_Image, ImageType in_ImageType,
		VStringParam in_sFilename) = 0;

protected:
	
	/* Call this method to register the saver to the factory */
	virtual void Register() = 0;

};
//-----------------------------------------------------------------------------
} // namespace image
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVIMAGESAVER_04_07_13_H