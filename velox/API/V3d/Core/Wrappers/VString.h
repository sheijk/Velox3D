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
 *
 * @author sheijk
 * @created 14-May-2003 12:40:39
 */
class VString
{
private:
	vchar* m_pCStr;
	vuint m_nLength;

	virtual void FreeMem();
public:
	/** standard constructor */
	VString();

	/** copy c'tor */
	VString(const VString& in_Source);

	/** assignment operator */
	void operator=(const VString& in_Source);

	/** sets value to the one of the c string */
	/*TODO: wieder reinnehmen explicit*/ VString(const vchar* in_pCStr);

	/** destructor, frees memory */
	virtual ~VString();

	/** returns the string converted to a c style string */
	const vchar* AsCString() const;

	/** sets the string to the value of a c style string */
	virtual void Set(const vchar* in_pCStr);

	void operator=(const vchar* in_pCStr);
	vbool operator<(const VString& in_Other) const;

	operator const char*() const;

	/** returns the string's length */
	vuint Length() const;
};

VString operator+(const vchar* in_pcChar, const VString& in_VStr);
VString operator+(const VString& in_VStr, const vchar* in_pcChar);

vbool operator==(const VString& left, const VString& right);
vbool operator!=(const VString& left, const VString& right);
//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTRING_H
