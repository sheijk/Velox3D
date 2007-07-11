/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#ifndef V3D_VNODE_2007_05_18_H
#define V3D_VNODE_2007_05_18_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Core/VTypeInfo.h>
#include <V3d/Core/RangeIter.h>

#include <V3d/Tags/VTag.h>

#include <vector>
//-----------------------------------------------------------------------------
namespace v3d {
	namespace xml {
		class IVXMLElement;
	}

	namespace messaging {
		class VMessage;
		class VMessageInterpreter;
	}
}

namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VNode;

class VNodeDependency
{
public:
	enum Condition { Optional, Mandatory };

	Condition GetCondition() const { return m_Condition; }
	const VTypeInfo& GetTypeInfo() const { return *m_pTypeInfo; }
	VNode* GetTarget() const { return m_pTarget; }

protected:
	VNodeDependency(
		Condition condition, 
		const VTypeInfo& typeInfo, 
		VNode* pContainedIn);

	void RegisterAt(VNode* pNode);

private:
	vbool Connect(VNode* pStartNode);
	void Disconnect();
	friend class VNode;

	Condition m_Condition;
	const VTypeInfo* m_pTypeInfo;
	VNode* m_pTarget;
};

template<typename TargetType>
class VNodeConnection : public VNodeDependency
{
public:
	VNodeConnection(
		Condition condition,
		VNode* pContainedIn)
	: VNodeDependency( 
		condition, 
		::v3d::GetTypeInfo<TargetType>(), pContainedIn )
	{}

	VNodeConnection(VNode* pContainedIn) 
	: VNodeDependency( 
		Mandatory, 
		::v3d::GetTypeInfo<TargetType>(), pContainedIn )
	{}

	TargetType* Get() const
	{ 
		return reinterpret_cast<TargetType*>( GetTarget() ); 
	}

	TargetType* operator->() const
	{
		return Get();
	}

	vbool IsConnected() const 
	{
		return GetTarget() != 0;
	}
};

/**
 * A node is the basic block of the velox entity system (scene graph). 
 * You can find an introduction to the entity in the velox trac at
 * http://www.sechsta-sinn.de/velox
 *
 * Nodes can receive message using the Send method.
 *
 * A node can provide properties which have a name and a value. These are
 * automatically serialized in the Load/Save methods and can be edited by the
 * velox editor. If a class provides properties it has to override the methods
 * GetMessageInterpreterForClass and SetupProperties. For the first one simply
 * copy the implementation in VNode.cpp to your new class (the message
 * interpreter is specific for a class, so every class needs to provide it's
 * own one). To provide properties, use the AddOption methods in
 * VMessageInterpreter in SetupProperties. Be sure to call the method for
 * super to get super classes' properties
 *
 * @author sheijk
 *
 * @see IVPart
 * @see VEntity
 */
class VNode
{
public:
	VNode();
	virtual ~VNode();

	virtual void Load(const xml::IVXMLElement& in_Element);
	virtual void Save(xml::IVXMLElement& in_Element);

	enum ActivationResult { ActivatedAll, ActivatedSome, ActivatedNone };

	/** When called, the part has to register itself to it's subsystem */
	ActivationResult Activate();

	/** When called, the part has to unregister itself from it's subsystem */
	void Deactivate();

	enum State { NotInScene, Inactive, Active };

	State GetState() const;
	static std::string StateName(State state);

	/// child nodes

	virtual VRangeIterator<VNode> ChildIterator();
	virtual VRangeIterator<const VNode> ChildIterator() const;
	virtual VRangeIterator< VSharedPtr<VNode> > ChildPtrIterator();

	virtual void Add( VSharedPtr<VNode> node, vint pos = -1 );
	virtual void Remove( VSharedPtr<VNode> node );

	/** returns the first child of the given type or 0 */
	VNode* GetFirst(const std::string& in_strType);

	template<typename NodeType>
	NodeType* GetFirst();

	/// type information

	/** Return information about the type of the part */
	virtual const VTypeInfo& GetTypeInfo() const = 0;

	template<typename T>
	vbool IsOfType() const;

	/** Returns 0 if part could not be converted */
	template<typename T>
	const T* Convert() const;

	/** Returns 0 if part could not be converted */
	template<typename T>
	T* Convert();

	/// messaging

	/** Send a message to the part. Used by the serialization manager, the
	* editor and maybe in the future to notify parts about events */
	void Send(const messaging::VMessage& in_Message, 
		messaging::VMessage* in_pAnswer = 0);

	/// connections
	VRangeIterator<VNodeDependency> Connections();
	VNode* GetParent();

	/// misc

	void DumpInfo(const std::string& prefix = "") const;

	std::string GetName() const;
	void SetName(const std::string& in_strName);

	/// tags

	void AttachTag(const tags::VTag& tag);
	void RemoveTag(const tags::VTag& tag);
	vbool HasTag(const tags::VTag& tag) const;
	VRangeIterator<const tags::VTag> Tags() const;

private:
	VNode* m_pParent;

	std::string m_strName;

	std::vector<const tags::VTag*> m_Tags;

protected:
	void AddConnection(VNodeDependency* connection);
	friend class VNodeDependency;

	void DisconnectAll();

	VNode* RegisterTo();
private:
	/** 
	* Each node class needs it's own message interpreter, return the correct
	* one for this classes instance
	*/
	virtual messaging::VMessageInterpreter* GetMessageInterpreterForClass();

	typedef std::vector< VSharedPtr<VNode> > NodeSequence;
	NodeSequence m_ChildNodes;

	typedef std::vector<VNodeDependency*> ConnectionSequence;
	ConnectionSequence m_Connections;

	State m_State;

protected:
	NodeSequence::iterator FindChildNode(VNode* node);

	virtual void SetupProperties(messaging::VMessageInterpreter& interpreter);

	virtual void OnMessage(const messaging::VMessage& in_Message, 
		messaging::VMessage* in_pAnswer = 0);

	virtual void OnActivate();
	virtual void OnDeactivate();

	std::string ShortInfo() const;
};

//-----------------------------------------------------------------------------

template<typename T>
vbool VNode::IsOfType() const
{
	return GetTypeInfo().CanBeCastedTo(GetCompileTimeTypeInfo<T>(0));
	//return (typeid(*this) == typeid(T)) != 0;
}

template<typename T>
const T* VNode::Convert() const
{
	if( IsOfType<T>() )
		return reinterpret_cast<const T*>(this);
	else
		return 0;
}

template<typename T>
T* VNode::Convert()
{
	if( IsOfType<T>() )
		return reinterpret_cast<T*>(this);
	else
		return 0;
}

template<typename PartType>
PartType* VNode::GetFirst()
{
	VNode* part = GetFirst( 
		v3d::GetTypeInfo<PartType>().GetName() );

	if( part != 0 && part->IsOfType<PartType>() )
	{
		return part->Convert<PartType>();
	}
	else
	{
		return 0;
	}
}

//-----------------------------------------------------------------------------
}
} // namespace v3d::entity
V3D_TYPEINFO( v3d::entity::VNode );
//-----------------------------------------------------------------------------
#endif // V3D_VNODE_2007_05_18_H

