#ifndef V3D_VSTRING_H
#define V3D_VSTRING_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/SmartPtr/VGuards.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

/**
 * Simply wraps a C-Style string to guarantee memory release
 * @author sheijk
 * @version 1.0
 * @generator Enterprise Architect
 * @created 14-May-2003 12:40:39
 */
class VString
{
private:
	mutable VPointer<vchar>::SharedPtr m_pCStr;
	vuint m_nLength;

public:
	/** standard constructor */
	VString();

	/** sets value to the one of the c string */
	VString(const vchar* in_pCStr);

	/** destructor, frees memory */
	virtual ~VString();

	/** returns the string converted to a c style string */
	const vchar* AsCString() const;

	/** sets the string to the value of a c style string */
	void Set(const vchar* in_pCStr);

	/** returns the string's length */
	vuint Length() const;
};

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTRING_H
