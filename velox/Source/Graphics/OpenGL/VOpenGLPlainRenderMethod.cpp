//-----------------------------------------------------------------------------
#include "VOpenGLPlainRenderMethod.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
VOpenGLVertexMesh* VOpenGLPlainRenderMethod::CreateMesh(
	VMeshDescription& in_MeshDescr)
{
	//TODO: was wenn new scheitert? -ins
	VOpenGLVertexMesh* pMesh = new VOpenGLVertexMesh(in_MeshDescr);
	return pMesh;
}
//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------