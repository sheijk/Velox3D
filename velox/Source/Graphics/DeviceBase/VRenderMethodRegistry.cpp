#include "VRenderMethodRegistry.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

VRenderMethodRegistry::VRenderMethodRegistry()
{
}

VRenderMethodRegistry::~VRenderMethodRegistry()
{
}

void VRenderMethodRegistry::RegisterRenderMethod(
	IVRenderMethod& in_RenderMethod)
{
	V3D_ASSERT(&in_RenderMethod != 0);

	m_RenderMethods.push_front(&in_RenderMethod);
}

VMeshBase* VRenderMethodRegistry::CreateMesh(
	const VMeshDescription& in_MeshDescr, 
	MeshCreationFlags in_Flags,
	IVMaterial* in_pMaterial
	)
{
	V3D_ASSERT(in_pMaterial != 0);

	// select appropriate rendering method
	IVRenderMethod& renderMethod = * m_RenderMethods.front();

	// create mesh for it
	return renderMethod.CreateMesh(in_MeshDescr, in_Flags, in_pMaterial);
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
