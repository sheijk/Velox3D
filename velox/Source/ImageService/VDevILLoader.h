/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_DEVILLOADER_04_06_17_H
#define V3D_DEVILLOADER_04_06_17_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Image/IVImageLoader.h>
#include <IL/il.h>

//-----------------------------------------------------------------------------
namespace v3d{
namespace image{
//-----------------------------------------------------------------------------

   /**
	* wrapps the DevIL image libary to v3d
	* @author ins
	* @version 1.0
	* @created 17-Jun-2004 18:04:01
	*/

class VDevILLoader : public IVImageLoader 
{

public:
	VDevILLoader();
	virtual ~VDevILLoader();


	   /**
		* Create an image out of a vfs stream *
		* @param in_pStream
		* 
		*/
	virtual VImage* Create(vfs::IVStream* in_pStream, VStringParam in_sExt);

protected:
	   
	   /**
		* Call this method to register the loader to the factory *
		*/
	virtual void Register();

	ILenum GetMode(VStringParam in_sExt);
	

};
//-----------------------------------------------------------------------------
} // namespace image
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_DEVILLOADER_04_06_17_H
 
