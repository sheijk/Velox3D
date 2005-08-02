#ifndef V3D_VMESSAGE_2005_07_28_H
#define V3D_VMESSAGE_2005_07_28_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3dLib/Utils/VStringValue.h>

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

	void Set(const std::string& in_strName, const utils::VStringValue& in_Value);
	utils::VStringValue Get(const std::string& inin_strName) const;

	vbool HasProperty(const std::string& in_strName) const;
	void AddProperty(const std::string& in_strName);

private:
	typedef std::map<std::string, utils::VStringValue> PropertyMap;

    PropertyMap m_Properties;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::messaging
//-----------------------------------------------------------------------------
#endif // V3D_VMESSAGE_2005_07_28_H
