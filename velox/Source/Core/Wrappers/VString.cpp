#include <v3d/Core/Wrappers/VString.h>
//-----------------------------------------------------------------------------
#include <cstring>

//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

VString::VString()
{
	vchar* pChr = new vchar[1];
	pChr[0] = '\0';

	m_pCStr.Reset(pChr);
	m_nLength = 0;
}

VString::VString(const vchar *in_pCStr)
{
	Set(in_pCStr);
}

VString::~VString()
{
	m_nLength = 0;
}

const vchar* VString::AsCString() const
{
	return m_pCStr.Get();
}

void VString::Set(const vchar* in_pCStr)
{
	m_nLength = strlen(in_pCStr);
	vchar* pChr = new char[m_nLength];

	strcpy(pChr, in_pCStr);

	m_pCStr.Reset(pChr);
}

vuint VString::Length() const
{
	return m_nLength;
}

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
