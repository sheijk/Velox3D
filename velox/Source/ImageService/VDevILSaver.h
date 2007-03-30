/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_DEVILSAVER_04_07_13_H
#define V3D_DEVILSAVER_04_07_13_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Image/IVImageSaver.h>
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
 
