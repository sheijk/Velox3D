#include "VResourceData.h"
//-----------------------------------------------------------------------------

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

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
