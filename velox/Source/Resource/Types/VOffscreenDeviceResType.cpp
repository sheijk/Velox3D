#include "VOffscreenDeviceResType.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent
using namespace v3d::resource;

VOffscreenDeviceResType::VOffscreenDeviceResType()
{
	m_ManagedTypes.push_back(GetTypeInfo<IVDevice>());
}

VOffscreenDeviceResType::~VOffscreenDeviceResType()
{
}

VRangeIterator<VTypeInfo> VOffscreenDeviceResType::CreatedTypes()
{
	return CreateBeginIterator<std::vector<VTypeInfo> >(m_ManagedTypes);
}

VRangeIterator<VTypeInfo> VOffscreenDeviceResType::ManagedTypes()
{
	return CreateBeginIterator<std::vector<VTypeInfo> >(m_ManagedTypes);
}

vbool VOffscreenDeviceResType::Generate(
	resource::VResource* in_pResource, 
	VTypeInfo in_Type)
{
	V3D_ASSERT(GetTypeInfo<IVDevice>() == in_Type);

	VResourceDataPtr<const IVRenderContext> pContextData;
	IVRenderContext* pContext = 0;

	try
	{
		//get the Render Context
		pContextData = in_pResource->GetData<IVRenderContext>();
		pContext = const_cast<IVRenderContext*>(&*pContextData);
	}
	catch(resource::VDataNotFoundException&) 
	{
		return false;
	}

	//create OpenGL Device for the PBuffer
	in_pResource->AddData<IVDevice>(new VOpenGLDevice(*pContext->GetDisplaySettings(), 
		pContext));

	return true;
}

vbool VOffscreenDeviceResType::AllowMutableAccess(
	const VTypeInfo& in_TypeInfo, const resource::VResource* in_Resource) const
{
	return true;
}

void VOffscreenDeviceResType::NotifyChange(
	const VTypeInfo& in_Type, resource::VResource* in_pResource)
{
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------