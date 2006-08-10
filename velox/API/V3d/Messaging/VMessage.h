#ifndef V3D_VMESSAGE_2005_07_28_H
#define V3D_VMESSAGE_2005_07_28_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Utils/VStringValue.h>
#include <V3d/Core/RangeIter/VRangeIterator.h>

#include <map>
#include <string>

//-----------------------------------------------------------------------------
namespace v3d { namespace messaging {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

V3D_DECLARE_EXCEPTION(VMessagingException, VException);
V3D_DECLARE_EXCEPTION(VInvalidPropertyException, VMessagingException);

/**
 * A message stores typed key/value pairs. Keys are always strings while values 
 * can be float/int/string/...
 * It's primary intent is to communicate with objects whose type is not known 
 *
 * @author sheijk
 */
class VMessage
{
public:
	VMessage();
	virtual ~VMessage();

	void AddProperty(const std::string& in_strName, const utils::VStringValue& in_Default);

	template<typename T>
	void AddProperty(const std::string& in_strName, T in_Value);

	void Set(const std::string& in_strName, const utils::VStringValue& in_Value);
	void Set(const std::string& in_strName, const std::string& in_strValue);

	utils::VStringValue Get(const std::string& inin_strName) const;

	template<typename T>
	T GetAs(const std::string& in_strName) const;

	vbool HasProperty(const std::string& in_strName) const;

	VRangeIterator<const std::string> PropertyIterator() const;

	std::string ToString() const;
private:
	typedef std::map<std::string, utils::VStringValue> PropertyMap;

    PropertyMap m_Properties;
};

//-----------------------------------------------------------------------------
template<typename T>
T VMessage::GetAs(const std::string& in_strName) const
{
	return Get(in_strName).Get<T>();
}

template<typename T>
void VMessage::AddProperty(const std::string& in_strName, T in_Value)
{
	AddProperty(in_strName, utils::VStringValue(in_Value));
}

//-----------------------------------------------------------------------------
}} // namespace v3d::messaging
//-----------------------------------------------------------------------------
#endif // V3D_VMESSAGE_2005_07_28_H
