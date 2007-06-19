/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#include <V3d/Entity/VNode.h>
//-----------------------------------------------------------------------------

#include <V3d/Core/VIOStream.h>
#include <V3d/Core/VLogging.h>
#include <V3d/Messaging/VMessageInterpreter.h>
#include <V3d/Entity/VEntityExceptions.h>
#include <V3d/XML/IVXMLElement.h>
#include <V3d/XML/IVXMLNode.h>
#include <V3d/Tags/VTagRegistry.h>
#include <V3d/Entity/IVEntitySerializationService.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

namespace {
	template<typename T>
	void Set(messaging::VMessage* msg, const std::string& name, const T& value)
	{
		if( msg->HasProperty(name) )
			msg->Set(name, utils::VStringValue(value));
		else
			msg->AddProperty(name, value);
	}
}

//-----------------------------------------------------------------------------

namespace {
	VNode* Find(const VTypeInfo& typeInfo, VNode* startNode, VNode* sourceNode)
	{
		if( startNode != 0 )
		{
			VNode* found = 0;

			VRangeIterator<VNode> child = startNode->ChildIterator();
			while( child.HasNext() )
			{
				if( &*child == sourceNode )
				{
					if( found != 0 )
						return found;
					else
						return Find( typeInfo, startNode->GetParent(), sourceNode );
				}

				if( child->GetTypeInfo().CanBeCastedTo(typeInfo) )
					found = &*child;

				++child;
			}

			if( found != 0 )
				return found;
			else
				return Find( typeInfo, startNode->GetParent(), sourceNode );
		}
		else
		{
			return 0;
		}
	}
}

VNodeDependency::VNodeDependency(
	Condition condition, 
	const VTypeInfo& typeInfo,
	VNode* pContainedIn)
{
	m_Condition = condition;
	m_pTypeInfo = & typeInfo;
	m_pTarget = 0;

	RegisterAt( pContainedIn );
}

void VNodeDependency::RegisterAt(VNode* pNode)
{
	pNode->AddConnection( this );
}

vbool VNodeDependency::Connect(VNode* pStartNode)
{
	m_pTarget = Find( GetTypeInfo(), pStartNode->GetParent(), pStartNode );

	return GetCondition() == Optional || m_pTarget != 0;
}

void VNodeDependency::Disconnect()
{
	m_pTarget = 0;
}

VNode* VNode::GetParent()
{
	return m_pParent;
}

//-----------------------------------------------------------------------------

/**
 * standard c'tor
 */
VNode::VNode()
{
	m_State = NotInScene;
	m_pParent = 0;
}

/**
 * d'tor
 */
VNode::~VNode()
{
	if( m_State != NotInScene )
	{
		V3D_LOGLN( "Warning, node is deleted while being in scene! 0x" << this
			<< ", state = " << StateName(m_State) );
	}

	while( ChildPtrIterator().HasNext() )
	{
		Remove( *ChildPtrIterator() );
	}
}

/// child nodes

void VNode::Add( VSharedPtr<VNode> node, vint pos )
{
	if( node->GetState() == NotInScene )
	{
		if( pos < 0 )
			pos = vint( m_ChildNodes.size() );

		NodeSequence::iterator insertPos = m_ChildNodes.begin();
		std::advance( insertPos, pos );

		m_ChildNodes.insert( insertPos, node );

		node->m_State = Inactive;
		node->m_pParent = this;
	}
	else
	{
		V3D_THROWMSG( VEntityException, 
			"Added node to scene which has an invalid state. " 
			<< "Inserted: " << node->ShortInfo()
			<< " To: " << this->ShortInfo() );
	}
}

void VNode::Remove( VSharedPtr<VNode> node )
{
	if( node->GetState() == Inactive )
	{
		m_ChildNodes.erase( FindChildNode(node.Get()) );
		node->m_pParent = 0;
		node->m_State = NotInScene;
	}
	else
	{
		V3D_THROWMSG( VEntityException, 
			"Removed node from scene which was not inactive: " 
			<< node->ShortInfo() << " (from " << this->ShortInfo() << ")" );
	}
}

VNode::NodeSequence::iterator VNode::FindChildNode(VNode* searchedNode)
{
	const NodeSequence::iterator childNodesEnd = m_ChildNodes.end();
	for(NodeSequence::iterator iter = m_ChildNodes.begin();
		iter != childNodesEnd;
		++iter)
	{
		VSharedPtr<VNode> node = *iter;

		if( node == searchedNode )
			return iter;
	}

	return childNodesEnd;
}


VRangeIterator<VNode> VNode::ChildIterator()
{
	return CreateDerefBeginIterator<VNode>( m_ChildNodes );
}

VRangeIterator<const VNode> VNode::ChildIterator() const
{
	return CreateDerefBeginIterator<const VNode>( m_ChildNodes );
}

VRangeIterator< VSharedPtr<VNode> > VNode::ChildPtrIterator()
{
	return CreateBeginIterator( m_ChildNodes );
}

