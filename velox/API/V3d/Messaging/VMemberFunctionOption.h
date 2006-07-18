#ifndef V3D_VMEMBERFUNCTIONOPTION_2006_07_18_H
#define V3D_VMEMBERFUNCTIONOPTION_2006_07_18_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>

#include <V3d/Messaging/VTypedOptionBase.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace messaging {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * A property/option which will be get/set by calling appropriate
 * member functions from the part
 *
 * @author sheijk
 */
template<typename ClassType, typename OptionType>
class VMemberFunctionOption : public VTypedOptionBase<OptionType>
{
public:
	typedef OptionType (ClassType::*Getter)() const;
	typedef void (ClassType::*Setter)(const OptionType&);

	VMemberFunctionOption(const std::string& name, Getter in_Getter, Setter in_Setter)
		: VTypedOptionBase<OptionType>(name), m_Getter(in_Getter), m_Setter(in_Setter)
	{
	}

private:
	Getter m_Getter;
	Setter m_Setter;

	virtual OptionType Get(void* object)
	{
		ClassType* pPart = reinterpret_cast<ClassType*>(object);
		return (pPart->*m_Getter)();
	}

	virtual void Set(const OptionType& in_NewValue, void* object)
	{
		ClassType* pPart = reinterpret_cast<ClassType*>(object);
		(pPart->*m_Setter)(in_NewValue);
	}
};

//-----------------------------------------------------------------------------
}} // namespace v3d::messaging
//-----------------------------------------------------------------------------
#endif // V3D_VMEMBERFUNCTIONOPTION_2006_07_18_H
