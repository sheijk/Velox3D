#include <V3d/Resource/VResourceId.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VResourceId::VResourceId(VResource* in_pResource)
{
	m_pResource = in_pResource;
}

VResource* VResourceId::operator->()
{
	return m_pResource;
}

VResource& VResourceId::operator*()
{
	return *m_pResource;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::resource
//-----------------------------------------------------------------------------
