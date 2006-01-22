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

VResource* VResourceData::GetEnclosingResource()
{
	return m_pResource;
}

const VResource* VResourceData::GetEnclosingResource() const
{
	return m_pResource;
}

vuint VResourceData::GetReferenceCount() const
{
	return m_nReferenceCount;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
