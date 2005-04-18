#ifndef V3D_IVMESH_H
#define V3D_IVMESH_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
class IVMaterial;

/**
 * A handle for a mesh loaded in the device
 *
 * @author sheijk
 */
class IVMesh
{
public:
	virtual ~IVMesh() {};

	//virtual vuint GetMaterialCount() const = 0;
	//virtual IVMaterial& GetMaterial(vuint in_nMaterialId) = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVMESH_H
