#ifndef V3D_IVIMAGEFACTORY_H
#define V3D_IVIMAGEFACTORY_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VNamedObject.h>
#include <v3d/Image/VImage.h>
#include <v3d/Image/IVImageLoader.h>
#include <v3d/Core/VObjectRegistry.h>
#include <v3d/Core/SmartPtr/VServicePtr.h>

//-----------------------------------------------------------------------------
namespace v3d{
namespace image{
//-----------------------------------------------------------------------------

/* Factory for laoding image data
 * @author ins
 *
 */

class IVImageFactory : public VNamedObject 
{

public:

	typedef VPointer<VImage>::SharedPtr ImagePtr;
	
	/* initialize the interface and make it queryable */
	IVImageFactory(VStringParam in_strName, VNamedObject* in_pParent) 
		: VNamedObject(in_strName, in_pParent){}


	/* Creates and decodes an image file given by its param */
	virtual ImagePtr CreateImage(VStringParam in_sFilename) = 0;

	/* Register an Imageloader object to this factory */
	virtual void Register(IVImageLoader* in_ImageLoader,
		VStringParam in_sExtension)	= 0;

	
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
