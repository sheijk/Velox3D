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
	m_nLength = (vuint) strlen(in_pCStr);
	vchar* pChr = new char[m_nLength];

	strcpy(pChr, in_pCStr);

	m_pCStr.Reset(pChr);
}

void VString::operator=(const char* in_pCStr)
{
	Set(in_pCStr);
}

bool VString::operator<(const VString& in_Other) const
{
	return (strcmp(this->AsCString(), in_Other.AsCString()) < 0);
}

VString::operator const char*() const
{
	return this->AsCString();
}

vuint VString::Length() const
{
	return m_nLength;
}

VString operator+(const char* in_pcChar, const VString& in_VStr)
{
	vuint nCStrLen = (vuint) strlen(in_pcChar);
	vuint nVStrLen = in_VStr.Length();

	char* pChars = new char[nVStrLen + nCStrLen + 1];

	strcpy(pChars, in_pcChar);
	strcpy(pChars + nCStrLen, in_VStr.AsCString());

	pChars[nVStrLen+nCStrLen] = '\0';

	VString vstr(pChars);
	
	delete[] pChars;

	return vstr;
}

VString operator+(const VString& in_VStr, const char* in_pcChar)
{
	vuint nCStrLen = strlen(in_pcChar);
	vuint nVStrLen = in_VStr.Length();

	char* pChars = new char[nVStrLen + nCStrLen + 1];

	strcpy(pChars, in_VStr.AsCString());
	strcpy(pChars + nVStrLen, in_pcChar);

	pChars[nVStrLen+nCStrLen] = '\0';

	VString vstr(pChars);

	delete[] pChars;

	return vstr;
}

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------
