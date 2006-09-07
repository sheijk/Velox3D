/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#ifndef V3D_VNODEBASE_H
#define V3D_VNODEBASE_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <V3d/Graphics/SimpleSG/IVNode.h>
#include <list>

//-----------------------------------------------------------------------------
namespace v3d {
namespace graphics {
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
		IVDrawList* in_pDrawList, 
		IVCamera*);

	virtual void Remove(IVDrawList* in_pDrawList);

	virtual void SetParent(IVNode* in_pNode);
	virtual void AddChild(IVNode* in_pChild);
	virtual void DeleteChild(IVNode* in_pChild);
	//virtual void AddIntoFrameList(drawlist::IVDrawList* in_pDrawlist);

	virtual NodeIterator ChildsBegin();
	virtual NodeIterator ChildsEnd();

protected:
	typedef std::list<IVNode*> NodeList;

	//typedef VSTLDerefIteratorPol<NodeList::iterator, IVNode> IterPol;

	virtual void RemoveThis(IVDrawList* in_pDrawList) = 0;
	virtual void CullThis(IVDrawList* in_pDrawList, IVCamera*) = 0;

    IVNode* m_pParent;
	NodeList m_NodeList;
	// used a VString for faster conversion to c-string than with std::string
	VString m_strName;
};

//-----------------------------------------------------------------------------
} // namespace graphics
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VNODEBASE_H

