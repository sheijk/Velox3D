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
public:
	virtual VMeshBase* CreateMesh(
		const VMeshDescription& in_MeshDescr,
		MeshCreationFlags in_Flags,
		IVMaterial* in_pMaterial
		);
};

//-----------------------------------------------------------------------------
} //namespace graphics
} //namespace v3d
//-----------------------------------------------------------------------------

#endif //V3D_VIMMEDIATERENDERMETHOD_H