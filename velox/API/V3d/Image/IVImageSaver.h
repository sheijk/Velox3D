/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVIMAGESAVER_04_07_13_H
#define V3D_IVIMAGESAVER_04_07_13_H
//-------------------------------------------------------------------------
#include <V3d/Image/VImage.h>
#include <V3d/VFS/IVStream.h>
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
	
	virtual ~IVImageSaver(){};


	//TODO: hier sollte wie beim loader IVStream& als parameter sein --sheijk
	/* Create an image out of a vfs stream */ //TODO: nicht anders rum?
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
