//-----------------------------------------------------------------------------
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Image/IVImageFactory.h>
#include <v3d/Image/VImage.h>
#include <V3dLib/Utils/VStreamReader.h>
#include <memory.h>
#include <string>
#include "VDevILLoader.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace image{
//-----------------------------------------------------------------------------

VDevILLoader::VDevILLoader()
{
	Register();

	ilInit();
}


VDevILLoader::~VDevILLoader()
{
}

VImage* VDevILLoader::Create(vfs::IVStream* in_pStream, VStringParam in_sExt)
{
	
	ILuint id;

	utils::VStreamReader StreamReader(in_pStream);
	vbyte* pRawData = new vbyte[StreamReader.GetSizeOfBuffer()];

	memcpy(pRawData, (vbyte*)StreamReader.GetStreamBuffer(), StreamReader.GetSizeOfBuffer());

	ilGenImages(1, &id);
	ilBindImage(id);

	
	ilLoadL(GetMode(in_sExt), pRawData, StreamReader.GetSizeOfBuffer());

	vbyte* pData = ilGetData();

	VImage* pic = new VImage();

	pic->iWidth  = ilGetInteger(IL_IMAGE_WIDTH);
	pic->iHeight = ilGetInteger(IL_IMAGE_HEIGHT);

	pic->pData = new VImage::ImageData(pData, pic->GetWidth()*pic->GetHeight());
	
	return pic;
}


void VDevILLoader::Register()
{
	IVImageFactory* Factory = QueryObject<IVImageFactory>("image.service");
	Factory->Register(this, "jpg");
	Factory->Register(this, "tga");
	Factory->Register(this, "bmp");

}

ILenum VDevILLoader::GetMode(VStringParam in_sExt)
{
	// get the format we use

	ILenum eValue = IL_TYPE_UNKNOWN;

	std::string sExt(in_sExt);
	
    if(sExt == "jpg")
        return IL_JPG;
	if(sExt == "tga")
		return IL_TGA;
	if(sExt == "bmp")
		return IL_BMP;

	return eValue;
}

//-----------------------------------------------------------------------------
} // namespace image
} // namespace v3d
//-----------------------------------------------------------------------------