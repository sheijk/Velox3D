#include <v3d/Core/Wrappers/VString.h>
#include <v3dLib/Utils/VStringValue.h>

#include <iostream>
#include <sstream>

#include <v3d/Core/VException.h>
#include <v3d/Core/MemManager.h>

//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
//-----------------------------------------------------------------------------

V3D_DECLARE_EXCEPTION(VStringValueException, VException)

template <class T>
vbool ConvertString(
				   T& t,
				   const std::string &s,
				   std::ios_base &(*f)(std::ios_base&))
{
	std::istringstream iss(s);
	return !(iss>>f>>t).fail();
}

VStringValue::VStringValue(VStringParam in_Value)
{
	m_sValue = in_Value;
}

vfloat32 VStringValue::AsFloat()
{
	vfloat32 retVal;

	if(ConvertString<vfloat32>(retVal, m_sValue, std::dec))
		return retVal;
	else
		V3D_THROW(VStringValueException, "invalid string to convert!");
}

vint32 VStringValue::AsInt()
{
	vint32 retVal;

	if(ConvertString<vint32>(retVal, m_sValue, std::dec))
		return retVal;
	else
		V3D_THROW(VStringValueException, "invalid string to convert!");
}

VStringRetVal VStringValue::AsString()
{
	return m_sValue.c_str();
}
//-----------------------------------------------------------------------------
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------
