//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Image/IVImageFactory.h>
#include "VImageManipulator.h"

#include <IL/il.h>
#include <IL/ilu.h>

#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace image{
//-----------------------------------------------------------------------------

VImageManipulator::VImageManipulator()
{
	Register();
}
//-----------------------------------------------------------------------------

VImageManipulator::~VImageManipulator()
{
}

//-----------------------------------------------------------------------------
void VImageManipulator::Scale(VImage& in_ImageSource, VImage& in_ImageDest)
{
	ilInit();
	iluInit();

	ILuint id;

	ilGenImages(1, &id);
	ilBindImage(id);

	ilTexImage(
		in_ImageSource.GetWidth(),
		in_ImageSource.GetHeight(),
		1,
		in_ImageSource.GetBPP() / 8,
		IL_RGB,
		IL_UNSIGNED_BYTE,
		in_ImageSource.GetData().GetDataAddress()
		);

	iluScale(
		in_ImageDest.GetWidth(),
		in_ImageDest.GetHeight(),
 		1);

	if(in_ImageDest.pData != 0)
	{
		in_ImageDest.pData->~VBuffer();
	}

	const vuint nSize = 
		ilGetInteger(IL_IMAGE_WIDTH) * 
		ilGetInteger(IL_IMAGE_HEIGHT) * ilGetInteger(IL_IMAGE_BPP);

	in_ImageDest.iWidth = ilGetInteger(IL_IMAGE_WIDTH);
	in_ImageDest.iHeight = ilGetInteger(IL_IMAGE_HEIGHT);
	in_ImageDest.iBPP = ilGetInteger(IL_IMAGE_BPP) * 8;


	
	in_ImageDest.pData = new VImage::ImageData(new vuchar[nSize], nSize);

	vuchar* pDataPtr = ilGetData();

	memcpy(in_ImageDest.pData->GetDataAddress(), pDataPtr, nSize);

    
	ilDeleteImages(1, &id);
	
	ilShutDown();
}
//-----------------------------------------------------------------------------
void VImageManipulator::Convert(VImage& in_ImageSource, VImage& in_ImageDest)
{
	ilInit();
	
	ILuint id;

	ilGenImages(1, &id);
	ilBindImage(id);

	ilTexImage(
		in_ImageSource.GetWidth(),
		in_ImageSource.GetHeight(),
		1,
		in_ImageSource.GetBPP() / 8,
		IL_RGB,
		IL_UNSIGNED_BYTE,
		in_ImageSource.GetData().GetDataAddress()
		);

	switch(in_ImageDest.GetBPP())
	{
	case 32:
		{
            ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
			break;
		}
	case 24:
		{
			ilConvertImage(IL_RGB, IL_UNSIGNED_BYTE);
			break;
		}
	case 16:
		{
			//TODO: find out how 16 textures are to be handled
			V3D_THROW(VException, "16 bit per pixel are not supported by now!");
			break;
		}

	case 8:
		{
			ilConvertImage(IL_LUMINANCE, IL_UNSIGNED_BYTE);
			break;
		}
	
	default:
		{
			V3D_THROW(VException, "invalid bit per pixel format specified");
			break;
		}

	}

	if(in_ImageDest.pData != 0)
	{
		in_ImageDest.pData->~VBuffer();
	}

	const vuint nSize = 
		ilGetInteger(IL_IMAGE_WIDTH) * 
		ilGetInteger(IL_IMAGE_HEIGHT) * ilGetInteger(IL_IMAGE_BPP);

	in_ImageDest.iWidth = ilGetInteger(IL_IMAGE_WIDTH);
	in_ImageDest.iHeight = ilGetInteger(IL_IMAGE_HEIGHT);
	in_ImageDest.iBPP = ilGetInteger(IL_IMAGE_BPP) * 8;


	
	in_ImageDest.pData = new VImage::ImageData(new vuchar[nSize], nSize);

	vuchar* pDataPtr = ilGetData();

	memcpy(in_ImageDest.pData->GetDataAddress(), pDataPtr, nSize);

    
	ilDeleteImages(1, &id);
	
	ilShutDown();

}

//-----------------------------------------------------------------------------

void VImageManipulator::Register()
{
	IVImageFactory* Factory = QueryObject<IVImageFactory>("image.service");
	Factory->Register(this);
	
}

//-----------------------------------------------------------------------------
} // namespace image
} // namespace v3d
//-----------------------------------------------------------------------------