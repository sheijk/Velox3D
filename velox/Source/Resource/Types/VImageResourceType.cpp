#include "VImageResourceType.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace image {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VImageResourceType::VImageResourceType()
{
}

/**
 * d'tor
 */
VImageResourceType::~VImageResourceType()
{
}

resource::VResourceData::TypeId VImageResourceType::GetTypeId() const
{
	return resource::VResource::GetTypeId<VImage>();
}

vbool VImageResourceType::Generate(resource::VResource* in_pResource)
{
	// if a file name is present
	const resource::VFileName* pFileName = &*in_pResource->GetData<resource::VFileName>();

	if( 0 != pFileName )
	{
		// get image service
		VImageServicePtr pImageServicePtr;

		// create image
		IVImageFactory::ImagePtr pImage = 
			pImageServicePtr->CreateImage(pFileName->AsString().c_str());

		//TODO: change VResource.AddData parameter to shared ptr
		VImage* pCopy = new VImage(*pImage);

		// add it to resource
		in_pResource->AddData(pCopy);

		return true;
	}
	else
	{
		return false;
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::image
//-----------------------------------------------------------------------------
