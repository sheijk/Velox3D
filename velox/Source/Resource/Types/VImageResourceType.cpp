#include "VImageResourceType.h"
//-----------------------------------------------------------------------------
#include <V3d/Core/VTypeInfo.h>

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
	m_ManagedTypes.push_back(GetTypeInfo<VImage>());
}

/**
 * d'tor
 */
VImageResourceType::~VImageResourceType()
{
}

VRangeIterator<VTypeInfo> VImageResourceType::CreatedTypes()
{
	return CreateBeginIterator(m_ManagedTypes);
}

vbool VImageResourceType::Generate(
	resource::VResource* in_pResource,
	VTypeInfo in_Type)
{
	V3D_ASSERT(GetTypeInfo<VImage>() == in_Type);

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
