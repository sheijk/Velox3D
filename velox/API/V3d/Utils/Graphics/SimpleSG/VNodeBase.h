#ifndef V3D_VNODEBASE_H
#define V3D_VNODEBASE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <list>
#include <v3d/Core/Wrappers/VSTLDerefIteratorPol.h>

#include <v3d/Graphics/SimpleSG/IVNode.h>
//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
namespace simplesg {
//-----------------------------------------------------------------------------

/**
 * Abstract base class for node classes. Provides management of child and 
 * parent node.
 *
 * @author sheijk/ins
 */
class VNodeBase : public IVNode
{
public:
	VNodeBase(VStringParam in_pcName);

	virtual const vchar* GetNodeName();

	virtual void ApplyCulling(
		drawlist::IVDrawList* in_pDrawList, 
		IVCamera*);

	virtual void Remove(drawlist::IVDrawList* in_pDrawList);

	virtual void SetParent(IVNode* in_pNode);
	virtual void AddChild(IVNode* in_pChild);
	virtual void DeleteChild(IVNode* in_pChild);
	//virtual void AddIntoFrameList(drawlist::IVDrawList* in_pDrawlist);

	virtual NodeIterator ChildsBegin();
	virtual NodeIterator ChildsEnd();

protected:
	typedef std::list<IVNode*> NodeList;
	typedef VSTLDerefIteratorPol<NodeList::iterator, IVNode> IterPol;

	virtual void RemoveThis(drawlist::IVDrawList* in_pDrawList) = 0;
	virtual void CullThis(drawlist::IVDrawList* in_pDrawList, IVCamera*) = 0;

    IVNode* m_pParent;
	NodeList m_NodeList;
	// used a VString for faster conversion to c-string than with std::string
	VString m_strName;
};

//-----------------------------------------------------------------------------
} // namespace simplesg
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VNODEBASE_H
