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
	virtual void CreateImage(VStringParam in_sFilename, VImage& in_Image);

	virtual void SaveImageToFile(VStringParam in_sFilename, VImage& in_Image);

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

	void MakeDeepImageCopy(VImage& in_Image, VImage& in_ImageDest);
		 

};
//-----------------------------------------------------------------------------
} // namespace image
} // namespace v3d
//-----------------------------------------------------------------------------
#endif //V3D_VIMAGEFACTORY_H