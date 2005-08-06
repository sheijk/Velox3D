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
	m_ManagedTypes.push_back(GetTypeInfo<VOpenGLDevice>());
}

VOffscreenDeviceResType::~VOffscreenDeviceResType()
{
}

VRangeIterator<VTypeInfo> VOffscreenDeviceResType::CreatedTypes()
{
	return CreateBeginIterator<std::vector<VTypeInfo> >(m_ManagedTypes);
}

vbool VOffscreenDeviceResType::Generate(
	resource::VResource* in_pResource, 
	VTypeInfo in_Type)
{
	V3D_ASSERT(GetTypeInfo<VOpenGLDevice>() == in_Type);

	if(!in_pResource->ContainsData<IVRenderContext>())
	{
		VResourceDataPtr<const IVRenderContext> pContext;
		VResourceDataPtr<const VDisplaySettings> pSettings;

		try
		{
			//get Display Settings
			pSettings = in_pResource->GetData<VDisplaySettings>();

			//get the Render Context
			pContext = in_pResource->GetData<IVRenderContext>();
		}
		catch(resource::VDataNotFoundException&) 
		{
			return false;
		}

		//create OpenGL Device
		in_pResource->AddData<VOpenGLDevice>(new VOpenGLDevice(*pSettings, 
			reinterpret_cast<IVRenderContext*>(&pContext)));
	}

	return true;
}
//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------