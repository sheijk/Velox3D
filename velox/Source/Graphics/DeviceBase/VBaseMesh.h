#ifndef V3D_VBASEMESH_H
#define V3D_VBASEMESH_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/IVMesh.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * Interface for alle meshes...
 *
 * @author sheijk
 */
class VBaseMesh : public IVMesh
{
public:
	virtual void Render() = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VBASEMESH_H
