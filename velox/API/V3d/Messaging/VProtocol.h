#ifndef V3D_VPROTOCOL_2005_07_29_H
#define V3D_VPROTOCOL_2005_07_29_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Messaging/VMessage.h>
#include <V3d/Utils/VStringValue.h>

#include <map>
#include <string>

//-----------------------------------------------------------------------------
namespace v3d { namespace messaging {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * A message protocol defines the valid properties for a message. It can be 
 * used to easily check if a message follows an expected protocol and to 
 * condense protocol information in a central place (nice in case of changes 
 * because all participants are guaranteed to use the same protocol) 
 *
 * @author sheijk
 */
class VProtocol
{
public:
	VProtocol();
	virtual ~VProtocol();

	vbool IsValid(const VMessage& in_Message) const;
	VSharedPtr<VMessage> CreateMessage() const;

	VProtocol& SetDefault(const std::string& in_strName, utils::VStringValue in_Default);
	VProtocol& SetDefault(const std::string& in_strName, const std::string& in_strDefault);
	VProtocol& SetDefault(const std::string& in_strName, VStringParam in_strDefault);
	VProtocol& SetDefault(const std::string& in_strName, vint in_nDefault);
	VProtocol& SetDefault(const std::string& in_strName, vfloat32 in_fDefault);

private:
	typedef std::map<std::string, utils::VStringValue> DefaultsMap;

    DefaultsMap m_Defaults;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::messaging
//-----------------------------------------------------------------------------
#endif // V3D_VPROTOCOL_2005_07_29_H
