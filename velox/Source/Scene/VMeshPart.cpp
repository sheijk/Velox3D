/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Scene/VMeshPart.h>
//-----------------------------------------------------------------------------

#include <V3d/Resource.h>
#include <V3d/Graphics/IVMesh.h>
#include <V3d/Graphics/IVDevice.h>

#include <V3d/Entity/VGenericPartParser.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VMeshPart::VMeshPart() :
	VMeshPartBase(graphics::IVDevice::GetDefaultMaterial())
{
}

VMeshPart::VMeshPart(
		  resource::VResourceDataPtr<const graphics::IVMesh> in_hMesh,
		  resource::VResourceDataPtr<const graphics::IVMaterial> in_hMaterial
		  )
	: VMeshPartBase(in_hMaterial)
{
	m_hMesh = in_hMesh;
}

VMeshPart::VMeshPart(
		  const std::string& in_strMeshResource,
		  const std::string& in_strMaterialResource
		  )
	: VMeshPartBase(in_strMaterialResource)
{
	m_hMesh = resource::GetResourceData<graphics::IVMesh>(in_strMeshResource.c_str());
}

void VMeshPart::SendGeometry(graphics::IVDevice& in_Device) const
{
	in_Device.RenderMesh(&*m_hMesh);
}

V3D_REGISTER_PART_PARSER(VMeshPart);
//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------