VNode* VNode::RegisterTo()
{
	return this;
}

VNode* VNode::GetFirst(const std::string& in_strType)
{
	VRangeIterator<VNode> node = ChildIterator();
	while( node.HasNext() )
	{
		if( node->GetTypeInfo().CanBeCastedTo(in_strType) )
			return &*node;

		++node;
	}

	return 0;
}

/// (de)activation

VRangeIterator<VNodeDependency> VNode::Connections()
{
	return CreateDerefBeginIterator<VNodeDependency>( m_Connections );
}

void VNode::AddConnection(VNodeDependency* connection)
{
	m_Connections.push_back( connection );
}

void VNode::DisconnectAll()
{
	VRangeIterator<VNodeDependency> dep = Connections();
	while( dep.HasNext() )
	{
		dep->Disconnect();

		++dep;
	}
}

VNode::ActivationResult VNode::Activate()
{
	VRangeIterator<VNodeDependency> dep = Connections();
	while( dep.HasNext() )
	{
		if( ! dep->Connect( this ) )
		{
			Deactivate();

			return ActivatedNone;
		}

		++dep;
	}

	ActivationResult result = ActivatedAll;

	VRangeIterator<VNode> child = ChildIterator();
	while( child.HasNext() )
	{
		if( child->Activate() != ActivatedAll )
		{
			result = ActivatedSome;
		}

		++child;
	}

	OnActivate();
	m_State = Active;

	return result;
}

void VNode::Deactivate()
{
	if( GetState() == Active )
		OnDeactivate();

	VRangeIterator<VNode> child = ChildIterator();
	while( child.HasNext() )
	{
		child->Deactivate();

		++child;
	}

	DisconnectAll();

	m_State = Inactive;
}

void VNode::OnActivate()
{
}

void VNode::OnDeactivate()
{
}

VNode::State VNode::GetState() const
{
	return m_State;
}

std::string VNode::StateName(State state)
{
	switch( state )
	{
	case NotInScene: return "NotInScene";
	case Inactive: return "Inactive";
	case Active: return "Active";
	default: return "InvalidStateValue";
	}
}

std::string VNode::ShortInfo() const
{
	std::stringstream stream;
	stream << "( 0x" << this << ", state = " << StateName(m_State) << " )";
	return stream.str();
}

/// messages

void VNode::SetupProperties(messaging::VMessageInterpreter& interpreter)
{
	// Override in classes which have properties, add the classes' properties 
	// and call super.SetupProperties

	interpreter.AddAccessorOption<VNode, std::string>("name", &VNode::GetName, &VNode::SetName);
}

messaging::VMessageInterpreter* VNode::GetMessageInterpreterForClass()
{
	// this method will need to be put into each class providing properties
	static messaging::VMessageInterpreter interpreter;

	return &interpreter;
}

void VNode::OnMessage(
	const messaging::VMessage& in_Message, 
	messaging::VMessage* in_pAnswer)
{
	messaging::VMessageInterpreter* interpreter = GetMessageInterpreterForClass();

	if( interpreter != 0 )
	{
		if( ! interpreter->IsInitialized() )
		{
			SetupProperties( *interpreter );
		}

		interpreter->HandleMessage(this, in_Message, in_pAnswer);
	}
}

void VNode::Send(
	const messaging::VMessage& in_Message, 
	messaging::VMessage* in_pAnswer)
{
	try 
	{
		OnMessage(in_Message, in_pAnswer);
	}
	catch(VException& e)
	{
		if( in_pAnswer != 0 )
		{
			Set(in_pAnswer, "catched-exception", "true");
			Set(in_pAnswer, "exception-message", e.GetErrorString());
			Set(in_pAnswer, "exception-file", e.GetErrorFile());
			Set(in_pAnswer, "exception-line", e.GetErrorLine());
		}
		else
		{
			vout << "Exception when sending message to part:\n"
				<< in_Message.ToString()
				<< e.ToString();
		}
	}
}

std::string VNode::GetName() const
{
	return m_strName;
}

void VNode::SetName(const std::string& in_TrName)
{
	m_strName = in_TrName;
}


namespace {
	void PrintPartSettings(const VNode& in_Part, const std::string& prefix)
	{
		using messaging::VMessage;

		VNode& part = const_cast<VNode&>(in_Part);

		VMessage request;
		request.AddProperty("type", "getSettings");
		VMessage answer;

		part.Send(request, &answer);

		VRangeIterator<const std::string> propertyIter = answer.PropertyIterator();
		while( propertyIter.HasNext() )
		{
			vout << prefix 
				<< *propertyIter 
				<< " = " 
				<< answer.GetAs<std::string>(*propertyIter) 
				<< vendl;
			++propertyIter;
		}
	}
}

