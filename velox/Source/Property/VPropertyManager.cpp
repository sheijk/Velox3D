/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */
#include <V3d/Property/VPropertyManager.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/RangeIter/VSTLAccessorRangePolicy.h>

#include <V3d/Core/VLogging.h>
#include <V3d/Core/VIOStream.h>
#include <V3d/XML.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace property {
//-----------------------------------------------------------------------------

namespace
{
	xml::IVXMLElement* GetChildWithName(const char* name, xml::IVXMLElement& parent)
	{
		VRangeIterator<xml::IVXMLNode> child = parent.ChildBegin();
		for( ; child.HasNext(); ++child )
		{
			xml::IVXMLElement* asElement = child->ToElement();

			if( asElement != NULL && asElement->GetName() == name )
				return asElement;
		}

		return NULL;
	}
}

v3d::property::VPropertyManager::VPropertyManager( VStringParam in_strName ) : VNamedObject(in_strName, 0)
{
	LoadPropertiesFromInitFile("init.xml");
}

void VPropertyManager::SetValue(
	VStringParam in_strName, 
	const utils::VStringValue& in_strValue)
{
	m_Properties[std::string(in_strName)] = in_strValue;
}

void v3d::property::VPropertyManager::LoadPropertiesFromInitFile( const char* fileName ) 
{
	try
	{
		VSharedPtr<xml::IVXMLElement> root =
			xml::VXMLServicePtr()->GetRootElement( fileName );

		xml::IVXMLElement* propertyNode = GetChildWithName("Properties", *root);

		if( propertyNode != NULL )
			LoadProperties( *propertyNode );
	}
	catch( VException& e)
	{
		V3D_LOG( "Warning, could not load properties from init.xml: " << e.ToString() );
	}
}

void VPropertyManager::LoadProperties(xml::IVXMLElement& element)
{
	VRangeIterator<xml::IVXMLNode> childNode = element.ChildBegin();
	for( ; childNode.HasNext(); ++childNode )
	{
		xml::IVXMLElement* asElement = childNode->ToElement();

		if( asElement != NULL )
		{
			std::string name = asElement->GetAttributeValue<std::string>("name");
			std::string value = asElement->GetAttributeValue<std::string>("value");

			SetProperty( name.c_str(), value );
		}
	}
}

const utils::VStringValue& VPropertyManager::GetValue(VStringParam in_strName)
{
	PropertyTable::iterator iter = m_Properties.find(std::string(in_strName));

	if( iter != m_Properties.end() )
	{
		return iter->second;
	}
	else
	{
		std::ostringstream message;
		message << "Could not find property '" << in_strName << "'";

		V3D_THROW(VPropertyNotFoundException, message.str().c_str());
	}
}

vbool VPropertyManager::ExistsProperty(VStringParam in_strName)
{
	return m_Properties.find(in_strName) != m_Properties.end();
}

VRangeIterator<const std::string> VPropertyManager::GetPropertyNames() const
{
	return CreateAccesssorIterator<VPair1stAccessor, const std::string>(
		m_Properties.begin(), m_Properties.end());
}

vbool ExistsProperty(VStringParam in_strName)
{
	static VServicePtr<VPropertyManager> propertyManager;
	return propertyManager->ExistsProperty(in_strName);	
}

//-----------------------------------------------------------------------------
}} // namespace v3d::property
//-----------------------------------------------------------------------------

