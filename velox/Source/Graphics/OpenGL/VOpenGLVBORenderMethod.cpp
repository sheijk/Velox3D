//-----------------------------------------------------------------------------
#include "VOpenGLVBORenderMethod.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

VMeshBase* VOpenGLVBORenderMethod::CreateMesh(
		const VMeshDescription& in_MeshDescr,
		MeshCreationFlags in_Flags,
		IVMaterial* in_pMaterial
		)
{
	V3D_ASSERT(in_pMaterial != 0);
	V3D_ASSERT(&in_MeshDescr != 0);

	VMeshBase* pMesh = 0;

	
	if( in_MeshDescr.triangleVertices.hBuffer != 0 )
	{

		pMesh = new VOpenGLVBOMesh(in_MeshDescr, in_pMaterial);
	}

	V3D_ASSERT(pMesh != 0);

	return pMesh;

}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------

