#include <V3dLib/Graphics/SimpleSG/VSceneGraphTools.h>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics{
//-----------------------------------------------------------------------------
using namespace v3d;

void UpdateLocations(
					 v3d::graphics::IVNode* in_pNode, 
					 const VMatrix44f& in_Transform
					 )
{
	v3d::graphics::IVNode::NodeIterator child = in_pNode->ChildsBegin();

	for( ; child != in_pNode->ChildsEnd(); ++child)
	{
		VMatrix44f mat = in_Transform;
		child->ApplyTransformation(&mat);
		child->SetAbsoluteTransformation(mat);
		UpdateLocations(&*child, mat);
	}
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
