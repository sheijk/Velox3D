#include <V3dLib/Graphics/SimpleSG/VNodeBase.h>
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
#include <functional>

using namespace std;
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
//-----------------------------------------------------------------------------
VNodeBase::VNodeBase(VStringParam in_pcName)
{
	m_pParent = 0;
	m_strName = in_pcName;
}

const vchar* VNodeBase::GetNodeName()
{
	return m_strName.AsCString();
}

void VNodeBase::SetParent(IVNode* in_pNode)
{
	m_pParent = in_pNode;
}

void VNodeBase::AddChild(IVNode* in_pNode)
{
	m_NodeList.push_back(in_pNode);
}

void VNodeBase::DeleteChild(IVNode* in_pNode)
{
	m_NodeList.remove(in_pNode);
}

VNodeBase::NodeIterator VNodeBase::ChildsBegin()
{
	return NodeIterator(new IterPol(m_NodeList.begin()));
}

VNodeBase::NodeIterator VNodeBase::ChildsEnd()
{
	return NodeIterator(new IterPol(m_NodeList.end()));
}

class VCullNode
{
	IVDrawList* m_pDrawList;
	IVCamera* m_pCamera;

public:
	VCullNode(IVDrawList* in_pDrawList, IVCamera* in_pCamera) :
		m_pDrawList(in_pDrawList), m_pCamera(in_pCamera)
	{}

	void operator()(IVNode* in_pNode) const
	{
		in_pNode->ApplyCulling(m_pDrawList, m_pCamera);
	}
};

void VNodeBase::ApplyCulling(
	IVDrawList* in_pDrawList, 
	IVCamera* in_pCamera)
{
	// cull the node
	CullThis(in_pDrawList, in_pCamera);

	// let all childs cull themselves
	std::for_each(
		m_NodeList.begin(), 
		m_NodeList.end(), 
		VCullNode(in_pDrawList, in_pCamera)
		);

	//for(
	//	NodeList::iterator child = m_NodeList.begin(); 
	//	child != m_NodeList.end();
	//	++child)
	//{
	//	(*child)->ApplyCulling(in_pDrawList, in_pCamera);
	//}
}

class VRemoveGeometry
{
	IVDrawList* m_pDrawList;
public:
	VRemoveGeometry(IVDrawList* in_pDrawList) :
		m_pDrawList(in_pDrawList)
	{}

	void operator()(IVNode* in_pNode) const
	{
		in_pNode->Remove(m_pDrawList);
	}
};

void VNodeBase::Remove(IVDrawList* in_pDrawList)
{
	// remove the node's geometry
	RemoveThis(in_pDrawList);

	// let the childs remove their geometry
	for_each(
		m_NodeList.begin(),
		m_NodeList.end(),
		VRemoveGeometry(in_pDrawList)
		);

	//for(
	//	NodeList::iterator child = m_NodeList.begin(); 
	//	child != m_NodeList.end();
	//	++child)
	//{
	//	(*child)->Remove(in_pDrawList);
	//}
}

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
