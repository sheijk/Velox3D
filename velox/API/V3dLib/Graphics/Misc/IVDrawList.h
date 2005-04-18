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

///**
// * Holds a mesh and a material. Util class, can be removed when a mesh
// * provides access to it's associated render states.
// * (or a position matrix could be added..
// *
// * @author sheijk
// */
//struct VModel
//{
//	typedef VMatrix44f TransformMatrix;
//	typedef VPointer<TransformMatrix>::SharedPtr TransformMatrixPtr;
//
//	VModel(IVDevice::MeshHandle in_hMesh, TransformMatrixPtr in_pTransform);
//	VModel(IVDevice::MeshHandle in_hMesh);
//
//	/** the mesh to be rendered */
//	IVDevice::MeshHandle hMesh;
//
//	/** it's associated transformation (position, rotation,..) */
//	TransformMatrixPtr pTransformation;
//
//	vbool operator==(const VModel& other);
//	};

/**
 * Holds a list of meshes and renders them. Should sort meshes by their
 * render states to gain speed
 *
 * @author sheijk
 */
struct IVDrawList
{
	//typedef IVDevice::BufferHandle BufferHandle;
	//typedef IVDevice::MeshHandle MeshHandle;
	//typedef IVDevice::MaterialHandle MaterialHandle;

	virtual ~IVDrawList() {}

	virtual void Add(VModelMesh in_Model) = 0;
	//virtual void Remove(VModelMesh in_Model) = 0;

	virtual void Render() = 0;

	virtual IVDevice& GetDevice() = 0;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_IVDRAWLIST_H