void VNode::DumpInfo(const std::string& prefix) const
{
	if( this != 0 )
	{
		const std::string indent = "\t";

		vout
			<< (GetState() == Active ? "" : "!")
			<< prefix
			<< "Entity \"" << GetName() << "\""
			<< (GetState() == Active ? "" : " (inactive)")
			<< vendl;

		PrintPartSettings( *this, prefix + "|\t" );

		VRangeIterator<const VNode> node = ChildIterator();
		while( node.HasNext() )
		{
			node->DumpInfo( prefix + indent );

			++node;
		}
	}
}

/// tags

namespace {
	vbool IsValidTagName(const tags::VTag& tag)
	{
		return tag.GetName().length() > 0;
	}
}

void VNode::AttachTag(const tags::VTag& tag)
{
	if( IsValidTagName(tag) && ! HasTag(tag) )
	{
		m_Tags.push_back(&tag);
	}
}


void VNode::RemoveTag(const tags::VTag& tag)
{
	for(std::vector<const tags::VTag*>::iterator tagIter = m_Tags.begin();
		tagIter != m_Tags.end();
		++tagIter)
	{
		if( (**tagIter) == tag )
		{
			m_Tags.erase(tagIter);
			break;
		}
	}
}

vbool VNode::HasTag(const tags::VTag& tag) const
{
	for(std::vector<const tags::VTag*>::const_iterator tagIter = m_Tags.begin();
		tagIter != m_Tags.end();
		++tagIter)
	{
		if( **tagIter == tag )
			return true;
	}

	return false;
}

VRangeIterator<const tags::VTag> VNode::Tags() const
{
	return CreateDerefBeginIterator<const tags::VTag>(m_Tags);
}

/// serialization

void VNode::Load(const xml::IVXMLElement& in_Node)
{
	// load and apply properties

	VRangeIterator<const xml::IVXMLAttribute> attrib = in_Node.AttributeBegin();
	while( attrib.HasNext() )
	{
		std::string name = attrib->GetName();
		std::string value = attrib->GetValueAs<std::string>();

		if( name != "type" && name != "tags" )
		{
			messaging::VMessage message;
			message.AddProperty("type", "update");
			message.AddProperty("name", name);
			message.AddProperty("value", value);

			Send(message);
		}
		else if( name == "tags" )
		{
			tags::VTagRegistryPtr pTagRegistry;

			std::stringstream tags(value);
			std::string tagName;

			while( ! tags.eof() )
			{
				tags >> tagName;
				AttachTag(pTagRegistry->GetTagWithName(tagName));
			}
		}

		++attrib;
	}

	// load child nodes

	VRangeIterator<xml::IVXMLNode> childNode = const_cast<xml::IVXMLElement&>(in_Node).ChildBegin();
	while( childNode.HasNext() )
	{
		xml::IVXMLElement* element = childNode->ToElement();
		if( element != NULL &&
			(element->GetName() == "part" ||
			element->GetName() == "entity" ||
			element->GetName() == "node") )
		{
			std::string type;
			
			// workaround, to load old scenes
			if( element->GetName() == "entity" )
				type = "v3d::entity::VEntity";
			else
				type = element->GetAttributeValue<std::string>("type");

			VSharedPtr<VNode> child = 
				VEntitySerializationServicePtr()->CreateNode(type);

			child->Load( *element );

			Add( child );
		}

		++childNode;
	}
}

namespace {
	typedef std::map<std::string, std::string> SettingsMap;

	SettingsMap CollectSettings(VNode& part)
	{
		messaging::VMessage request;
		request.AddProperty("type", "getSettings");

		messaging::VMessage reply;
		part.Send(request, &reply);

		std::map<std::string, std::string> settings;

		VRangeIterator<const std::string> property = reply.PropertyIterator();
		while( property.HasNext() )
		{
			const std::string name = *property;
			const std::string value = reply.GetAs<std::string>(name);

			settings.insert( std::make_pair(name, value) );

			++property;
		}

		return settings;
	}
}

void VNode::Save(xml::IVXMLElement& node)
{
	node.SetName("node");

	node.AddAttribute( "type", utils::VStringValue(GetTypeInfo().GetName()) );

	SettingsMap settings = CollectSettings(*this);

	const SettingsMap::iterator settingsEnd = settings.end();
	for(SettingsMap::iterator setting = settings.begin();
		setting != settingsEnd;
		++setting)
	{
		const std::string name = setting->first;
		const std::string value = setting->second;

		node.AddAttribute(name.c_str(), utils::VStringValue(value));
	}

	std::string tagList;
	const vuint tagCount = m_Tags.size();
	if( tagCount > 0 )
	{
		for(vuint tagNum = 0; tagNum < tagCount; ++tagNum)
		{
			const tags::VTag* tag = m_Tags[tagNum];

			if( tag != NULL )
			{
				const std::string tagName = tag->GetName();
				if( tagNum > 0 )
					tagList += " ";

				tagList += tagName;
			}
		}

		node.AddAttribute("tags", utils::VStringValue(tagList));
	}

	VRangeIterator<VNode> child = ChildIterator();
	while( child.HasNext() )
	{
		xml::IVXMLElement* element = node.AddElement("part");
		child->Save(*element);

		++child;
	}
}

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------

