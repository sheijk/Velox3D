#ifndef V3D_DEVILSAVER_04_07_13_H
#define V3D_DEVILSAVER_04_07_13_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Image/IVImageSaver.h>
#include <IL/il.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace image{
//-----------------------------------------------------------------------------

   /**
	* wrapps the DevIL image libary saving functions to v3d
	* @author ins
	* @version 1.0
	*/

class VDevILSaver : public IVImageSaver
{
public:
	VDevILSaver();
	virtual ~VDevILSaver();

	   /**
		* Save an image to file
		* @note: does alwyas overwrite filename!
		*/
	virtual void SaveImageToFile(VImage& in_Image, ImageType in_ImageType,
		VStringParam in_sFilename);

protected:
	   
	   /**
		* Call this method to register the saver to the factory *
		*/
	virtual void Register();
};
//-----------------------------------------------------------------------------
} // namespace image
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_DEVILSAVER_04_07_13_H
 