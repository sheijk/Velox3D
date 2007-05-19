/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Messaging/VMessageInterpreter.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace messaging {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

void v3d::messaging::VMessageInterpreter::AddOption(VSharedPtr<VOption> option) 
{
	m_Options.push_back(make_pair(option->GetName(), option));
}

VMessageInterpreter::Result VMessageInterpreter::HandleMessage(void* object,
					const messaging::VMessage& in_Message,
					messaging::VMessage* io_pAnswer)
{
	if( ! in_Message.HasProperty("type") )
		return NotProcessed;

	std::string request = in_Message.Get("type").Get<std::string>();

	if( request == "getSettings" )
	{
		if( io_pAnswer == 0 )
			return Done;

		OptionList::iterator option = m_Options.begin();
		for( ; option != m_Options.end(); ++option)
		{
			std::string name = option->first;
			std::string value = option->second->Read(object);

			io_pAnswer->AddProperty(name, value);
		}

		return GetSettings;
	}
	else if( request == "update" )
	{
		const std::string name = in_Message.GetAs<std::string>("name");
		const std::string value = in_Message.GetAs<std::string>("value");

		OptionList::iterator option = findKey<std::string, VSharedPtr<VOption> >(name, m_Options);

		if( option != m_Options.end() )
		{
			option->second->Write(value, object);
			return Done;
		}
		else
			return ApplySetting;
	}
	else
	{
		return NotProcessed;
	}
}

VMessageInterpreter::OptionList::iterator VMessageInterpreter::FindOption(const std::string& name)
{
	const OptionList::iterator optionsEnd = m_Options.end();
	for(OptionList::iterator iter = m_Options.begin();
		iter != optionsEnd;
		++iter)
	{
		if( iter->first == name )
			return iter;
	}	

	return optionsEnd;
}

vbool VMessageInterpreter::IsInitialized() const
{
	return m_bInitialized;
}

void VMessageInterpreter::SetInitialized(const vbool& in_Value)
{
	m_bInitialized = in_Value;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::messaging
//-----------------------------------------------------------------------------

