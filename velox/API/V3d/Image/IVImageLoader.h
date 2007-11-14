/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_IVIMAGELOADER_H
#define V3D_IVIMAGELOADER_H
//-------------------------------------------------------------------------
#include <V3d/Image/VImage.h>
#include <V3d/VFS/IVStream.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace image{
//-----------------------------------------------------------------------------

/* Interface for image loading routines
 * @author: ins
 *
 */

class IVImageLoader
{
public:
	virtual ~IVImageLoader(){};
	/* Create an image out of a vfs stream */
	virtual VImage* Create(vfs::IVStream* in_pStream, VStringParam in_sExt) = 0;

protected:
	
	/* Call this method to register the loader to the factory */
	virtual void Register() = 0;

};
//-----------------------------------------------------------------------------
} // namespace image
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVIMAGELOADER_H
