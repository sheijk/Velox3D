#ifndef V3D_IVIMAGEFACTORY_H
#define V3D_IVIMAGEFACTORY_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VNamedObject.h>
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/SmartPtr/VServicePtr.h>

#include <v3d/Image/VImage.h>
#include <v3d/Image/IVImageLoader.h>
#include <v3d/Image/IVImageSaver.h>
#include <v3d/Image/IVImageManipulator.h>
//-----------------------------------------------------------------------------
namespace v3d{
namespace image{
//-----------------------------------------------------------------------------

/** 
 * Factory for loading / saving / manipulating image data
 * @author ins
 */

class IVImageFactory : public VNamedObject
{

public:

	typedef VPointer<VImage>::SharedPtr ImagePtr;

	/** returns an image containing the image data of the given image file */
	virtual ImagePtr CreateImage(VStringParam in_sFilename) = 0;

	/* Creates and decodes an image file by its param and destination type */
	virtual void CreateImage(VStringParam in_sFilename, VImage& in_Image) = 0;


	/* Save an image to a file */
	virtual void SaveImageToFile(VStringParam in_sFilename,
		VImage& in_Image) = 0;

	//TODO: warum nicht nur ConvertImage? --sheijk
	/* Scale an image to the given image parameters
	 * @note: only scales images. does not convert to other byte format
	 */
	virtual void ScaleImage(VImage& in_ImageSource, VImage& in_ImageDest) = 0;

	//TODO: io_ImageDest, weil ein- und ausgabeparameter --sheijk
	/* Converts an image to the given image parameters */
	virtual void ConvertImage(VImage& in_ImageSource, VImage& in_ImageDest) = 0;



	/* Register an Imageloader object to this factory */
	virtual void Register(IVImageLoader* in_ImageLoader,
		VStringParam in_sExtension)	= 0;

	/* Register an image saver object to this factory */
	virtual void Register(
		IVImageSaver* in_ImageSaver,
		VStringParam in_sExtension
		) = 0;

	/* Register an image manipulator object to this factory */
	virtual void Register(
		IVImageManipulator* in_ImageManipulator
		) = 0;

protected:
	/* initialize the interface and make it queryable */
	IVImageFactory(VStringParam in_strName, VNamedObject* in_pParent)
		: VNamedObject(in_strName, in_pParent){}
};
//-----------------------------------------------------------------------------
} // namespace image
} // namespace v3d
//-----------------------------------------------------------------------------
template<>
inline v3d::image::IVImageFactory* v3d::QueryService<v3d::image::IVImageFactory>()
{
	return QueryObject<v3d::image::IVImageFactory>("image.service");
}
//-----------------------------------------------------------------------------
#endif // V3D_IVIMAGEFACTORY_H
