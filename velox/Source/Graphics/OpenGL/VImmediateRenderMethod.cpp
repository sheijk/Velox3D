//-----------------------------------------------------------------------------
#include "VImmediateRenderMethod.h"

#include "VOpenGLVertexMesh.h"
#include "VOpenGLIndexMesh.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
VBaseMesh* VImmediateRenderMethod::CreateMesh(
	VMeshDescription& in_MeshDescr)
{
	//TODO: was wenn new scheitert? -ins dann stuertzt es halt ab -- sheijk

	VBaseMesh* pMesh = 0;

	// on indexed mode
	if( in_MeshDescr.triangleIndices.hBuffer != 0 )
	{
		pMesh = new VOpenGLIndexMesh(in_MeshDescr);
	}
	// on non indexed mode
	else
	{
		pMesh = new VOpenGLVertexMesh(in_MeshDescr);
	}

	return pMesh;
}
//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------