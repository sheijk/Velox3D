#ifndef V3D_VIMAGEFACTORY_H
#define V3D_VIMAGEFACTORY_H
//-----------------------------------------------------------------------------
#include <v3d/Image/IVImageFactory.h>
#include <v3d/Image/IVImageLoader.h>
#include <map>
#include <vector>
//-----------------------------------------------------------------------------
namespace v3d{
namespace image{
//-----------------------------------------------------------------------------

class VImageFactory : public IVImageFactory
{

public:
	VImageFactory();
	virtual ~VImageFactory();

	/* Creates and decodes an image file given by its param */
	virtual ImagePtr CreateImage(VStringParam in_sFilename);

	/* Creates and decodes an image file by its param and destination type */
	virtual void CreateImage(VStringParam in_sFilename, ImagePtr& in_Image);

	virtual void SaveImageToFile(VStringParam in_sFilename, VImage& in_Image, 
		IVImageSaver::ImageType in_Type);

	/* Scale an image to the given image parameters */
	virtual void ScaleImage(VImage& in_ImageSource, VImage& in_ImageDest);

	/* Converts an image to the given image parameters */
	virtual void ConvertImage(VImage& in_ImageSource, VImage& in_ImageDest);

	
	virtual void Register(
		IVImageLoader* in_ImageLoader,
		VStringParam in_sExtension
		);

	virtual void Register(
		IVImageSaver* in_ImageSaver,
		VStringParam in_sExtension
		);

	virtual void Register(
		IVImageManipulator* in_ImageManipulator
		);

	

private:
	typedef std::pair<VString, IVImageLoader*> MapPair;
	typedef std::pair<VString, IVImageSaver*> MapPairSaver;


	std::map<VString, IVImageLoader*> m_LoaderMap;
	std::map<VString, IVImageSaver*> m_SaverMap;
	std::vector<IVImageManipulator*> m_ManipulatorList;
	
	VStringRetVal ParseFileExtension(VStringParam sName);
	
	//std::vector<std::string> m_ExtensionList;

	VStringRetVal GetExtensionType(IVImageSaver::ImageType in_Type);


};
//-----------------------------------------------------------------------------
} // namespace image
} // namespace v3d
//-----------------------------------------------------------------------------
#endif //V3D_VIMAGEFACTORY_H