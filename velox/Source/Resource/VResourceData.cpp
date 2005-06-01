#include <V3d/Resource/VResourceData.h>
//-----------------------------------------------------------------------------

#include <cstring>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d;

VResourceData::VResourceData(VResource* in_pResource)
{
	m_nReferenceCount = 0;
	m_pResource = in_pResource;
}

VResourceData::~VResourceData()
{
}

VResource* VResourceData::GetEnclosingResource() const
{
	return m_pResource;
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

const vchar* VResourceData::TypeId::ToString() const
{
	return m_strName;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------