#include <v3d/Utils/Graphics/SimpleSG/VTransformNode.h>
//-----------------------------------------------------------------------------
#include <v3d/Math/VMatrixOps.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
namespace simplesg {
//-----------------------------------------------------------------------------

VTransformNode::VTransformNode(const Matrix44f& in_Transform)
	:
	VNodeBase("transform"),
	m_Transform(in_Transform)
{
}

void VTransformNode::ApplyTransformation(Matrix44f* io_pMatrix)
{
	// apply transformation
	Mult(*io_pMatrix, *io_pMatrix, m_Transform);
}

void VTransformNode::SetAbsoluteTransformation(const Matrix44f& in_Matrix)
{
	// a transform node doesn't need any knowledge about it's position..
}

void VTransformNode::RemoveThis(drawlist::IVDrawList* in_pDrawList)
{
	// no geometry to remove here (geometry of childs is removed
	// by VNodeBase::Remove
}

void VTransformNode::CullThis(drawlist::IVDrawList* in_pDrawList, IVCamera*)
{
	// nothing to do here. child's geometry will be culled by
	// VNodeBase::ApplyCulling
}

//-----------------------------------------------------------------------------
} // namespace simplesg
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------