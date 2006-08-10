#ifndef V3D_VPROPERTYMANAGER_2004_09_25_H
#define V3D_VPROPERTYMANAGER_2004_09_25_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Core/VException.h>
#include <V3d/Utils/VStringValue.h>
#include <V3d/Core/VNamedObject.h>
#include <V3d/Core/VObjectRegistry.h>
#include <V3d/Core/SmartPtr/VServicePtr.h>
#include <V3d/Core/RangeIter/VRangeIterator.h>

#include <map>
#include <string>
//-----------------------------------------------------------------------------
namespace v3d { namespace property {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

V3D_DECLARE_EXCEPTION(VPropertyException, VException);
V3D_DECLARE_EXCEPTION(VPropertyNotFoundException, VPropertyException);

template<typename T>
T GetProperty(VStringParam in_strName);

template<typename T>
void SetProperty(VStringParam in_strName, const T& in_Value);

vbool ExistsProperty(VStringParam in_strName);

class VPropertyManager : public VNamedObject
{
public:
	VPropertyManager(VStringParam in_strName) : VNamedObject(in_strName, 0) {}

	void SetValue(VStringParam in_strName, const utils::VStringValue& in_strValue);
	const utils::VStringValue& GetValue(VStringParam in_strName);
	
	vbool ExistsProperty(VStringParam in_strName);
	
	VRangeIterator<const std::string> GetPropertyNames() const;

private:
	typedef std::map<std::string, utils::VStringValue> PropertyTable;

	PropertyTable m_Properties;
};

typedef VServicePtr<VPropertyManager> VPropertyManagerPtr;

//-----------------------------------------------------------------------------
template<typename T>
T GetProperty(VStringParam in_strName)
{
	static VServicePtr<VPropertyManager> propertyManager;
	return propertyManager->GetValue(in_strName).Get<T>();
}

template<typename T>
void SetProperty(VStringParam in_strName, const T& in_Value)
{
	static VServicePtr<VPropertyManager> propertyManager;
	utils::VStringValue value;
	value.Set(in_Value);
	propertyManager->SetValue(in_strName, value);
}

//-----------------------------------------------------------------------------
}} // namespace v3d::property
//-----------------------------------------------------------------------------
template<>
inline v3d::property::VPropertyManager* v3d::QueryService<v3d::property::VPropertyManager>()
{
	return QueryObject<v3d::property::VPropertyManager>("property.manager");
}
//-----------------------------------------------------------------------------
#endif // V3D_VPROPERTYMANAGER_2004_09_25_H
