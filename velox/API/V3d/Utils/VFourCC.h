#ifndef V3D_VFOURCC_2004_10_09_H
#define V3D_VFOURCC_2004_10_09_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>

#include <string>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------
using namespace v3d; // prevent auto indenting

/**
 * A four character code class. Can be used for efficient representation
 * of four byte long strings to be used as ids etc
 *
 * @author
 */
class VFourCC
{
	enum { Length = 4 };
public:
	VFourCC();
	VFourCC(VStringParam in_strVal);
	VFourCC(const std::string& in_strVal);
	VFourCC(const VFourCC& in_Val);

	VStringRetVal AsString() const;
	std::string AsStdString() const;

	vchar CharAt(vuint i) const;

	vbool operator==(const VFourCC& other) const;
	vbool operator!=(const VFourCC& other) const;

	vbool operator<(const VFourCC& other) const;

private:
	union
	{
		vuint32 m_Val;
		vchar m_Chars[Length];
	};
};

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------
#endif // V3D_VFOURCC_2004_10_09_H
