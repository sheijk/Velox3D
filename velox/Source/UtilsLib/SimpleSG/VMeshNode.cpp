#include <V3dLib/Graphics/SimpleSG/VMeshNode.h>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
VMeshNode::VMeshNode(IVDevice::MeshHandle in_hMesh)
	:
	VNodeBase("mesh"),
	m_pAbsTransform(new VMatrix44f()),
	m_Model(in_hMesh, m_pAbsTransform),
	m_hMesh(in_hMesh),
	m_bInDrawList(false)
{
	V3D_ASSERT(in_hMesh != 0);
}

void VMeshNode::ApplyTransformation(Matrix44f* io_pMatrix)
{
	// simulate a transformation by the unit matrix ;)
}

void VMeshNode::SetAbsoluteTransformation(const Matrix44f& in_Matrix)
{
	*m_pAbsTransform = in_Matrix;
	//TODO: store it and tell the drawlist
	//(add a shared ptr to the matrix to drawlist::VModel?)
}

void VMeshNode::CullThis(IVDrawList* in_pDrawList, IVCamera*)
{
	if( !m_bInDrawList )
	{
		in_pDrawList->Add(m_Model);
		m_bInDrawList = true;
	}
}

void VMeshNode::RemoveThis(IVDrawList* in_pDrawList)
{
	if( m_bInDrawList )
	{
		in_pDrawList->Remove(m_Model);
		m_bInDrawList = false;
	}
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
