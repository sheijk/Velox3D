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

	virtual VImagePtr CreateImage(VStringParam in_sFilename);
	
	virtual void Register(
		IVImageLoader* in_ImageLoader,
		VStringParam in_sExtension
		);

private:
	typedef std::pair<VString, IVImageLoader*> MapPair;

	std::map<VString, IVImageLoader*> m_LoaderMap;
	VStringRetVal ParseFileExtension(VStringParam sName);
	
	//std::vector<std::string> m_ExtensionList;

};
//-----------------------------------------------------------------------------
} // namespace image
} // namespace v3d
//-----------------------------------------------------------------------------
#endif //V3D_VIMAGEFACTORY_H