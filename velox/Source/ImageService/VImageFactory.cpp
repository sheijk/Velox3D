#include <v3d/Core/VObjectRegistry.h>
#include <v3d/VFS/IVFileSystem.h>
#include "VImageFactory.h"
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
	vuint PointPos = Filename.rfind(".");
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


VImagePtr VImageFactory::CreateImage(VStringParam in_sFilename)
{
	IVImageLoader* theLoader = NULL;
	VImage* theImage = NULL;

	
	vfs::IVFileSystem& fileSys = *QueryObject<vfs::IVFileSystem>("vfs.fs");

	// open file
	vfs::IVFileSystem::FileStreamPtr fileStream = 
		fileSys.OpenFile(in_sFilename, vfs::VReadAccess);

	VString theExtension = ParseFileExtension(in_sFilename);
	theLoader = m_LoaderMap[theExtension.AsCString()];

	if(theLoader)
		theImage = theLoader->Create(fileStream.Get());
	
	VImagePtr retrunImage;
	retrunImage.Assign(theImage);
	return retrunImage;


}
//-----------------------------------------------------------------------------
} // namespace image
} // namespace v3d
//-----------------------------------------------------------------------------