//-----------------------------------------------------------------------------
#include "VOpenGLIndexRenderMethod.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
VOpenGLIndexMesh* VOpenGLIndexRenderMethod::CreateMesh(
	VMeshDescription& in_MeshDescr)
{
	//TODO: was wenn new scheitert? -ins
	//TODO: wer released den mem???
	VOpenGLIndexMesh* pMesh = new VOpenGLIndexMesh(in_MeshDescr);
	return pMesh;
}
//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------