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

void VRenderMethodRegistry::RegisterRenderMethod(IVRenderMethod& in_RenderMethod)
{
	m_RenderMethods.push_back(&in_RenderMethod);
}

VBaseMesh* VRenderMethodRegistry::CreateMesh(
	VMeshDescription& in_MeshDescr, 
	MeshCreationFlags in_Flags
	)
{
	// select appropriate rendering method
	IVRenderMethod& renderMethod = * m_RenderMethods.front();

	// create mesh for it
	return renderMethod.CreateMesh(in_MeshDescr);
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
