#include "VResourceData.h"
//-----------------------------------------------------------------------------

#include <cstring>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d;

VResourceData::VResourceData()
{
	m_nReferenceCount = 0;
}

VResourceData::~VResourceData()
{
}

vuint VResourceData::GetReferenceCount() const
{
	return m_nReferenceCount;
}

VResourceData::TypeId::TypeId(const vchar* in_strName)
{
	m_strName = in_strName;
}

vbool VResourceData::TypeId::operator <(const VResourceData::TypeId& in_Other) const
{
	return std::strncmp(m_strName, in_Other.m_strName, 1000) < 0;
}

vbool VResourceData::TypeId::operator==(const VResourceData::TypeId& in_Other) const
{
	return std::strncmp(m_strName, in_Other.m_strName, 1000) == 0;
}

vbool VResourceData::TypeId::operator!=(const VResourceData::TypeId& in_Other) const
{
	return std::strncmp(m_strName, in_Other.m_strName, 1000) != 0;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
