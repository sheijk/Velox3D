/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Core/Wrappers/VString.h>
//-----------------------------------------------------------------------------
#include <cstring>
#include <algorithm>

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------

VString::VString()
{
	vchar* pChr = new vchar[1];
	pChr[0] = '\0';

	m_pCStr = pChr;
//	m_pCStr.Reset(pChr);
	m_nLength = 0;
}

VString::VString(const vchar *in_pCStr)
{
	m_pCStr = 0;
	Set(in_pCStr);
}

VString::~VString()
{
	FreeMem();
}

void VString::FreeMem()
{
	//FIXME: das muss wieder rein, aber so dass es keinen absturz gibt :) -- sheijk
	delete[] m_pCStr;
	m_pCStr = 0;
	m_nLength = 0;
}

/** copy c'tor */
VString::VString(const VString& in_Source)
{
	m_pCStr = 0;
	this->operator=(in_Source);
}

/** assignment operator */
void VString::operator=(const VString& in_Source)
{
	this->Set(in_Source.AsCString());
}

const vchar* VString::AsCString() const
{
	return m_pCStr;
}

void VString::Set(const vchar* in_pCStr)
{
	FreeMem();

	m_nLength = (vuint) strlen(in_pCStr);
	vchar* pChr = new char[m_nLength+1];

	strcpy(pChr, in_pCStr);

	pChr[m_nLength] = '\0';

	m_pCStr = pChr;
//	m_pCStr.Reset(pChr);
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
	vuint nCStrLen =  (vuint)strlen(in_pcChar);
	vuint nVStrLen = in_VStr.Length();

	char* pChars = new char[nVStrLen + nCStrLen + 1];

	strcpy(pChars, in_VStr.AsCString());
	strcpy(pChars + nVStrLen, in_pcChar);

	pChars[nVStrLen+nCStrLen] = '\0';

	VString vstr(pChars);

	delete[] pChars;

	return vstr;
}

vbool operator==(const VString& left, const VString& right)
{
	if( left.Length() != right.Length() )
	{
		return false;
	}
	else
	{
		return std::equal(
				left.AsCString(),
				left.AsCString() + left.Length(),
				right.AsCString()
				);
	}
}

vbool operator!=(const VString& left, const VString& right)
{
	return ! (left == right);
}

vbool operator==(const VString& left, VStringParam right)
{
	return left == VString(right);
}

vbool operator!=(const VString& left, VStringParam right)
{
	return left != VString(right);
}

vbool operator==(VStringParam left, const VString& right)
{
	return VString(left) == right;
}

vbool operator!=(VStringParam left, const VString& right)
{
	return VString(left) != right;
}

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------

