//-----------------------------------------------------------------------------
#include "VImmediateRenderMethod.h"

#include "VOpenGLVertexMesh.h"
#include "VOpenGLIndexMesh.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
VMeshBase* VImmediateRenderMethod::CreateMesh(
	const VMeshDescription& in_MeshDescr,
	MeshCreationFlags in_Flags,
	IVMaterial* in_pMaterial
	)
{
	V3D_ASSERT(in_pMaterial != 0);
	V3D_ASSERT(&in_MeshDescr != 0);

	VMeshBase* pMesh = 0;

	// on indexed mode
	if( in_MeshDescr.triangleIndices.hBuffer != 0 )
	{
		pMesh = new VOpenGLIndexMesh(in_MeshDescr, in_pMaterial);
	}
	// on non indexed mode
	else
	{
		pMesh = new VOpenGLVertexMesh(in_MeshDescr, in_pMaterial);
	}

	V3D_ASSERT(pMesh != 0);

	return pMesh;
}
//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------