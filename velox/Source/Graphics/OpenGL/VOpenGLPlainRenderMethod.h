//-----------------------------------------------------------------------------
#ifndef V3D_VOPENGLPLAINRENDERMETHOD_H
#define V3D_VOPENGLPLAINRENDERMETHOD_H
//-----------------------------------------------------------------------------
#include "VOpenGLVertexMesh.h"
#include "../DeviceBase/VRenderMethodRegistry.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * Simplest rendering method. Renders using glBegin, glVertex.. etc
 *
 * @author sheijk
 */

class VOpenGLPlainRenderMethod : public IVRenderMethod
{
	virtual VOpenGLVertexMesh* CreateMesh(VMeshDescription& in_MeshDescr);
};

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------

#endif //V3D_VOPENGLPLAINRENDERMETHOD_H