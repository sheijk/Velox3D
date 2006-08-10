#ifndef V3D_VSTRINGVALUE_08_31_04_H
#define V3D_VSTRINGVALUE_08_31_04_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/VException.h>
#include <string>
#include <sstream>
//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
//-----------------------------------------------------------------------------

V3D_DECLARE_EXCEPTION(VStringValueException, VException);

/**
 * Represents data as string and provides casting to other types eg. float
 * int, const char
 *
 * @author: ins, doc by sheijk
 */
class VStringValue
{
public:
	// some constructors
	VStringValue() { m_sValue = ""; }
	explicit VStringValue(VStringParam in_Value) { m_sValue = in_Value; }
	VStringValue(const VStringValue& in_Source) { m_sValue = in_Source.m_sValue; }

	template<typename T>
	explicit VStringValue(const T& in_Value) { Set<T>(in_Value); }

	/**
	 * Assigns a new value to the object. The given type will be converted to
	 * a string using a stringstream. Thus you need to provide an operator
	 * with the following signature for types which shall be written to a
	 * string value: <br>
	 * <code>std::ostream& operator<<(std::ostream&, T);</code> <br>
	 * <br>
	 * See V3dLib/Graphics/Materials/StateTypes.h for some examples
	 */
	template<typename T>
		void Set(const T& val);

    /**
     * Converts the value stored in the object to the given type T. If the
	 * format is invalid, it will return the value T() (an instance created
	 * using the standard constructor). Types which shall be read this way
	 * must provide an operator with the following signature: <br>
	 * <code>std::istream& operator>>(std::istream&, T);</code><br>
	 * <br>
	 * See V3dLib/Graphics/Materials/StateTypes.h for some examples
     */
	template <typename T>
		T Get() const;

	/**
	 * Behaves the same way like <code>T Get() const</code> apart from error
	 * handling. If the format is invalid for the type T, it will throw an
	 * exception of type VStringValueException.
	 *
	 * @throws VStringValueException
	 */
	template<typename T>
		T GetSafe() const;

private:
	
	std::string m_sValue;

	template<class T>
	vbool ConvertString(
		T& t,
		const std::string &s,
		std::ios_base &(*f)(std::ios_base&)) const
	{
		std::istringstream iss(s);
		return !(iss>>f>>t).fail();
	}

	template<>
	vbool ConvertString<std::string>(
		std::string& t,
		const std::string &s,
		std::ios_base &(*f)(std::ios_base&)) const
	{
		t = s;
		return true;
	}
};

//-----------------------------------------------------------------------------
template<typename T>
void VStringValue::Set(const T& val)
{
	std::stringstream str;
	str << val;
	m_sValue = str.str();
}

template<>
inline void VStringValue::Set(const vbool& val)
{
	m_sValue = (val ? "true" : "false");
}

template <typename T>
T VStringValue::Get() const
{
	T returnValue;

	if(ConvertString<T>(returnValue, m_sValue, std::dec))
		return returnValue;
	else
		return T();
}

template<>
inline vbool VStringValue::Get() const
{
	return m_sValue == std::string("true");
}

template<typename T>
T VStringValue::GetSafe() const
{
	T returnValue;

	if(ConvertString<T>(returnValue, m_sValue, std::dec))
	{
		return returnValue;
	}
	else
	{
		std::stringstream message;
		message << "Could not convert the string '";
		message << m_sValue;
		message << "' due to an invalid format";

		V3D_THROW(VStringValueException, message.str().c_str());
	}
}

template<>
inline vbool VStringValue::GetSafe() const
{
	if( m_sValue == std::string("true") )
	{
		return true;
	}
	else if( m_sValue == std::string("false") )
	{
		return false;
	}
	else
	{
		std::stringstream message;
		message << "Could not convert the string '";
		message << m_sValue;
		message << "' due to an invalid format";

		V3D_THROW(VStringValueException, message.str().c_str());
	}
}

//-----------------------------------------------------------------------------
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTRINGVALUE_08_31_04_H
