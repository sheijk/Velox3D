#include <V3d/Resource/VResourceId.h>
//-----------------------------------------------------------------------------

#include <V3d/Resource/IVResourceManager.h>
//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace resource {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

VResourceId::VResourceId(VStringParam in_pResName) :
	m_pResource(VResourceManagerPtr()->GetResourceByName(in_pResName).m_pResource)
{
	;
}

VResourceId::VResourceId(VResource* in_pResource) :
	m_pResource(in_pResource)
{
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
