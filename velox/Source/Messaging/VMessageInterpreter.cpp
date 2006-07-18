#include <V3d/Messaging/VMessageInterpreter.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace messaging {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

void VMessageInterpreter::AddOption(VOption* option)
{
	m_Options.insert(make_pair(option->GetName(), SharedPtr(option)));
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

		OptionMap::iterator option = m_Options.begin();
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
		const std::string name = in_Message.Get("name").Get<std::string>();
		const std::string value = in_Message.Get("value").Get<std::string>();

		OptionMap::iterator option = m_Options.find(name);

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
