#include <v3d/Utils/Graphics/SimpleSG/VSceneGraphTools.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics{
namespace simplesg {
//-----------------------------------------------------------------------------
using namespace v3d;

void UpdateLocations(
					 v3d::graphics::simplesg::IVNode* in_pNode, 
					 const VMatrix44f& in_Transform
					 )
{
	v3d::graphics::simplesg::IVNode::NodeIterator child = in_pNode->ChildsBegin();

	for( ; child != in_pNode->ChildsEnd(); ++child)
	{
		VMatrix44f mat = in_Transform;
		child->ApplyTransformation(&mat);
		child->SetAbsoluteTransformation(mat);
		UpdateLocations(&*child, mat);
	}
}

//-----------------------------------------------------------------------------
} // namespace simplesg
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
