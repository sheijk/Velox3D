//-----------------------------------------------------------------------------
#ifndef V3D_VIMMEDIATERENDERMETHOD_H
#define V3D_VIMMEDIATERENDERMETHOD_H
//-----------------------------------------------------------------------------
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

class VImmediateRenderMethod : public IVRenderMethod
{
	virtual VBaseMesh* CreateMesh(VMeshDescription& in_MeshDescr);
};

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------

#endif //V3D_VIMMEDIATERENDERMETHOD_H