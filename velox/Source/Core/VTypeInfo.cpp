/*
 * Copyright 2002-2006 Velox Development Team. This file is licenced under the
 * revised BSD licence. See licence_bsd.txt in the root of the Velox 
 * distribution or http://www.sechsta-sinn.de/velox/licence_bsd.txt for the
 * complete licence text
 */

#include <V3d/Core/VTypeInfo.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <V3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VTypeInfo::VTypeInfo()
{
}

VTypeInfo::~VTypeInfo()
{
}

std::string VTypeInfo::GetName() const
{
	return m_strName;
}

void VTypeInfo::SetName(const std::string& in_strName)
{
	m_strName = in_strName;
}

vbool VTypeInfo::CanBeCastedTo(const VTypeInfo& in_DestType) const
{
	// can be casted to itself and any one if it's supertypes
	return (m_strName == in_DestType.m_strName) ||
		(m_SuperTypes.find(in_DestType.GetName()) != m_SuperTypes.end());
}

vbool VTypeInfo::IsInitialized() const
{
	return m_strName != "";
}

void VTypeInfo::AddSuperType(const VTypeInfo& in_SuperTypeInfo)
{
	m_SuperTypes.insert(in_SuperTypeInfo.GetName());
	m_SuperTypes.insert(
		in_SuperTypeInfo.m_SuperTypes.begin(), 
		in_SuperTypeInfo.m_SuperTypes.end());
}

vbool VTypeInfo::operator<(const VTypeInfo& other) const
{
	return m_strName < other.m_strName;
}

vbool VTypeInfo::operator==(const VTypeInfo& other) const
{
	return m_strName == other.m_strName;
}

vbool VTypeInfo::operator!=(const VTypeInfo& other) const
{
	return m_strName != other.m_strName;
}

//-----------------------------------------------------------------------------
} // namespace v3d
//-----------------------------------------------------------------------------

