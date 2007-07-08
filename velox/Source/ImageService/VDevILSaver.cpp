/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

//-----------------------------------------------------------------------------
#include <V3d/Core/VObjectRegistry.h>
#include <V3d/Image/IVImageFactory.h>
#include <V3d/Image/VImage.h>
#include <V3d/Utils/VStreamReader.h>
#include <memory.h>
#include <string>
#include "VDevILSaver.h"
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace image{
//-----------------------------------------------------------------------------

VDevILSaver::VDevILSaver()
{
	Register();
}
//-----------------------------------------------------------------------------

VDevILSaver::~VDevILSaver()
{
}

//-----------------------------------------------------------------------------
void VDevILSaver::SaveImageToFile(VImage& in_Image, ImageType in_ImageType,
								VStringParam in_sFilename)
{
	ilInit();

	ILuint id;
	
	ilEnable(IL_FILE_OVERWRITE);

	ilGenImages(1, &id);
	ilBindImage(id);

	ilTexImage(
		in_Image.GetWidth(),
		in_Image.GetHeight(),
		1,
		in_Image.GetBitsPerPixel() / 8,
		IL_RGB,
		IL_UNSIGNED_BYTE,
		in_Image.GetData().GetDataAddress()
		);

	switch(in_ImageType)
	{
	case IVImageSaver::SaveBMP:
		{
			if(in_Image.GetBitsPerPixel() == 8 ||
			   in_Image.GetBitsPerPixel() == 32)
			{
				V3D_THROW(VException, "8/32 bit per pixel are not supported by bmp format!");
			}

			ilSave(IL_BMP, (vchar*)in_sFilename);
			break;
		}

	case IVImageSaver::SaveJPG:
		{
			if(in_Image.GetBitsPerPixel() == 32)
				V3D_THROW(VException, "32 bit per pixel are not supported by jpg format!");

			ilSave(IL_JPG, (vchar*)in_sFilename);
			break;
		}
	case IVImageSaver::SaveTGA:
		{
			if(in_Image.GetBitsPerPixel() == 8)
				V3D_THROW(VException, "8 bit per pixel are not supported by tga format!");

			ilSave(IL_TGA, (vchar*)in_sFilename);
			break;
		}
	default:
		{
			V3D_THROW(VException, "invalid saving format specified");
			ilSave(IL_BMP, (vchar*)in_sFilename);
			break;
		}
	}
	
	ilDeleteImages(1, &id);
	ilShutDown();
}
//-----------------------------------------------------------------------------

void VDevILSaver::Register()
{
	IVImageFactory* Factory = QueryObject<IVImageFactory>("image.service");
	Factory->Register(this, "jpg");
	Factory->Register(this, "tga");
	Factory->Register(this, "bmp");
}

//-----------------------------------------------------------------------------
} // namespace image
} // namespace v3d
//-----------------------------------------------------------------------------
