/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#include <V3d/Entity/VNode.h>
//-----------------------------------------------------------------------------

#include <V3d/Core/VIOStream.h>
#include <V3d/Messaging/VMessageInterpreter.h>
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

/**
 * standard c'tor
 */
VNode::VNode()
{
}

/**
 * d'tor
 */
VNode::~VNode()
{
}

void VNode::SetupProperties(messaging::VMessageInterpreter& interpreter)
{
	// Nothing to do here. Override in classe which have properties, add
	// the classes' properties and call super.SetupProperties
}

messaging::VMessageInterpreter* VNode::GetMessageInterpreterForClass()
{
	// this method will need to be put into each class providing properties
	static messaging::VMessageInterpreter interpreter;

	return &interpreter;
}

VNode::ActivationResult VNode::Activate()
{
	OnActivate();

	return ActivatedNone;
}

void VNode::Deactivate()
{
	OnDeactivate();
}

void VNode::OnActivate()
{
}

void VNode::OnDeactivate()
{
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

//-----------------------------------------------------------------------------
}} // namespace v3d::entity
//-----------------------------------------------------------------------------

