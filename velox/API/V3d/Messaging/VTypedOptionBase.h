#ifndef V3D_VTYPEDOPTIONBASE_2006_07_18_H
#define V3D_VTYPEDOPTIONBASE_2006_07_18_H
//-----------------------------------------------------------------------------
#include <V3d/Core/VCoreLib.h>
#include <V3d/Messaging/VOption.h>
#include <V3d/Utils/VStringValue.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace messaging {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indenting

/**
 * Base class for an option of VMessageInterpreter with a type T. Derive
 * from this class and overwrite Get and Set if you want to create a
 * new way to access properties/options of an part using 
 * VMessageInterpreter
 *
 * @author sheijk
 */
template<typename T>
class VTypedOptionBase : public VOption
{
public:
	VTypedOptionBase(const std::string& name) : VOption(name)
	{}

	virtual void Write(const std::string& value, void* object)
	{
		utils::VStringValue val(value);
		T newValue = val.Get<T>();

		Set(newValue, object);
	}

	virtual std::string Read(void* object)
	{
		utils::VStringValue val;
		val.Set(Get(object));
		return val.Get<std::string>();
	}

private:
	virtual T Get(void* object) = 0;
	virtual void Set(const T& in_NewValue, void* object) = 0;
};

//-----------------------------------------------------------------------------
}} // namespace v3d::messaging
//-----------------------------------------------------------------------------
#endif // V3D_VTYPEDOPTIONBASE_2006_07_18_H
