#ifndef V3D_VSTRINGVALUE_08_31_04_H
#define V3D_VSTRINGVALUE_08_31_04_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <string>
//-----------------------------------------------------------------------------
namespace v3d {
namespace utils {
//-----------------------------------------------------------------------------

	/**
	 * represents data as string on provides casting to other types eg. float
	 * int, const char
	 * @author: ins
	 */

class VStringValue
{
public:

	VStringValue(VStringParam in_Value);
	
	vfloat32 AsFloat();
	vint32   AsInt();
	VStringRetVal AsString();

private:
	
	std::string m_sValue;
};

//-----------------------------------------------------------------------------
} // namespace utils
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTRINGVALUE_08_31_04_H
