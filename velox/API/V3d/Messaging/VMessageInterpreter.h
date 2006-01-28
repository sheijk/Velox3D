#ifndef V3D_VMESSAGEINTERPRETER_2006_01_28_H
#define V3D_VMESSAGEINTERPRETER_2006_01_28_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Messaging/VMessage.h>
#include <string>
//-----------------------------------------------------------------------------
namespace v3d { namespace messaging {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

class VOption
{
public:
	VOption(const std::string& name);
	virtual ~VOption();

	virtual void Write(const std::string& value, void* object) = 0;
	virtual std::string Read(void* object) = 0;

	std::string GetName() const;
	void SetName(const std::string& in_Value);
private:
	std::string m_strName;
};

template<typename T>
class VMemberVarOption : public VOption
{
public:
	VMemberVarOption(const std::string& name, void* object, T* member) :
	VOption(name)
	{
		m_nOffsetBytes = BytesDistance(object, member);
	}

	virtual void Write(const std::string& value, void* object)
	{
		T* address = MemberAddress(object);

		utils::VStringValue val(value);
		T newValue = val.Get<T>();
		*address = newValue;
	}

	virtual std::string Read(void* object)
	{
		T* address = MemberAddress(object);

		utils::VStringValue val;
		val.Set(*address);
		return val.Get<std::string>();
	}

private:
	T* MemberAddress(void* object)
	{
		vbyte* objectAddress = reinterpret_cast<vbyte*>(object);
		vbyte* memberAddress = objectAddress + m_nOffsetBytes;
		return reinterpret_cast<T*>(memberAddress);
	}

	vuint BytesDistance(void* a, void* b)
	{
		return vuint((vbyte*)b - (vbyte*)a);
	}

	vuint m_nOffsetBytes;
};

//TODO: mehrere VMessageInterpreter "zusammenschalten", fuer part + parent part
class VMessageInterpreter
{
public:
	void AddOption(VOption* option);

	vbool HandleMessage(void* object,
		const messaging::VMessage& in_Message,
		messaging::VMessage* io_pAnswer);

	vbool IsInitialized() const;
	void SetInitialized(const vbool& in_Value);

	template<typename T>
	void AddMemberOption(const std::string& name, void* object, T* pMember);

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
	AddOption(new VMemberVarOption<T>(name, object, pMember));
}

//-----------------------------------------------------------------------------
}} // namespace v3d::messaging
//-----------------------------------------------------------------------------
#endif // V3D_VMESSAGEINTERPRETER_2006_01_28_H
