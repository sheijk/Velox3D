#include <V3dLib/Property/VPropertyManager.h>
//-----------------------------------------------------------------------------

#include <V3d/Core/RangeIter/VSTLAccessorRangePolicy.h>

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
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

VRangeIterator<const std::string> VPropertyManager::GetPropertyNames() const
{
	return CreateAccesssorIterator<VPair1stAccessor, const std::string>(
		m_Properties.begin(), m_Properties.end());
}

//-----------------------------------------------------------------------------
}} // namespace v3d::property
//-----------------------------------------------------------------------------
