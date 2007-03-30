/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Utils/VFourCC.h>
//-----------------------------------------------------------------------------
#include <V3d/Core.h>
//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace utils {
//-----------------------------------------------------------------------------

VFourCC::VFourCC()
{
    m_Val = 0;
}

VFourCC::VFourCC(VStringParam in_strVal)
{
	V3D_ASSERT(in_strVal[Length] == '\0');

    for(int i = 0; i < 4; ++i)
		m_Chars[i] = in_strVal[i];
}

VFourCC::VFourCC(const std::string& in_strVal)
{
	V3D_ASSERT(in_strVal.length() == Length);

	for(int i = 0; i < Length; ++i)
		m_Chars[i] = in_strVal[i];
}

VFourCC::VFourCC(const VFourCC& in_Val)
{
	m_Val = in_Val.m_Val;
}

VStringRetVal VFourCC::AsString() const
{
	vchar chars[Length+1];
	for(int i = 0; i < Length; ++i)
		chars[i] = m_Chars[i];
	chars[Length] = '\0';

	VString str(&(chars[0]));

	return str;
}

std::string VFourCC::AsStdString() const
{
	std::string str;
	str.resize(Length, '\0');
	
	for(int i = 0; i < Length; ++i)
		str[i] = m_Chars[i];

	return str;
}

vchar VFourCC::CharAt(vuint i) const
{
	V3D_ASSERT(i < Length);
	return m_Chars[i];
}

vbool VFourCC::operator==(const VFourCC& other) const
{
	return m_Val == other.m_Val;
}

vbool VFourCC::operator!=(const VFourCC& other) const
{
	return m_Val != other.m_Val;
}

vbool VFourCC::operator<(const VFourCC& other) const
{
	for(int i = 0; i < Length; ++i)
	{
		if( m_Chars[i] < other.m_Chars[i] )
			return true;
	}

	return false;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::utils
//-----------------------------------------------------------------------------

