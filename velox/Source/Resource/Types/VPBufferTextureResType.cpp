#include "VPBufferTextureResType.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::resource;

VPBufferTextureResType::VPBufferTextureResType()
{
	m_ManagedTypes.push_back(GetTypeInfo<VPBufferTexture>());
}

VPBufferTextureResType::~VPBufferTextureResType()
{
}

VRangeIterator<VTypeInfo> VPBufferTextureResType::CreatedTypes()
{
	return CreateBeginIterator<std::vector<VTypeInfo> >(m_ManagedTypes);
}

vbool VPBufferTextureResType::Generate(
	resource::VResource* in_pResource, 
	VTypeInfo in_Type)
{
	V3D_ASSERT(GetTypeInfo<VPBufferTexture>() == in_Type);

	VResourceDataPtr<const IVRenderContext> pContextData;
	IVRenderContext* pContext = 0;

	try
	{
		//get Pixel Buffer Context
		pContextData = in_pResource->GetData<IVRenderContext>();
		pContext = const_cast<IVRenderContext*>(&*pContextData);
	}
	catch(resource::VDataNotFoundException&) 
	{
		return false;
	}

	in_pResource->AddData<VPBufferTexture>(
		new VPBufferTexture(static_cast<VPBufferWindowContext*>(pContext)));

	return true;
}
//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------