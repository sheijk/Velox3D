#ifndef V3D_VSTRING_H
#define V3D_VSTRING_H
//-----------------------------------------------------------------------------
#include <v3d/Core/VCoreLib.h>
#include <v3d/Core/SmartPtr/VGuards.h>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
//TODO: SmartPointer oder sowas benutzen

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
	//TODO: einen deep copy ptr verwenden
	//VArrayPtr<vchar>::SharedPtr m_pCStr;
	vchar* m_pCStr;
	vuint m_nLength;

public:
	/** standard constructor */
	VString();

	/** copy c'tor */
	VString(const VString& in_Source);

	/** assignment operator */
	void operator=(const VString& in_Source);

	/** sets value to the one of the c string */
	VString(const vchar* in_pCStr);

	/** destructor, frees memory */
	virtual ~VString();

	/** returns the string converted to a c style string */
	const vchar* AsCString() const;

	/** sets the string to the value of a c style string */
	virtual void Set(const vchar* in_pCStr);

	void operator=(const char* in_pCStr);
	bool operator<(const VString& in_Other) const;

	operator const char*() const;

	/** returns the string's length */
	vuint Length() const;
};

VString operator+(const char* in_pcChar, const VString& in_VStr);
VString operator+(const VString& in_VStr, const char* in_pcChar);

vbool operator==(const VString& left, const VString& right);
vbool operator!=(const VString& left, const VString& right);
//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
#endif // V3D_VSTRING_H
