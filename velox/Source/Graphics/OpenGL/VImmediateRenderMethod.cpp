//-----------------------------------------------------------------------------
#include "VImmediateRenderMethod.h"

#include "VOpenGLVertexMesh.h"
#include "VOpenGLIndexMesh.h"

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
VMeshBase* VImmediateRenderMethod::CreateMesh(
	const VMeshDescription& in_MeshDescr,
	MeshCreationFlags in_Flags,
	std::vector<IVMaterial*> in_Materials
	)
{
	for(vuint matid = 0; matid < in_Materials.size(); ++matid)
	{
		V3D_ASSERT(in_Materials[matid] != 0);
	}

	V3D_ASSERT(&in_MeshDescr != 0);

	VMeshBase* pMesh = 0;

	// on indexed mode
	if( in_MeshDescr.GetIndexBuffer() != 0)
	//if( in_MeshDescr.triangleIndices.hBuffer != 0 )
	{
		pMesh = new VOpenGLIndexMesh(in_MeshDescr, in_Materials);
	}
	// on non indexed mode
	else
	{
		pMesh = new VOpenGLVertexMesh(in_MeshDescr, in_Materials);
	}

	V3D_ASSERT(pMesh != 0);

	return pMesh;
}
//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------