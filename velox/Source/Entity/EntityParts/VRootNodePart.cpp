#include <v3dlib/EntityParts/VRootNodePart.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VRootNodePart::VRootNodePart()
{
	m_Transform = VRBTransform();
}

void VSceneGraphPart::Update()
{
	for(std::list<VSceneGraphPart*>::iterator iter = m_pChilds.begin();
		iter != m_pChilds.end();
		++iter)
	{
		(*iter)->Update();
	}
}

void VSceneGraphPart::SetParent(VSceneGraphPart* in_pParent)
{
}

void VSceneGraphPart::Activate()
{
}

void VSceneGraphPart::Deactivate()
{
}

VRBTransform VSceneGraphPart::GetAbsoluteTransform()
{
	return m_Transform;
}


//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------
