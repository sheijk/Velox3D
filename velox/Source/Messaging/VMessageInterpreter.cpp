#include <V3d/Messaging/VMessageInterpreter.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace messaging {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VOption::VOption(const std::string& name)
{
	m_strName = name;
}

VOption::~VOption()
{
}

std::string VOption::GetName() const
{
	return m_strName;
}

void VOption::SetName(const std::string& in_Value)
{
	m_strName = in_Value;
}


void VMessageInterpreter::AddOption(VOption* option)
{
	m_Options.insert(make_pair(option->GetName(), SharedPtr(option)));
}

vbool VMessageInterpreter::HandleMessage(void* object,
					const messaging::VMessage& in_Message,
					messaging::VMessage* io_pAnswer)
{
	if( ! in_Message.HasProperty("type") )
		return false;

	std::string request = in_Message.Get("type").Get<std::string>();

	if( request == "getSettings" )
	{
		if( io_pAnswer == 0 )
			return false;

		OptionMap::iterator option = m_Options.begin();
		for( ; option != m_Options.end(); ++option)
		{
			std::string name = option->first;
			std::string value = option->second->Read(object);

			io_pAnswer->AddProperty(name, value);
		}

		return true;
	}
	else if( request == "update" )
	{
		const std::string name = in_Message.Get("name").Get<std::string>();
		const std::string value = in_Message.Get("value").Get<std::string>();

		OptionMap::iterator option = m_Options.find(name);

		if( option != m_Options.end() )
		{
			option->second->Write(value, object);
			return true;
		}
		else
			return false;
	}
	else
	{
		return false;
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
