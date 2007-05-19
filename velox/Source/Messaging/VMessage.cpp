/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Messaging/VMessage.h>
//-----------------------------------------------------------------------------

#include <V3d/Core/RangeIter/VSTLAccessorRangePolicy.h>

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace messaging {
//-----------------------------------------------------------------------------
using namespace std;
using v3d::utils::VStringValue;

/**
 * standard c'tor
 */
VMessage::VMessage()
{
}

/**
 * d'tor
 */
VMessage::~VMessage()
{
}

void VMessage::Set(const std::string& in_strName, const utils::VStringValue& in_Value)
{
	PropertyMap::iterator prop = findKey( in_strName, m_Properties );

	if( prop != m_Properties.end() )
	{
        prop->second = in_Value;
	}
	else
	{
		V3D_THROWMSG(VInvalidPropertyException,
			"Could not set property '" << in_strName << "' to value '"
			<< in_Value.Get<string>()  << "' because the property does not "
			<< "exists");
	}
}

void VMessage::Set(const std::string& in_strName, const std::string& in_strValue)
{
	Set(in_strName, VStringValue(in_strValue));
}

utils::VStringValue VMessage::Get(const std::string& in_strName) const
{
	PropertyMap::const_iterator prop = findKey( in_strName, m_Properties );

	if( prop != m_Properties.end() )
	{
		return prop->second;
	}
	else
	{
		V3D_THROWMSG(VInvalidPropertyException,
			"Could not return value of property '" << in_strName
			<< "' because it does not exist");
	}
}

vbool VMessage::HasProperty(const std::string& in_strName) const
{
	PropertyMap::const_iterator pos = findKey( in_strName, m_Properties );

	return ( pos != m_Properties.end() );
}

void VMessage::AddProperty(const std::string& in_strName, const utils::VStringValue& in_Default)
{
	if( ! HasProperty(in_strName) )
	{
		m_Properties.push_back(PropertyMap::value_type(in_strName, in_Default));
	}
}

VRangeIterator<const std::string> VMessage::PropertyIterator() const
{
	return CreateAccesssorIterator<VPair1stAccessor, const std::string>(
		m_Properties.begin(), m_Properties.end());
}

std::string VMessage::ToString() const
{
	const std::string indent = "\t";

	std::string str = "Message\n";

	for(VRangeIterator<const std::string> prop = PropertyIterator(); prop.HasNext(); ++prop)
	{
		const std::string name = *prop;
		const std::string value = GetAs<std::string>(name);

		str += indent + name + "=\"" + value + "\"\n";
	}

	return str;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::messaging
//-----------------------------------------------------------------------------

