#include <V3d/Messaging/VProtocol.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace messaging {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VProtocol::VProtocol()
{
}

/**
 * d'tor
 */
VProtocol::~VProtocol()
{
}

vbool VProtocol::IsValid(const VMessage& in_Message) const
{
	// check if all default arguments are present
	DefaultsMap::const_iterator pDefault = m_Defaults.begin();

	try
	{
		for( ; pDefault != m_Defaults.end(); ++pDefault)
		{
			in_Message.Get(pDefault->first);
		}

		return true;
	}
	catch(VInvalidPropertyException&)
	{
		return false;
	}
}

VSharedPtr<VMessage> VProtocol::CreateMessage() const
{
	VSharedPtr<VMessage> pMessage(new VMessage());

	// add all default values to message

	DefaultsMap::const_iterator pDefault = m_Defaults.begin();

	for( ; pDefault != m_Defaults.end(); ++pDefault)
	{
		pMessage->AddProperty(pDefault->first);
		pMessage->Set(pDefault->first, pDefault->second);
	}

	return pMessage;
}

VProtocol& VProtocol::SetDefault(const std::string& in_strName, utils::VStringValue in_Default)
{
	m_Defaults[in_strName] = in_Default;
	return *this;
}

VProtocol& VProtocol::SetDefault(const std::string& in_strName, const std::string& in_strDefault)
{
	m_Defaults[in_strName] = utils::VStringValue(in_strDefault);
	return *this;
}

VProtocol& VProtocol::SetDefault(const std::string& in_strName, VStringParam in_strDefault)
{
	m_Defaults[in_strName] = utils::VStringValue(in_strDefault);
	return *this;
}

VProtocol& VProtocol::SetDefault(const std::string& in_strName, vint in_nDefault)
{
	m_Defaults[in_strName] = utils::VStringValue(in_nDefault);
	return *this;
}

VProtocol& VProtocol::SetDefault(const std::string& in_strName, vfloat32 in_fDefault)
{
	m_Defaults[in_strName] = utils::VStringValue(in_fDefault);
	return *this;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::messaging
//-----------------------------------------------------------------------------
