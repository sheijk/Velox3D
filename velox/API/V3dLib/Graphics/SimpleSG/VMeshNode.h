#ifndef V3D_VMESHNODE_H
#define V3D_VMESHNODE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Graphics/IVDevice.h>

#include "VNodeBase.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------

/**
 * A scenegraph node containing a renderable mesh
 *
 * @author sheijk
 */
class VMeshNode : public VNodeBase
{
public:
	VMeshNode(IVDevice::MeshHandle in_hMesh);

	virtual void ApplyTransformation(Matrix44f* io_pMatrix);
	virtual void SetAbsoluteTransformation(const Matrix44f& in_Matrix);

protected:
	virtual void RemoveThis(IVDrawList* in_pDrawList);
	virtual void CullThis(IVDrawList* in_pDrawList, IVCamera*);

private:
	vbool m_bInDrawList;
	IVDevice::MeshHandle m_hMesh;
	VModel::TransformMatrixPtr m_pAbsTransform;
	VModel m_Model;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VMESHNODE_H
