/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Entity/IVPart.h>
//-----------------------------------------------------------------------------

#include <V3d/Core/VIOStream.h>
#include <V3d/XML/IVXMLElement.h>
#include <V3d/Tags/VTagRegistry.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace entity {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

namespace {
	vbool IsValidTagName(const tags::VTag& tag)
	{
		return tag.GetName().length() > 0;
	}
}

void IVPart::AttachTag(const tags::VTag& tag)
{
	if( IsValidTagName(tag) && ! HasTag(tag) )
	{
		m_Tags.push_back(&tag);
	}
}


void IVPart::RemoveTag(const tags::VTag& tag)
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

vbool IVPart::HasTag(const tags::VTag& tag) const
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

VRangeIterator<const tags::VTag> IVPart::Tags() const
{
	return CreateDerefBeginIterator<const tags::VTag>(m_Tags);
}

namespace {
	typedef std::map<std::string, std::string> SettingsMap;
	
	SettingsMap CollectSettings(IVPart& part)
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

void IVPart::Save(xml::IVXMLElement& node)
{
	node.SetName("part");
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

void IVPart::Load(const xml::IVXMLElement& in_Node)
{
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
}

//-----------------------------------------------------------------------------
}} // namespace v3d
//-----------------------------------------------------------------------------

