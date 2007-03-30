/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include "VPBufferTextureResType.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
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
	//V3D_ASSERT(GetTypeInfo<VPBufferTexture>() == in_Type);

	VResourceDataPtr<IVRenderContext> pContextData;

	try
	{
		//get Pixel Buffer Context
		pContextData = in_pResource->GetMutableData<IVRenderContext>();
		//pContextData = in_pResource->GetData<IVRenderContext>();
		//pContext = const_cast<IVRenderContext*>(&*pContextData);
	}
	catch(resource::VDataNotFoundException&) 
	{
		return false;
	}

	in_pResource->AddData<VPBufferTexture>(
		new VPBufferTexture(static_cast<VOffscreenContextBase*>(&*pContextData)));

	return true;
}

void VPBufferTextureResType::NotifyChange(
	const VTypeInfo& in_Type, resource::VResource* in_pResource)
{
}
//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
