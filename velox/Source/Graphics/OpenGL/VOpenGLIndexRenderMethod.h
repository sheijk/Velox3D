//-----------------------------------------------------------------------------
#ifndef V3D_VOPENGLINDEXRENDERMETHOD_H
#define V3D_VOPENGLINDEXRENDERMETHOD_H
//-----------------------------------------------------------------------------
#include "VOpenGLIndexMesh.h"
#include "../DeviceBase/VRenderMethodRegistry.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * Simplest rendering method. Renders using glBegin, glVertex.. etc
 *
 * @author ins
 */

class VOpenGLIndexRenderMethod : public IVRenderMethod
{
	virtual VOpenGLIndexMesh* CreateMesh(VMeshDescription& in_MeshDescr);
};

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------

#endif //V3D_VOPENGLINDEXRENDERMETHOD_H