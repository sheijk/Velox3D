#include <V3d/Graphics/VMeshHandle.h>
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
#include <v3d/Core/MemManager.h>
//-----------------------------------------------------------------------------
namespace v3d { namespace graphics {
//-----------------------------------------------------------------------------
using namespace v3d; // anti auto indent

/**
 * standard c'tor
 */
VMeshHandle::VMeshHandle(IVDevice::MeshHandle in_hMesh)
{
	m_hMesh = in_hMesh;
}

/**
 * d'tor
 */
VMeshHandle::~VMeshHandle()
{
}

IVDevice::MeshHandle VMeshHandle::GetMeshHandle() const
{
	return m_hMesh;
}

//-----------------------------------------------------------------------------
}} // namespace v3d::graphics
//-----------------------------------------------------------------------------
