#ifndef V3D_IVDRAWLIST_H
#define V3D_IVDRAWLIST_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Math/VMatrix.h>
#include <v3d/Graphics/IVDevice.h>
#include <V3d/Graphics/VModel.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * Holds a list of meshes and renders them. Should sort meshes by their
 * render states to gain speed
 *
 * @author sheijk
 */
struct IVDrawList
{
	typedef vuint ModelMeshId;

	virtual ~IVDrawList() {}

	virtual ModelMeshId Add(VModelMesh in_Model) = 0;
	virtual void Remove(ModelMeshId in_Model) = 0;

	virtual void Render() = 0;

	virtual IVDevice& GetDevice() = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVDRAWLIST_H
