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

	/**
	 * represents data as string on provides casting to other types eg. float
	 * int, const char
	 * @author: ins
	 */

V3D_DECLARE_EXCEPTION(VStringValueException, VException);

class VStringValue
{
public:
	VStringValue()
	{
		m_sValue = "";
	}

	VStringValue(VStringParam in_Value)
	{
		m_sValue = in_Value;
	}
	
	template<typename T>
		void Set(const T val)
	{
		std::stringstream str;
		str << val;
		m_sValue = str.str();
	}

	template <typename T>
		T Get() const
	{
		T returnValue;

		if(ConvertString<T>(returnValue, m_sValue, std::dec))
			return returnValue;
		else
			return T();
	}

	template <typename T>
		T Get() 
	{
		T returnValue;

		if(ConvertString<T>(returnValue, m_sValue, std::dec))
			return returnValue;
		else
			return T();
	}

	template<typename T>
		T GetSafe() const
	{
		T returnValue;

		if(ConvertString<T>(returnValue, m_sValue, std::dec))
			return returnValue;
		else
			V3D_THROW(VStringValueException, "invalid string to convert!");
	}

	template<typename T>
		T GetSafe()
	{
		T returnValue;

		if(ConvertString<T>(returnValue, m_sValue, std::dec))
			return returnValue;
		else
			V3D_THROW(VStringValueException, "invalid string to convert!");
	}
private:
	
	std::string m_sValue;

	template <class T>
		vbool ConvertString(
		T& t,
		const std::string &s,
		std::ios_base &(*f)(std::ios_base&))
	{
		std::istringstream iss(s);
		return !(iss>>f>>t).fail();
	}
};

//-----------------------------------------------------------------------------
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTRINGVALUE_08_31_04_H
