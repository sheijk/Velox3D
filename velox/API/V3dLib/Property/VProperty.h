#ifndef V3D_VPROPERTY_2004_09_25_H
#define V3D_VPROPERTY_2004_09_25_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <V3dLib/Utils/VStringValue.h>
#include <V3dLib/Property/VPropertyManager.h>

#include <string>
//-----------------------------------------------------------------------------
namespace v3d { namespace property {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

template<typename T>
class VProperty
{
public:
	VProperty(const std::string& in_strName) : m_strName(in_strName) {}

	std::string GetName() const
	{
		return m_strName;
	}

	std::string GetRefId() const
	{
		std::string refid = "@";
		refid += m_strName;

		return refid;
	}

	T Get() const
	{
		VPropertyManagerPtr pPropertyManager;
		const utils::VStringValue& value(pPropertyManager->GetValue(m_strName.c_str()));
		return value.Get<T>();		
	}

	void Set(const T& in_Value)
	{
		VPropertyManagerPtr pPropertyManager;
		utils::VStringValue valAsString;
		valAsString.Set<T>(in_Value);
		pPropertyManager->SetValue(m_strName.c_str(), valAsString);
	}

private:
	std::string m_strName;	
};

//-----------------------------------------------------------------------------
}} // namespace v3d::property
//-----------------------------------------------------------------------------
#endif // V3D_VPROPERTY_2004_09_25_H
