#include <V3d/Scene/VMeshPart.h>
//-----------------------------------------------------------------------------

#include <V3d/Resource.h>
#include <V3d/Graphics/IVMesh.h>
#include <V3d/Graphics/IVDevice.h>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace scene {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

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

//-----------------------------------------------------------------------------
}} // namespace v3d::scene
//-----------------------------------------------------------------------------
