#ifndef V3D_IVMESH_H
#define V3D_IVMESH_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * A handle for a mesh loaded in the device
 *
 * @author sheijk/insane
 */
class IVMesh
{
public:
	virtual ~IVMesh() {};
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVMESH_H
