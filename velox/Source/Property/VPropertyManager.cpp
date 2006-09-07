/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Property/VPropertyManager.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/RangeIter/VSTLAccessorRangePolicy.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace property {
//-----------------------------------------------------------------------------
void VPropertyManager::SetValue(
	VStringParam in_strName, 
	const utils::VStringValue& in_strValue)
{
	m_Properties[std::string(in_strName)] = in_strValue;
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

