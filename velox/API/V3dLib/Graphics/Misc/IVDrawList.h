#ifndef V3D_IVDRAWLIST_H
#define V3D_IVDRAWLIST_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Math/VMatrix.h>
#include <v3d/Graphics/IVDevice.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * Holds a mesh and a material. Util class, can be removed when a mesh
 * provides access to it's associated render states.
 * (or a position matrix could be added..
 *
 * @author sheijk
 */
struct VModel
{
	typedef VMatrix44f TransformMatrix;
	typedef VPointer<TransformMatrix>::SharedPtr TransformMatrixPtr;

	/** the mesh to be rendered */
	IVDevice::MeshHandle hMesh;

	/** it's associated transformation (position, rotation,..) */
	TransformMatrixPtr pTransformation;

	VModel(
		IVDevice::MeshHandle in_hMesh,
		TransformMatrixPtr in_pTransform
		):
		hMesh(in_hMesh),
		pTransformation(in_pTransform)
	{
	}

	vbool operator==(const VModel& other)
	{
		return (hMesh == other.hMesh);
	}
};

/**
 * Holds a list of meshes and renders them. Should sort meshes by their
 * render states to gain speed
 *
 * @author sheijk
 */
struct IVDrawList
{
	typedef IVDevice::BufferHandle BufferHandle;
	typedef IVDevice::MeshHandle MeshHandle;
	typedef IVDevice::MaterialHandle MaterialHandle;

	virtual ~IVDrawList() {}

	virtual void Add(VModel in_Model) = 0;
	virtual void Remove(VModel in_Model) = 0;

	virtual void Render() = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVDRAWLIST_H
