#include "VRenderMethodRegistry.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
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
	std::vector<IVMaterial*> in_Materials
	)
{
	for(vuint matid = 0; matid < in_Materials.size(); ++matid)
	{
		V3D_ASSERT(in_Materials[matid] != 0);
	}

	// select appropriate rendering method
	IVRenderMethod& renderMethod = * m_RenderMethods.front();

	// create mesh for it
	VMeshBase* pMesh = renderMethod.CreateMesh(in_MeshDescr, in_Flags, in_Materials);
	pMesh->SetBuffers(in_MeshDescr.GetAllBuffers());

	return pMesh;
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
