#include <v3d/Core/VObjectRegistry.h>
#include <v3d/VFS/IVFileSystem.h>
#include "VImageFactory.h"
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace image{
//-----------------------------------------------------------------------------

VImageFactory::VImageFactory() : IVImageFactory("image.service", 0)
{
}
//-----------------------------------------------------------------------------

VImageFactory::~VImageFactory()
{
}
//-----------------------------------------------------------------------------

VStringRetVal VImageFactory::ParseFileExtension(VStringParam sName)
{
	std::string Filename(sName);
	std::string Extension;
	std::size_t PointPos = Filename.rfind(".");
	Extension = Filename.substr(PointPos+1, Filename.size());
	return Extension.c_str();
}
//-----------------------------------------------------------------------------

void VImageFactory::Register(IVImageLoader* in_ImageLoader,
							 VStringParam in_sExtension)
{
	m_LoaderMap.insert(MapPair(in_sExtension, in_ImageLoader));

}
//-----------------------------------------------------------------------------


IVImageFactory::ImagePtr VImageFactory::CreateImage(VStringParam in_sFilename)
{
	IVImageLoader* theLoader = 0;
	VImage* theImage = 0;

	
	vfs::IVFileSystem& fileSys = *QueryObject<vfs::IVFileSystem>("vfs.fs");

	// open file
	vfs::IVFileSystem::FileStreamPtr fileStream = 
		fileSys.OpenFile(in_sFilename, vfs::VReadAccess);

	VString theExtension = ParseFileExtension(in_sFilename);
	theLoader = m_LoaderMap[theExtension];

	if(theLoader)
	{
		theImage = theLoader->Create(fileStream.Get(), theExtension);
	}
	else
	{
		VString message = "no loader for ." + theExtension + " Format found";
		V3D_THROW(VException, message.AsCString());
	}
	
	//TODO: check if this is not a real bad mistake
	ImagePtr retrunImage;
	retrunImage.Assign(theImage);
	
	return retrunImage;
}
//-----------------------------------------------------------------------------

void VImageFactory::Register(IVImageSaver* in_ImageSaver,
							 VStringParam in_sExtension)
{
	m_SaverMap.insert(MapPairSaver(in_sExtension, in_ImageSaver));

}
//-----------------------------------------------------------------------------

void VImageFactory::Register(IVImageManipulator* in_ImageManipulator)
{
	m_ManipulatorList.push_back(in_ImageManipulator);
}
//-----------------------------------------------------------------------------

void VImageFactory::SaveImageToFile(VStringParam in_sFilename, VImage& in_Image)
{
	IVImageSaver* theImageSaver = 0;

	theImageSaver = m_SaverMap[ParseFileExtension(in_sFilename)];

    if(theImageSaver)
	{

		VString sExtension = ParseFileExtension(in_sFilename);

		if(strcmp(sExtension, "bmp") == 0)
		{
			theImageSaver->SaveImageToFile(in_Image,
			IVImageSaver::ImageType::SaveBMP, in_sFilename);
		}
		else if(strcmp(sExtension,"tga") == 0)
		{
			theImageSaver->SaveImageToFile(in_Image,
				IVImageSaver::ImageType::SaveTGA, in_sFilename);
		}
		else if(strcmp(sExtension,"jpg") == 0)
		{
			theImageSaver->SaveImageToFile(in_Image,
				IVImageSaver::ImageType::SaveJPG, in_sFilename);
		}
	}
		
	else
	{
		V3D_THROW(VException, "the selected save format is not supported by now!");
	}

}
//-----------------------------------------------------------------------------
void VImageFactory::ScaleImage(VImage& in_ImageSource, VImage& in_ImageDest)
{
	//TODO: make flexible by choosing manipulator to use
	m_ManipulatorList[0]->Scale(in_ImageSource, in_ImageDest);
}
//-----------------------------------------------------------------------------

void VImageFactory::ConvertImage(VImage& in_ImageSource, VImage& in_ImageDest)
{
	//TODO: make flexible by choosing manipulator to use
	m_ManipulatorList[0]->Convert(in_ImageSource, in_ImageDest);
}
//-----------------------------------------------------------------------------

void VImageFactory::CreateImage(VStringParam in_sFilename,
								VImage& in_Image)
{

	if(	in_Image.GetWidth() == 0 ||
		in_Image.GetHeight()== 0 ||
		in_Image.GetBitsPerPixel() == 0)
	{
		V3D_THROW(VException, "cannot create image. parameters are surely wrong!");
	}

	ImagePtr returnImage = CreateImage(in_sFilename);



	if(returnImage->IsEqualInProperties(in_Image))
	{
		MakeDeepImageCopy(*returnImage, in_Image);
//		in_Image = *returnImage;
	}
	
	else
	{
		/* store the old values because convert returns only a valid image */
		const vuint nWidth = in_Image.GetWidth();
		const vuint nHeight = in_Image.GetHeight();

		ConvertImage(*returnImage, in_Image);

		/* restore old values */
		returnImage->iWidth = nWidth;
		returnImage->iHeight = nHeight;

        ScaleImage(in_Image, *returnImage);
	}

	//TODO: gets mem of returnImage freed?

		
	MakeDeepImageCopy(*returnImage, in_Image);
	//in_Image = *returnImage;
}

void VImageFactory::MakeDeepImageCopy(VImage& in_Image, VImage& in_ImageDest)
{
	const vuint nSize = in_Image.GetWidth() * in_Image.GetHeight() * in_Image.GetBPP() / 8;

	in_ImageDest.iBPP = in_Image.GetBPP();
	in_ImageDest.iWidth = in_Image.GetWidth();
	in_ImageDest.iHeight = in_Image.GetHeight();

	//delete mem if already exists
	if(in_ImageDest.pData != 0)
	{
		in_ImageDest.pData->~VBuffer();
	}

	in_ImageDest.pData = new VImage::ImageData(new vuchar[nSize], nSize);
	memcpy(in_ImageDest.pData->GetDataAddress(), in_Image.GetData().GetDataAddress(), nSize);
}

//-----------------------------------------------------------------------------
} // namespace image
} // namespace v3d
//-----------------------------------------------------------------------------