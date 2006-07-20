#ifndef V3D_VMESSAGEINTERPRETER_2006_01_28_H
#define V3D_VMESSAGEINTERPRETER_2006_01_28_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Messaging/VMessage.h>
#include <V3d/Messaging/VOption.h>
#include <V3d/Messaging/VMemberVarOption.h>
#include <V3d/Messaging/VMemberFunctionOption.h>

#include <string>
//-----------------------------------------------------------------------------
namespace v3d { namespace messaging {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

//TODO: mehrere VMessageInterpreter "zusammenschalten", fuer part + parent part
/**
 * Realizes the message protocol of entity parts which is used for 
 * serialisation and by the editor. Each part class will create a static
 * instance of a message interpreter which it delegates messages to from
 * OnMessage. For each persistent property in the part an VOption is added
 * to the message interpreter which will read/write the property from the
 * part. There are several different option classes which provide different
 * ways of accessing properties.
 * 
 * @author sheijk
 * @see v3d::entity::IVPart
 * @see v3d::entity::IVPart::OnMessage
 * @see v3d::messaging::VOption
 */
class VMessageInterpreter
{
public:
	void AddOption(VSharedPtr<VOption> option);

	enum Result { Done, GetSettings, ApplySetting, NotProcessed };

	Result HandleMessage(void* object,
		const messaging::VMessage& in_Message,
		messaging::VMessage* io_pAnswer);

	vbool IsInitialized() const;
	void SetInitialized(const vbool& in_Value);

	template<typename T>
	void AddMemberOption(const std::string& name, void* object, T* pMember);

	template<typename ClassType, typename OptionType>
	void AddAccessorOption(
		const std::string& name,
		typename VMemberFunctionOption<ClassType, OptionType>::Getter getter,
		typename VMemberFunctionOption<ClassType, OptionType>::Setter setter);

private:
	typedef std::map<std::string, VSharedPtr<VOption> > OptionMap;
	OptionMap m_Options;

	vbool m_bInitialized;
};

//-----------------------------------------------------------------------------

template<typename T>
void VMessageInterpreter::AddMemberOption(
	const std::string& name, void* object, T* pMember)
{
	AddOption(SharedPtr(new VMemberVarOption<T>(name, object, pMember)));
}

template<typename ClassType, typename OptionType>
void VMessageInterpreter::AddAccessorOption(
	const std::string& name, 
	typename VMemberFunctionOption<ClassType, OptionType>::Getter getter,
	typename VMemberFunctionOption<ClassType, OptionType>::Setter setter)
{
	AddOption(SharedPtr(new VMemberFunctionOption<ClassType, OptionType>(name, getter, setter)));
}

//-----------------------------------------------------------------------------
}} // namespace v3d::messaging
//-----------------------------------------------------------------------------
#endif // V3D_VMESSAGEINTERPRETER_2006_01_28_H
