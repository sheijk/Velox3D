#ifndef V3D_VTRANSFORMNODE_H
#define V3D_VTRANSFORMNODE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <v3d/Math/VMatrix.h>
#include "VNodeBase.h"
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
namespace simplesg {
//-----------------------------------------------------------------------------
using namespace v3d;

/**
 * Does a simple matrix transformation. Use this for translation, rotation
 * etc.
 *
 * @author sheijk
 */
class VTransformNode : public VNodeBase
{
	Matrix44f m_Transform;

public:
	VTransformNode(const Matrix44f& in_Transform);

	virtual void ApplyTransformation(Matrix44f* io_pMatrix);
	virtual void SetAbsoluteTransformation(const Matrix44f& in_Matrix);

protected:
	virtual void RemoveThis(drawlist::IVDrawList* in_pDrawList);
	virtual void CullThis(drawlist::IVDrawList* in_pDrawList, IVCamera*);
};

//-----------------------------------------------------------------------------
} // namespace simplesg
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VTRANSFORMNODE_H
